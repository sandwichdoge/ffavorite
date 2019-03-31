#include "../gen/tfmand.h"

#define TFMAN_DBUS "tfman.service"
#define TFMAN_DBUS_PATH "/tfman/service"

class client
{
    public:
        client();
        virtual ~client();

        int init();
        static int uinit();

    private:
        /*Ritual D-Bus stuff*/
        GDbusConnection *_gConn;
        static GMainLoop *_gLoop;
        TerminalFileManager *_gProxy;

        static void *startGLoop(void *);
        
        /*Our functions*/
        static std::string getFileList();
        static bool addFile(std::string path);
        static bool removeFile(std::string path);

};