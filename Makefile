## -*- Makefile -*-
##
## User: aepp
## Time: 12.08.2013 15:11:01
## Makefile created by Oracle Solaris Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = gcc
BASICOPTS = -g
CFLAGS = $(BASICOPTS)


# Define the target directories.
TARGETDIR_main=GNU-amd64-Linux
TARGETDIR_server=GNU-amd64-Linux
TARGETDIR_client=GNU-amd64-Linux


all: $(TARGETDIR_main)/main $(TARGETDIR_server)/server $(TARGETDIR_client)/client

## Target: main
OBJS_main =  \
	$(TARGETDIR_main)/main.o \
	$(TARGETDIR_main)/ktransport.o \
	$(TARGETDIR_main)/client.o \
	$(TARGETDIR_main)/http_parser.o \
	$(TARGETDIR_main)/http.o \
	$(TARGETDIR_main)/kt_server.o
USERLIBS_main = $(SYSLIBS_main) -lzmq -lczmq
DEPLIBS_main =
LDLIBS_main = $(USERLIBS_main)


# Link or archive
$(TARGETDIR_main)/main: $(TARGETDIR_main) $(OBJS_main) $(DEPLIBS_main)
	$(LINK.c) $(CFLAGS_main) $(CPPFLAGS_main) -o $@ $(OBJS_main) $(LDLIBS_main)


# Compile source files into .o files
$(TARGETDIR_main)/main.o: $(TARGETDIR_main) main.c
	$(COMPILE.c) $(CFLAGS_main) $(CPPFLAGS_main) -o $@ main.c

$(TARGETDIR_main)/ktransport.o: $(TARGETDIR_main) ktransport.c
	$(COMPILE.c) $(CFLAGS_main) $(CPPFLAGS_main) -o $@ ktransport.c

$(TARGETDIR_main)/client.o: $(TARGETDIR_main) client.c
	$(COMPILE.c) $(CFLAGS_main) $(CPPFLAGS_main) -o $@ client.c

$(TARGETDIR_main)/http_parser.o: $(TARGETDIR_main) http_parser.c
	$(COMPILE.c) $(CFLAGS_main) $(CPPFLAGS_main) -o $@ http_parser.c

$(TARGETDIR_main)/http.o: $(TARGETDIR_main) http.c
	$(COMPILE.c) $(CFLAGS_main) $(CPPFLAGS_main) -o $@ http.c

$(TARGETDIR_main)/kt_server.o: $(TARGETDIR_main) kt_server.c
	$(COMPILE.c) $(CFLAGS_main) $(CPPFLAGS_main) -o $@ kt_server.c



## Target: server
OBJS_server =  \
	$(TARGETDIR_server)/ktransport.o \
	$(TARGETDIR_server)/client.o \
	$(TARGETDIR_server)/http_parser.o \
	$(TARGETDIR_server)/http.o \
	$(TARGETDIR_server)/main_server.o \
	$(TARGETDIR_server)/kt_server.o
USERLIBS_server = $(SYSLIBS_server) -lzmq -lczmq
DEPLIBS_server =
LDLIBS_server = $(USERLIBS_server)


# Link or archive
$(TARGETDIR_server)/server: $(TARGETDIR_server) $(OBJS_server) $(DEPLIBS_server)
	$(LINK.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ $(OBJS_server) $(LDLIBS_server)


# Compile source files into .o files
$(TARGETDIR_server)/ktransport.o: $(TARGETDIR_server) ktransport.c
	$(COMPILE.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ ktransport.c

$(TARGETDIR_server)/client.o: $(TARGETDIR_server) client.c
	$(COMPILE.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ client.c

$(TARGETDIR_server)/http_parser.o: $(TARGETDIR_server) http_parser.c
	$(COMPILE.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ http_parser.c

$(TARGETDIR_server)/http.o: $(TARGETDIR_server) http.c
	$(COMPILE.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ http.c

$(TARGETDIR_server)/main_server.o: $(TARGETDIR_server) main_server.c
	$(COMPILE.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ main_server.c

$(TARGETDIR_server)/kt_server.o: $(TARGETDIR_server) kt_server.c
	$(COMPILE.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ kt_server.c



## Target: client
OBJS_client =  \
	$(TARGETDIR_client)/main_client.o \
	$(TARGETDIR_client)/ktransport.o \
	$(TARGETDIR_client)/client.o \
	$(TARGETDIR_client)/http_parser.o \
	$(TARGETDIR_client)/http.o \
	$(TARGETDIR_client)/kt_server.o
USERLIBS_client = $(SYSLIBS_client) -lzmq -lczmq
DEPLIBS_client =
LDLIBS_client = $(USERLIBS_client)


# Link or archive
$(TARGETDIR_client)/client: $(TARGETDIR_client) $(OBJS_client) $(DEPLIBS_client)
	$(LINK.c) $(CFLAGS_client) $(CPPFLAGS_client) -o $@ $(OBJS_client) $(LDLIBS_client)


# Compile source files into .o files

$(TARGETDIR_client)/main_client.o: $(TARGETDIR_client) main_client.c
	$(COMPILE.c) $(CFLAGS_client) $(CPPFLAGS_client) -o $@ main_client.c

$(TARGETDIR_client)/ktransport.o: $(TARGETDIR_client) ktransport.c
	$(COMPILE.c) $(CFLAGS_client) $(CPPFLAGS_client) -o $@ ktransport.c

$(TARGETDIR_client)/client.o: $(TARGETDIR_client) client.c
	$(COMPILE.c) $(CFLAGS_client) $(CPPFLAGS_client) -o $@ client.c

$(TARGETDIR_client)/http_parser.o: $(TARGETDIR_client) http_parser.c
	$(COMPILE.c) $(CFLAGS_client) $(CPPFLAGS_client) -o $@ http_parser.c

$(TARGETDIR_client)/http.o: $(TARGETDIR_client) http.c
	$(COMPILE.c) $(CFLAGS_client) $(CPPFLAGS_client) -o $@ http.c

$(TARGETDIR_client)/kt_server.o: $(TARGETDIR_client) kt_server.c
	$(COMPILE.c) $(CFLAGS_client) $(CPPFLAGS_client) -o $@ kt_server.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_main)/main \
		$(TARGETDIR_main)/main.o \
		$(TARGETDIR_main)/ktransport.o \
		$(TARGETDIR_main)/client.o \
		$(TARGETDIR_main)/http_parser.o \
		$(TARGETDIR_main)/http.o \
		$(TARGETDIR_main)/kt_server.o \
		$(TARGETDIR_server)/server \
		$(TARGETDIR_server)/ktransport.o \
		$(TARGETDIR_server)/client.o \
		$(TARGETDIR_server)/http_parser.o \
		$(TARGETDIR_server)/http.o \
		$(TARGETDIR_server)/main_server.o \
		$(TARGETDIR_server)/kt_server.o \
		$(TARGETDIR_client)/client \
		$(TARGETDIR_client)/main.o \
		$(TARGETDIR_client)/main_client.o \
		$(TARGETDIR_client)/ktransport.o \
		$(TARGETDIR_client)/client.o \
		$(TARGETDIR_client)/http_parser.o \
		$(TARGETDIR_client)/http.o \
		$(TARGETDIR_client)/kt_server.o
	rm -f -r $(TARGETDIR_server)
	rm -f -r $(TARGETDIR_client)
	rm -f -r $(TARGETDIR_main)


# Create the target directory (if needed)
$(TARGETDIR_server):
	mkdir -p $(TARGETDIR_server)
$(TARGETDIR_client):
	mkdir -p $(TARGETDIR_client)
$(TARGETDIR_main):
	mkdir -p $(TARGETDIR_main)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Linux

