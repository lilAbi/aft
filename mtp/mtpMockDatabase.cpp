#include "mtpMockDatabase.h"

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
    spdlog::info("MockDatabase {}:, path={}, objFormat={}, pHandle={}, storageID={}",__func__, path, format, parent, storageID);
    return lastObjectHandle;
}

