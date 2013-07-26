/* 
 * File:   client.h
 * Author: aepp
 *
 * Created on 24. Juli 2013, 14:25
 */

#ifndef CLIENT_H
#define	CLIENT_H

#ifdef	__cplusplus
extern "C" {
#endif

static void *client_native(void *args);
static void *client_curl(void *args);

#ifdef	__cplusplus
}
#endif

#endif	/* CLIENT_H */

