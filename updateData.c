#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdint.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	int pid;
    char *args[4] = {"./infoSound", NULL, NULL, NULL};
    char room[10];
    char quality[10];
    
	int fd;
	unsigned char receive_data = 0;
	printf("Raspberry's receiving: \n");
	wiringPiSetup();
	fd = serialOpen ("/dev/ttyAMA0", 115200);
	
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char *server = "localhost";
	char *user = "admin";
	char *password = "123456"; 
	char *database = "service_robot";
	char sql[200];
	
	conn = mysql_init(NULL);
	mysql_real_connect(conn,server,user,password,database,0,NULL,0); 
	
	while(1)
	{
		if(serialDataAvail(fd)>0)
		{
			receive_data = serialGetchar(fd);
			printf("data = %d\n", receive_data);
			fflush(stdout);
			if (receive_data > 100)
			{
				sprintf(sql, "select * from set_data");
				mysql_query(conn,sql);
				res = mysql_store_result(conn); 	
				row = mysql_fetch_row(res);
				
				sprintf(room,"%d",receive_data%100/10);
				sprintf(quality, "%c", *row[receive_data%10]);
				args[1] = room;
				args[2] = quality;
				pid = fork();
				if (pid != 0)
				{
					execvp(args[0], args);
				}
			}
			else
			{
				sprintf(sql,"update update_data set room_%d='%d'", receive_data/10, receive_data%10);
				mysql_query(conn,sql);
				if (receive_data%10 == 1)
				{
					pid = fork();
					if (pid != 0)
					{
						execvp("./thankSound", NULL);
					}
				}	
			}
		}
	}
	
	mysql_close(conn);
	return 0;
}
