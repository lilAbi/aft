#ifndef MTPDEVHANDLE_H
#define MTPDEVHANDLE_H

#include "iMtpHandle.h"


namespace mtp {
    class MtpDevHandle : public IMtpHandle {
    public:
        MtpDevHandle() = default;
        ~MtpDevHandle() override;

        int read(void* data, std::size_t length) override;
        int write(const void* data, std::size_t length) override;

        int receiveFile(MtpFileRange fileShape, bool empty) override;

        int sendFile(MtpFileRange fileShape) override;

        int sendEvent(MtpEvent event) override;

        int start(bool ptp) override;

        void close() override;

    private:
        int fd;
    };

}



#endif //MTPDEVHANDLE_H
