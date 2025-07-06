#ifndef MTPMOCKDATABASE_H
#define MTPMOCKDATABASE_H

#include "iMtpDatabase.h"
#include "mtpStorage.h"
#include "mtpObjectInfo.h"

#include <map>


namespace mtp {

    class MtpMockDatabase final : public IMtpDatabase {
    public:
        MtpMockDatabase() = default;
        ~MtpMockDatabase() override;

        void addStorage(MtpStorage* storage);

        bool hasStorage(MtpStorageID storageID) const;

        void addObject(MtpObjectInfo* info);

        MtpObjectHandle allocateObjectHandle();

        //libmtp interface methods
        //Called from SendObjectInfo to reserve a database entry for the incoming file
        MtpObjectHandle beginSendObject(const char *path, MtpObjectFormat format, MtpObjectHandle parent, MtpStorageID storageID) override;

        //Called to report success or failure of the SendObject file transfer
        void endSendObject(MtpObjectHandle handle, bool sent) override;

        //Called to rescan a file, such as after an edit
        void rescanFile(const char *path, MtpObjectFormat format, MtpObjectHandle handle) override;

        MtpObjectHandleList* getObjectList(MtpStorageID storage, MtpObjectFormat format, MtpObjectHandle parent) override;

        int getNumObjects(MtpStorageID storage, MtpObjectFormat format, MtpObjectHandle parent) override;

        //callee should delete[] the results from these- results can be NULL
        MtpObjectFormatList* getSupportedPlaybackFormats() override;
        MtpObjectFormatList* getSupportedCaptureFormats() override;
        MtpObjectPropertyList* getSupportedObjectProperties(MtpObjectFormat format) override;
        MtpObjectPropertyList* getSupportedDeviceProperties() override;

        MtpResponseCode getObjectPropertyValue(MtpObjectHandle handle, MtpObjectProperty property, MtpDataPacket &packet) override;

        MtpResponseCode setObjectPropertyValue(MtpObjectHandle handle, MtpObjectProperty property, MtpDataPacket &packet) override;

        MtpResponseCode getDevicePropertyValue(MtpObjectProperty property, MtpDataPacket &packet) override;

        MtpResponseCode setDevicePropertyValue(MtpObjectProperty property, MtpDataPacket &packet) override;

        MtpResponseCode resetDeviceProperty(MtpDeviceProperty property) override;

        MtpResponseCode getObjectPropertyList(MtpObjectHandle handle, std::uint32_t format, std::uint32_t property, int groupCode, int depth, MtpDataPacket &packet) override;

        MtpResponseCode getObjectInfo(MtpObjectHandle handle, MtpObjectInfo &info) override;

        void* getThumbnail(MtpObjectHandle handle, std::size_t &thumbNailSize) override;

        MtpResponseCode getObjectFilePath(MtpObjectHandle handle, std::string buffer, std::int64_t fileLength, MtpObjectFormat format) override;

        int openFilePath(const char *path, bool transcode) override;

        MtpResponseCode beginDeleteObject(MtpObjectHandle handle) override;
        MtpResponseCode endDeleteObject(MtpObjectHandle handle, bool deleted) override;

        MtpObjectHandleList* getObjectReferences(MtpObjectHandle handle) override;

        MtpResponseCode setObjectReferences(MtpObjectHandle handle, MtpObjectHandleList *references) override;

        MtpProperty* getObjectPropertyDesc(MtpPropertyList property, MtpObjectFormat format) override;

        MtpProperty* getDevicePropertyDesc(MtpDeviceProperty property) override;

        MtpResponseCode beginMoveObject(MtpObjectHandle handle, MtpObjectHandle newParent, MtpStorageID storage) override;

        void endMoveObject(MtpObjectHandle oldParent, MtpObjectHandle newParent, MtpStorageID oldStorage, MtpStorageID newStorage, MtpObjectHandle handle, bool moved) override;

        MtpResponseCode beginCopyObject(MtpObjectHandle handle, MtpObjectHandle newParent, MtpStorageID newStorage) override;

        void endCopyObject(MtpObjectHandle handle, bool copied) override;

    public:
        std::map<MtpStorageID, MtpStorage*> storages{};
        std::vector<MtpObjectInfo*> objects{};
        std::uint32_t lastObjectHandle{};
    };
}

#endif //MTPMOCKDATABASE_H
