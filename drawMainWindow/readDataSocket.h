#ifndef _MYSOCKET_H
#define _MYSOCKET_H

#include "QtNetwork/QHostAddress"
#include "QtNetwork/QAbstractSocket"
#include "QDataStream"
#include "dataStruct.h"
#include "QtCore/QString"
#include "QtNetwork/QTcpSocket"
#include "QThread"
#include "QDir"



bool connectServer(QTcpSocket *);

void sendReadFileList(QTcpSocket *);//�����ȡ�ļ��б�

bool  sendReadFileName(QTcpSocket *);//����׼����ȡ�ļ�����server �ļ���ȡ��ť���º�ʼ

void readServerFlieList(); //��ȡserver���������ļ��б���

void displayTcpSocketError(QAbstractSocket::SocketError);

bool readFileContent(QTcpSocket *);

#endif // !_MYSOCKET_H
