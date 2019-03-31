#What

Example of remote method call using glib dbus.

Client will send request to call addOne() on server, server adds 1 to param then return value.

#Dependencies

libglib2.0-dev

#How to build
```
cd gen
make
cd ..
make
```

#How to run
```
./sv.out
./cl.out
```
