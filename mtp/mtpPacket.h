#ifndef MTPPACKET_H
#define MTPPACKET_H
#include <cstddef>

namespace mtp {
    class MtpPacket {
    public:
        explicit MtpPacket(int bufferSize);
        virtual ~MtpPacket();

        virtual void reset(); //sets packet size to the default container size and sets buffer to zero
        void allocate(std::size_t length);
        void dump();
        void copyFrom(const MtpPacket& source);



    };
}



#endif //MTPPACKET_H
