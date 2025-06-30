#ifndef MTPPROPERTY_H
#define MTPPROPERTY_H

#include <cstdint>

#include "mtpTypes.h"
#include <string>

#include "mtpTypes.h"

namespace mtp {
    class MtpDataPacket;

    struct MtpPropertyValue {
        MtpPropertyValue() = default;

        union {
            int8_t          i8;
            uint8_t         u8;
            int16_t         i16;
            uint16_t        u16;
            int32_t         i32;
            uint32_t        u32;
            int64_t         i64;
            uint64_t        u64;
            __int128_t        i128;
            __uint128_t       u128;
        } u;

        char* str{nullptr};
    };

    class MtpProperty {
    public:
        MtpProperty() = default;
        MtpProperty(MtpPropertyCode propCode, MtpDataType type, bool writeable = false, int defaultValue = 0);
        virtual ~MtpProperty() = default;

        MtpPropertyCode getPropertyCode() const { return code; }
        MtpDataType getDataType() const { return type; }

        bool read(MtpDataPacket& packet);
        bool write(MtpDataPacket& packet);

        void setDefaultValue(const std::uint16_t* str);
        void setCurrentValue(const std::uint16_t* str);
        void setCurrentValue(const char* str);
        void setCurrentValue(MtpDataPacket& packet);
        const MtpPropertyValue& getCurrentValue() { return currentValue; }

        void setFormRange(int min, int max, int step);
        void setFormEnum(const int* value, int count);
        void setFormDateTime();

        void print();

        inline bool isDeviceProperty() const {
            return( ( (code & 0xF000) == 0x5000) || ((code & 0xF800) == 0xD000) );
        }

    private:
        bool readValue(MtpDataPacket& packet, MtpPropertyValue& value);
        void writeValue(MtpDataPacket& packet, MtpPropertyValue& value);
        MtpPropertyValue* readArrayValues(MtpDataPacket& packet, std::uint32_t length);
        void readArrayValues(MtpDataPacket& packet, std::uint32_t length, MtpPropertyValue* values);

        void print(MtpPropertyValue& value);

    public:
        MtpPropertyCode code;
        MtpDataType type;
        bool writeable;
        MtpPropertyValue defaultValue;
        MtpPropertyValue currentValue;

        std::uint32_t defaultArrayLength;
        MtpPropertyValue* defaultArrayValues;
        std::uint32_t currentArrayLength;
        MtpPropertyValue* currentArrayValues;

        enum class Form {NONE = 0, RANGE, ENUM, FORM_DATE_TIME};

        std::uint32_t groupCode;
        std::uint8_t formFlag;

        //for range form
        MtpPropertyValue minimumValue;
        MtpPropertyValue maximumValue;
        MtpPropertyValue stepSize;

        //for enum form
        std::uint16_t enumLength;
        MtpPropertyValue* enumValues;

    };
}



#endif //MTPPROPERTY_H
