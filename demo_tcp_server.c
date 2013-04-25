/*
*  C Implementation: server
*
* Description: 
*
*
* Author: Tomas Pospisek <tpo_deb@sourcepole.ch>, (C) 2006
*
* Copyright: See COPYING file that comes with this distribution
*
*/
#include <stdlib.h>      // exit
#include <stdio.h>
#include <string.h>      // strlen
#include <unistd.h>      // getopt
#include "conn_server.h"
#include "conn_io.h"     // send_all

void report_error( char* message ) {
  fprintf( stderr, "ERROR: %s\n", message );
}

// Roles that a node can play
#define HOP    0
#define ZIEL   1
#define QUELLE 2
short node_role = HOP;

#define NO_TCP_PORT -1
int   tcp_port  = NO_TCP_PORT;

static void usage()
{
  printf("Usage: server port [-z|-q]\n");
  exit(0);
}

void parse_options( int argc, char *argv[])
{
  char optchar;

  if (argc < 2)
    usage();
  tcp_port = atoi(argv[1]);

  while( ( optchar = getopt( argc-1, argv+1, "hqz" ) ) != -1 ) {
    switch( optchar ) {
      case 'z':
        printf("ZIEL\n");
        node_role = ZIEL;
        break;
      case 'q':
        printf("QUELLE\n");
        node_role = QUELLE;
        break;
      case 'h':
      case '?':
      default:
		break;
    }
  }
}

int main(int argc, char *argv[])
{
  int sock_fd, connection_fd;

  parse_options( argc, argv );

  if( (sock_fd = listen_on_port(tcp_port) ) < 0 ) {
    report_error("failed to listen on the port");
    return sock_fd;
  }

  if( (connection_fd = connect_with_client( sock_fd )) != 0) {
    send_all(connection_fd, "Hello\n",         strlen("Hello\n"));
    send_all(connection_fd, "Hello Goodbye\n", strlen("Hello Goodbye\n"));
  }
  else {
    report_error("failed to get a client connection");
  }
  disconnect_client( sock_fd);

  return 0; 
}
