#ifndef MTPPROPERTY_H
#define MTPPROPERTY_H

#include <cstdint>

#include "mtpTypes.h.h"
#include <string>

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

    };
}



#endif //MTPPROPERTY_H
