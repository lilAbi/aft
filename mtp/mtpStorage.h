#ifndef MTPSTORAGE_H
#define MTPSTORAGE_H

#include <string>

#include "mtpTypes.h"
#include "mtp.h"

#include

namespace mtp {

    class MtpStorage {
    public:
        MtpStorage(MtpStorageID id, const char* filePath, const char* description, bool removeable, std::uint64_t maxFileSize);
        virtual ~MtpStorage() = default;

        inline MtpStorageID getStorageID() const { return storageID; }
        int getType() const;
        int getFileSystemType() const;
        int getAccessCapability() const;
        std::uint64_t getMaxCapacity();
        std::uint64_t getFreeSpace();
        std::string getDescription();
        inline std::string getPath() const { return filePath; }
        inline bool isRemoveable() const { return removable; }
        inline std::uint64_t getMaxFileSize() const { return maxFileSize; }

    private:
        MtpStorageID storageID;
        std::string filePath;
        std::string description;
        std::uint64_t maxCapacity;
        std::uint64_t maxFileSize;
        bool removable;
    };
}



#endif //MTPSTORAGE_H
