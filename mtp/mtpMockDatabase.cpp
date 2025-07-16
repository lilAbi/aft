#include "mtpMockDatabase.h"

#include <bits/valarray_before.h>
#include <spdlog/spdlog.h>


mtp::MtpMockDatabase::~MtpMockDatabase() {
    for (const MtpObjectInfo* objInfo : objects) { delete objInfo; }
    objects.clear();
}

void mtp::MtpMockDatabase::addStorage(MtpStorage* storage) {
    storages[storage->getStorageID()] = storage;
}

bool mtp::MtpMockDatabase::hasStorage(MtpStorageID storageID) const {
    return storages.contains(storageID);
}

void mtp::MtpMockDatabase::addObject(MtpObjectInfo *info) {
    //we own this object now
    objects.push_back(info);
}

mtp::MtpObjectHandle mtp::MtpMockDatabase::allocateObjectHandle() {
    //this is in sync with our "objects" database
    return lastObjectHandle++;
}

mtp::MtpObjectHandle mtp::MtpMockDatabase::beginSendObject(const char *path, MtpObjectFormat format, MtpObjectHandle parent, MtpStorageID storageID) {
    if (!hasStorage(storageID)) {
        spdlog::info("{}: storageID {} does not exist", __func__, storageID);
        return 0xFFFFFFFF;
    }
    spdlog::info("MockDatabase {}:, path={}, objFormat={}, pObjHandle={}, storageID={}",__func__, path, format, parent, storageID);
    return lastObjectHandle;
}

void mtp::MtpMockDatabase::endSendObject(MtpObjectHandle handle, bool sent) {
    spdlog::info("MockDatabase {}: objHandle={} sent={}", __func__, handle, sent);
}

void mtp::MtpMockDatabase::rescanFile(const char *path, MtpObjectFormat format, MtpObjectHandle handle) {
    spdlog::info("MockDatabase {}: objHandle={} objFormat={}", __func__, handle, format);
}

mtp::MtpObjectHandleList* mtp::MtpMockDatabase::getObjectList(MtpStorageID storageID, MtpObjectFormat format, MtpObjectHandle parent) {
    spdlog::info("MockDatabase {}: storageID={}, objFormats={}, pObjHandle={}", __func__, storageID, format, parent);
    return nullptr;
}

int mtp::MtpMockDatabase::getNumObjects(MtpStorageID storageID, MtpObjectFormat format, MtpObjectHandle parent) {
    spdlog::info("MockDataBase {}: storageID={}, objFormat={}, pObjHandle={}", __func__, storageID, format, parent);
    return 0;
}

mtp::MtpObjectFormatList* mtp::MtpMockDatabase::getSupportedPlaybackFormats() {
    spdlog::info("MockDataBase {}", __func__);
    return nullptr;
}

mtp::MtpObjectFormatList * mtp::MtpMockDatabase::getSupportedCaptureFormats() {
    spdlog::info("MockDataBase {}", __func__);
    return nullptr;
}

mtp::MtpObjectPropertyList * mtp::MtpMockDatabase::getSupportedObjectProperties(MtpObjectFormat format) {
    spdlog::info("MockDataBase {}: objFormat: {}", __func__, format);
    return nullptr;
}

mtp::MtpObjectPropertyList * mtp::MtpMockDatabase::getSupportedDeviceProperties() {
    spdlog::info("MockDataBase {}", __func__);
    return nullptr;
}

mtp::MtpResponseCode mtp::MtpMockDatabase::getObjectPropertyValue(MtpObjectHandle handle, MtpObjectProperty property, MtpDataPacket &packet) {
    spdlog::info("MockDataBase {}: property={}, packet={}", __func__, property, packet);
    return MTP_RESPONSE_OK;
}

mtp::MtpResponseCode mtp::MtpMockDatabase::setObjectPropertyValue(MtpObjectHandle handle, MtpObjectProperty property, MtpDataPacket &packet) {
    spdlog::info("MockDataBase {}: property={}, packet={}", __func__, property, packet);
    return MTP_RESPONSE_OK;
}

mtp::MtpResponseCode mtp::MtpMockDatabase::getDevicePropertyValue(MtpObjectProperty property, MtpDataPacket &packet) {
    spdlog::info("MockDataBase {}: property={}", __func__, property);
    return MTP_RESPONSE_OK;
}

mtp::MtpResponseCode mtp::MtpMockDatabase::setDevicePropertyValue(MtpObjectProperty property, MtpDataPacket &packet) {
    spdlog::info("MockDataBase {}: property={}", __func__, property);
    return MTP_RESPONSE_OK;
}

mtp::MtpResponseCode mtp::MtpMockDatabase::resetDeviceProperty(MtpDeviceProperty property) {
    spdlog::info("MockDataBase {}: property={}", __func__, property);
    return MTP_RESPONSE_OK;
}

mtp::MtpResponseCode mtp::MtpMockDatabase::getObjectPropertyList(MtpObjectHandle handle, std::uint32_t format,
                                                                 std::uint32_t property, int groupCode, int depth, MtpDataPacket &packet) {
    spdlog::info("MockDataBase {}: objHandle={} objFormat={} property={}, groupCode={} depth={}", __func__, handle,
                                                                                                  property,
                                                                                                  groupCode,
                                                                                                  depth);
    return MTP_RESPONSE_OK;
}

mtp::MtpResponseCode mtp::MtpMockDatabase::getObjectInfo(MtpObjectHandle handle, MtpObjectInfo &info) {
    spdlog::info("MockDataBase {}: objHandle={}", __func__, handle);

    if (handle == 0x0) {
        return MTP_RESPONSE_INVALID_OBJECT_HANDLE;
    } else {

        if (objects.size() == 0) {
            return MTP_RESPONSE_INVALID_OBJECT_HANDLE;
        }

        //apparently makes the handle smaller
        MtpObjectHandle newHandle = handle % objects.size();
        MtpObjectInfo* object = objects[newHandle];

        info = *object;
        info.handle = handle;

        if (!object->name.empty()) info.name = object->name;
        if (!object->keywords.empty()) info.keywords = object->keywords;

        return MTP_RESPONSE_OK;
    }
}

void * mtp::MtpMockDatabase::getThumbnail(MtpObjectHandle handle, std::size_t &thumbNailSize) {
    spdlog::info("MockDataBase {}: objHandle={}", __func__, handle);
    //0 to 4095 for buffer allocation
    std::size_t thumbNailAllocSize = handle % 0x1000;
    void* data = new std::uint32_t[thumbNailAllocSize];
    if (data != nullptr) {
        thumbNailSize = thumbNailAllocSize;
        return data;
    } else {
        return nullptr;
    }
}

mtp::MtpResponseCode mtp::MtpMockDatabase::getObjectFilePath(MtpObjectHandle handle, std::string buffer,
    std::int64_t fileLength, MtpObjectFormat format){
    spdlog::info("MockDataBase {}: objHandle={}", __func__, handle);

    if (objects.size() == 0) {
        return MTP_RESPONSE_INVALID_OBJECT_HANDLE;
    }

    const MtpObjectHandle newHandle = handle % objects.size();
    const MtpObjectInfo* objectInfo = objects[newHandle];
    MtpStorage* storage = storages[objectInfo->storageID];

    //walk up the tree to build the path of the object
    MtpObjectHandle currHandle = newHandle;
    std::string path;

    while (currHandle != MTP_PARENT_ROOT) {
        const MtpObjectInfo* nextHandle = objects[currHandle];

        if (path.empty()) {
            path = nextHandle->name;
        } else {
            path = nextHandle->name + "/" + path;
        }
    }

    buffer = storage->getPath();
    buffer.append("/");
    buffer.append(path);

    format = objectInfo->format;

}












