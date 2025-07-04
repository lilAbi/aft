#ifndef MTPDATAPACKET_H
#define MTPDATAPACKET_H

#include <string>

#include "mtpPacket.h"
#include "mtp.h"

namespace mtp {

    class IMtpHandle;

    class MtpDataPacket final : public MtpPacket{
    public:
                            MtpDataPacket();

        virtual             ~MtpDataPacket();

        void                reset() override;

        void                setOperationCode(MtpOperationCode code);
        void                setTransactionID(MtpTransactionID id);

        const std::uint8_t* getData() const { return buffer +  MTP_CONTAINER_HEADER_SIZE; }

        bool                getUInt8(std::uint8_t& value);
        bool                getInt8(std::int8_t& value) { return getUInt8(reinterpret_cast<std::uint8_t&>(value)); }
        bool                getUInt16(std::uint16_t& value);
        bool                getInt16(std::int16_t& value) { return getUInt16(reinterpret_cast<std::uint16_t&>(value)); }
        bool                getUInt32(std::uint32_t& value);
        bool                getInt32(std::int32_t& value) { return getUInt32(reinterpret_cast<std::uint32_t&>(value)); }
        bool                getUInt64(std::uint64_t& value);
        bool                getInt64(std::int64_t& value) { return getUInt64(reinterpret_cast<std::uint64_t&>(value)); }
        bool                getUInt128(__uint128_t& value); //does not work in 32 bit OS
        bool                getInt128(__int128& value) { return getUInt128(reinterpret_cast<__uint128_t&>(value)); }

        bool                getString(std::string& buffer);

        std::vector<std::int8_t>*           getInt8Arr();
        std::vector<std::uint8_t>*          getUInt8Arr();
        std::vector<std::int16_t>*          getInt16Arr();
        std::vector<std::uint16_t>*         getUInt16Arr();
        std::vector<std::int32_t>*          getInt32Arr();
        std::vector<std::uint32_t>*         getUInt32Arr();
        std::vector<std::int64_t>*          getInt64Arr();
        std::vector<std::uint64_t>*         getUInt64Arr();
        std::vector<__int128_t>*            getInt128Arr();
        std::vector<__uint128_t>*   getUInt128Arr();

        //todo: see if template is possible
        void setInt8(const std::int8_t& value);
        void setUInt8(const std::uint8_t& value);
        void setInt16(const std::int16_t& value);
        void setUInt16(const std::uint16_t& value);
        void setInt32(const std::int32_t& value);
        void setUInt32(const std::uint32_t& value);
        void setInt64(const std::int64_t& value);
        void setUInt64(const std::uint64_t& value);
        void setInt128(const __int128_t& value);
        void setUInt128(const __uint128_t& value);
        void setInt128(const std::int64_t value);
        void setUInt128(const std::uint8_t value);

        //todo: see if template is possible
        void setInt8Arr(const std::int8_t* values, int count);
        void setInt8Arr(std::vector<std::int8_t>* vecPtr);
        void setUInt8Arr(const std::uint8_t* values, int count);
        void setUInt8Arr(std::vector<std::uint8_t>* vecPtr);
        void setInt16Arr(const std::int16_t* values, int count);
        void setInt16Arr(std::vector<std::int16_t>* vecPtr);
        void setUInt16Arr(const std::uint16_t* values, int count);
        void setUInt16Arr(std::vector<std::uint16_t>* vecPtr);
        void setInt32Arr(const std::int32_t* values, int count);
        void setInt32Arr(std::vector<std::int32_t>* vecPtr);
        void setUInt32Arr(const std::uint32_t* values, int count);
        void setUInt32Arr(std::vector<std::uint32_t>* vecPtr);
        void setInt64Arr(const std::int64_t* values, int count);
        void setInt64Arr(std::vector<std::int64_t>* vecPtr);
        void setUInt64Arr(const std::uint64_t* values, int count);
        void setUInt64Arr(std::vector<std::uint64_t>* vecPtr);
        void setInt128Arr(const __int128_t* values, int count);
        void setInt128Arr(std::vector<__int128_t>* vecPtr);
        void setUInt128rr(const __uint128_t* values, int count);
        void setUInt128Arr(std::vector<__uint128_t>* vecPtr);
        void setEmptyArray() { setUInt8(0); }

        void setString(std::string stringBuffer);
        void setString(const std::uint16_t stringBuffer);
        void setEmptyString() { setUInt32(0); }

        int read(IMtpHandle* handle); //fill the buffer with data from the usb handle
        int write(IMtpHandle* handle); //write data to the usb handle
        int writeData(IMtpHandle* handle, void* data, std::uint32_t length);

        int read(struct usb_request* request);
        int readData(struct usb_request* request, void* buffer, int length);
        int readDataAsync(struct usb_request* request);
        int readDataWait(struct usb_device* device);
        int readDataHeader(struct usb_request* endpoint);

        //Write a whole data packet with payload to the end point given by a request. Return the number of bytes (including header size) sent to the device on success. Otherwise -1.
        int write(struct usb_request* request, UrbPacketDivisionMode divisionMode);
        //Similar to previous write method but it reads the payload from |fd|. If |size| is larger than MTP_BUFFER_SIZE, the data will be sent by multiple bulk transfer requests.
        std::int64_t write(struct usb_struct* request, UrbPacketDivisionMode divisionMode, int fd, std::size_t size);

        inline bool hasData() const { return packetSize > MTP_CONTAINER_HEADER_SIZE; }
        inline std::uint32_t getContainerLength() const { return MtpPacket::getUInt32(MTP_CONTAINER_LENGTH_OFFSET); }
        void* getData(int* outLength) const;

    private:
        std::size_t offset;
    };

}



#endif //MTPDATAPACKET_H
