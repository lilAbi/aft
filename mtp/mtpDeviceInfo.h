#ifndef MTPDEVICEINFO_H
#define MTPDEVICEINFO_H
#include <cstdint>
#include <vector>

#include "mtpTypes.h"

namespace mtp {
    class MtpDataPacket;

    class MtpDeviceInfo {
    public:
        MtpDeviceInfo() = default;
        ~MtpDeviceInfo() = default;

        bool read(MtpDataPacket& dataPacket);

        void print();

    public:
        std::uint16_t standardVersion;
        std::uint32_t vendorExtensionID;
        std::uint16_t vendorExtensionVersion;
        char* vendorExtensionDesc;
        std::uint16_t functionalMode;
        std::vector<std::uint16_t>* operations;
        std::vector<std::uint16_t>* events;
        MtpDevicePropertyList* deviceProperties;
        MtpObjectFormatList* captureFormats;
        MtpObjectFormatList* playbackFormats;
        char* manufacturer;
        char* model;
        char* version;
        char* serial;

    };

}



#endif //MTPDEVICEINFO_H
