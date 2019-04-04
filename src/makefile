INCL_DBUS=-I/usr/include/gio-unix-2.0/ -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/      
LIBS_DBUS=-L/usr/local/lib -lgio-2.0 -lgobject-2.0 -lgmodule-2.0 -lglib-2.0 -pthread -L./gen -lmyex


all: main.cpp rememberd.o
	g++ $^ $(INCL_DBUS) $(LIBS_DBUS) ../gen/dbusrememberd.o -o rememberd

rememberd.o: rememberd.cpp rememberd.h
	g++ -c $^ $(INCL_DBUS) $(LIBS_DBUS)

clean:
	rm *.out *.o *.gch

install:
	ln -sf $(shell pwd)/rememberd /usr/sbin/
	cp -vf remember.service /lib/systemd/system
	ln -sf /lib/systemd/system/remember.service /usr/lib/systemd/user/remember.service
	ln -sf /lib/systemd/system/remember.service /etc/systemd/user/default.target.wants/remember.service
	systemctl --user enable remember.service
