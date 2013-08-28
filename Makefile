#### Compiler and tool definitions shared by all build targets #####
CC = gcc
# CC = clang
BASICOPTS = -g
CFLAGS = $(BASICOPTS)


# Define the target directories.
BUILDDIR=GNU-x86_64-MACOSX
# BUILDDIR=LLVM-x86_64-MACOSX
# BUILDDIR=GNU-x86_64-LINUX
# BUILDDIR=LLVM-x86_64-LINUX


all: server_http server_0mq client_0mq
server_http: $(BUILDDIR)/server_http
server_0mq: $(BUILDDIR)/server_0mq
client_0mq: $(BUILDDIR)/client_0mq

## Target: server_http
OBJS_server_http =  \
	$(BUILDDIR)/main_server_http.o \
	$(BUILDDIR)/ktransport.o \
	$(BUILDDIR)/kt_server.o
USERLIBS_server_http = -lzmq -lczmq
DEPLIBS_server_http =
LDLIBS_server_http = $(USERLIBS_server_http)

## Target: server_0mq
OBJS_server_0mq =  \
	$(BUILDDIR)/main_server_0mq.o \
	$(BUILDDIR)/ktransport.o \
	$(BUILDDIR)/kt_server.o
USERLIBS_server_0mq = -lzmq -lczmq
DEPLIBS_server_0mq =
LDLIBS_server_0mq = $(USERLIBS_server_0mq)

## Target: client_0mq
OBJS_client_0mq =  \
	$(BUILDDIR)/main_client_0mq.o \
	$(BUILDDIR)/ktransport.o \
	$(BUILDDIR)/kt_client.o
USERLIBS_client_0mq = -lzmq -lczmq
DEPLIBS_client_0mq =
LDLIBS_client_0mq = $(USERLIBS_client_0mq)




# Link or archive
$(BUILDDIR)/server_http: $(BUILDDIR) $(OBJS_server_http) $(DEPLIBS_server_http)
	$(LINK.c) $(CFLAGS_server_http) $(CPPFLAGS_server_http) -o $@ $(OBJS_server_http) $(LDLIBS_server_http)

# Link or archive
$(BUILDDIR)/server_0mq: $(BUILDDIR) $(OBJS_server_0mq) $(DEPLIBS_server_0mq)
	$(LINK.c) $(CFLAGS_server_0mq) $(CPPFLAGS_server_0mq) -o $@ $(OBJS_server_0mq) $(LDLIBS_server_0mq)

# Link or archive
$(BUILDDIR)/client_0mq: $(BUILDDIR) $(OBJS_client_0mq) $(DEPLIBS_client_0mq)
	$(LINK.c) $(CFLAGS_client_0mq) $(CPPFLAGS_client_0mq) -o $@ $(OBJS_client_0mq) $(LDLIBS_client_0mq)




# Compile source files into .o files
$(BUILDDIR)/ktransport.o: $(BUILDDIR) src/core/ktransport.c
	$(COMPILE.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ src/core/ktransport.c

$(BUILDDIR)/kt_server.o: $(BUILDDIR) src/core/kt_server.c
	$(COMPILE.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ src/core/kt_server.c

$(BUILDDIR)/kt_client.o: $(BUILDDIR) src/core/kt_client.c
	$(COMPILE.c) $(CFLAGS_client) $(CPPFLAGS_client) -o $@ src/core/kt_client.c

$(BUILDDIR)/main_server_http.o: $(BUILDDIR) src/examples/main_server_http.c
	$(COMPILE.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ src/examples/main_server_http.c

$(BUILDDIR)/main_server_0mq.o: $(BUILDDIR) src/examples/main_server_0mq.c
	$(COMPILE.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ src/examples/main_server_0mq.c
	
$(BUILDDIR)/main_client_0mq.o: $(BUILDDIR) src/examples/main_client_0mq.c
	$(COMPILE.c) $(CFLAGS_client) $(CPPFLAGS_client) -o $@ src/examples/main_client_0mq.c


#### Clean target deletes all generated files ####
clean:
	rm -f -r $(BUILDDIR)


# Create the target directory (if needed)
$(BUILDDIR):
	mkdir -p $(BUILDDIR)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU_x86_64_MACOSX

