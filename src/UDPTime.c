#include <sys/types.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUFSIZE 64

#define UNIXEPOCH 2208988800UL  /* UNIX epoch, in UCT secs      */
#define MSG "what time is it?\n"

extern int errno;

int connectUDP(const char *host, const char *format);
int errexit(const char *format, ...);

/*------------------------------------------------------------------
 * main - UDP client for TIME service that prints the resulting time
 *------------------------------------------------------------------
 */
int main(int argc, char **argv[])
{
   char *host = "localhost";
   char *service = "time";
   time_t now;
   int s,n;

   switch (argc){
   case 1:
      host = "localhost";
      break;
   case 3:
      service = argv[2];
   case 2:
      host = argv[1];
      break;
   default:
      fprintf(stderr, "usage: UDPTime [host [port]\n]");
      exit(1);
   }

   s = connectUDP(host, service);

   (void) write(s, MSG, strlen(MSG));

   /* Read the time */
   n = read(s, (char *)&now, sizeof now);
   if (n < 0)
      errexit("read failed: %s\n", strerror(errno));
   now = ntohl((unsigned long)now);   /* put host in order */
   now -= UNIXEPOCH;     /* convert UCT to UNIX epoch */

   printf("%s", ctime(&now));
   exit(0);
}