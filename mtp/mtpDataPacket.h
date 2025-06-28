#ifndef MTPDATAPACKET_H
#define MTPDATAPACKET_H

#include "mtpPacket.h"
#include "mtp.h"

namespace mtp {

    class IMtpHandle;

    class MtpDataPacket : public MtpPacket{
    public:
                        MtpDataPacket();

        virtual         ~MtpDataPacket();

        virtual void    reset() override;

        void setOperationCode(MtpOperationCode code);
        void setTransactionID(MtpTransactionID id);

        inline const std::uint8_t* getData() const { return buffer +  MTP_CONTAINER_HEADER_SIZE; }

        bool getUInt8(std::uint8_t& value);
        inline bool getInt8(std::int8_t& value) { return getUInt8(reinterpret_cast<std::uint8_t&>(value)); }

        bool getUInt16(std::uint16_t& value);
        inline bool getInt16(std::int16_t& value) { return getUInt16(reinterpret_cast<std::uint16_t&>(value)); }

        bool getUInt32(std::uint32_t& value);
        inline bool getInt32(std::int32_t& value) { return getUInt32(reinterpret_cast<std::uint32_t&>(value)); }

        bool getUInt64(std::uint64_t& value);
        inline bool getInt64(std::int64_t& value) { return getUInt64(reinterpret_cast<std::uint64_t&>(value)); }

        bool getUInt128(unsigned __int128_t& value); //does not work on 32 bit
        inline bool getInt128(__int128& value) { return getUInt128(reinterpret_cast<unsigned __int128_t&>(value)); }


    };

}



#endif //MTPDATAPACKET_H
