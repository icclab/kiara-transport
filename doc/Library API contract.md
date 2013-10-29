# General

Transport Library RFC style documentation, this document describes the binding provided from the transport library to the KIARA upper layers.

## Language
C++11 (without GNU or clang or MSVC extensions)

## Memory handling

The code allocating memory is also responsible to free it.

If you cannot ensure this, you MUST provide a struct with a function freeing the memory.

```
struct foo {
	void *ptr;
	void free_foo(foo *to_be_freed);
}

…

foo.free_foo (foo);
free (foo);
```

# Constructs

## kt_conn_session

```
typedef struct kt_conn_session {
	void* kt_conn_session_info;
	void* k_user_data;
} kt_conn_session;
```

## kt_msg

```
typedef struct kt_msg {
	std::map <std::string, std::string> metadata;
	void* payload;
	std::size_t payload_size;
	void (*free_payload) (void*);
}
```

# Client

## connect

Connect the client to a remote server

`connect` requires a valid remote endpoint description according to its transport stack.

The `connect` shall return a kt_conn_session and null on failure.

A valid remote endpoint may look like "tcp://192.168.1.1:1234" or "dds://foobar.tld:6666".

## send

## recv

## disconnect

# Server