#ifndef MTPEVENTPACKET_H
#define MTPEVENTPACKET_H

#include "mtpPacket.h"
#include "mtp.h"

namespace mtp {
    class IMtpHandle;

    class MtpEventPacket : public MtpPacket {
    public:
        MtpEventPacket();
        ~MtpEventPacket() override = default;

        int write(IMtpHandle* handle);

        int sendRequest(struct usb_request* request);
        int readResponse(struct usb_device* device);

        inline MtpEventCode getEventCode() const { return getContainerCode(); }
        inline void setEventCode(const MtpEventCode code) { return setContainerCode(code); }
    };

}



#endif //MTPEVENTPACKET_H
