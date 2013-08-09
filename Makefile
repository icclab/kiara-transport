## -*- Makefile -*-
##
## User: aepp
## Time: 06.08.2013 18:14:54
## Makefile created by Oracle Solaris Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = gcc
BASICOPTS = -g
CFLAGS = $(BASICOPTS)


# Define the target directories.
TARGETDIR_server=GNU-amd64-Linux
TARGETDIR_client=GNU-amd64-Linux


all: $(TARGETDIR_server)/server $(TARGETDIR_client)/client

## Target: server
OBJS_server =  \
	$(TARGETDIR_server)/http.o \
	$(TARGETDIR_server)/http_parser.o \
	$(TARGETDIR_server)/main.o \
	$(TARGETDIR_server)/server.o
USERLIBS_server = /usr/local/lib64/libzmq.so /usr/local/lib64/libczmq.so $(SYSLIBS_server) 
DEPLIBS_server =    
LDLIBS_server = $(USERLIBS_server)


# Link or archive
$(TARGETDIR_server)/server: $(TARGETDIR_server) $(OBJS_server) $(DEPLIBS_server)
	$(LINK.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ $(OBJS_server) $(LDLIBS_server)


# Compile source files into .o files
$(TARGETDIR_server)/http.o: $(TARGETDIR_server) http.c
	$(COMPILE.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ http.c

$(TARGETDIR_server)/http_parser.o: $(TARGETDIR_server) http_parser.c
	$(COMPILE.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ http_parser.c

$(TARGETDIR_server)/main.o: $(TARGETDIR_server) main.c
	$(COMPILE.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ main.c

$(TARGETDIR_server)/server.o: $(TARGETDIR_server) server.c
	$(COMPILE.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ server.c



## Target: client
OBJS_client =  \
	$(TARGETDIR_client)/client.o
USERLIBS_client = /usr/local/lib64/libzmq.so /usr/local/lib64/libczmq.so $(SYSLIBS_client) 
DEPLIBS_client =    
LDLIBS_client = $(USERLIBS_client)


# Link or archive
$(TARGETDIR_client)/client: $(TARGETDIR_client) $(OBJS_client) $(DEPLIBS_client)
	$(LINK.c) $(CFLAGS_client) $(CPPFLAGS_client) -o $@ $(OBJS_client) $(LDLIBS_client)


# Compile source files into .o files
$(TARGETDIR_client)/client.o: $(TARGETDIR_client) client.c
	$(COMPILE.c) $(CFLAGS_client) $(CPPFLAGS_client) -o $@ client.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_server)/server \
		$(TARGETDIR_server)/http.o \
		$(TARGETDIR_server)/http_parser.o \
		$(TARGETDIR_server)/main.o \
		$(TARGETDIR_server)/server.o \
		$(TARGETDIR_client)/client \
		$(TARGETDIR_client)/client.o
	rm -f -r $(TARGETDIR_server)
	rm -f -r $(TARGETDIR_client)


# Create the target directory (if needed)
$(TARGETDIR_server):
	mkdir -p $(TARGETDIR_server)
$(TARGETDIR_client):
	mkdir -p $(TARGETDIR_client)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Linux

