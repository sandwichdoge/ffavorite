#include "../gen/rememberd.h"
#include <vector>
#include <string>

#define TFMAN_DBUS "remember.service"
#define TFMAN_DBUS_PATH "/remember/service"



class rememberd
{
    public:
        rememberd();
        virtual ~rememberd();

        int init();
        static int uinit();


    private:
        /*Ritual D-Bus stuff*/
        static void name_acquired_cb(GDBusConnection *conn, const gchar *name, gpointer user_data);
        static void name_lost_cb(GDBusConnection *conn, const gchar *name, gpointer user_data);
        static void bus_acquired_cb(GDBusConnection *conn, const gchar *name, gpointer user_data);
        static void* startGLoop(void *args);

        static GMainLoop *_gLoop;
        static RememberDaemon *_gSkel;

        /*Callback handlers*/
        static gboolean list_cb(RememberDaemon *object, GDBusMethodInvocation *invocation);
        static gboolean list_fmt_cb(RememberDaemon *object, GDBusMethodInvocation *invocation);
        static gboolean total_cb(RememberDaemon *object, GDBusMethodInvocation *invocation);
        static gboolean access_cb(RememberDaemon *object, GDBusMethodInvocation *invocation, guint arg_index);
        static gboolean add_cb(RememberDaemon *object, GDBusMethodInvocation *invocation, const gchar *arg_filename);
        static gboolean rm_cb(RememberDaemon *object, GDBusMethodInvocation *invocation, unsigned index);
        static gboolean export_cb(RememberDaemon *object, GDBusMethodInvocation *invocation, const gchar *arg_dest);
        static gboolean import_cb(RememberDaemon *object, GDBusMethodInvocation *invocation, const gchar *arg_src);

        static std::vector<std::string> _storage; // Stack of saved file paths.

};