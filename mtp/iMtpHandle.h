#ifndef IMTPHANDLE_H
#define IMTPHANDLE_H
#include <cstddef>

#include "mtpTypes.h"

namespace mtp {

    class IMtpHandle {
    public:
        IMtpHandle() = default;

        virtual ~IMtpHandle() = default;

        //returns number of bytes read/written, or -1 on error
        virtual int read(void* data, std::size_t len) = 0;
        virtual int write(const void* data, std::size_t len) = 0;

        //return 0 if send/recieve is successful, or -1 else
        virtual int receiveFile(MtpFileRange fileShape, bool empty) = 0;
        virtual int sendFile(MtpFileRange fileShape) = 0;
        virtual int sendEvent(MtpEvent event) = 0;

        //return 0 is the operation is successful, or -1 else
        virtual int start(bool ptp) = 0;
        virtual void close() = 0;

    };


}

#endif //IMTPHANDLE_H
