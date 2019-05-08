#! /bin/sh

if [ -z "$ONLINE_MAIN" ] ; then
    echo "You must define ONLINE_MAIN to point to the install area."
    echo "  .e.g. export ONLINE_MAIN=$HOME/desmond/daq/install"
    exit 1
fi
ONLINE_MAIN=/home/phnxrc/desmond/daq/rcdaq/rcdaq/install; export ONLINE_MAIN
OS_VER=`uname -r`; export OS_VER
OSNAME=Linux.$OS_VER;export OSNAME
INSTALL_DIR=/export/software/$OSNAME
./autogen.sh --prefix=/home/phnxrc/desmond/daq/rcdaq/rcdaq/install
#make install
