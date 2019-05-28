[![Build Status](https://travis-ci.org/SoPra-Team-10/Network.svg?branch=master)](https://travis-ci.org/SoPra-Team-10/Network)
# Network
The C++ Websockets component.

## Overview
The complete interface is similar to the Java-TCP Interface.
One major difference is that all communication is managed asynchronous
using callback-functors.

### Client
Only one class, `network::WebSocketClient`. Create one per connection.

### Server
For every server create an instance of `network::WebSocketServer`
for every connected client, this will create 
a new `network:Connection`.

### Utility
The `Listener<Args...>` class implements a generic message system 
with arbitrary many receivers and usually one sender
`Args...` specifies the type of message. Clients can
subscribe by calling `Listener::operator()`, the sender can send
a message by calling the same operator with the argument types
as specified by `Args...`.

## Installing
### Libwebsockets
First you need to install libssl, on ubuntu this can be done by running

```
sudo apt install libssl-dev
```
next clone libwebsockets from GitHub by running

```
git clone https://github.com/warmcat/libwebsockets.git
```

change into the cloned directory (`cd libwebsockets`) and create the Makefile by running:

```
cmake .
```

next compile the project by running the makefile

```
make
```

finally install the library by running

```
sudo make install
```

To be able to use the library without rebooting reload the linker cache by running

```
sudo ldconfig
```

### Installing SopraNetwork
In the root directory of the  project run cmake to generate a Makefile by running
```
cmake .
```
next compile the program by running
```
make
```
finally install the program by running
```
sudo make install
```
the library can now be included using

```
#include <SopraNetwork/Filename>
```
with `Filename` beeing one of the header files without their relative path.

and linked using

```
-lSopraNetwork
```

## SonarQube Analyse
Das Analyseergebniss von SonarQube ist [hier auf SonarCloud](https://sonarcloud.io/dashboard?id=SoPra-Team-10_Network) zu finden.