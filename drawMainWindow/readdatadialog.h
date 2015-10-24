#ifndef READDATADIALOG_H
#define READDATADIALOG_H


#include <QDialog>
#include "ui_readdatadialog.h"

#include "QMessageBox"

//�ļ�
#include "QFile"
#include "QListWidgetItem"
#include "QFileDialog"
#include "QDir"

#include "QString"//��ȡ�ļ�����

#include "QTextStream"
#include "QCloseEvent"
#include "QtNetwork/QAbstractSocket"
#include "QTcpSocket"




class readDataDialog : public QDialog
{
	Q_OBJECT

public:
	readDataDialog(QWidget *parent = 0);
	~readDataDialog();


	QString readSignalFileLineEdit_str;//Ϊ����ʱ�����ȡ���ļ���Ϣ,

signals:
	void sendFileNameSignal(const QString&);//�����ź�

	void closeDialogEventSignal(const QString &);

private:
	Ui::readDataDialog *ui;
	//friend class drawMainWindow; //��Ե��ϵ


private slots:
	void readFileListSlot();
	void getReadFileNameFromFileListSlot(QListWidgetItem *);//���ļ��������ȡ�ļ��������ļ������

	//void readDataToMainWindowSlot();

				//void readDataDialog::readDataToMainWindowSlot() //���ɶ��������ӦΪ��qobject����������һ��ui_touwenj��
				//{
				//}
	void readSignalFlieAdmitButton_emitSlot();
	void readMultiFileAdmitButton_emitSlot();

	void displayTcpSocketError(QAbstractSocket::SocketError);//�õ����ڲ���
	void disconnectSlot();//�õ����ڲ���
	void readServerFlieListSlot(); //��ȡserver���������ļ��б���
	void readFileContent2();

private:
	void closeEvent(QCloseEvent *);
};




#endif // READDATADIALOG_H


