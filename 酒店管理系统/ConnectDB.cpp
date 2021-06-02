#include "pch.h"
#include<Windows.h>
#include<WinSock.h>
#include "mysql.h"
#include <string.h>
#pragma comment(lib,"libmysql.lib")
#pragma comment(lib,"wsock32.lib")

class Staff {
public:
    CString StaffID;
    CString StaffName;
    CString StaffPasswd;
    char CharStaffID[100];
    /*char CharStaffName[100];*/
    char CharStaffPasswd[100];
    CString Staffrwx;
};
class Room {
public:
    CString RoomID;
    CString RoomType;
    CString RoomAddress;
    CString RoomPrice;
    CString StaffName;
};
class DataBase {
public:
	MYSQL* mysql = new MYSQL; //mysql连接  
	MYSQL_FIELD* fd;//字段列数组  
	char field[32][32];    //存字段名二维数组  
	MYSQL_RES* res; //这个结构代表返回行的一个查询结果集  
	MYSQL_ROW column; //一个行数据的类型安全(type-safe)的表示，表示数据行的列  
	char query[300]; //查询语句  

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
        mysql_query(mysql, "set names gb2312"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码  
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
            StaffNum = 0;
            return false;
        }

        //打印数据行数  
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
            char strID[100] = {};
            char strPasswd[100] = {};
            strcpy(strID, column[0]);
            strcpy(strPasswd, column[2]);
            worker1[i].StaffID.Format(_T("%S"), column[0]);
            worker1[i].StaffName.Format(_T("%S"), column[1]);
            worker1[i].StaffPasswd.Format(_T("%S"), column[2]);
            worker1[i].Staffrwx.Format(_T("%S"), column[3]);
            strcpy(worker1[i].CharStaffID, strID);
            /*strcpy(worker1[i].CharStaffName, column[1]);*/
            strcpy(worker1[i].CharStaffPasswd, column[2]);
            i++;
        }
        return true;
    }
    bool ChangePasswd(char Passwd[],char StaffID[])//修改员工密码
    {
        char QueryArray1[200] = "UPDATE `hotel`.`staff` SET `StaffPasswd` = '";
        char QueryArray2[200] = "' WHERE `StaffID` = '";
        char QueryArray3[10] = "'";
        strcat(QueryArray1, Passwd);
        strcat(QueryArray1, QueryArray2);
        strcat(QueryArray1, StaffID);
        strcat(QueryArray1, QueryArray3);
        sprintf_s(query, QueryArray1); 
        if (mysql_query(mysql, query))    //执行SQL语句
        {
            printf("Query failed (%s)\n", mysql_error(mysql));
            MessageBox(NULL, TEXT("修改失败了."), TEXT("Title"), MB_OKCANCEL);
            return false;
        }
        else
        {
            printf("query success\n");
            MessageBox(NULL, TEXT("修改成功了."), TEXT("Title"), MB_OKCANCEL);
        }
        mysql_close(mysql);
        return true;
    }
    bool QueryRoom(int& RoomNum, Room* room)//查房间
    {
        char A[299] = "SELECT room.RoomID,room.RoomType,RoomAddress,RoomPrice,StaffName FROM `room`,roomtypesize, roommanage, staff WHERE room.RoomType = roomtypesize.RoomType AND room.RoomID = roommanage.RoomID AND roommanage.StaffID = staff.StaffID";
        sprintf_s(query, A); //执行查询语句，这里是查询所有，user是表名，不用加引号，用strcpy也可以  
        mysql_query(mysql, "set names gb2312"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码  
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
            RoomNum = 0;
            return false;
        }

        //打印数据行数  
        RoomNum = mysql_affected_rows(mysql);
        //获取字段的信息  
        char* str_field[100];  //定义一个字符串数组存储字段信息  
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
            room[i].RoomID = column[0];
            room[i].RoomType = column[1];
            room[i].RoomAddress = column[2];
            room[i].RoomPrice = column[3];
            room[i].StaffName = column[4];
            i++;
        }
        return true;
    }
    void CloseConnection(DataBase A)
    {
        mysql_close(A.mysql);
    }
};
class Guest {
public:
    CString GuestID;
    CString Name;
    CString PhoneNumber;
};
class CstringChar {
public:
    /*char* __Ary_(CString str)
    {
        int len = str.GetLength();
        char* ch = new char[len];
        //
        int i;
        for (i = 0; i < len; i++)
        {
            ch[i] = str.GetAt(i);
        }
        ch[i] = '\0';
        return ch;
    }*/
};
