# Authors:
#  * Mathias Hablützel (ZHAW) <habl@zhaw.ch>
#  * Philipp Aeschlimann (ZHAW) <aepp@zhaw.ch>
#  * Sandro Brunner (ZHAW) <brnr@zhaw.ch>


# Tested with:
# * MAC OS X 10.9 MAVERICKS (built from macports)
#  * clang version 3.4 (tags/RELEASE_34/final)
#    Target: x86_64-apple-darwin13.1.0
#    Thread model: posix
#  * clang version 3.5.0 (trunk 206638)
#    Target: x86_64-apple-darwin13.1.0
#    Thread model: posix

CC = clang
CXX = clang++

# Use clang >=3.4 when turning ASAN on
ASAN = 1

# Be sure to run dsymutil(1) on the binaries/executables on OSX
# or you'll lack of symbols even though -g is turned on

ASAN_COMPILER_FLAGS = 	-fsanitize=address \
						-fno-omit-frame-pointer \
						-fsanitize-memory-track-origins

ASAN_LINKER_FLAGS =		-fsanitize=address

# if you want to turn off ASAN, just append to make {TARGET} ASAN=0
ifeq ($(ASAN),0)
	ASAN_COMPILER_FLAGS =
	ASAN_LINKER_FLAGS =
endif

CCFLAGS =	-Weverything\
			-Wno-padded \
			-pedantic \
			-std=c99 \
			-O0 \
			-g \
			$(ASAN_COMPILER_FLAGS)
	
negoc: CCFLAGS =	-Weverything\
			-Wno-padded \
			-pedantic \
			-O0 \
			-g \
			$(ASAN_COMPILER_FLAGS)

CXXFLAGS =	-Weverything \
			-Wno-padded \
			-Wno-c++98-compat-pedantic \
			-pedantic \
			-std=c++11 \
			-O0 \
			-g \
			$(ASAN_COMPILER_FLAGS)

LDFLAGS = -lzmq -lczmq -ljansson $(ASAN_LINKER_FLAGS)

DEST=build
ARCH=$(shell uname -m)-$(shell uname -s)
BUILDDIR=$(DEST)/$(ARCH)-$(CC)

$(BUILDDIR):
		mkdir -p $(BUILDDIR)

clean:
		rm -f -r $(BUILDDIR)

negoc:	server_0mq_http_nego \
		client_0mq_http_nego

all:	examples \
        demo \
	negoc

demo:	demo_broker \
        demo_reply \
        demo_subscriber

examples:   server_0mq_http_pp \
    		client_0mq_http_pp \
    		server_0mq_rep_pp \
    		client_0mq_req_pp \
    		server_0mq_rep_c \
    		client_0mq_req_c \
            server_0mq_pub_c \
            client_0mq_sub_c 

# Demo applications

demo_broker:	$(BUILDDIR)/k_transport.o \
				$(BUILDDIR)/KT_Configuration.o \
				$(BUILDDIR)/KT_Connection.o \
				$(BUILDDIR)/KT_HTTP_Responder.o \
				$(BUILDDIR)/KT_Msg.o \
				$(BUILDDIR)/KT_Session.o \
				$(BUILDDIR)/KT_Zeromq.o \
				$(BUILDDIR)/demo_main_broker.o \
				$(BUILDDIR)/demo_broker

demo_reply:    	$(BUILDDIR)/k_transport.o \
				$(BUILDDIR)/KT_Configuration.o \
				$(BUILDDIR)/KT_Connection.o \
				$(BUILDDIR)/KT_HTTP_Responder.o \
				$(BUILDDIR)/KT_Msg.o \
				$(BUILDDIR)/KT_Session.o \
				$(BUILDDIR)/KT_Zeromq.o \
				$(BUILDDIR)/demo_main_reply.o \
				$(BUILDDIR)/demo_reply

demo_subscriber:   	$(BUILDDIR)/k_transport.o \
    				$(BUILDDIR)/KT_Configuration.o \
    				$(BUILDDIR)/KT_Connection.o \
    				$(BUILDDIR)/KT_HTTP_Responder.o \
    				$(BUILDDIR)/KT_Msg.o \
    				$(BUILDDIR)/KT_Session.o \
    				$(BUILDDIR)/KT_Zeromq.o \
    				$(BUILDDIR)/demo_main_subscriber.o \
    				$(BUILDDIR)/demo_subscriber 

# Examples Server

server_0mq_http_pp:	$(BUILDDIR)/KT_Client.o \
					$(BUILDDIR)/KT_Configuration.o \
					$(BUILDDIR)/KT_Connection.o \
					$(BUILDDIR)/KT_HTTP_Parser.o \
					$(BUILDDIR)/KT_HTTP_Responder.o \
					$(BUILDDIR)/KT_Msg.o \
					$(BUILDDIR)/KT_Session.o \
					$(BUILDDIR)/KT_Zeromq.o \
					$(BUILDDIR)/http_parser.o \
					$(BUILDDIR)/main_server_0mq_http_pp.o  \
					$(BUILDDIR)/server_0mq_http_pp

server_0mq_http_nego:	$(BUILDDIR)/KT_Client.o \
					$(BUILDDIR)/KT_Configuration.o \
					$(BUILDDIR)/KT_Connection.o \
					$(BUILDDIR)/KT_HTTP_Parser.o \
					$(BUILDDIR)/KT_HTTP_Responder.o \
					$(BUILDDIR)/KT_HTTP_Requester.o \
					$(BUILDDIR)/KT_Msg.o \
					$(BUILDDIR)/KT_Session.o \
					$(BUILDDIR)/KT_Zeromq.o \
					$(BUILDDIR)/http_parser.o \
					$(BUILDDIR)/negotiation.o \
					$(BUILDDIR)/reco_engine.o \
					$(BUILDDIR)/registry.o \
					$(BUILDDIR)/main_nego.o  \
					$(BUILDDIR)/server_0mq_http_nego

server_0mq_rep_pp:	$(BUILDDIR)/KT_Client.o \
					$(BUILDDIR)/KT_Configuration.o \
					$(BUILDDIR)/KT_Connection.o \
					$(BUILDDIR)/KT_HTTP_Parser.o \
					$(BUILDDIR)/KT_HTTP_Responder.o \
					$(BUILDDIR)/KT_Msg.o \
					$(BUILDDIR)/KT_Session.o \
					$(BUILDDIR)/KT_Zeromq.o \
					$(BUILDDIR)/http_parser.o \
					$(BUILDDIR)/main_server_0mq_rep_pp.o  \
					$(BUILDDIR)/server_0mq_rep_pp

server_0mq_rep_c:	$(BUILDDIR)/k_transport.o \
					$(BUILDDIR)/KT_C99_CallbackWrapper.o \
					$(BUILDDIR)/KT_Configuration.o \
					$(BUILDDIR)/KT_Connection.o \
					$(BUILDDIR)/KT_HTTP_Responder.o \
					$(BUILDDIR)/KT_HTTP_Parser.o \
					$(BUILDDIR)/KT_Msg.o \
					$(BUILDDIR)/KT_Session.o \
					$(BUILDDIR)/KT_Zeromq.o \
					$(BUILDDIR)/main_server_0mq_rep_c.o \
					$(BUILDDIR)/server_0mq_rep_c

server_0mq_pub_c:	$(BUILDDIR)/k_transport.o \
					$(BUILDDIR)/KT_C99_CallbackWrapper.o \
					$(BUILDDIR)/KT_Configuration.o \
					$(BUILDDIR)/KT_Connection.o \
					$(BUILDDIR)/KT_HTTP_Responder.o \
					$(BUILDDIR)/KT_Msg.o \
					$(BUILDDIR)/KT_Session.o \
					$(BUILDDIR)/KT_Zeromq.o \
					$(BUILDDIR)/main_server_0mq_pub_c.o \
					$(BUILDDIR)/server_0mq_pub_c

# Examples Clients

client_0mq_http_pp: $(BUILDDIR)/KT_Client.o \
                    $(BUILDDIR)/KT_Configuration.o \
                    $(BUILDDIR)/KT_Connection.o \
                    $(BUILDDIR)/KT_HTTP_Parser.o \
                    $(BUILDDIR)/KT_HTTP_Responder.o \
                    $(BUILDDIR)/KT_Msg.o \
                    $(BUILDDIR)/KT_Session.o \
                    $(BUILDDIR)/KT_Zeromq.o \
                    $(BUILDDIR)/http_parser.o \
                    $(BUILDDIR)/main_client_0mq_http_pp.o  \
                    $(BUILDDIR)/client_0mq_http_pp

client_0mq_http_nego:	$(BUILDDIR)/KT_Client.o \
			$(BUILDDIR)/KT_Configuration.o \
			$(BUILDDIR)/KT_Connection.o \
			$(BUILDDIR)/KT_HTTP_Parser.o \
			$(BUILDDIR)/KT_HTTP_Responder.o \
			$(BUILDDIR)/KT_HTTP_Requester.o \
			$(BUILDDIR)/KT_Msg.o \
			$(BUILDDIR)/KT_Session.o \
			$(BUILDDIR)/KT_Zeromq.o \
			$(BUILDDIR)/http_parser.o \
			$(BUILDDIR)/negotiation.o \
			$(BUILDDIR)/reco_engine.o \
			$(BUILDDIR)/registry.o \
			$(BUILDDIR)/main_nego_client.o  \
			$(BUILDDIR)/client_0mq_http_nego

client_0mq_req_pp: $(BUILDDIR)/KT_Client.o \
                   $(BUILDDIR)/KT_Configuration.o \
                   $(BUILDDIR)/KT_Connection.o \
                   $(BUILDDIR)/KT_HTTP_Parser.o \
                   $(BUILDDIR)/KT_HTTP_Responder.o \
                   $(BUILDDIR)/KT_Msg.o \
                   $(BUILDDIR)/KT_Session.o \
                   $(BUILDDIR)/KT_Zeromq.o \
                   $(BUILDDIR)/http_parser.o \
                   $(BUILDDIR)/main_client_0mq_req_pp.o  \
                   $(BUILDDIR)/client_0mq_req_pp

client_0mq_req_c:	$(BUILDDIR)/k_transport.o \
					$(BUILDDIR)/KT_Configuration.o \
					$(BUILDDIR)/KT_Connection.o \
					$(BUILDDIR)/KT_HTTP_Responder.o \
					$(BUILDDIR)/KT_Msg.o \
					$(BUILDDIR)/KT_Session.o \
					$(BUILDDIR)/KT_Zeromq.o \
					$(BUILDDIR)/main_client_0mq_req_c.o \
					$(BUILDDIR)/client_0mq_req_c

client_0mq_sub_c:	$(BUILDDIR)/k_transport.o \
					$(BUILDDIR)/KT_Configuration.o \
					$(BUILDDIR)/KT_Connection.o \
					$(BUILDDIR)/KT_HTTP_Responder.o \
					$(BUILDDIR)/KT_Msg.o \
					$(BUILDDIR)/KT_Session.o \
					$(BUILDDIR)/KT_Zeromq.o \
					$(BUILDDIR)/main_client_0mq_sub_c.o \
					$(BUILDDIR)/client_0mq_sub_c

# Demo build deps

DEMO_BROKER_DEPS =	$(BUILDDIR)/demo_main_broker.o \
					$(BUILDDIR)/k_transport.o \
					$(BUILDDIR)/http_parser.o \
					$(BUILDDIR)/KT_C99_CallbackWrapper.o \
					$(BUILDDIR)/KT_Configuration.o \
					$(BUILDDIR)/KT_Connection.o \
					$(BUILDDIR)/KT_HTTP_Responder.o \
					$(BUILDDIR)/KT_HTTP_Parser.o \
					$(BUILDDIR)/KT_Msg.o \
					$(BUILDDIR)/KT_Session.o \
					$(BUILDDIR)/KT_Zeromq.o

DEMO_REPLY_DEPS =	$(BUILDDIR)/demo_main_reply.o \
					$(BUILDDIR)/k_transport.o \
					$(BUILDDIR)/http_parser.o \
					$(BUILDDIR)/KT_C99_CallbackWrapper.o \
					$(BUILDDIR)/KT_Configuration.o \
					$(BUILDDIR)/KT_Connection.o \
					$(BUILDDIR)/KT_HTTP_Responder.o \
					$(BUILDDIR)/KT_HTTP_Parser.o \
					$(BUILDDIR)/KT_Msg.o \
					$(BUILDDIR)/KT_Session.o \
					$(BUILDDIR)/KT_Zeromq.o

DEMO_SUBSCRIBER_DEPS =	$(BUILDDIR)/demo_main_subscriber.o \
			    		$(BUILDDIR)/k_transport.o \
						$(BUILDDIR)/http_parser.o \
			    		$(BUILDDIR)/KT_C99_CallbackWrapper.o \
			    		$(BUILDDIR)/KT_Configuration.o \
			    		$(BUILDDIR)/KT_Connection.o \
			    		$(BUILDDIR)/KT_HTTP_Responder.o \
						$(BUILDDIR)/KT_HTTP_Parser.o \
			    		$(BUILDDIR)/KT_Msg.o \
			    		$(BUILDDIR)/KT_Session.o \
			    		$(BUILDDIR)/KT_Zeromq.o

# Example Servers build deps

SERVER_0MQ_HTTP_CPP_DEPS =	$(BUILDDIR)/KT_Client.o \
							$(BUILDDIR)/KT_Configuration.o \
							$(BUILDDIR)/KT_Connection.o \
							$(BUILDDIR)/KT_HTTP_Parser.o \
							$(BUILDDIR)/KT_HTTP_Responder.o \
							$(BUILDDIR)/KT_Msg.o \
							$(BUILDDIR)/KT_Session.o \
							$(BUILDDIR)/KT_Zeromq.o \
							$(BUILDDIR)/http_parser.o \
							$(BUILDDIR)/main_server_0mq_http_pp.o

SERVER_0MQ_REP_CPP_DEPS =	$(BUILDDIR)/KT_Client.o \
							$(BUILDDIR)/KT_Configuration.o \
							$(BUILDDIR)/KT_Connection.o \
							$(BUILDDIR)/KT_Msg.o \
							$(BUILDDIR)/KT_Session.o \
							$(BUILDDIR)/KT_Zeromq.o \
							$(BUILDDIR)/main_server_0mq_rep_pp.o

SERVER_0MQ_REP_CC_DEPS =	$(BUILDDIR)/main_server_0mq_rep_c.o \
							$(BUILDDIR)/k_transport.o \
							$(BUILDDIR)/http_parser.o \
							$(BUILDDIR)/KT_C99_CallbackWrapper.o \
							$(BUILDDIR)/KT_Configuration.o \
							$(BUILDDIR)/KT_Connection.o \
							$(BUILDDIR)/KT_HTTP_Responder.o \
							$(BUILDDIR)/KT_HTTP_Parser.o \
							$(BUILDDIR)/KT_Msg.o \
							$(BUILDDIR)/KT_Session.o \
							$(BUILDDIR)/KT_Zeromq.o

SERVER_0MQ_PUB_CC_DEPS =	$(BUILDDIR)/main_server_0mq_pub_c.o \
							$(BUILDDIR)/k_transport.o \
							$(BUILDDIR)/http_parser.o \
							$(BUILDDIR)/KT_C99_CallbackWrapper.o \
							$(BUILDDIR)/KT_Configuration.o \
							$(BUILDDIR)/KT_Connection.o \
							$(BUILDDIR)/KT_HTTP_Responder.o \
							$(BUILDDIR)/KT_HTTP_Parser.o \
							$(BUILDDIR)/KT_Msg.o \
							$(BUILDDIR)/KT_Session.o \
							$(BUILDDIR)/KT_Zeromq.o

SERVER_0MQ_C_NEGO_DEPS =	$(BUILDDIR)/KT_Client.o \
							$(BUILDDIR)/KT_Configuration.o \
							$(BUILDDIR)/KT_Connection.o \
							$(BUILDDIR)/KT_HTTP_Parser.o \
							$(BUILDDIR)/KT_HTTP_Responder.o \
							$(BUILDDIR)/KT_HTTP_Requester.o \
							$(BUILDDIR)/KT_Msg.o \
							$(BUILDDIR)/KT_Session.o \
							$(BUILDDIR)/KT_Zeromq.o \
							$(BUILDDIR)/http_parser.o \
							$(BUILDDIR)/negotiation.o \
							$(BUILDDIR)/reco_engine.o \
							$(BUILDDIR)/registry.o \
							$(BUILDDIR)/main_nego.o
	
CLIENT_0MQ_C_NEGO_DEPS =	$(BUILDDIR)/KT_Client.o \
					$(BUILDDIR)/KT_Configuration.o \
					$(BUILDDIR)/KT_Connection.o \
					$(BUILDDIR)/KT_HTTP_Parser.o \
					$(BUILDDIR)/KT_HTTP_Responder.o \
					$(BUILDDIR)/KT_HTTP_Requester.o \
					$(BUILDDIR)/KT_Msg.o \
					$(BUILDDIR)/KT_Session.o \
					$(BUILDDIR)/KT_Zeromq.o \
					$(BUILDDIR)/http_parser.o \
					$(BUILDDIR)/negotiation.o \
					$(BUILDDIR)/reco_engine.o \
					$(BUILDDIR)/registry.o \
					$(BUILDDIR)/main_nego_client.o
# Example Clients build deps

CLIENT_0MQ_HTTP_CPP_DEPS =	$(BUILDDIR)/KT_Client.o \
                   		    $(BUILDDIR)/KT_Configuration.o \
                   		    $(BUILDDIR)/KT_Connection.o \
                   		    $(BUILDDIR)/KT_HTTP_Parser.o \
                   		    $(BUILDDIR)/KT_HTTP_Responder.o \
                   		    $(BUILDDIR)/KT_Msg.o \
                   		    $(BUILDDIR)/KT_Session.o \
                   		    $(BUILDDIR)/KT_Zeromq.o \
                   		    $(BUILDDIR)/http_parser.o \
                   		    $(BUILDDIR)/main_client_0mq_http_pp.o

CLIENT_0MQ_REQ_CPP_DEPS =	$(BUILDDIR)/KT_Client.o \
                    		$(BUILDDIR)/KT_Configuration.o \
                    		$(BUILDDIR)/KT_Connection.o \
                    		$(BUILDDIR)/KT_Msg.o \
                    		$(BUILDDIR)/KT_Session.o \
                    		$(BUILDDIR)/KT_Zeromq.o \
                    		$(BUILDDIR)/main_client_0mq_req_pp.o

CLIENT_0MQ_REQ_CC_DEPS =	$(BUILDDIR)/main_client_0mq_req_c.o \
							$(BUILDDIR)/k_transport.o \
							$(BUILDDIR)/http_parser.o \
							$(BUILDDIR)/KT_C99_CallbackWrapper.o \
							$(BUILDDIR)/KT_Configuration.o \
							$(BUILDDIR)/KT_Connection.o \
							$(BUILDDIR)/KT_HTTP_Responder.o \
							$(BUILDDIR)/KT_HTTP_Parser.o \
							$(BUILDDIR)/KT_Msg.o \
							$(BUILDDIR)/KT_Session.o \
							$(BUILDDIR)/KT_Zeromq.o

CLIENT_0MQ_SUB_CC_DEPS =	$(BUILDDIR)/main_client_0mq_sub_c.o \
							$(BUILDDIR)/k_transport.o \
							$(BUILDDIR)/http_parser.o \
							$(BUILDDIR)/KT_C99_CallbackWrapper.o \
							$(BUILDDIR)/KT_Configuration.o \
							$(BUILDDIR)/KT_Connection.o \
							$(BUILDDIR)/KT_HTTP_Responder.o \
							$(BUILDDIR)/KT_HTTP_Parser.o \
							$(BUILDDIR)/KT_Msg.o \
							$(BUILDDIR)/KT_Session.o \
							$(BUILDDIR)/KT_Zeromq.o
# Build instructions API/Lib

$(BUILDDIR)/k_transport.o: $(BUILDDIR) src/core/k_transport.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ src/core/k_transport.cpp

$(BUILDDIR)/KT_C99_CallbackWrapper.o: $(BUILDDIR) src/core/KT_C99_CallbackWrapper.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ src/core/KT_C99_CallbackWrapper.cpp

$(BUILDDIR)/KT_Client.o: $(BUILDDIR) src/core/KT_Client.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/core/KT_Client.cpp

$(BUILDDIR)/KT_Connection.o: $(BUILDDIR) src/core/KT_Connection.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/core/KT_Connection.cpp

$(BUILDDIR)/KT_Configuration.o: $(BUILDDIR) src/core/KT_Configuration.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/core/KT_Configuration.cpp
		
$(BUILDDIR)/KT_HTTP_Parser.o: $(BUILDDIR) src/core/KT_HTTP_Parser.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/core/KT_HTTP_Parser.cpp

$(BUILDDIR)/KT_HTTP_Responder.o: $(BUILDDIR) src/core/KT_HTTP_Responder.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/core/KT_HTTP_Responder.cpp
	
$(BUILDDIR)/KT_HTTP_Requester.o: $(BUILDDIR) src/core/KT_HTTP_Requester.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/core/KT_HTTP_Requester.cpp

$(BUILDDIR)/KT_Msg.o: $(BUILDDIR) src/core/KT_Msg.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/core/KT_Msg.cpp

$(BUILDDIR)/KT_Session.o: $(BUILDDIR) src/core/KT_Session.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/core/KT_Session.cpp

$(BUILDDIR)/KT_Zeromq.o: $(BUILDDIR) src/core/KT_Zeromq.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/core/KT_Zeromq.cpp
	
$(BUILDDIR)/negotiation.o: $(BUILDDIR) src/core/negotiation.c
	$(CC) -c $(CCFLAGS) -o $@ src/core/negotiation.c

$(BUILDDIR)/reco_engine.o: $(BUILDDIR) src/core/reco_engine.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ src/core/reco_engine.cpp

$(BUILDDIR)/registry.o: $(BUILDDIR) src/core/registry.c
	$(CC) -c $(CCFLAGS) -o $@ src/core/registry.c

$(BUILDDIR)/http_parser.o: $(BUILDDIR) src/core/http_parser.c
		$(CXX) -c $(CXXFLAGS) -Wno-everything -o $@ src/core/http_parser.c

# Build instructions Example Server

$(BUILDDIR)/main_server_0mq_http_pp.o: $(BUILDDIR) src/examples/main_server_0mq_http.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/examples/main_server_0mq_http.cpp

$(BUILDDIR)/main_nego.o: $(BUILDDIR) src/examples/main_nego.c
		$(CC) -c $(CCFLAGS) -o $@ src/examples/main_nego.c
	
$(BUILDDIR)/main_nego_client.o: $(BUILDDIR) src/examples/main_nego_client.c
		$(CC) -c $(CCFLAGS) -o $@ src/examples/main_nego_client.c

$(BUILDDIR)/server_0mq_http_pp: $(BUILDDIR) $(SERVER_0MQ_HTTP_CPP_DEPS)
		$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $(SERVER_0MQ_HTTP_CPP_DEPS)

$(BUILDDIR)/main_server_0mq_rep_pp.o: $(BUILDDIR) src/examples/main_server_0mq_rep.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/examples/main_server_0mq_rep.cpp

$(BUILDDIR)/server_0mq_rep_pp: $(BUILDDIR) $(SERVER_0MQ_REP_CPP_DEPS)
		$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $(SERVER_0MQ_REP_CPP_DEPS)

$(BUILDDIR)/main_server_0mq_rep_c.o: $(BUILDDIR) src/examples/main_server_0mq_rep.c
		$(CC) -c $(CCFLAGS) -o $@ src/examples/main_server_0mq_rep.c

$(BUILDDIR)/server_0mq_rep_c: $(BUILDDIR) $(SERVER_0MQ_REP_CC_DEPS)
		$(CXX) $(LDFLAGS) -lc $(CXXFLAGS) -o $@ $(SERVER_0MQ_REP_CC_DEPS)

$(BUILDDIR)/main_server_0mq_pub_c.o: $(BUILDDIR) src/examples/main_server_0mq_pub.c
		$(CC) -c $(CCFLAGS) -o $@ src/examples/main_server_0mq_pub.c

$(BUILDDIR)/server_0mq_pub_c: $(BUILDDIR) $(SERVER_0MQ_PUB_CC_DEPS)
		$(CXX) $(LDFLAGS) -lc $(CXXFLAGS) -o $@ $(SERVER_0MQ_PUB_CC_DEPS)

# Build instructions Example Clients

$(BUILDDIR)/main_client_0mq_http_pp.o: $(BUILDDIR) src/examples/main_client_0mq_http.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/examples/main_client_0mq_http.cpp

$(BUILDDIR)/client_0mq_http_pp: $(BUILDDIR) $(CLIENT_0MQ_HTTP_CPP_DEPS)
		$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $(CLIENT_0MQ_HTTP_CPP_DEPS)

$(BUILDDIR)/main_client_0mq_req_pp.o: $(BUILDDIR) src/examples/main_client_0mq_req.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/examples/main_client_0mq_req.cpp

$(BUILDDIR)/client_0mq_req_pp: $(BUILDDIR) $(CLIENT_0MQ_REQ_CPP_DEPS)
		$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $(CLIENT_0MQ_REQ_CPP_DEPS)

$(BUILDDIR)/main_client_0mq_req_c.o: $(BUILDDIR) src/examples/main_client_0mq_req.c
		$(CC) -c $(CCFLAGS) -o $@ src/examples/main_client_0mq_req.c

$(BUILDDIR)/client_0mq_req_c: $(BUILDDIR) $(CLIENT_0MQ_REQ_CC_DEPS)
		$(CXX) $(LDFLAGS) -lc $(CXXFLAGS) -o $@ $(CLIENT_0MQ_REQ_CC_DEPS)

$(BUILDDIR)/server_0mq_http_nego: $(BUILDDIR) $(SERVER_0MQ_C_NEGO_DEPS)
		$(CXX) $(LDFLAGS) $(FLAGS) -o $@ $(SERVER_0MQ_C_NEGO_DEPS)
	
$(BUILDDIR)/client_0mq_http_nego: $(BUILDDIR) $(CLIENT_0MQ_C_NEGO_DEPS)
		$(CXX) $(LDFLAGS) $(FLAGS) -o $@ $(CLIENT_0MQ_C_NEGO_DEPS)

$(BUILDDIR)/main_client_0mq_sub_c.o: $(BUILDDIR) src/examples/main_client_0mq_sub.c
		$(CC) -c $(CCFLAGS) -o $@ src/examples/main_client_0mq_sub.c

$(BUILDDIR)/client_0mq_sub_c: $(BUILDDIR) $(CLIENT_0MQ_SUB_CC_DEPS)
		$(CXX) $(LDFLAGS) -lc $(CXXFLAGS) -o $@ $(CLIENT_0MQ_SUB_CC_DEPS)

# Build instructions Demo

$(BUILDDIR)/demo_main_broker.o: $(BUILDDIR) src/examples/demo_main_broker.c
		$(CC) -c $(CCFLAGS) -o $@ src/examples/demo_main_broker.c

$(BUILDDIR)/demo_broker: $(BUILDDIR) $(DEMO_BROKER_DEPS)
		$(CXX) $(LDFLAGS) -lc $(CXXFLAGS) -o $@ $(DEMO_BROKER_DEPS)

$(BUILDDIR)/demo_main_reply.o: $(BUILDDIR) src/examples/demo_main_reply.c
		$(CC) -c $(CCFLAGS) -o $@ src/examples/demo_main_reply.c

$(BUILDDIR)/demo_reply: $(BUILDDIR) $(DEMO_REPLY_DEPS)
		$(CXX) $(LDFLAGS) -lc $(CXXFLAGS) -o $@ $(DEMO_REPLY_DEPS)

$(BUILDDIR)/demo_main_subscriber.o: $(BUILDDIR) src/examples/demo_main_subscriber.c
		$(CC) -c $(CCFLAGS) -o $@ src/examples/demo_main_subscriber.c

$(BUILDDIR)/demo_subscriber: $(BUILDDIR) $(DEMO_SUBSCRIBER_DEPS)
		$(CXX) $(LDFLAGS) -lc $(CXXFLAGS) -o $@ $(DEMO_SUBSCRIBER_DEPS)

