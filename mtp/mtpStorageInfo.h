#ifndef MTPSTORAGEINFO_H
#define MTPSTORAGEINFO_H

#include <string>
#include "mtpTypes.h"

class MtpDataPacket;

namespace mtp {
    class MtpStorageInfo {
    public:
        MtpStorageInfo() = default;
        explicit MtpStorageInfo(MtpStorageID id);
        virtual ~MtpStorageInfo();

        bool read(MtpDataPacket& dataPacket);

        void print();
    public:
        MtpStorageID    storageID;
        std::uint16_t   storageType;
        std::uint16_t   fileSystemType;
        std::uint16_t   accessCapability;
        std::uint64_t   maxCapacity;
        std::uint64_t   freeSpaceBytes;
        std::uint32_t   freeSpaceObjects;
        std::string     storageDescription;
        std::string     volumeIdentifier;
    };
}


#endif //MTPSTORAGEINFO_H
