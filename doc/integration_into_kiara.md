# Integration into KIARA

As SCALN is eventually part of KIARA some work was done to integrate the SCALN code into KIARA. The following steps are required to achieve a good integration:

* Stable and clean code
* Windows and Linux support
* Unlinking the APIs so that KIARA and SCALN can talk over the design API
* Integration of the SCALN stack
* Passing the unit tests

# Status

So far SCALN is not integrated into KIARA.

## Done

Meanwhile the master tree of SCALN is close to be stable enough that it can be integrated into KIARA. There are though still a lot of memory leaks that inhibit to bump the codes status to stable. The other features like negotiation and infiniband require further work before they can be merged into the master branch of SCALN.

Linux and OS X are fully supported, but for Windows there are some problems especially with the usage of `std::thread` which is not supported so far even though standardized in C++11 and supported by the MSVC++ compiler.

The API in KIARA has been unlinked to the stage that it does not pass around `io_service` objects anymore but opaque handler.

## Todo

So far the SCALN stack itself is not integrated yet and requires to rewrite some code in KIARA to actually use the defined API of the SCALN library.