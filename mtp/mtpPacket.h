#ifndef MTPPACKET_H
#define MTPPACKET_H
#include <cstddef>
#include <cstdint>

#include "mtpTypes.h"

namespace mtp {
    class MtpPacket {
    public:
        explicit            MtpPacket(int bufferSize);
        virtual             ~MtpPacket();

        virtual void        reset(); //sets packet size to the default container size and sets buffer to zero

        void                allocate(std::size_t length);
        void                dump();
        void                copyFrom(const MtpPacket& source);

        std::uint16_t       getContainerCode() const;
        void                setContainerCode(std::uint16_t code);

        std::uint16_t       getContainerType();

        MtpTransactionID    getTransactionID() const;
        void                setTransactionID(MtpTransactionID id);

        uint32_t            getParameterValue(int index) const;
        void                setParameterValue(int index, std::uint32_t value);

        int                 transfer(struct usb_request* request);

    protected:
        std::uint16_t       getUInt16(int offset) const;
        std::uint32_t       getUInt32(int offset) const;
        void                putUInt16(int offset, std::uint16_t value);
        void                putUInt32(int offset, std::uint32_t value);

    protected:
        std::uint8_t*       buffer{};
        std::size_t         bufferSize{};
        std::size_t         allocationIncrement{};
        std::size_t         packetSize{};

    };
}



#endif //MTPPACKET_H
