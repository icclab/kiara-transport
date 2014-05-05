/*
 * KIARA transport library
 *
 * Author: Mathias Hablützel <habl@zhaw.ch>
 * Reference: doc/Library API contract.md
 */

#include "../../include/k_transport.h"

#include <iostream>
#include <vector>
#include <functional>

#include "KT_C99_CallbackWrapper.hpp"
#include "KT_Configuration.h"
#include "KT_Configuration.hpp"
#include "KT_Configuration_glob.h"
#include "KT_Msg.hpp"
#include "KT_Session.hpp"
#include "KT_Zeromq.hpp"

#include "KT_HTTP_Responder.hpp"
#include "KT_HTTP_Parser.hpp"

#ifdef __cplusplus
extern "C" {
#endif

/* KIARA::Transport::KT_Msg C wrapper */
KIARA::Transport::KT_C99_CallbackWrapper* cb_wrapper;

kt_msg_t* kt_msg_new ()
{
	return reinterpret_cast<kt_msg_t*>(new KIARA::Transport::KT_Msg());
}

void kt_msg_destroy ( kt_msg_t* c_msg )
{
	KIARA::Transport::KT_Msg *msg = reinterpret_cast<KIARA::Transport::KT_Msg *> (c_msg);
	delete (msg);
}

void kt_msg_set_payload ( kt_msg_t* c_msg, void* payload, size_t payload_size)
{
	KIARA::Transport::KT_Msg *msg = reinterpret_cast<KIARA::Transport::KT_Msg *> (c_msg);
	char* payload_ptr = reinterpret_cast<char*> (payload);
	std::vector<char> payload_vector (payload_ptr, payload_ptr + payload_size);
	msg->set_payload (payload_vector);
}

void* kt_msg_get_payload ( kt_msg_t* c_msg )
{
	KIARA::Transport::KT_Msg *msg = reinterpret_cast<KIARA::Transport::KT_Msg *> (c_msg);
	return msg->get_payload_ptr()->data();
}

unsigned int kt_msg_get_payload_size ( kt_msg_t* c_msg )
{
    KIARA::Transport::KT_Msg *msg = reinterpret_cast<KIARA::Transport::KT_Msg *> (c_msg);
    return msg->get_payload().size();
}

kt_msg_t* kt_msg_http_reply (char* content, size_t size)
{
    kt_msg_t* msg = kt_msg_new();
    std::string payload = KIARA::Transport::KT_HTTP_Responder::generate_200_OK( std::vector<char>(content, content + size) );
    char* p = reinterpret_cast<char*>(malloc(sizeof(char)*payload.size()));
    payload.copy(p,payload.size());
    kt_msg_set_payload(msg, p, payload.size());
    return msg;
}

char* kt_msg_http_get_payload (kt_msg_t* c_msg)
{
    KIARA::Transport::KT_Msg *msg = reinterpret_cast<KIARA::Transport::KT_Msg *> (c_msg);
    KIARA::Transport::KT_HTTP_Parser parser (*msg);
    std::string s = parser.get_payload();
    s.append(1, '\0');
    char* ptr = (char*)malloc(sizeof(char) * s.size());
    s.copy(ptr, s.size());
    return ptr;
}

kt_conn_session_t* kt_connect ( const kt_configuration_t* conf )
{
	const KIARA::Transport::KT_Configuration* config =
	        reinterpret_cast<const KIARA::Transport::KT_Configuration*> (conf);
	KIARA::Transport::KT_Connection* connection;

	if ( KT_ZEROMQ == config->get_application_layer() )
	{
		connection = new KIARA::Transport::KT_Zeromq ();
		connection->set_configuration (*config);
	}
	else {
	    std::cerr << "Could not connect, you indicated an unsupported application layer" << std::endl;
	    return nullptr;
	}

	KIARA::Transport::KT_Session* session = nullptr;
    if ( 0 != connection->connect(&session) )
    {
        std::cerr << "Failed to connect" << std::endl;
    }

    if (nullptr == session)
    {
        std::cerr << "Session object was not set" << std::endl;
        return nullptr;
    }

    kt_conn_session_t* conn_session = new kt_conn_session;
    conn_session->connection = connection;
    conn_session->session = session;
    return conn_session;
}

void* kt_disconnect ( kt_conn_session_t* conn_session )
{
    KIARA::Transport::KT_Connection* connection =
            reinterpret_cast<KIARA::Transport::KT_Connection*> (conn_session->connection);
    KIARA::Transport::KT_Session* session =
            reinterpret_cast<KIARA::Transport::KT_Session*> (conn_session->session);

    connection->disconnect(*session);

    delete connection;
    void* k_user_data = session->get_k_user_data();
    delete session;

    return k_user_data;
}

int kt_send ( kt_conn_session_t* conn_session, kt_msg_t* msg, int linger )
{
    KIARA::Transport::KT_Connection* connection =
            reinterpret_cast<KIARA::Transport::KT_Connection*> (conn_session->connection);
    KIARA::Transport::KT_Session* session =
            reinterpret_cast<KIARA::Transport::KT_Session*> (conn_session->session);
    KIARA::Transport::KT_Msg* message =
            reinterpret_cast<KIARA::Transport::KT_Msg*> (msg);

    int ret = connection->send(*message, *session, linger);

    kt_msg_destroy(msg);
    msg = nullptr;

    return ret;
}

kt_msg_t* kt_recv ( kt_conn_session_t* conn_session, int linger )
{
    KIARA::Transport::KT_Connection* connection =
            reinterpret_cast<KIARA::Transport::KT_Connection*> (conn_session->connection);
    KIARA::Transport::KT_Session* session =
            reinterpret_cast<KIARA::Transport::KT_Session*> (conn_session->session);

    KIARA::Transport::KT_Msg* message = new KIARA::Transport::KT_Msg;
    if (0 != connection->recv(*session, *message, linger)) {
        std::cerr << "Receive failed" << std::endl;
        return nullptr;
    }

    return reinterpret_cast<kt_msg_t*> (message);
}

kt_conn_session_t* kt_init_server ( kt_configuration_t* conf,
        kt_handle_t callback_handle)
{
    KIARA::Transport::KT_Configuration* config =
            reinterpret_cast<KIARA::Transport::KT_Configuration*> (conf);
    KIARA::Transport::KT_Connection* connection;

    if ( KT_WEBSERVER == config->get_application_type() ) {
        if ( 0 == config->get_port_number() ) {
            // TODO: How to check if we have enough privileges to allocate port 80?
            config->set_port_number(8080);
        }
        if ( KT_ZEROMQ == config->get_application_layer() ) {
            connection = new KIARA::Transport::KT_Zeromq();
            connection->set_configuration(*config);
            goto connection_object_created;
        } else {
            std::cerr << "Could not connect, you indicated an unsupported application layer" << std::endl;
        }
    }
    if ( KT_REQUESTREPLY == config->get_application_type() ) {
        if ( 0 == config->get_port_number()) {
            config->set_port_number(5555);
        }
        connection = new KIARA::Transport::KT_Zeromq();
        connection->set_configuration(*config);
        goto connection_object_created;
    }
    if ( KT_ZEROMQ == config->get_application_layer() )
    {
        connection = new KIARA::Transport::KT_Zeromq ();
        connection->set_configuration (*config);
        goto connection_object_created;
    }
    else {
        std::cerr << "Could not connect, you indicated an unsupported application layer" << std::endl;
        return nullptr;
    }

    connection_object_created:
    kt_conn_session_t* conn_session = new kt_conn_session;
    conn_session->connection = connection;
    conn_session->session = nullptr;

    if (NULL != callback_handle) {
        kt_register_handle(conn_session, callback_handle);
    }

    return conn_session;
}

void kt_register_handle ( kt_conn_session_t* conn_session, kt_handle_t callback_handle)
{
    KIARA::Transport::KT_Connection* connection =
            reinterpret_cast<KIARA::Transport::KT_Connection*> (conn_session->connection);
    // Memory leak, cb_wrapper is never deleted
    cb_wrapper = new KIARA::Transport::KT_C99_CallbackWrapper(callback_handle);
    connection->register_callback( cb_wrapper->make_function());
}

int kt_run_server ( kt_conn_session_t* conn_session )
{
    KIARA::Transport::KT_Connection* connection =
            reinterpret_cast<KIARA::Transport::KT_Connection*> (conn_session->connection);

    int ret = connection->bind();
    if ( 0 != ret )
    {
        std::cerr << "Failed to bind" << std::endl;
        std::cerr << std::strerror(ret) << std::endl;
        return -1;
    }
    conn_session->session = reinterpret_cast<void*>(connection->get_session()->begin()->second);
    return 0;
}

void* kt_stop_server ( kt_conn_session_t* conn_session, int linger )
{
    KIARA::Transport::KT_Connection* connection =
            reinterpret_cast<KIARA::Transport::KT_Connection*> (conn_session->connection);
    KIARA::Transport::KT_Session* session =
            reinterpret_cast<KIARA::Transport::KT_Session*> (conn_session->session);
    connection->unbind();
    return session->get_k_user_data();
}

#ifdef __cplusplus
}
#endif
