#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include "rememberd.h"
#include <errno.h>

RememberDaemon *rememberd::_gSkel = NULL;
GMainLoop *rememberd:: _gLoop = NULL;
std::vector<std::string> rememberd::_storage;

rememberd::rememberd() {};
rememberd::~rememberd() {};


int rememberd::uinit()
{
    g_main_loop_quit(_gLoop);
    g_main_loop_unref(_gLoop);
    _gLoop = NULL;

    return 0;
}

int rememberd::init()
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

    _storage.push_back("NoneHere");

    return 0;
}

void rememberd::name_lost_cb(GDBusConnection *conn, const gchar *name, gpointer user_data)
{

}

void rememberd::bus_acquired_cb(GDBusConnection *conn, const gchar *name, gpointer user_data)
{
    GError *err = NULL;

    _gSkel = remember_daemon__skeleton_new();
    _gSkel = remember_daemon__skeleton_new();

    g_signal_connect(_gSkel, "handle-list", G_CALLBACK(list_cb), NULL);
    g_signal_connect(_gSkel, "handle-list-fmt", G_CALLBACK(list_fmt_cb), NULL);
    g_signal_connect(_gSkel, "handle-total", G_CALLBACK(total_cb), NULL);
    g_signal_connect(_gSkel, "handle-access", G_CALLBACK(access_cb), NULL);
    g_signal_connect(_gSkel, "handle-add", G_CALLBACK(add_cb), NULL);
    g_signal_connect(_gSkel, "handle-rm", G_CALLBACK(rm_cb), NULL);

    g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(_gSkel), conn, TFMAN_DBUS_PATH, &err);

    if (err != NULL) {
        g_print("Problem exporting skel %s.", err->message);
        g_error_free(err);
        g_main_loop_quit(_gLoop);
    }


    g_print("Exported skeleton.\n");
}

void* rememberd::startGLoop(void *args)
{
	g_main_loop_run(_gLoop);
	return NULL;
}

void rememberd::name_acquired_cb(GDBusConnection *conn, const gchar *name, gpointer user_data)
{
    g_print("Name acquired.\n");
}


gboolean rememberd::list_cb(RememberDaemon *object, GDBusMethodInvocation *invocation)
{
    const char** container = new const char*[_storage.size() + 1];

    for (int i = 0; i < _storage.size(); i++) {
        container[i] = _storage[i].c_str();
    }
    container[_storage.size()] = NULL; // All dbus arrays are null terminated.

    remember_daemon__complete_list(object, invocation, container);
    
    delete[] container;

    return TRUE;
}


gboolean rememberd::list_fmt_cb(RememberDaemon *object, GDBusMethodInvocation *invocation)
{
    g_print("Sending formatted file list.\n");
    
    std::string s = "";

    for (int i = 0; i < _storage.size(); i++) {
        s += std::to_string(i) + "." + _storage[i] + "\n";
    }

    remember_daemon__complete_list_fmt(object, invocation, s.c_str());

    return TRUE;
}


gboolean rememberd::total_cb(RememberDaemon *object, GDBusMethodInvocation *invocation)
{
    unsigned int count = _storage.size();
    g_print("coutn [%d]\n", count);
    remember_daemon__complete_total(object, invocation, count);

    return TRUE;
}


gboolean rememberd::access_cb(RememberDaemon *object, GDBusMethodInvocation *invocation, guint arg_index)
{
    //g_print("Sending item %d.\n", arg_index);

    std::string result = "";

    if (arg_index < _storage.size())
    {
        result = _storage[arg_index];
    }
    else
    {
        g_print("Index exceeds number of stored items.");
        result = "INDEX_ERROR";
    }

    remember_daemon__complete_access(object, invocation, result.c_str());

    return TRUE;
}



gboolean rememberd::add_cb(RememberDaemon *object, GDBusMethodInvocation *invocation, const gchar *arg_filename)
{
    std::string file = std::string(arg_filename);
    _storage.push_back(file);

    remember_daemon__complete_add(object, invocation);

    return TRUE;
}


gboolean rememberd::rm_cb(RememberDaemon *object, GDBusMethodInvocation *invocation, unsigned arg_index)
{
    if (arg_index >= _storage.size()) return FALSE;

    std::string target = _storage[arg_index];

    _storage.erase(_storage.begin() + arg_index);

    remember_daemon__complete_rm(object, invocation, target.c_str());

    return TRUE;
}

