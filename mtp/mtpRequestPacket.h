#ifndef MTPREQUESTPACKET_H
#define MTPREQUESTPACKET_H

#include "mtpPacket.h"
#include "mtp.h"

class IMtpHandle;

namespace mtp {

    class MtpRequestPacket : public MtpPacket {
    public:
        MtpRequestPacket();
        ~MtpRequestPacket() override = default;

        int read(IMtpHandle* handle); //fill our buffer with data from the usb

        int write(struct usb_request* request); //write our buffer to the endpoint

        inline MtpOperationCode getOperationCode() const { return getContainerCode(); }
        inline void setOperationCode(const MtpOperationCode code) { return setContainerCode(code); }

        inline int getParameterCount() const { return parameterCount; }

    private:
        int parameterCount;
    };

}



#endif //MTPREQUESTPACKET_H
