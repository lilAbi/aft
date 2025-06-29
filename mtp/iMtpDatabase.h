#ifndef IMTPDATABASE_H
#define IMTPDATABASE_H

#include "mtpTypes.h"

namespace mtp {

    class MtpDataPacket;
    class MtpProperty;
    class MtpObjectInfo;

    class IMtpDatabase {
    public:
        IMtpDatabase() = default;
        virtual ~IMtpDatabase() = default;

        //Called from SendObjectInfo to reserve a database entry for the incoming file.
        virtual MtpObjectHandle beginSendObject(const char* path, MtpObjectFormat format, MtpObjectHandle parent, MtpStorageID storage) = 0;
        //Called to report success or failure of the SendObject file transfer.
        virtual void endSendObject(MtpObjectHandle handle, bool sent);
        //Called to rescan a file, such as after an edit.
        virtual void rescanFile(const char* path, MtpObjectFormat format, MtpObjectHandle handle);
        //Get list of files
        virtual MtpObjectHandleList* getObjectList(MtpStorageID storage, MtpObjectFormat format, MtpObjectHandle parent);
        virtual int getNumObjects(MtpStorageID storage, MtpObjectFormat format, MtpObjectHandle parent);

        virtual MtpObjectFormatList* getSupportedPlaybackFormats() = 0;
        virtual MtpObjectFormatList* getSupportedCaptureFormats() = 0;
        virtual MtpObjectPropertyList* getSupportedObjectProperties(MtpObjectFormat format) = 0;
        virtual MtpObjectPropertyList* getSupportedDeviceProperties() = 0;

        virtual MtpResponseCode getObjectPropertyValue(MtpObjectHandle handle, MtpObjectProperty property, MtpDataPacket& packet);
        virtual MtpResponseCode setObjectPropertyValue(MtpObjectHandle handle, MtpObjectProperty property, MtpDataPacket& packet);

        virtual MtpResponseCode getDevicePropertyValue(MtpObjectProperty property, MtpDataPacket& packet);
        virtual MtpResponseCode setDevicePropertyValue(MtpObjectProperty property, MtpDataPacket& packet);

        virtual MtpResponseCode resetDeviceProperty(MtpDeviceProperty property) = 0;
        virtual MtpResponseCode getObjectPropertyList(MtpObjectHandle handle, std::uint32_t format, std::uint32_t property, int groupCode, int depth, MtpDataPacket& packet) = 0;



    };
}

#endif //IMTPDATABASE_H
