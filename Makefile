clean:
	rm -f *~ *.bak

all: conn_handling_client.c conn_handling_client.h conn_handling_server.c conn_handling_server.h conn_read_line.c demo_tcp_client.c demo_tcp_server.c
	gcc -c conn_handling_client.c -o conn_handling_client.o
	gcc -c conn_handling_server.c -o conn_handling_server.o
	gcc -c conn_read_line.c -o conn_read_line.o
	# on linux:
	#gcc demo_tcp_client.c conn_handling_client.o conn_read_line.o -o demo_tcp_client
	#gcc demo_tcp_server.c conn_handling_server.o -o demo_tcp_server
	# on sunos
	gcc demo_tcp_client.c conn_handling_client.o conn_read_line.o -lnsl -lsocket -o demo_tcp_client
	gcc demo_tcp_server.c conn_handling_server.o -lnsl -lsocket -o demo_tcp_server

