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

# Dependencies
## ZeroMQ 4
Install https://github.com/zeromq/zeromq4-x
## czmq
Install https://github.com/zeromq/czmq

# Installation instructions
* checkout this repo

# Build instructions
* `make all` and if you don't want address sanitizer to run (e.g. when debugging) `make all ASAN=0`

or if you have scons installed

* `scons`

# Documentation
A doxyfile is available and the documentation can be built via `doxygen` and is found in `doc/html/index.html`

Also see doc/SCALN.md

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
