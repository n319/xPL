xPL Hal (lite)
==============

The goal of this project is to get an xPL HAL server running on an embedded ARM device, such as a linux-based router or a NAS. To this end, this code is written in C++ and compiles with GCC. Additionally, to make the code portable, it uses the POCO libraries, as they should be cross platform.

Currently, it's semi-working. In the least, it supports the most common parts of the determinator spec, and the needed parts of XHCP. You should be able to talk to it using the Windows XHCP client, or using telnet. For more info, check the recent changelog.

What is xPL / an xPLHAL server?
-------------------------------
xPL is a home automation protocol that is medium independent, but almost all of the software using it does do with the xPL messages delivered over UDP packets. For example, I have a desk lamp that sends packets containing xPL messages when it's front buttons are pressed, and changes brightness when the right xPL messages are received.

An xPLHAL server is the 'brains' of an xPL network, providing a central place on a network to manage device configuraion, simple rules (called 'determinators'), and more complex scripting. In the example with a desk lamp, it is what might connect the bottom button on a panel with the action of turning off a lamp.

Usage
=====
First off, you'll need the POCO libraries, which are almost certianly packaged for whatever system you're on. On debian-based systems, try:
```
sudo apt-get install libpoco-dev
```

When fetching, remember to fetch the xPLsdk submodule using either:
```bash
git clone --recursive <this repo>
cd xPL
```
or
```bash
git clone <this repo>
git submodule update --init
```

To build, use cmake:
```bash
mkdir build
cd build
cmake ../src
make
``` 

Then try the executable with:
```bash
./xplhallite
```
Remember that if you ever run cmake from the /src directory, it will dump some files in /src (like CMakeCache.txt) that cause future builds to be there too.

Also keep in mind that you'll want an xPL hub, like the one included as a demo with the xPL4Linux C library. If you're not on i386, you'll need to recompile it.
http://www.xpl4java.org/xPL4Linux/

When run, the server will keep it's data in ~/.xPL/xplhallite, including the xml determinators.

Useful Links
------------
XPL_Message_Schemas
http://xplproject.org.uk/wiki/index.php?title=XPL_Message_Schema
