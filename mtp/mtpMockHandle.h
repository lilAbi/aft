#ifndef MTPMOCKHANDLE_H
#define MTPMOCKHANDLE_H

#include "iMtpHandle.h"

#include <cstdint>
#include <vector>
#include <memory>
#include <spdlog/spdlog.h>

using Packet = std::vector<std::uint8_t>;

namespace mtp {

    class MtpMockHandle final : public IMtpHandle {
    public:
        MtpMockHandle() : packetNumber(0), packetOffset(0) {}

        virtual ~MtpMockHandle() override = default;

        void addPacket(const Packet& packet) { packets.push_back(packet); }

        //a pointer to the data, and the length might refer to how big *data block is, or how many 8 bytes are there
        int read(void* data, std::size_t len) override;

        int write(const void* data, std::size_t len) override;

        int receiveFile(MtpFileRange fileShape, bool empty) override;

        int sendFile(MtpFileRange fileShape) override;

        int sendEvent(MtpEvent event) override;

        int start(bool ptp) override;

        void close() override;

    private:
        std::size_t packetNumber;
        std::size_t packetOffset;
        std::vector<Packet> packets;

    };

}



#endif //MTPMOCKHANDLE_H
