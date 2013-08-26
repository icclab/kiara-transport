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


all: server client
server: $(BUILDDIR)/server
client: $(BUILDDIR)/client

## Target: server
OBJS_server =  \
	$(BUILDDIR)/ktransport.o \
	$(BUILDDIR)/main_server.o \
	$(BUILDDIR)/kt_server.o
USERLIBS_server = -lzmq -lczmq
DEPLIBS_server =
LDLIBS_server = $(USERLIBS_server)

## Target: client
OBJS_client =  \
	$(BUILDDIR)/main_client.o \
	$(BUILDDIR)/ktransport.o \
	$(BUILDDIR)/kt_client.o
USERLIBS_client = -lzmq -lczmq
DEPLIBS_client =
LDLIBS_client = $(USERLIBS_client)

# Link or archive
$(BUILDDIR)/server: $(BUILDDIR) $(OBJS_server) $(DEPLIBS_server)
	$(LINK.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ $(OBJS_server) $(LDLIBS_server)

# Link or archive
$(BUILDDIR)/client: $(BUILDDIR) $(OBJS_client) $(DEPLIBS_client)
	$(LINK.c) $(CFLAGS_client) $(CPPFLAGS_client) -o $@ $(OBJS_client) $(LDLIBS_client)

# Compile source files into .o files
$(BUILDDIR)/ktransport.o: $(BUILDDIR) src/core/ktransport.c
	$(COMPILE.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ src/core/ktransport.c

$(BUILDDIR)/kt_server.o: $(BUILDDIR) src/core/kt_server.c
	$(COMPILE.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ src/core/kt_server.c

$(BUILDDIR)/kt_client.o: $(BUILDDIR) src/core/kt_client.c
	$(COMPILE.c) $(CFLAGS_client) $(CPPFLAGS_client) -o $@ src/core/kt_client.c

$(BUILDDIR)/main_server.o: $(BUILDDIR) src/examples/main_server.c
	$(COMPILE.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ src/examples/main_server.c
	
$(BUILDDIR)/main_client.o: $(BUILDDIR) src/examples/main_client.c
	$(COMPILE.c) $(CFLAGS_client) $(CPPFLAGS_client) -o $@ src/examples/main_client.c


#### Clean target deletes all generated files ####
clean:
	rm -f -r $(BUILDDIR)


# Create the target directory (if needed)
$(BUILDDIR):
	mkdir -p $(BUILDDIR)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU_x86_64_MACOSX

