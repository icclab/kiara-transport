# Architecture
## Language
C++11 (without GNU or clang or MSVC extensions)
## Diagram
Where does my code come into play in Dmitris KIARA diagram
## UML diagram for API
Function signatures/declaration

| Setup     | Teardown   |
|-----------|------------|
| init      | destroy    |
| bind      | unbind     |
| connect   | disconnect |
| send      | recv       |

## Function outline with (prosa) description
Non-Coder readable description of what the functions do or have to implement

### init
Setup the context and transport stack

`init` requires a valid handler to an implementation of the transport class.

The `init` shall return a reference to an opaque context object and a null-pointer on failure

The implementation may call the negotiation routine and use it's results to configure the current network stack.

A context contains a set of socket handlers which will be added by binding or connecting respectively removed by unbinding or disconnecting.

### destroy
Destroy the context and transport stack

`destroy` requires a reference to a context object, the context object shall be deallocated by the function itself.

The `destroy` shall return zero on success and non-zero on failure.

The sockets in the context object are force closed and the context object destroyed under any circumstances. 

### bind
Bind the server socket and wait for incomming connection

`bind` requires a valid construct containing a local endpoint description according to its transport stack and a callback thread handle which will be called when a incomming connection arrives.

The `bind` shall return a handle to the socket and null or 0 on failure.

A valid local endpoint description may look like "tcp://*:1234" or "dds://*:6666". This function must only add the handle to the context on success.

### unbind
Stop listening to the server socket and close the active connections

`unbind` requires a handle to close the listening socket.

The `unbind` shall return 0 on success and non-zero on failure.

This function must only remove the handle from the context on success.

### connect
Connect the client to a remote server

`connect` requires a valid remote endpoint description according to its transport stack.

The `connect` shall return a handle to the connection and null or 0 on failure.

A valid remote endpoint may look like "tcp://192.168.1.1:1234" or "dds://foobar.tld:6666". This function must only add the handle to context on success.

### disconnect
Disconnect the client from the remote server

`disconnect` requires a valid handle to close the connection.

The `disconnect` shall return 0 on success and non-zero on failure.

This function must only remove the handle from the context on success.

### send
Send data to the remote host

`send` requires a vector of data (payload and size of every payload).

!!!! NEEDS A WAY TO KNOW THE DESTINATOR !!!!

### recv
Receive data from the remote host

## nota bene

* connection init returns a connection configuration (discovery of remote participant if KIARA or something else and negotiation of transport protocols)
* open connection/connect
* callbacks (hooks) for Dmitri
* synchronous and asynchronous calls (blocking, non-blocking, lingering)
* fetching IDL files

# Use Case
Description of the use of the library
## Sequence diagram
Example of how things works

# Roadmap
## What has been done
* First design done
* First implementation done

## Future
1. Dates (to be determined)
2. RFC-like protocol description (contract)
3. Full negotiation for KIARA-to-KIARA services (JSEP, see `aepp`)
4. QoS settings (and calibration)
5. Extensive tests (every feature is not pushed before a test exists)
6. Multithreading, dispatching

# Problems
## Multithreading
Pool of threads? Spawning threads? Which spawning algorithms?