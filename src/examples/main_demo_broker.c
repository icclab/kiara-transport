/*
 * main_demo_broker.c
 *
 *  Created on: Apr 15, 2014
 *      Author: habl
 */

#include <stdlib.h>
#include <stdio.h>
#include "../../include/k_transport.h"
#include "../../src/core/KT_Configuration.h"

void cb (kt_conn_session_t*, kt_msg_t*);
void cb (kt_conn_session_t* conn_sess, kt_msg_t* msg) {
    // When we get the HTTP request, we connect to a req/rep service and
    // forward the answer back to the HTTP client
}

int main ()
{
    // Bind as a HTTP service
}
