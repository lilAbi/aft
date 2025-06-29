#ifndef MTPTYPES_H
#define MTPTYPES_H

#include <cstdint>
#include <vector>

namespace mtp {
    //This identifies the operation being initiated by the device
    using MtpOperationCode = std::uint16_t;

    //Following every operation, the responder returns a response dataset
    using MtpResponseCode = std::uint16_t;

    //Identifies the type of event sent from the initiator/responder
    using MtpEventCode = std::uint16_t;

    //SessionIDs are chosen by the Initiator and communicated in an OpenSession operation.
    using MtpSessionID = std::uint32_t;

    //The first 16 bits identifies the physical location, the last 16 bits identifies a logical partition
    using MtpStorageID = std::uint32_t;

    //TransactionIDs are chosen by the Initiator and should be chosen starting at 0x1 for the first operation initiated in a session
    using MtpTransactionID = std::uint32_t;

    //A specific ObjectPropCode identifying this property.
    using MtpPropertyCode = std::uint16_t;

    //Identifies the data type code of the property - basically tells the type of the incoming data value
    using MtpDataType = std::uint16_t;

    //Every object format type is identified by an ObjectFormatCode
    using MtpObjectFormat = std::uint16_t;

    //Device properties identify settings or state conditions of the device, and are not linked to any data objects on the device
    using MtpDeviceProperty = std::uint16_t;

    //Object properties provide a mechanism for exchanging object-describing metadata separate from the objects themselves
    using MtpObjectProperty = std::uint16_t;

    //object handles are unique across all storage but only within a single session, object handles cannot be reused after an object is deleted
    using MtpObjectHandle = uint32_t;

    class MtpStorage; //forward deceleration
    using MtpStorageList = std::vector<MtpStorage*>;

    class MtpDevice; //forward deceleration
    using MtpDeviceList = std::vector<MtpDevice*>;

    class MtpProperty; //forward deceleration
    using MtpPropertyList = std::vector<MtpProperty*>;

    using MtpObjectPropertyList = std::vector<std::uint16_t>;
    using MtpObjectDeviceList = std::vector<std::uint16_t>;
    using MtpObjectFormatList = std::vector<std::uint16_t>;
    using MtpObjectHandleList = std::vector<std::uint32_t>;
    using MtpObjectPropertyList = std::vector<std::uint16_t>;
    using MtpStorageIDList = std::vector<std::uint32_t>;

    enum class UrbPacketDivisionMode {
        FIRST_PACKET_ONLY_HEADER, //First packet only contains a header
        FIRST_PACKET_HAS_PAYLOAD, //First packet contains payload much as possible
    };

    struct MtpFileRange {
        int fd;
        std::size_t offset;
        std::uint16_t commmand;
        std::uint32_t transactionID;
        std::int64_t length;
    };

    struct MtpEvent {
        std::size_t length;
        void* data;
    };

}

#endif //MTPTYPES_H
