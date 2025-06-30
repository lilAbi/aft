#ifndef MTPRESPONSEPACKET_H
#define MTPRESPONSEPACKET_H

#include "MtpPacket.h"
#include "mtp.h"

namespace mtp {

    class IMtpHandle;

    class MtpResponsePacket : public MtpPacket {
    public:
        MtpResponsePacket();
        virtual ~MtpResponsePacket() override = default;

        int write(IMtpHandle* handle);
        int read(struct usb_request* request);

        inline MtpResponseCode getResponseCode() const { return getContainerCode(); }
        inline void setResponseCode(MtpResponseCode code) { return setContainerCode(code); }
    };

}



#endif //MTPRESPONSEPACKET_H
