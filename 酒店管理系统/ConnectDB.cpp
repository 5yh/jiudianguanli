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
class Guest {
public:
    CString GuestID;
    CString GuestName;
    CString PhoneNumber;
};
class DataBase {
public:
	MYSQL* mysql = new MYSQL; //mysql����  
	MYSQL_FIELD* fd;//�ֶ�������  
	char field[32][32];    //���ֶ�����ά����  
	MYSQL_RES* res; //����ṹ�������е�һ����ѯ�����  
	MYSQL_ROW column; //һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���  
	char query[300]; //��ѯ���  

    bool ConnectDatabase(CString &status)
    {
        //��ʼ��mysql  
        mysql_init(mysql);
        //����false������ʧ�ܣ�����true�����ӳɹ�  
        if (!(mysql_real_connect(mysql, "wanglifa.f3322.net", "root", "1234568", "hotel", 3306, NULL, 0))) //�м�ֱ����������û��������룬���ݿ������˿ںţ�����дĬ��0����3306�ȣ���������д�ɲ����ٴ���ȥ  
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
    bool QueryStaff(int &StaffNum,Staff *worker1)//��Ա��
    {
        sprintf_s(query, "select * from staff"); //ִ�в�ѯ��䣬�����ǲ�ѯ���У�user�Ǳ��������ü����ţ���strcpyҲ����  
        mysql_query(mysql, "set names gb2312"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������  
        //����0 ��ѯ�ɹ�������1��ѯʧ��  
        if (mysql_query(mysql, query))    //ִ��SQL���
        {
            printf("Query failed (%s)\n", mysql_error(mysql));
            return false;
        }
        else
        {
            printf("query success\n");
        }
        //��ȡ�����  
        if (!(res = mysql_store_result(mysql)))   //���sql�������󷵻صĽ����  
        {
            StaffNum = 0;
            return false;
        }

        //��ӡ��������  
        StaffNum = mysql_affected_rows(mysql);
        //��ȡ�ֶε���Ϣ  
        char* str_field[32];  //����һ���ַ�������洢�ֶ���Ϣ  
        for (int i = 0; i < 3; i++)  //����֪�ֶ�����������»�ȡ�ֶ���  
        {
            str_field[i] = mysql_fetch_field(res)->name;
        }
        for (int i = 0; i < 3; i++)  //��ӡ�ֶ�  
            printf("%10s\t", str_field[i]);
        printf("\n");
        int i = 0;
        while (column = mysql_fetch_row(res))
        {
            worker1[i].StaffID = column[0];
            worker1[i].StaffName = column[1];
            worker1[i].StaffPasswd = column[2];
            worker1[i].Staffrwx= column[3];
            i++;
        }
        return true;
    }
    bool ChangePasswd(char Passwd[],char StaffID[])//�޸�Ա������
    {
        char QueryArray1[200] = "UPDATE `hotel`.`staff` SET `StaffPasswd` = '";
        char QueryArray2[200] = "' WHERE `StaffID` = '";
        char QueryArray3[10] = "'";
        strcat(QueryArray1, Passwd);
        strcat(QueryArray1, QueryArray2);
        strcat(QueryArray1, StaffID);
        strcat(QueryArray1, QueryArray3);
        sprintf_s(query, QueryArray1); 
        if (mysql_query(mysql, query))    //ִ��SQL���
        {
            printf("Query failed (%s)\n", mysql_error(mysql));
            MessageBox(NULL, TEXT("�޸�ʧ����."), TEXT("Title"), MB_OKCANCEL);
            return false;
        }
        else
        {
            printf("query success\n");
            MessageBox(NULL, TEXT("�޸ĳɹ���."), TEXT("Title"), MB_OKCANCEL);
        }
        mysql_close(mysql);
        return true;
    }
    bool QueryRoom(int& RoomNum, Room* room)//�鷿��
    {
        char A[299] = "SELECT room.RoomID,room.RoomType,RoomAddress,RoomPrice,StaffName FROM `room`,roomtypesize, roommanage, staff WHERE room.RoomType = roomtypesize.RoomType AND room.RoomID = roommanage.RoomID AND roommanage.StaffID = staff.StaffID";
        sprintf_s(query, A); //ִ�в�ѯ��䣬�����ǲ�ѯ���У�user�Ǳ��������ü����ţ���strcpyҲ����  
        mysql_query(mysql, "set names gb2312"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������  
        //����0 ��ѯ�ɹ�������1��ѯʧ��  
        if (mysql_query(mysql, query))    //ִ��SQL���
        {
            printf("Query failed (%s)\n", mysql_error(mysql));
            return false;
        }
        else
        {
            printf("query success\n");
        }
        //��ȡ�����  
        if (!(res = mysql_store_result(mysql)))   //���sql�������󷵻صĽ����  
        {
            RoomNum = 0;
            return false;
        }

        //��ӡ��������  
        RoomNum = mysql_affected_rows(mysql);
        //��ȡ�ֶε���Ϣ  
        char* str_field[100];  //����һ���ַ�������洢�ֶ���Ϣ  
        for (int i = 0; i < 3; i++)  //����֪�ֶ�����������»�ȡ�ֶ���  
        {
            str_field[i] = mysql_fetch_field(res)->name;
        }
        for (int i = 0; i < 3; i++)  //��ӡ�ֶ�  
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
    bool QueryGuest(int& GuestNum, Guest *guest)//�鷿��
    {
        sprintf_s(query, "select * from guest"); //ִ�в�ѯ��䣬�����ǲ�ѯ���У�user�Ǳ��������ü����ţ���strcpyҲ����  
        mysql_query(mysql, "set names gb2312"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������  
        //����0 ��ѯ�ɹ�������1��ѯʧ��  
        if (mysql_query(mysql, query))    //ִ��SQL���
        {
            printf("Query failed (%s)\n", mysql_error(mysql));
            return false;
        }
        else
        {
            //MessageBox(NULL, TEXT("�ɹ�"), TEXT("ASJAS"), 0);
            printf("query success\n");
        }
        //��ȡ�����  
        if (!(res = mysql_store_result(mysql)))   //���sql�������󷵻صĽ����  
        {
            
            GuestNum = 0;
            return false;
        }

        //��ӡ��������  
        GuestNum = mysql_affected_rows(mysql);
        //��ȡ�ֶε���Ϣ  
        char* str_field[100];  //����һ���ַ�������洢�ֶ���Ϣ  
        for (int i = 0; i < 3; i++)  //����֪�ֶ�����������»�ȡ�ֶ���  
        {
            str_field[i] = mysql_fetch_field(res)->name;
        }
        int i = 0;
        while (column = mysql_fetch_row(res))
        {
            guest[i].GuestID = column[0];
            guest[i].GuestName = column[1];
            guest[i].PhoneNumber = column[2];
            i++;
        }
        return true;
    }
    bool AddGuest(CString NewGuestID,CString NewGuestName,CString NewGuestPhone)//�鷿��
    {
        CString QueryArray = TEXT("INSERT INTO `hotel`.`guest` (`GuestID`, `Name`, `PhoneNumber`) VALUES (");
        QueryArray += NewGuestID;
        QueryArray += TEXT(", \'");
        QueryArray += NewGuestName;
        QueryArray += TEXT("\', ");
        QueryArray += NewGuestPhone;
        QueryArray += TEXT(")");
        CStringA temp;
        temp = QueryArray;
        sprintf_s(query, temp.GetBuffer()); //ִ�в�ѯ��䣬�����ǲ�ѯ���У�user�Ǳ��������ü����ţ���strcpyҲ����  
        mysql_query(mysql, "set names gb2312"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������  
        //����0 ��ѯ�ɹ�������1��ѯʧ��  
        if (mysql_query(mysql, query))    //ִ��SQL���
        {
            printf("Query failed (%s)\n", mysql_error(mysql));
            return false;
        }
        else
        {
            //MessageBox(NULL, TEXT("�ɹ�"), TEXT("ASJAS"), 0);
            printf("query success\n");
        }
        //��ȡ�����  
        if (!(res = mysql_store_result(mysql)))   //���sql�������󷵻صĽ����  
        {

            return false;
        }
        return true;
    }
    bool OrderRoom()
    {
        CString QueryArray = TEXT("INSERT INTO `hotel`.`guest` (`GuestID`, `Name`, `PhoneNumber`) VALUES (");
        CStringA temp;
        temp = QueryArray;
        sprintf_s(query, temp.GetBuffer()); //ִ�в�ѯ��䣬�����ǲ�ѯ���У�user�Ǳ��������ü����ţ���strcpyҲ����  
        mysql_query(mysql, "set names gb2312"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������  
        //����0 ��ѯ�ɹ�������1��ѯʧ��  
        if (mysql_query(mysql, query))    //ִ��SQL���
        {
            printf("Query failed (%s)\n", mysql_error(mysql));
            return false;
        }
        else
        {
            //MessageBox(NULL, TEXT("�ɹ�"), TEXT("ASJAS"), 0);
            printf("query success\n");
        }
        //��ȡ�����  
        if (!(res = mysql_store_result(mysql)))   //���sql�������󷵻صĽ����  
        {

            return false;
        }
        return true;
    }
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
