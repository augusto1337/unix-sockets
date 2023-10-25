#include "connectsock.h"

int connectUDP(const char *host, const char *service)
/*
   Arguments:
   host - name of host to wich connection is desired
   service - service associated with the desired port
*/
{
   return connectsock(host, service, "udp");
}