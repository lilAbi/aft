#ifndef IMTPDATABASE_H
#define IMTPDATABASE_H

#include "mtpTypes.h"
#include <string>

namespace mtp {

    class MtpDataPacket;
    class MtpProperty;
    class MtpObjectInfo;

    class IMtpDatabase {
    public:
        IMtpDatabase() = default;
        virtual ~IMtpDatabase() = default;

        //Called from SendObjectInfo to reserve a database entry for the incoming file.
        virtual MtpObjectHandle beginSendObject(const char* path, MtpObjectFormat format, MtpObjectHandle parent, MtpStorageID storageID) = 0;
        //Called to report success or failure of the SendObject file transfer.
        virtual void endSendObject(MtpObjectHandle handle, bool sent) = 0;
        //Called to rescan a file, such as after an edit.
        virtual void rescanFile(const char* path, MtpObjectFormat format, MtpObjectHandle handle) = 0;
        //Get list of files
        virtual MtpObjectHandleList* getObjectList(MtpStorageID storageID, MtpObjectFormat format, MtpObjectHandle parent) = 0;
        virtual int getNumObjects(MtpStorageID storageID, MtpObjectFormat format, MtpObjectHandle parent) = 0;

        virtual MtpObjectFormatList* getSupportedPlaybackFormats() = 0;
        virtual MtpObjectFormatList* getSupportedCaptureFormats() = 0;
        virtual MtpObjectPropertyList* getSupportedObjectProperties(MtpObjectFormat format) = 0;
        virtual MtpObjectPropertyList* getSupportedDeviceProperties() = 0;

        virtual MtpResponseCode getObjectPropertyValue(MtpObjectHandle handle, MtpObjectProperty property, MtpDataPacket& packet) = 0;
        virtual MtpResponseCode setObjectPropertyValue(MtpObjectHandle handle, MtpObjectProperty property, MtpDataPacket& packet) = 0;

        virtual MtpResponseCode getDevicePropertyValue(MtpObjectProperty property, MtpDataPacket& packet) = 0;
        virtual MtpResponseCode setDevicePropertyValue(MtpObjectProperty property, MtpDataPacket& packet) = 0;

        virtual MtpResponseCode resetDeviceProperty(MtpDeviceProperty property) = 0;

        virtual MtpResponseCode getObjectPropertyList(MtpObjectHandle handle, std::uint32_t format, std::uint32_t property, int groupCode, int depth, MtpDataPacket& packet) = 0;

        virtual MtpResponseCode getObjectInfo(MtpObjectHandle handle, MtpObjectInfo& info) = 0;

        virtual void* getThumbnail(MtpObjectHandle handle, std::size_t& thumbNailSize) = 0;

        virtual MtpResponseCode getObjectFilePath(MtpObjectHandle handle, std::string buffer, std::int64_t fileLength, MtpObjectFormat format) = 0;

        virtual int openFilePath(const char* path, bool transcode) = 0;

        virtual MtpResponseCode beginDeleteObject(MtpObjectHandle handle) = 0;
        virtual MtpResponseCode endDeleteObject(MtpObjectHandle handle, bool deleted) = 0;

        virtual MtpObjectHandleList* getObjectReferences(MtpObjectHandle handle) = 0;
        virtual MtpResponseCode setObjectReferences(MtpObjectHandle handle, MtpObjectHandleList* references) = 0;

        virtual MtpProperty* getObjectPropertyDesc(MtpPropertyList property, MtpObjectFormat format) = 0;

        virtual MtpProperty* getDevicePropertyDesc(MtpDeviceProperty property) = 0;

        virtual MtpResponseCode beginMoveObject(MtpObjectHandle handle, MtpObjectHandle newParent, MtpStorageID storageID) = 0;

        virtual void endMoveObject(MtpObjectHandle oldParent, MtpObjectHandle newParent, MtpStorageID oldStorageID, MtpStorageID newStorageID, MtpObjectHandle handle, bool moved) = 0;

        virtual MtpResponseCode beginCopyObject(MtpObjectHandle handle, MtpObjectHandle newParent, MtpStorageID newStorage) = 0;

        virtual void endCopyObject(MtpObjectHandle handle, bool copied) = 0;

    };
}

#endif //IMTPDATABASE_H
