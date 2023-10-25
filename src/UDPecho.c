#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern int errno;

int UDPecho(const char *host, const char *service);
int errexit(const char *format, ...);
int connectUDP(const char *host, const char *service);

#define LINELEN 128

/*----------------------------------------------
 * main - UDP client for ECHO service
 *----------------------------------------------
 */
int main(int argc, char **argv[])
{
   char *host = "localhost";
   char *service = "echo";

   switch(argc) {
   case 1:
      host = "localhost";
      break;
   case 3:
      service = argv[2];
   case 2: 
      service = argv[1];
      break;
   default:
      fprintf(stderr, "usage: TCPecho <host> <port>\n");
      exit(1);
   }
   UDPecho(host, service);
   exit(0);
}

/*-----------------------------------------------------------------------
 * UDPecho - send input to ECHO service on specified host and print reply
 *-----------------------------------------------------------------------
 */
int
UDPecho(const char *host, const char *service)
{
   char buf[LINELEN+1];
   int s,nchars;

   s = connectUDP(host, service);

   while(fgets(buf, sizeof buf, stdin)) {
      buf[LINELEN] = '\0';
      nchars = strlen(buf);
      (void) write(s, buf, nchars);

         if (read(s, buf, nchars < 0))
            errexit("socket read failed: %s\n", strerror(errno));

      fputs(buf, stdout);
   }
}