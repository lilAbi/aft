#ifndef MTPSERVER_H
#define MTPSERVER_H

#include "MtpRequestPacket.h"
#include "MtpDataPacket.h"
#include "MtpResponsePacket.h"
#include "MtpEventPacket.h"
#include "mtp.h"
#include "IMtpHandle.h"

#include <memory>
#include <mutex>
#include <queue>

namespace mtp {

    class IMtpDatabase;
    class MtpStorage;

    class MtpServer {
    public:
        MtpServer(IMtpDatabase* database, int controlFD, bool ptp,  const char* deviceInfoManufacturer,
                                                                    const char* deviceInfoModel,
                                                                    const char* deviceInfoDeviceVersion,
                                                                    const char* deviceInfoSerialNumber);
        virtual ~MtpServer() = default;

        MtpStorage* getStorage(MtpStorageID id);
        inline bool hasStorage() { return storages.size() > 0; }
        bool hasStorage(MtpStorageID id);
        void addStorage(MtpStorage* storage);
        void removeStorage(MtpStorage* storage);

        void run();

        void sendObjectAdded(MtpObjectHandle handle);
        void sendObjectRemoved(MtpObjectHandle handle);
        void sendObjectInfoChanged(MtpObjectHandle handle);
        void sendDevicePropertyChanged(MtpDeviceProperty property);

    private:
        void sendStoreAdded(MtpStorageID id);
        void sendStoreRemoved(MtpStorageID id);
        void sendEvent(MtpEventCode code, std::uint32_t param1);

        void addEditObject(MtpObjectHandle handle, std::string path, std::uint64_t size, MtpObjectFormat format, int fd);
        ObjectEdit* getEditObject(MtpObjectHandle handle);
        void removeEditObject(MtpObjectHandle handle);
        void commitEdit(ObjectEdit* edit);
    };

}



#endif //MTPSERVER_H
