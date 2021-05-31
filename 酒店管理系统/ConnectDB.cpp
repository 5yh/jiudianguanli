#include "pch.h"
#include<Windows.h>
#include<WinSock.h>
#include "mysql.h"
#pragma comment(lib,"libmysql.lib")
#pragma comment(lib,"wsock32.lib")

class Staff {
public:
    CString StaffID;
    CString StaffName;
    CString StaffPasswd;
    int Staffrwx;
};
class DataBase {
public:
	MYSQL* mysql = new MYSQL; //mysql连接  
	MYSQL_FIELD* fd;//字段列数组  
	char field[32][32];    //存字段名二维数组  
	MYSQL_RES* res; //这个结构代表返回行的一个查询结果集  
	MYSQL_ROW column; //一个行数据的类型安全(type-safe)的表示，表示数据行的列  
	char query[150]; //查询语句  

    bool ConnectDatabase(CString &status)
    {
        //初始化mysql  
        mysql_init(mysql);
        //返回false则连接失败，返回true则连接成功  
        if (!(mysql_real_connect(mysql, "wanglifa.f3322.net", "root", "123456", "hotel", 3306, NULL, 0))) //中间分别是主机，用户名，密码，数据库名，端口号（可以写默认0或者3306等），可以先写成参数再传进去  
        {
            status.Format(_T("Error connecting to database:\n%S"), mysql_error(mysql));
            return false;
        }
        else
        {
            status = "connected!";
            return true;
        }
        return true;
    }
    bool QueryStaff(int &StaffNum,Staff *worker1)//查员工
    {
        sprintf_s(query, "select * from staff"); //执行查询语句，这里是查询所有，user是表名，不用加引号，用strcpy也可以  
        //mysql_query(mysql, "set names gbk"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码  
        //返回0 查询成功，返回1查询失败  
        if (mysql_query(mysql, query))    //执行SQL语句
        {
            printf("Query failed (%s)\n", mysql_error(mysql));
            return false;
        }
        else
        {
            printf("query success\n");
        }
        //获取结果集  
        if (!(res = mysql_store_result(mysql)))   //获得sql语句结束后返回的结果集  
        {
            //printf("Couldn't get result from %s\n", mysql_error(mysql));
            StaffNum = 0;
            return false;
        }

        //打印数据行数  
        //printf("number of dataline returned: %I64d\n", mysql_affected_rows(mysql));
        StaffNum = mysql_affected_rows(mysql);
        //获取字段的信息  
        char* str_field[32];  //定义一个字符串数组存储字段信息  
        for (int i = 0; i < 3; i++)  //在已知字段数量的情况下获取字段名  
        {
            str_field[i] = mysql_fetch_field(res)->name;
        }
        for (int i = 0; i < 3; i++)  //打印字段  
            printf("%10s\t", str_field[i]);
        printf("\n");
        int i = 0;
        while (column = mysql_fetch_row(res))
        {
            worker1[i].StaffID.Format(_T("%S"), column[0]);
            worker1[i].StaffName.Format(_T("%S"), column[1]);
            worker1[i].StaffPasswd.Format(_T("%S"), column[2]);
            i++;
        }
        return true;
    }
};
extern Staff LoginStaff;
