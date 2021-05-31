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
	MYSQL* mysql = new MYSQL; //mysql����  
	MYSQL_FIELD* fd;//�ֶ�������  
	char field[32][32];    //���ֶ�����ά����  
	MYSQL_RES* res; //����ṹ�������е�һ����ѯ�����  
	MYSQL_ROW column; //һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���  
	char query[150]; //��ѯ���  

    bool ConnectDatabase(CString &status)
    {
        //��ʼ��mysql  
        mysql_init(mysql);
        //����false������ʧ�ܣ�����true�����ӳɹ�  
        if (!(mysql_real_connect(mysql, "wanglifa.f3322.net", "root", "123456", "hotel", 3306, NULL, 0))) //�м�ֱ����������û��������룬���ݿ������˿ںţ�����дĬ��0����3306�ȣ���������д�ɲ����ٴ���ȥ  
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
        //mysql_query(mysql, "set names gbk"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������  
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
            //printf("Couldn't get result from %s\n", mysql_error(mysql));
            StaffNum = 0;
            return false;
        }

        //��ӡ��������  
        //printf("number of dataline returned: %I64d\n", mysql_affected_rows(mysql));
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
            worker1[i].StaffID.Format(_T("%S"), column[0]);
            worker1[i].StaffName.Format(_T("%S"), column[1]);
            worker1[i].StaffPasswd.Format(_T("%S"), column[2]);
            i++;
        }
        return true;
    }
};
extern Staff LoginStaff;
