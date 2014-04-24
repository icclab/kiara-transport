CC = clang
CXX = clang++

ASAN = 1

ASAN_COMPILER_FLAGS = 	-fsanitize=address \
						-fno-omit-frame-pointer \
						-fsanitize-memory-track-origins

ASAN_LINKER_FLAGS =		-fsanitize=address

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

CXXFLAGS =	-Weverything \
			-Wno-padded \
			-Wno-c++98-compat-pedantic \
			-pedantic \
			-std=c++11 \
			-O0 \
			-g \
			$(ASAN_COMPILER_FLAGS)

LDFLAGS = -lzmq -lczmq $(ASAN_LINKER_FLAGS)

DEST=build
ARCH=$(shell uname -m)-$(shell uname -s)
BUILDDIR=$(DEST)/$(ARCH)-$(CC)

$(BUILDDIR):
		mkdir -p $(BUILDDIR)

clean:
		rm -f -r $(BUILDDIR)

all: 	server_0mq_http_pp \
		client_0mq_http_pp \
		server_0mq_rep_pp \
		client_0mq_req_pp \
		server_0mq_rep_c \
		client_0mq_req_c \
        server_0mq_pub_c \
        client_0mq_sub_c

demo:	demo_broker

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

demo_broker:	$(BUILDDIR)/k_transport.o \
				$(BUILDDIR)/KT_Configuration.o \
				$(BUILDDIR)/KT_Connection.o \
				$(BUILDDIR)/KT_HTTP_Responder.o \
				$(BUILDDIR)/KT_Msg.o \
				$(BUILDDIR)/KT_Session.o \
				$(BUILDDIR)/KT_Zeromq.o \
				$(BUILDDIR)/main_demo_broker.o \
				$(BUILDDIR)/demo_broker


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
							$(BUILDDIR)/KT_C99_CallbackWrapper.o \
							$(BUILDDIR)/KT_Configuration.o \
							$(BUILDDIR)/KT_Connection.o \
							$(BUILDDIR)/KT_HTTP_Responder.o \
							$(BUILDDIR)/KT_Msg.o \
							$(BUILDDIR)/KT_Session.o \
							$(BUILDDIR)/KT_Zeromq.o

SERVER_0MQ_PUB_CC_DEPS =	$(BUILDDIR)/main_server_0mq_pub_c.o \
							$(BUILDDIR)/k_transport.o \
							$(BUILDDIR)/KT_C99_CallbackWrapper.o \
							$(BUILDDIR)/KT_Configuration.o \
							$(BUILDDIR)/KT_Connection.o \
							$(BUILDDIR)/KT_HTTP_Responder.o \
							$(BUILDDIR)/KT_Msg.o \
							$(BUILDDIR)/KT_Session.o \
							$(BUILDDIR)/KT_Zeromq.o

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
							$(BUILDDIR)/KT_C99_CallbackWrapper.o \
							$(BUILDDIR)/KT_Configuration.o \
							$(BUILDDIR)/KT_Connection.o \
							$(BUILDDIR)/KT_HTTP_Responder.o \
							$(BUILDDIR)/KT_Msg.o \
							$(BUILDDIR)/KT_Session.o \
							$(BUILDDIR)/KT_Zeromq.o

CLIENT_0MQ_SUB_CC_DEPS =	$(BUILDDIR)/main_client_0mq_sub_c.o \
							$(BUILDDIR)/k_transport.o \
							$(BUILDDIR)/KT_C99_CallbackWrapper.o \
							$(BUILDDIR)/KT_Configuration.o \
							$(BUILDDIR)/KT_Connection.o \
							$(BUILDDIR)/KT_HTTP_Responder.o \
							$(BUILDDIR)/KT_Msg.o \
							$(BUILDDIR)/KT_Session.o \
							$(BUILDDIR)/KT_Zeromq.o

DEMO_BROKER_DEPS =	$(BUILDDIR)/main_demo_broker.o \
					$(BUILDDIR)/k_transport.o \
					$(BUILDDIR)/KT_C99_CallbackWrapper.o \
					$(BUILDDIR)/KT_Configuration.o \
					$(BUILDDIR)/KT_Connection.o \
					$(BUILDDIR)/KT_HTTP_Responder.o \
					$(BUILDDIR)/KT_Msg.o \
					$(BUILDDIR)/KT_Session.o \
					$(BUILDDIR)/KT_Zeromq.o


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

$(BUILDDIR)/KT_Msg.o: $(BUILDDIR) src/core/KT_Msg.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/core/KT_Msg.cpp

$(BUILDDIR)/KT_Session.o: $(BUILDDIR) src/core/KT_Session.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/core/KT_Session.cpp

$(BUILDDIR)/KT_Zeromq.o: $(BUILDDIR) src/core/KT_Zeromq.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/core/KT_Zeromq.cpp

$(BUILDDIR)/http_parser.o: $(BUILDDIR) src/core/http_parser.c
		$(CC) -c $(CFLAGS) -Wno-everything -o $@ src/core/http_parser.c

$(BUILDDIR)/main_server_0mq_http_pp.o: $(BUILDDIR) src/examples/main_server_0mq_http.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/examples/main_server_0mq_http.cpp

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

$(BUILDDIR)/main_client_0mq_sub_c.o: $(BUILDDIR) src/examples/main_client_0mq_sub.c
		$(CC) -c $(CCFLAGS) -o $@ src/examples/main_client_0mq_sub.c

$(BUILDDIR)/client_0mq_sub_c: $(BUILDDIR) $(CLIENT_0MQ_SUB_CC_DEPS)
		$(CXX) $(LDFLAGS) -lc $(CXXFLAGS) -o $@ $(CLIENT_0MQ_SUB_CC_DEPS)

$(BUILDDIR)/main_demo_broker.o: $(BUILDDIR) src/examples/main_demo_broker.c
		$(CC) -c $(CCFLAGS) -o $@ src/examples/main_demo_broker.c

$(BUILDDIR)/demo_broker: $(BUILDDIR) $(DEMO_BROKER_DEPS)
		$(CXX) $(LDFLAGS) -lc $(CXXFLAGS) -o $@ $(DEMO_BROKER_DEPS)
