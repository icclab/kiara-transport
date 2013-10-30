# General

Transport Library RFC style documentation, this document describes the binding provided from the transport library to the KIARA upper layers.

## Language

C++11, without GNU or clang or MSVC extensions, do not use std::thread.

Use as little third party libraries as possible (Boost) to keep the number of dependencies as low as possible.

## Memory handling

The code allocating memory is also responsible to free it.

If you cannot ensure this, you MUST provide a struct with a function freeing the memory.

```
struct foo {
	void *ptr;
	void free_foo(foo *to_be_freed);
	
	~foo()
	{
		if (ptr)
			free_foo (ptr);
	}
}

…

foo.free_foo (foo);
free (foo);
```

# Constructs

## kt_conn_session

```
typedef struct kt_conn_session {
	kt_conn_session_info* _info;
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
	
	~kt_msg()
	{
		if (free_payload && payload)
			free_payload (payload);
	}
} kt_msg;
```

## remote endpoint

A valid remote endpoint may look like "tcp://192.168.1.1:1234" or "dds://foobar.tld:6666" and is of type char*.

The EBNF:

```
/* http://railroad.my28msec.com/rr/ui for nice railroad diagrams */
remote-endpoint ::= (protocol)? url port
protocol ::= ( "http" | "tcp"  | "udp" | "dds" )?
url ::= ( ip | hostname )
ip ::=  ipnumblock ":" ipnumblock ":" ipnumblock ":" ipnumblock ":" ipnumblock ":" ipnumblock ":" ipnumblock ":" ipnumblock
ipnumblock ::= hex hex hex hex
hostname ::= ialpha (. hostname )?
port ::= "1".."65535"

xalpha ::= (alpha | digit | safe | extra | escape)
xalphas ::= xalpha ( xalphas )?
xpalpha ::= (xalpha | "+")
xpalphas ::= xpalpha ( xpalphas )?
ialpha ::= alpha ( xalphas )?
digits ::= digit ( digits )?
safe ::= ("$" | "-" | "_" | "@" | "." | "&" | "+" | "-")
extra ::= ("!" | "*" | '"' | "'" | "(" | ")" | ",")
escape ::= "%" hex hex
hex ::= (digit | "a" | "b" | "c" | "d" | "e" | "f" | "A" | "B" | "C" | "D" | "E" | "F")

```

# Client

## connect

Connect the client to a remote server

`connect` requires a valid remote endpoint description according to its transport stack.

The `connect` must return a kt_conn_session and nullptr on failure.

## send

Send data to the remote host

`send` requires a kt_conn_session and a reference to a kt_msg.

The `send` shall queue the message for delivery and must delete the kt_msg object if the delivery was successful.

## recv

Receive data from the remote host

`recv` requires a kt_conn_session.

The `recv` must return a reference to a kt_msg or a nullptr if there was no data received. The developper has now control over the returned kt_msg and must destroy the received kt_msg object.

## disconnect

# Server