#include "readdatadialog.h"
#include "drawmainwindow.h"
#include "QThread"
#include "dataStruct.h"
#include "readDataSocket.h"

quint16 cmd_type;//�����ļ�ʹ��external������
struct File_List_struct  filelist;

QTcpSocket * socket_RD;
readDataDialog::readDataDialog(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::readDataDialog;
	ui->setupUi(this);
	setMinimumSize(530, 641);
	setMaximumSize(530, 641);

	//socket_RD =  new QTcpSocket;

	QObject::connect(ui->readFileListButton, SIGNAL(clicked()), this, SLOT(readFileListSlot()));
	
		
	QObject::connect(ui->readFlieListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(getReadFileNameFromFileListSlot(QListWidgetItem*)));

	QObject::connect(ui->readSignlaFileAdmitButton, SIGNAL(clicked()), this, SLOT(readSignalFlieAdmitButton_emitSlot()));
	QObject::connect(ui->readMultiFileAdmitButton, SIGNAL(clicked()), this, SLOT(readMultiFileAdmitButton_emitSlot()));
}
//QString quanjuString = QString::fromLocal8Bit("�����ݣ���!");

readDataDialog::~readDataDialog()
{
	delete ui;
	//delete socket_RD;
}


void readDataDialog::readFileListSlot()//��ȡ�ļ��б�
{
	ui->readFlieListWidget->clear();//����б�

	socket_RD = new QTcpSocket;
	bool ok = connectServer(socket_RD);
	if (!ok)
	{
		QMessageBox::warning(this, "error", socket_RD->errorString());
	}

	//QObject::connect(socket_RD, SIGNAL(connected()), this, SLOT(sendReadFileList(socket_RD)));
	sendReadFileList(socket_RD); //Ӧ��ʹ��connected�ź��ٷ��ͣ�������������
	connect(socket_RD, SIGNAL(QAbstractSocket::SocketError), this, SLOT(displayTcpSocketError()));
	connect(socket_RD, SIGNAL(disconnected()), this, SLOT(disconnectSlot()));
	QObject::connect(socket_RD, SIGNAL(readyRead()), this, SLOT(readServerFlieListSlot()));
	//socket_RD->abort();

	//socket_RD->write((const char*)& cmd_type, sizeof(quint16)); //ֱ��дһ����ȥ��ȡ������ԣ�����qtversionδ��Ӧ
	
	
}


/*��ȡ�ļ��б��е�ĳ���ļ����������ļ����봰��*/
void readDataDialog::getReadFileNameFromFileListSlot(QListWidgetItem *item)
{
	//QMessageBox::information(this, "test", "item:" + item->text());
	ui->readSignalFileLineEdit->setText(item->text());
	ui->readMultiFileLineEdit->setText(item->text());

}

//�źźͲ۵ķ�ʽ����dialogҪ�����ļ� ���� ��ʾ��mainwindow���� 
QString exterStr;
void readDataDialog::readSignalFlieAdmitButton_emitSlot() //���¾ͷ���һ���źų�ȥ
{
	socket_RD = new QTcpSocket;
	bool ok = connectServer(socket_RD);
	if (!ok)
	{
		QMessageBox::warning(this, "error", socket_RD->errorString());
	}
	exterStr  = ui->readSignalFileLineEdit->text();
	sendReadFileName(socket_RD);//������Ȼ��Ӧ��ʹ��connected������������Ҫ���ùؼ��ַ���server�б���ʱ�ޣ���
	connect(socket_RD, SIGNAL(disconnected()), this, SLOT(disconnectSlot()));
	connect(socket_RD, SIGNAL(readyRead()), this, SLOT(readFileContent2()));

	QThread::msleep(10);//�ȴ�һ��رմ���
	//close();
}

//�źźͲ۵ķ�ʽ����dialogҪ�����ļ� ���� ��ʾ��mainwindow���� 
void readDataDialog::readMultiFileAdmitButton_emitSlot() //���¾ͷ���һ���źų�ȥ
{

	QThread::msleep(10);//�ȴ�һ��رմ���
	//close();
}

/*�رմ����¼����� ����һ���źŸ������ڣ������ȡ��ǰ�ļ�����*/
void readDataDialog::closeEvent(QCloseEvent *event)
{
	emit closeDialogEventSignal(ui->readSignalFileLineEdit->text());
	event->accept();
}

void readDataDialog::displayTcpSocketError(QAbstractSocket::SocketError )
{
	QMessageBox::warning(this, "SocketError", socket_RD->errorString());
}

void readDataDialog::disconnectSlot()
{	
	//QMessageBox::information(this, "tip", "client connection closed!");
	socket_RD->deleteLater();
}

/*��ȡ��server���͹������ļ��б�*/
void readDataDialog::readServerFlieListSlot()
{
	ui->readFlieListWidget->clear();
	readServerFlieList();


	if (filelist.fileNameList.size() == 0)
	{
		QMessageBox::information(this, "note", QString::fromLocal8Bit("���ļ���"));
		return;
	}
	for (int index = 0; index < filelist.fileNameList.size(); index++)
	{
		if (filelist.fileNameList.at(index) == " " || filelist.fileNameList.at(index) == "  ")
		{
			continue;
		}
		QListWidgetItem *item = new QListWidgetItem;
		item->setText(filelist.fileNameList.at(index));
		ui->readFlieListWidget->addItem(item);
	}
	//socket_RD->close();
	
}

void readDataDialog::readFileContent2()
{
	//QMessageBox::information(this, "TIP", QString::fromLocal8Bit(" �����ȡ�ļ���ʼ��ȡ�ļ�������"));
	readFileContent(socket_RD);
}