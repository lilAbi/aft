#ifndef MTPDEVICE_H
#define MTPDEVICE_H

#include "MtpEventPacket.h"
#include "MtpDataPacket.h"
#include "MtpRequestPacket.h"
#include "MtpResponsePacket.h"
#include "MtpTypes.h"

#include <mutex>

namespace mtp {
    class MtpDevice {
        using ReadObjectCallback = bool(void* data, std::uint32_t offset, std::uint32_t length, void* clientData);
    public:
        MtpDevice(struct usb_device* device,  //usb handler to mtp device
                  int interface,              //assign interface to it
                  const struct usb_endpoint_descriptor *epIn,
                  const struct usb_endpoint_descriptor *epOut,
                  const struct usb_endpoint_descriptor *epIntr);

        ~MtpDevice();

        static MtpDevice*       open(const char* deviceName, int fd);

        void                    init();
        void                    terminate();
        void                    print();
        bool                    openSession();
        bool                    closeSession();

        const char*             getDeviceName();
        MtpDeviceInfo*          getDeviceInfo();
        MtpProperty*            getDevicePropDesc(MtpDeviceProperty code);
        bool                    setDevicePropValueStr(MtpProperty* property);

        void*                   getThumbnail(MtpObjectHandle handle, int& outLength);

        MtpStorageInfo*         getStorageInfo(MtpStorageID storageID);
        MtpStorageIDList*       getStorageIDs();
        MtpStorageID            getStorageID(MtpObjectHandle handle);

        MtpObjectInfo*          getObjectInfo(MtpObjectHandle handle);
        MtpObjectHandle         sendObjectInfo(MtpObjectInfo* info);
        bool                    sendObject(MtpObjectHandle handle, std::uint32_t size, int srcFD);
        bool                    deleteObject(MtpObjectHandle handle);
        MtpObjectHandle         getParent(MtpObjectHandle handle);
        MtpObjectPropertyList*  getObjectPropsSupported(MtpObjectFormat format);
        MtpObjectHandleList*    getObjectHandles(MtpStorageID storageID, MtpObjectFormat format, MtpObjectHandle parent);
        MtpProperty*            getObjectPropDesc(MtpObjectProperty code, MtpObjectFormat format);
        bool                    getObjectPropValue(MtpObjectHandle handle, MtpProperty* property);

        bool                    readObject(MtpObjectHandle handle, ReadObjectCallback callback, std::uint32_t objectSize, void* clientData);
        bool                    readObject(MtpObjectHandle handle, const char* destPath, int group, int perm);
        bool                    readObject(MtpObjectHandle handle, int fd);
        bool                    readPartialObject(MtpObjectHandle handle,
                                                  std::uint32_t offset,
                                                  std::uint32_t size,
                                                  std::uint32_t *writtenSize,
                                                  ReadObjectCallback callback,
                                                  void* clientData);
        bool                    readPartialObject64(MtpObjectHandle handle,
                                                    std::uint32_t offset,
                                                    std::uint32_t size,
                                                    std::uint32_t *writtenSize,
                                                    ReadObjectCallback callback,
                                                    void* clientData);
        /*
        * Starts a request to read MTP event from MTP device.
        * It returns a request var.handle that can be used for blocking read or cancel.
        * If other thread has already been processing an event returns -1.
        */
        int             submitEventRequest();

        /*
        * Waits for MTP event from the device and returns MTP event code.
        * It blocks the current thread until it receives an event from the device.
        * var.handle should be a request var.handle returned by submitEventRequest().
        * The function writes event parameters to var.parameters.
        * Returns 0 for cancellations. Returns -1 for errors.
        */
        int             reapEventRequest(int handle, uint32_t (*parameters)[3]);

        /*
        * Cancels an event request. handle should be request var.handle returned by submitEventRequest().
        * If there is a thread blocked by reapEventRequest() with the same var.handle, the thread will resume.
        */
        void            discardEventRequest(int handle);

    private:
        //If var.objectSize is not NULL, it checks object size before reading data bytes.
        bool            readObjectInternal(MtpObjectHandle handle,
                                           ReadObjectCallback callback,
                                           const std::uint32_t* objectSize,
                                           void* clientData);
        // If var.objectSize is not NULL, it checks object size before reading data bytes.
        bool            readData(ReadObjectCallback callback,
                                 const std::uint32_t* objectSize,
                                 std::uint32_t* writtenData,
                                 void* clientData);
        bool            sendRequest(MtpOperationCode operation);
        bool            sendData();
        bool            readData();
        bool            writeDataHeader(MtpOperationCode operation, int dataLength);
        MtpResponseCode readResponse();

    private:
        usb_device* device;
        int mInterface;
        usb_request* requestIn1;
        usb_request* requestIn2;
        usb_request* requestOut;
        usb_request* requestIntr;

        MtpDeviceInfo* deviceInfo;
        MtpPropertyList deviceProperties;

        MtpSessionID currSessionID;
        MtpTransactionID currTransactionID;
        MtpRequestPacket request;
        MtpDataPacket data;
        MtpResponsePacket response;
        MtpEventPacket eventPacket;

        bool receivedResponse; //true if we received a response packet instead of a data packet
        bool processingEvent;
        int currentEventHandle;

        //to check if a sendObject request follows the last sendObjectInfo request
        MtpTransactionID lastSendObjectInfoTransactionID;
        MtpObjectHandle lastSendObjectInfoObjectHandle;

        // ensure only one MTP transaction at a time
        std::mutex mutex;
        std::mutex eventMutex;
        std::mutex eventMutexForInterrupt;

        //store the device's packet division mode
        UrbPacketDivisionMode packetDivisionMode;
    };

}



#endif //MTPDEVICE_H
