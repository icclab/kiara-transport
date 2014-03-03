/*
 * KT_BSDSocket.h
 *
 *  Created on: Feb 7, 2014
 *      Author: habl
 */

#ifndef KT_BSDSOCKET_H_
#define KT_BSDSOCKET_H_

#include "KT_Connection.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <thread>
#include <unistd.h>

namespace KIARA {
namespace Transport {

class KT_BSDSocket : public KIARA::Transport::KT_Connection
{
private:
	int sock_desc;
	std::thread* poller_thread;
	bool interupted;
	void poller ( int sock_desc );

public:
	KT_BSDSocket();
	virtual ~KT_BSDSocket();
	KT_BSDSocket ( std::string const& host);

	/**
	 * @return int
	 * @param endpoint Where to connect to
	 */
	KT_Session*
	connect ( KT_Client& endpoint );

	/**
	 * @param message Message for the receipient
	 * @param linger Linger time before it aborts if sending synchronous,
	 *    0 will block forever, -1 will make the call asynchronous
	 */
	void
	send ( KT_Msg& message, KT_Session& session, int linger = 0 );

	/**
	 * @return KIARA::Transport::KT_Msg
	 * @param linger Linger time before it aborts if receiving synchronous,
	 *    0 will block forever, -1 will make the call asynchronous and only
	 *    return a message if there was one previously received
	 */
	KT_Msg
	recv ( KT_Session& session, int linger = 0 );

	/**
	 * @return void*
	 */
	void
	disconnect ( KT_Session& session );

	/**
	 * callback function must accept KT_Msg* and KT_Session* object
	 * @param callback Function to be called when a message arrives
	 */
	void register_callback ( void (*callback)(KT_Msg& message, KT_Session* session, KT_Connection* obj) );

	/**
	 * bind requires a valid callback handler which is called when a message is
	 * received, it binds according to the set configuration
	 */
	void bind ( std::string endpoint );

	/**
	 * stops listening to incomming messages
	 */
	void unbind ( );


};
} /* end of namespace Transport */
} /* end of namespace KIARA */
#endif /* KT_BSDSOCKET_H_ */
