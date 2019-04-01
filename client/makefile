INCL_DBUS=-I/usr/include/gio-unix-2.0/ -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/      
LIBS_DBUS=-L/usr/local/lib -lgio-2.0 -lgobject-2.0 -lgmodule-2.0 -lglib-2.0 -pthread -L./gen -lmyex


all: tfmanctl.o main.cpp
	g++ $^ ../gen/librememberd.so $(INCL_DBUS) $(LIBS_DBUS) -o tfmanctl

tfmanctl.o: tfmanctl.cpp tfmanctl.h
	g++ -c $^ $(INCL_DBUS) $(LIBS_DBUS)

clean:
	rm *.out *.o *.gch tfmanctl