#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "connectTCP.h"
#include "errexit.h"

extern int errno;

int TCPDaytime(const char *host, const char *service);
int errexit(const char *format, ...);

#define LINELEN 128

/*------------------------------------------------------
 * main - TCP client for DAYTIME service
 *------------------------------------------------------
 */
int main(int argc, char **argv)
{
   char *host = "localhost";  /* host to use if none supplied */
   char *service = "daytime"; /* default service port         */

   switch(argc) {
   case 1:
      host = "localhost";
      break;
   case 3:
      host = argv[2];
   case 2:
      service = argv[1];
      break;
   default:
      fprintf(stderr, "usage: TCPDaytime <host> <port>\n");
      exit(1);
   }
   TCPDaytime(host, service);
   exit(0);
}

int TCPDaytime(const char *host, const char *service)
{
   char buf[LINELEN+1];
   int s,n;

   s = connectTCP(host, service);

   while( (n = read(s, buf, LINELEN)) > 0) {
      buf[n] = '\0';
      (void) fputs( buf, stdout );
   }

   return 1;
}