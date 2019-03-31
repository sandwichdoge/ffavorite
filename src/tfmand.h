#include "gen/tfmand.h"
#include <vector>
#include <string>

#define TFMAN_DBUS "tfman.service"
#define TFMAN_DBUS_PATH "/tfman/service"



class tfmand
{
    public:
        tfmand();
        virtual ~tfmand();

        int init();
        static int uinit();


    private:
        /*Ritual D-Bus stuff*/
        static void name_acquired_cb(GDBusConnection *conn, const gchar *name, gpointer user_data);
        static void name_lost_cb(GDBusConnection *conn, const gchar *name, gpointer user_data);
        static void bus_acquired_cb(GDBusConnection *conn, const gchar *name, gpointer user_data);
        static void* startGLoop(void *args);

        static GMainLoop *_gLoop;
        static TerminalFileManager *_gSkel ;

        /*Actual data*/
        static gboolean list_files(TerminalFileManager *object, GDBusMethodInvocation *invocation);
        static gboolean add_file(TerminalFileManager *object, GDBusMethodInvocation *invocation, const gchar *arg_filename);
        
        static std::vector<std::string> _files; // Stack of saved file paths.

};