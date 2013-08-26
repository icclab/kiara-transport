/* 
 * File:   http.h
 * Author: aepp
 *
 * Created on 26. Juli 2013, 10:24
 */
//Will be responsible for Request and Response. At the moment, there is only a
//request parser from joynet.
//For native ZMQ-Traffic (KIARA2KIARA) we use the ZMQ-Frames
#ifndef HTTP_H
#define	HTTP_H

#include <czmq.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct {
	struct http_parser parser;
	struct http_parser_url handle;
	struct http_parser_settings settings;
	char *query_string;
	char *host;
	char *user_agent;
	char *accept;
	char *tmp;
} http_parser_context;

/* main http request parser function */
http_parser_context *server_worker_parse_request(zframe_t *frame_content);

/* callback functions */
int on_url_cb(http_parser *p, const char *at, size_t len);
int on_header_field_cb(http_parser *p, const char *at, size_t len);
int on_header_value_cb(http_parser *p, const char *at, size_t len);
int on_body_cb(http_parser *p, const char *at, size_t len);
int on_message_begin_cb(http_parser *p);
int on_status_complete_cb(http_parser *p);
int on_headers_complete_cb(http_parser *p);
int on_message_complete_cb(http_parser *p);
/* END callback functions */

#ifdef	__cplusplus
}
#endif

#endif	/* HTTP_H */

