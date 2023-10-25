#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

MYSQL* connect() {
   MYSQL *con = mysql_init(NULL);

   if(con == NULL){
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
   }

   if(mysql_real_connect(con, "localhost", "phpmyadmin",
                         "testphp", NULL, 0, NULL, 0) == NULL)
   {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
   }

   return con;
}

int main(void)
{
   MYSQL *con = connect();

   if(!mysql_query(con, "DESCRIBE devweb"))
   {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
   }

   mysql_close(con);
   exit(0);
}