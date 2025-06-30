#ifndef MTPOBJECTINFO_H
#define MTPOBJECTINFO_H
#include <ctime>

#include "mtpTypes.h"

namespace mtp {
    class MtpDataPacket;

    class MtpObjectInfo {
    public:
        explicit MtpObjectInfo(MtpObjectHandle handle);
        virtual ~MtpObjectInfo() = default;
        bool read(MtpDataPacket& packet);
        void print();

    public:
        MtpObjectHandle handle;
        MtpStorageID    storageID;
        MtpObjectFormat format;
        std::uint16_t   protectionStatus;
        std::uint32_t   compressedSize;
        MtpObjectFormat thumbFormat;
        std::uint32_t   thumbCompressedSize;
        std::uint32_t   thumbPixWidth;
        std::uint32_t   thumbPixHeight;
        std::uint32_t   imagePixWidth;
        std::uint32_t   imagePixHeight;
        std::uint32_t   imagePixDepth;
        MtpObjectHandle parent;
        std::uint16_t   associationType;
        std::uint32_t   associationDescription;
        std::uint32_t   sequenceNumber;
        char*           name;
        std::time_t     dateCreated;
        std::time_t     dateModified;
        char*           keywords;
    };
}




#endif //MTPOBJECTINFO_H
