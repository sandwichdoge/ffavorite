#include "tfmanctl.h"

GMainLoop *_gLoop = NULL;

client::client()
{
    _gConn = NULL;
    _gProxy = NULL;
}

client::~client() {}

client::init()
{
    GError *err = NULL;

	_gConn = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, &err);
	if (err) g_print("Error %s\n", err->message);

	_gLoop = g_main_loop_new(NULL, FALSE);

	_proxy = terminal_file_manager__proxy_new_sync(_gConn,
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
	g_signal_connect(_proxy, "mysignal", G_CALLBACK(handle_mysignal), NULL);

	g_print("Initialized.\n");
}

client::uinit()
{
    g_main_loop_quit(_gLoop);
    g_main_loop_unref(_gLoop);
    _gLoop = NULL;
    
    return 0;
}