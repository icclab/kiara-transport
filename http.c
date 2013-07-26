/* 
 * File:   http.c
 * Author: aepp
 *
 * Created on 26. Juli 2013, 10:22
 */

#include "http_parser.h"
#include "http.h"

http_parser_context *server_worker_parse_request(zframe_t *frame_content) {
	char *content = zframe_strdup(frame_content);
	http_parser_context *context;
	int rc;

	context = malloc(sizeof(http_parser_context));
	//zframe_print(frame_content, NULL);
	//printf("Transmitted Content is: %s", content);
	
	context->settings.on_message_begin = 0;
	context->settings.on_url = on_url_cb;
	context->settings.on_status_complete = on_status_complete_cb;
	context->settings.on_header_field = on_header_field_cb;
	context->settings.on_header_value = on_header_value_cb;
	context->settings.on_headers_complete = 0;
	context->settings.on_body = on_body_cb;
	context->settings.on_message_complete = 0;

	http_parser_init(&context->parser, HTTP_REQUEST);
	context->parser.data = context;
	rc = http_parser_execute(&context->parser, &context->settings, content, strlen(content));
	return context;
}

int on_url_cb(http_parser *p, const char *at, size_t len) {
	http_parser_context *result = p->data;
	result->query_string = strndup(at + 0, len);
	return 0;
}

int on_header_field_cb(http_parser *p, const char *at, size_t len) {
	http_parser_context *result = p->data;
	return 0;
}

int on_message_begin_cb(http_parser *p) {
	http_parser_context *result = p->data;
	return 0;
}

int on_status_complete_cb(http_parser *p) {
	http_parser_context *result = p->data;
	return 0;
}

int on_header_value_cb(http_parser *p, const char *at, size_t len) {
	http_parser_context *result = p->data;
	return 0;
}

int on_headers_complete_cb(http_parser *p) {
	http_parser_context *result = p->data;
	return 0;
}

int on_body_cb(http_parser *p, const char *at, size_t len) {
	http_parser_context *result = p->data;
	return 0;
}

int on_message_complete_cb(http_parser *p) {
	http_parser_context *result = p->data;
	return 0;
}

