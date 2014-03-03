/*
 * KT_BSDSocket.cpp
 *
 *  Created on: Feb 7, 2014
 *      Author: habl
 */

#include "KT_BSDSocket.hpp"

namespace KIARA
{
namespace Transport
{

KT_BSDSocket::KT_BSDSocket()
{
	// TODO Auto-generated constructor stub

}

KT_BSDSocket::~KT_BSDSocket()
{
	// TODO Auto-generated destructor stub
}

KT_BSDSocket::KT_BSDSocket(const std::string& host)
{
}

void KT_BSDSocket::poller(int sock_desc)
{
	char buf[1024];
	std::vector<char> buffer;
	int k;
	struct sockaddr_in client;
	memset (&client, 0, sizeof(client));
	socklen_t len = sizeof(client);
	int temp_sock_desc = ::accept(sock_desc,(struct sockaddr*)&client,&len);
	    while(1)
	    {
	        k = ::recv(temp_sock_desc,buf,1024,0);
	        if(k>0)
	            printf("%s",buf);
	    }
	    close(temp_sock_desc);
}

KT_Session* KT_BSDSocket::connect(KT_Client& endpoint)
{
}

void KT_BSDSocket::send(KT_Msg& message, KT_Session& session, int linger)
{
}

KT_Msg KT_BSDSocket::recv(KT_Session& session, int linger)
{
}

void KT_BSDSocket::disconnect(KT_Session& session)
{
}

void KT_BSDSocket::register_callback(
		void (*callback)(KT_Msg& message, KT_Session* session, KIARA::Transport::KT_Connection* obj))
{
	_callback = callback;
}

void KT_BSDSocket::bind (std::string endpoint)
{
	// TODO: implement URI parser for protocol, hostname and port
    int k;
    struct sockaddr_in server;
    memset(&server,0,sizeof(server));
    sock_desc = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(7777);
    k = ::bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
    if (k != 0)
    	printf("bumm");
    k = ::listen(sock_desc,20);
    if (k != 0)
    	printf("bumm");

//    void* socket = new int;
//    socket = reinterpret_cast<void*>(sock_desc);
//    printf("int: %d, void* %d\n", sock_desc, reinterpret_cast<int>(socket));
//	KIARA::Transport::KT_Session* session = new KIARA::Transport::KT_Session();
//	session->set_socket ( socket ); // <-- put sock_desc on heap and cast to void*
//	session->set_endpoint ( endpoint );
//	_sessions.insert ( std::make_pair ( endpoint, session ) );

    interupted = false;
    poller_thread = new std::thread ( &KT_BSDSocket::poller, this, sock_desc );

}

void KT_BSDSocket::unbind()
{
	interupted = true;
	poller_thread->join();
	close(sock_desc);
}

} /* namespace Transport */
} /* namespace KIARA */
