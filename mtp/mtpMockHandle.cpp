#include "mtpMockHandle.h"

int mtp::MtpMockHandle::read(void *data, std::size_t len) {
    //if at the end of the incoming packet list
    if (packetNumber >=  packets.size()) {
        return 0;
    } else {
        int readAmount = 0;
        const auto packet = packets[packetNumber];

        spdlog::info("MockHandle {}: sz {} packet #{} +{} / {} ", __func__, len, packetNumber, packetOffset, packet.size());
        //packet bigger than what the caller can handle

        //todo: make sure this is accurate; use std::copy
        if (packet.size() - packetOffset > len) {
            std::memcpy(data, packet.data() + packetOffset, len);
            packetOffset += len;
            readAmount = len;
        } else {
            std::memcpy(data, packet.data() + packetOffset, packet.size() - packetOffset);
            packetNumber++;
            packetOffset = 0;
            readAmount = packet.size() - packetOffset;
        }
        return readAmount;
    }
}

int mtp::MtpMockHandle::write(const void *data, std::size_t len) {
    spdlog::info("MockHandle {}: len={} \n", __func__, len);
    //fake the write
    return len;
}

int mtp::MtpMockHandle::receiveFile(MtpFileRange fileShape, bool empty) {
    spdlog::info("MockHandle {}", __func__);
    return 0;
}

int mtp::MtpMockHandle::sendFile(MtpFileRange fileShape) {
    spdlog::info("MockHandle {}", __func__);
    return 0;
}

int mtp::MtpMockHandle::sendEvent(MtpEvent event) {
    spdlog::info("MockHandle {}: event_len={}", __func__, event.length);
    return 0;
}

int mtp::MtpMockHandle::start(bool ptp) {
    return 0;
}

void mtp::MtpMockHandle::close() {

}






