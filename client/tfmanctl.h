#include "../gen/rememberd.h"
#include <string>

#define TFMAN_DBUS "remember.service"
#define TFMAN_DBUS_PATH "/remember/service"

class client
{
    public:
        client();
        virtual ~client();

        int init();
        static int uinit();

        /*Our functions*/
        std::string getFileList();
        int addFile(std::string path);
        int removeFile(std::string path);

    private:
        /*Ritual D-Bus stuff*/
        GDBusConnection *_gConn;
        static GMainLoop *_gLoop;
        RememberDaemon *_gProxy;

        static void *startGLoop(void *);

};