#ifndef REM_CLIENT_H_
#define REM_CLIENT_H_
#include "../gen/rememberd.h"
#include <string>
#include <vector>

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
        std::string getFileListSimple();
        std::string getFileListVerbose();
        int getFileList(std::vector<std::string> &v);
        unsigned int getItemCount();
        std::string accessIndex(unsigned int i);
        int addFile(std::string path);
        int removeFile(unsigned int index, std::string &out);
        int importList(std::string src);
        int exportList(std::string dest);

    private:
        /*Ritual D-Bus stuff*/
        GDBusConnection *_gConn;
        static GMainLoop *_gLoop;
        RememberDaemon *_gProxy;

        static void *startGLoop(void *);

};
#endif