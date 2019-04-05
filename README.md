# ffavorite
Save files to favorite list from the shell.


# The backend

Is a string storing daemon, communicating via d-bus.

It only remembers strings, you can request it to remember or forget some strings, or show
all remembered strings, that's it.


# The frontend

Command line file manager.

Does most of the heavy lifting.

You can cd into a directory, tell it to remember a few files. Then cd to another directory and decide what to do
with the stored files (e.g. copy/move the stored files to the new directory).


# Dependencies

libglib2.0-dev

# Build
```
$git clone git@github.com:sandwichdoge/ffavorite.git
$cd ffavorite
$make
$sudo make install
```

# Run daemon
```
$cd ffavorite/src
$./rememberd &
```

# Run client
```
$cd ffavorite/client
$./rem -h
```
