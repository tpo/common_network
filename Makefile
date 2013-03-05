clean:
	rm -f *~ *.bak

all: conn_client.c conn_client.h conn_server.c conn_server.h conn_io.c demo_tcp_client.c demo_tcp_server.c
	gcc -c conn_client.c -o conn_client.o
	gcc -c conn_server.c -o conn_server.o
	gcc -c conn_io.c -o conn_io.o
	# on linux:
	#gcc demo_tcp_client.c conn_client.o conn_io.o -o demo_tcp_client
	#gcc demo_tcp_server.c conn_server.o -o demo_tcp_server
	# on sunos
	gcc demo_tcp_client.c conn_client.o conn_io.o -lnsl -lsocket -o demo_tcp_client
	gcc demo_tcp_server.c conn_server.o -lnsl -lsocket -o demo_tcp_server

