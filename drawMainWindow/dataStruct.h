#ifndef  _DATASTRUCT_H
#define  _DATASTRUCT_H

#include "QtCore/QString"
#include "QtGlobal"
#include "QtCore/QStringList"
#include "QTime"
#include "QFile"

/*
��������
*/

#define  SAR_STATE          0
#define  RF_PARAMETER_SET   1
#define  READ_FILELIST      2
#define  READ_FILE          3
#define  DELETE_FILE        4
#define  FORMAT_FILE        5
#define  RF_PARAMETER_TEST  6


//quint16 cmd_type = SAR_STATE; //����������ֻ������һ��cpp�ļ���ʹ�ã�������ظ�����

/*
����ϵͳ���������ȡclient���������������
*/
struct rf_Parameter_struct
{
	QString FRQ_String;
	QString BAND_String;
	QString PRf_String;
	QString PWD_String;
	QString ATT_String;
	QString TUNE_String;

	QString start = "start:";
	QString endx = "endx";
	//1 ����Ƶ��(��λMHz)
	//2 ����(��λMHz)
	//3 �����ظ�Ƶ��
	//4 ������
	//5 ˥����dB
	//6��гƵ��(NCO)
	//endx(����)
};

/*
��ȡ�ļ��б�
*/
struct File_List_struct
{

	QStringList  fileNameList;
};

/*
����Ҫ��ȡ���ļ�����server
*/
struct send_Read_File_struct
{
	quint16  flag; //1���Ƕ�һ���ļ�����0���Ƕ�����ļ�
	QString  start_fileName;
};
/*��ȡ�ļ�����*/
struct read_File_Content
{
	quint64 size;
	quint16 flag;
	//QString  fileName;
	QString fName;
	QFile *fileContent;
};

/*
ɾ���ļ�
*/
struct delete_File_struct
{
	QTime startTime;
	unsigned char line;
	QTime stopTime;
};





#endif // ! _DATASTRUCT_H
