/*
 * File:   newsimpletest.c
 * Author: aepp
 *
 * Created on 26.07.2013, 10:23:30
 */

#include <stdio.h>
#include <stdlib.h>
#include "client.h"

/*
 * Simple C Test Suite
 */

void testClient_curl() {
	void* args;
	void* result = client_curl(args);
	if (1 /*check result*/) {
		printf("%%TEST_FAILED%% time=0 testname=testClient_curl (newsimpletest) message=error message sample\n");
	}
}

void testClient_native() {
	void* args;
	void* result = client_native(args);
	if (1 /*check result*/) {
		printf("%%TEST_FAILED%% time=0 testname=testClient_native (newsimpletest) message=error message sample\n");
	}
}

int main(int argc, char** argv) {
	printf("%%SUITE_STARTING%% newsimpletest\n");
	printf("%%SUITE_STARTED%%\n");

	printf("%%TEST_STARTED%%  testClient_curl (newsimpletest)\n");
	testClient_curl();
	printf("%%TEST_FINISHED%% time=0 testClient_curl (newsimpletest)\n");

	printf("%%TEST_STARTED%%  testClient_native (newsimpletest)\n");
	testClient_native();
	printf("%%TEST_FINISHED%% time=0 testClient_native (newsimpletest)\n");

	printf("%%SUITE_FINISHED%% time=0\n");

	return (EXIT_SUCCESS);
}
