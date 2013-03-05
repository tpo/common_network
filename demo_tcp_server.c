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
#include <stdlib.h>     // exit
#include <stdio.h>
#include <string.h>     // strlen
#include <unistd.h>     // getopt
#include "conn_server.h"
#include "conn_io.h"     // send_all

void report_error( char* message ) {
  fprintf( stderr, "ERROR: %s\n", message );
}

void parse_options( int argc, char *argv[])
{
  char optchar;

  if (argc < 2) {
    report_error("no port provided");
    exit( -1);
  }
  while( ( optchar = getopt( argc, argv, "h" ) ) != -1 ) {
    switch( optchar ) {
      case 'h':
      case '?':
      default:
        printf("Usage: server port\n");
        exit( 0 );
    }
  }
}

int main(int argc, char *argv[])
{
  int sock_fd, connection_fd;
  pthread_t pthread;
  extern int optind;                // from unistd.h:getopt

  parse_options( argc, argv );

  if( (sock_fd = listen_on_port( atoi(argv[optind]) )) < 0 ) {
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
