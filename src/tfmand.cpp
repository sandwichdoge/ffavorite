#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include "tfmand.h"
#include <errno.h>


GMainLoop *tfmand:: _gLoop = NULL;
TerminalFileManager *tfmand::_gSkel = NULL;
std::vector<std::string> tfmand::_files;


tfmand::tfmand() {};
tfmand::~tfmand() {};


int tfmand::uinit()
{

}

int tfmand::init()
{
    g_bus_own_name(G_BUS_TYPE_SESSION,
                    TFMAN_DBUS,
                    G_BUS_NAME_OWNER_FLAGS_NONE, 
                    &bus_acquired_cb, &name_acquired_cb, &name_lost_cb,
                    NULL, NULL);
    
    _gLoop = g_main_loop_new(NULL, FALSE);

    pthread_t thread1;
	int perr = pthread_create(&thread1, NULL, startGLoop, (void*)NULL);
	if (perr) {
		g_print("pthread creation error.\n");
		uinit();
	}
    
    g_print("Owned bus name.\n");

    _files.push_back("None");

    return 0;
}

void tfmand::name_lost_cb(GDBusConnection *conn, const gchar *name, gpointer user_data)
{

}

void tfmand::bus_acquired_cb(GDBusConnection *conn, const gchar *name, gpointer user_data)
{
    GError *err = NULL;

    _gSkel = terminal_file_manager__skeleton_new();

    g_signal_connect(_gSkel, "handle-list", G_CALLBACK(list_files), NULL);
    g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(_gSkel), conn, TFMAN_DBUS_PATH, &err);

    if (err != NULL) {
        g_print("Problem exporting skel %s.", err->message);
        g_main_loop_quit(_gLoop);
    }


    g_print("Exported skeleton.\n");
}

void* tfmand::startGLoop(void *args)
{
    g_print("Startin gloop.\n");
	g_main_loop_run(_gLoop);
	return NULL;
}

void tfmand::name_acquired_cb(GDBusConnection *conn, const gchar *name, gpointer user_data)
{
    g_print("Name acquired.\n");
}


gboolean tfmand::list_files(TerminalFileManager *object, GDBusMethodInvocation *invocation)
{
    std::string s = "";

    for (int i = 0; i < _files.size(); i++) {
        s += std::to_string(i) + "." + _files[i];
    }

    terminal_file_manager__complete_list(object, invocation, s.c_str());
}


int main()
{
    tfmand *p = new tfmand();
    
    p->init();
    sleep(50);
    return 0;
}