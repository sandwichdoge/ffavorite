#include "tfmanctl.h"
#include <iostream>


GMainLoop *client::_gLoop = NULL;


client::client()
{
}

client::~client() {}

int client::init()
{
    GError *err = NULL;

	_gConn = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, &err);
	if (err) g_print("Error %s\n", err->message);

	_gLoop = g_main_loop_new(NULL, FALSE);

    

	_gProxy = remember_daemon__proxy_new_sync(_gConn,
							G_DBUS_PROXY_FLAGS_NONE,
							TFMAN_DBUS,
							TFMAN_DBUS_PATH,
							NULL, &err);
	if (err) {
		g_print("Error %s\n", err->message);
		g_error_free(err);
		uinit();
	}

	// Register callback function to handle mysignal received from server
	//g_signal_connect(_proxy, "mysignal", G_CALLBACK(handle_mysignal), NULL);

	g_print("Initialized.\n");
}

int client::uinit()
{
    g_main_loop_quit(_gLoop);
    g_main_loop_unref(_gLoop);
    _gLoop = NULL;
    
    return 0;
}


std::string client::getFormattedFileList()
{
    GError *err = NULL;
    char *out = NULL;

    remember_daemon__call_list_fmt_sync(_gProxy, &out, NULL, &err);
    if (err) {
        g_print("%s\n", err->message);
        return "";
    }

    return std::string(out);
}


int client::getFileList(std::vector<std::string> &v)
{
    GError *err = NULL;
    char **out = NULL;

    v.clear();

    remember_daemon__call_list_sync(_gProxy, &out, NULL, &err);
    if (err || out == NULL) return -1;

    for (int i = 0; out[i]; i++) {
        v.push_back(std::string(out[i]));
    }

    return 0;
}


int client::addFile(std::string path)
{
    GError *err = NULL;
    
    remember_daemon__call_add_sync(_gProxy, path.c_str(), NULL, &err);
    if (err) {
        g_print("%s\n", err->message);
        return -1;
    }

    return 0;
}


int client::removeFile(std::string path)
{
    GError *err = NULL;

    remember_daemon__call_rm_sync(_gProxy, path.c_str(), NULL, &err);
    if (err) {
        g_print("%s\n", err->message);
        return -1;
    }

    return 0;
}