#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

#define SAFE_DELETE(p) {if(p) {delete (p); (p)=NULL;}}

/*SQL Header*/
#include <mysql.h>
#pragma commnet(lib,"libmySQL.lib")
#include <sql.h>
#include <sqlext.h>