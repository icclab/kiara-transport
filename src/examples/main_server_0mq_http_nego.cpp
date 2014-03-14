/*
 * main_client_0mq_req.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: habl
 */


#include "../core/reco_engine.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>

int main() {
	std::cout << "test";
	RecoServer* myRecoServer = new RecoServer("tcp://localhost:81");
	std::cout << "Init Object";
	myRecoServer->RunServer();
	std::cout << "Running Server";
	exit(0);
}
