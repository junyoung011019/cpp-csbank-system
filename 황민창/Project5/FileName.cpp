#include <mysql.h>
#include <stdio.h>
#pragma comment(lib, "libmySQL.lib")

int main()
{
	MYSQL Conn;
	MYSQL* ConnPtr = NULL;
	MYSQL_RES* Result;
	MYSQL_ROW Row;
	int Stat;

	mysql_init(&Conn);

	ConnPtr = mysql_real_connect(&Conn, "localhost", "root", "0000", "sakila", 3306, (char*)NULL, 0);

	if (ConnPtr == NULL)
	{
		fprintf(stderr, "mysql 연결실패:%s", mysql_error(&Conn));
		return 1;
	}
	
	const char *Query = "SELECT * FROM tb_user";
	Stat = mysql_query(ConnPtr, Query);
	if (Stat != 0)
	{
		fprintf(stderr, "Mysql query error:%s\n", mysql_error(&Conn));
		return 1;
	}
	Result = mysql_store_result(ConnPtr);
	while ((Row = mysql_fetch_row(Result)) != NULL)
	{
		printf("%s %s %s\n", Row[0], Row[1], Row[2]);
	}
	mysql_free_result(Result);

	mysql_close(ConnPtr);

	return 0;
}
