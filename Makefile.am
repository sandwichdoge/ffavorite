bin_PROGRAMS = rememberd rem

APPNAME = rememberd


all: dbus_gen

dbus_gen: gen/rememberd.xml
	/usr/bin/gdbus-codegen --interface-prefix org.remember --c-namespace RememberDaemon --generate-c-code gen/$(APPNAME) gen/$(APPNAME).xml

rememberd_DEPENDENCIES = libdbusrememberd.la dbus_gen
rememberd_SOURCES = src/main.cpp src/rememberd.cpp src/rememberd.h
rememberd_CPPFLAGS = -I/usr/include/gio-unix-2.0/ -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/
rememberd_LDADD = -L./gen -ldbusrememberd -L/usr/local/lib -lgio-2.0 -lgobject-2.0 -lgmodule-2.0 -lglib-2.0
rememberd_LDFLAGS = -pthread


rem_DEPENDENCIES = libdbusrememberd.la dbus_gen
rem_SOURCES = client/main.cpp client/dbus_interface.cpp client/dbus_interface.h client/controller.cpp client/controller.h
rem_CPPFLAGS = -I/usr/include/gio-unix-2.0/ -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/
rem_LDADD = -L./gen -ldbusrememberd -L/usr/local/lib -lgio-2.0 -lgobject-2.0 -lgmodule-2.0 -lglib-2.0 -L./CommonCPP/StringUtils/ -lstrutils
rem_LDFLAGS = -pthread


lib_LTLIBRARIES = libdbusrememberd.la
libdbusrememberd_la_DEPENDENCIES = dbus_gen gen/$(APPNAME).c gen/$(APPNAME).h
libdbusrememberd_la_SOURCES = gen/$(APPNAME).c gen/$(APPNAME).h
libdbusrememberd_la_LIBDADD = -L/usr/local/lib  -lgio-2.0 -lgobject-2.0 -lgmodule-2.0   -lglib-2.0 -lrt
libdbusrememberd_la_CPPFLAGS = -I/usr/include/gio-unix-2.0/ -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -c -fPIC -shared
