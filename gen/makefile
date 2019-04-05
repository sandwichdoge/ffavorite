APPNAME=rememberd

GIO_CFLAGS=-I/usr/include/gio-unix-2.0/ -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/      
GIO_LIBS=-L/usr/local/lib  -lgio-2.0 -lgobject-2.0 -lgmodule-2.0   -lglib-2.0 -lrt

all:
	/usr/bin/gdbus-codegen --interface org.remember --c-namespace RememberDaemon --generate-c-code $(APPNAME) $(APPNAME).xml
	gcc -c -fPIC $(GIO_CFLAGS) $(GIO_LIBS) $(APPNAME).c -o dbus$(APPNAME).o

clean:
	rm *.c *.h *.so *.o
