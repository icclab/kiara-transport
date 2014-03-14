CC = clang
CXX = clang++

CCFLAGS =	-Weverything\
			-Wno-padded \
			-pedantic \
			-std=c99 \
			-O0 \
			-g \
			-fsanitize=address \
			-fno-omit-frame-pointer \
			-fsanitize-memory-track-origins

CXXFLAGS =	-Weverything \
			-Wno-padded \
			-Wno-c++98-compat-pedantic \
			-pedantic \
			-std=c++11 \
			-O0 \
			-g \
			-fsanitize=address \
			-fno-omit-frame-pointer \
			-fsanitize-memory-track-origins

LDFLAGS = -lzmq -lczmq -fsanitize=address

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
		client_0mq_req_c

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
					$(BUILDDIR)/KT_Msg.o \
					$(BUILDDIR)/KT_Session.o \
					$(BUILDDIR)/KT_Zeromq.o \
					$(BUILDDIR)/main_client_0mq_req_c.o \
					$(BUILDDIR)/client_0mq_req_c

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
							$(BUILDDIR)/KT_Configuration.o \
							$(BUILDDIR)/KT_Connection.o \
							$(BUILDDIR)/KT_Msg.o \
							$(BUILDDIR)/KT_Session.o \
							$(BUILDDIR)/KT_Zeromq.o


$(BUILDDIR)/k_transport.o: $(BUILDDIR) src/core/k_transport.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ src/core/k_transport.cpp

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
		$(CXX) -c $(CXXFLAGS) -Wno-everything -o $@ src/core/http_parser.c

$(BUILDDIR)/main_server_0mq_http_pp.o: $(BUILDDIR) src/examples/main_server_0mq_http.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/examples/main_server_0mq_http.cpp

$(BUILDDIR)/server_0mq_http_pp: $(BUILDDIR) $(SERVER_0MQ_HTTP_CPP_DEPS)
		$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $(SERVER_0MQ_HTTP_CPP_DEPS)

$(BUILDDIR)/main_server_0mq_rep_pp.o: $(BUILDDIR) src/examples/main_server_0mq_rep.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ src/examples/main_server_0mq_rep.cpp

$(BUILDDIR)/server_0mq_rep_pp: $(BUILDDIR) $(SERVER_0MQ_REP_CPP_DEPS)
		$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $(SERVER_0MQ_REP_CPP_DEPS)

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
		$(CC) $(LDFLAGS) $(CCFLAGS) -o $@ $(CLIENT_0MQ_REQ_CC_DEPS)
