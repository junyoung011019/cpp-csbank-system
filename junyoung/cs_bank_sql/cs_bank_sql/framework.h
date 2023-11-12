#pragma once
/*Window Header*/
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#define SAFE_DELETE(p) { if(p) {delete (p); (p) = NULL;}}

/*SQL Header*/
#include <mysql.h>
#pragma comment(lib, "libmySQL.lib")
#include <sql.h>
#include <sqlext.h>

/*추후 사용할 Class Header*/