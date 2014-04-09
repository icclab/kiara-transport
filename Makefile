CC = clang
CXX = clang++

negoc: CCFLAGS =	-Weverything\
			-Wno-padded \
			-pedantic \
			-O0 \
			-g

CCFLAGS =	-Weverything\
			-Wno-padded \
			-pedantic \
			-std=c99 \
			-O0 \
			-g \
			-fsanitize=address \
			-fno-omit-frame-pointer \
			-fsanitize-memory-track-origins

negoc: CXXFLAGS =	-Weverything \
			-Wno-padded \
			-Wno-c++98-compat-pedantic \
			-pedantic \
			-std=c++11 \
			-O0 \
			-g

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

negoc: LDFLAGS = -lzmq -lczmq -ljansson

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
		client_0mq_req_c
negoc:	server_0mq_http_nego \
		client_0mq_http_nego

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
					$(BUILDDIR)/KT_Msg.o \
					$(BUILDDIR)/KT_Session.o \
					$(BUILDDIR)/KT_Zeromq.o \
					$(BUILDDIR)/main_server_0mq_rep_c.o \
					$(BUILDDIR)/server_0mq_rep_c


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

SERVER_0MQ_REP_CC_DEPS =	$(BUILDDIR)/main_server_0mq_rep_c.o \
							$(BUILDDIR)/k_transport.o \
							$(BUILDDIR)/KT_C99_CallbackWrapper.o \
							$(BUILDDIR)/KT_Configuration.o \
							$(BUILDDIR)/KT_Connection.o \
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
