#ifndef MTPSERVER_H
#define MTPSERVER_H

#include "MtpRequestPacket.h"
#include "MtpDataPacket.h"
#include "MtpResponsePacket.h"
#include "MtpEventPacket.h"
#include "mtp.h"
#include "IMtpHandle.h"

#include <memory>
#include <mutex>
#include <queue>

namespace mtp {

    class IMtpDatabase;
    class MtpStorage;

    class MtpServer {
    private:
        class ObjectEdit {
        public:
            MtpObjectHandle handle;
            std::string path;
            std::uint64_t size;
            MtpObjectFormat format;
            int fd;

            ObjectEdit(MtpObjectHandle handle_, const char* path_, std::uint64_t size_, MtpObjectFormat format_, int fd_)
                : handle{handle_}, path{path_}, size{size_}, format{format_}, fd{fd_} {}

            virtual ~ObjectEdit() {
                //close(fd);
            }
        };
    public:
        MtpServer(IMtpDatabase* database, int controlFD, bool ptp,  const char* deviceInfoManufacturer,
                                                                    const char* deviceInfoModel,
                                                                    const char* deviceInfoDeviceVersion,
                                                                    const char* deviceInfoSerialNumber);
        virtual ~MtpServer() = default;

        MtpStorage* getStorage(MtpStorageID id);
        inline bool hasStorage() { return storages.size() > 0; }
        bool hasStorage(MtpStorageID id);
        void addStorage(MtpStorage* storage);
        void removeStorage(MtpStorage* storage);

        void run();

        void sendObjectAdded(MtpObjectHandle handle);
        void sendObjectRemoved(MtpObjectHandle handle);
        void sendObjectInfoChanged(MtpObjectHandle handle);
        void sendDevicePropertyChanged(MtpDeviceProperty property);

    private:
        void sendStoreAdded(MtpStorageID id);
        void sendStoreRemoved(MtpStorageID id);
        void sendEvent(MtpEventCode code, std::uint32_t param1);

        void addEditObject(MtpObjectHandle handle, std::string path, std::uint64_t size, MtpObjectFormat format, int fd);
        ObjectEdit* getEditObject(MtpObjectHandle handle);
        void removeEditObject(MtpObjectHandle handle);
        void commitEdit(ObjectEdit* edit);

        bool handleRequest();

        MtpResponseCode doGetDeviceInfo();
        MtpResponseCode doOpenSession();
        MtpResponseCode doCloseSession();
        MtpResponseCode doGetStorageIDs();
        MtpResponseCode doGetStorageInfo();
        MtpResponseCode doGetObjectPropsSupported();
        MtpResponseCode doGetObjectHandles();
        MtpResponseCode doGetNumObjects();
        MtpResponseCode doGetObjectReferences();
        MtpResponseCode doSetObjectReferences();
        MtpResponseCode doGetObjectPropValue();
        MtpResponseCode doSetObjectPropValue();
        MtpResponseCode doGetDevicePropValue();
        MtpResponseCode doSetDevicePropValue();
        MtpResponseCode doResetDevicePropValue();
        MtpResponseCode doGetObjectPropList();
        MtpResponseCode doGetObjectInfo();
        MtpResponseCode doGetObject();
        MtpResponseCode doGetThumb();
        MtpResponseCode doGetPartialObject(MtpOperationCode operation);
        MtpResponseCode doSendObjectInfo();
        MtpResponseCode doSendObject();
        MtpResponseCode doDeleteObject();
        MtpResponseCode doMoveObject();
        MtpResponseCode doCopyObject();
        MtpResponseCode doGetObjectPropDesc();
        MtpResponseCode doGetDevicePropDesc();
        MtpResponseCode doSendPartialObject();
        MtpResponseCode doTruncateObject();
        MtpResponseCode doBeginEditObject();
        MtpResponseCode doEndEditObject();

    private:
        IMtpDatabase* database;

        //appear as a ptp device
        bool ptpHost;

        std::string deviceInfoManufacturer; //Manufacturer to report in DeviceInfo
        std::string deviceInfoModel;        //Model to report in DeviceInfo
        std::string deviceInfoDeviceVersion;//Device version to report in DeviceInfo
        std::string deviceInfoSerialNumber; //Serial number to report in DeviceInfo

        MtpSessionID sessionID;
        bool isSessionOpen;

        MtpRequestPacket requestPacket;
        MtpDataPacket   dataPacket;
        MtpResponsePacket responsePacket;
        MtpEventPacket eventPacket;
        MtpStorageList storageList;

        IMtpHandle* handle;

        MtpObjectHandle sendObjectHandle;
        MtpObjectFormat sendObjectFormat;
        std::string sendObjectFilePath;
        std::size_t sendObjectFileSize;
        std::time_t sendObjectModifiedTime;

        std::mutex mutex;

        std::vector<ObjectEdit*> objectEditList;

    };

}



#endif //MTPSERVER_H
