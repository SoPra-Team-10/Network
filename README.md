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
In the root directory of the project run
```
sudo make install
```
the library can now be included using

```
#include <SopraNetwork/XY>
```

and linked using

```
-lSopraNetwork
```
