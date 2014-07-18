# SCALN
SCALN stands for System Call Abstraction Layer for Networking
and is a C++11 library for easy development of next generation networking
application with C99 bindings.

Internally this project was named KIARA Transport and is part of the FI-PPP FI-Ware Middleware project.

# License

TBD

# Requirements
* git
* cmake
* clang >= 3.4
* C++11 support
* std::thread support
* facultative: scons

## For Ubuntu minimal 14.04 copy&paste one-liner
`sudo apt-get install clang gcc git cmake libtool automake autoconf libjansson-dev uthash-dev && git clone https://github.com/zeromq/zeromq4-x.git && git clone git://github.com/jedisct1/libsodium.git && git clone git clone git://github.com/zeromq/libzmq.git && git clone git://github.com/zeromq/czmq.git && cd zeromq4-x && ./autogen.sh && ./configure && make check && sudo make install && sudo ldconfig && cd libsodium/ && ./autogen.sh && ./configure && make check && sudo make install && sudo ldconfig && cd ../libzmq && ./autogen.sh && ./configure && make check && sudo make install && sudo ldconfig && cd ../czmq && git checkout v2.0.2 && ./autogen.sh && ./configure && make check && sudo make install && sudo ldconfig && git clone https://github.com/icclab/kiara-transport.git && cd kiara-transport && make all`



# Dependencies
## ZeroMQ 4
Install https://github.com/zeromq/zeromq4-x
## czmq
Install https://github.com/zeromq/czmq
## libjansson
Either install it via your package manager or via http://www.digip.org/jansson/
## uthash
Either install it via your package manager or via https://troydhanson.github.io/uthash/

# Installation instructions
* checkout this repo

# Build instructions
* `make all` and if you don't want address sanitizer to run (e.g. when debugging) `make all ASAN=0`

or if you have scons installed

* `scons`

# Documentation
A doxyfile is available and the documentation can be built via `doxygen` and is found in `doc/html/index.html`

Also see doc/SCALN.md

## Tests, Demo, Examples

### Tests

Unfortunately no tests, unittests exist.

### Demo

* Build the demo files with `make demo` or `scons`
* Start in separate terminals `demo_broker`, `demo_reply` and `demo_subscriber`
* Point a HTTP REST client to localhost:5555 and send some arbitrary request, for instance `hello world` with HTTP PUT

### Examples
* Build the examples with `make examples` or `scons`
* Run the following pairs

  Client                   | Server
  ------------------------ | ----------------------
  client_0mq_http_nego     | server_0mq_http_nego
  client_0mq_http_pp       | server_0mq_http_pp
  client_0mq_http_pp_nego  | server_0mq_http_nego
  client_0mq_req_c         | server_0mq_rep_c
  client_0mq_req_pp        | server_0mq_rep_pp
  client_0mq_sub_c         | server_0mq_pub_c


# git
## Branches
* master: "stable" branch (owner: habl)
* infiniband: Support for infiniband, playground for infiniband applications (owner: brnr)
* dev: Integration branch, testing (owner: all)
* negotiation: Protocol and socket settings to negotiate with remote host (owner: aepp)
* refactor: Attempt to use std::string instead of std::vector<char> (owner: habl)
* sbengine: Support for scons (owner: rubinstein, was merged into master)
* tls: Support for encrypted connections (owner: aepp)
* zeromq-communication: Formerly used to integrate ZeroMQ support (owner: habl, was merged into master)

## Tags
* 0.3.2-beta - latest stable code base
* 0.4.0-alpha - integrated negotiation

## Rules
* Always comment your commits
* Keep the makefile up-to-date
* Project leader decides if your code is merged into master
* Don't commit directly on the master

# Authors
* Mathias Hablützel <habl@zhaw.ch>
* Philipp Aeschlimann <aepp@zhaw.ch>
* Sandro Brunner <brnr@zhaw.ch>
* Dmitri Rubinstein <rubinstein@cs.uni-saarland.de>
