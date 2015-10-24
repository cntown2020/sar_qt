#include "readDataSocket.h"

extern quint16 cmd_type;


/*���ӵ�������*/
bool connectServer(QTcpSocket *socket)
{


	socket->connectToHost("192.168.0.71", 6666);
	//socket->connectToHost("127.0.0.1", 6666);
	if (!socket->waitForConnected(1000))
	{
		return false;
	}
	else
	{
		return true;
	}
}
/*��server���Ͷ�ȡ�ļ��б�����*/
void sendReadFileList(QTcpSocket *socket_RD)
{
	cmd_type = READ_FILELIST;
	QByteArray block;
	QDataStream out(&block, QIODevice::ReadWrite);
	out.setVersion(QDataStream::Qt_5_5);
	out << (quint16)cmd_type;
	socket_RD->write(block);
	socket_RD->waitForBytesWritten();
}

/*get server�ʹ���ļ��б�*/
void readServerFlieList()
{
	//ui->readFlieListWidget->clear();
	extern QTcpSocket *socket_RD;//zzuo��Ϊһ���βδ��ݸ��ã�����ʹ���ⲿ������
	QDataStream in(socket_RD);
	in.setVersion(QDataStream::Qt_5_5);


	extern struct File_List_struct  filelist;
	in >> filelist.fileNameList; //�����������ǿ������ת�������
	//in >> ��qstringList ��filelist.fileNameList; ��Ϊ��������һ��stringlist��stringlist������
	//�����ڷ����У������ٴ�ǿ������ת����������why����
	socket_RD->waitForBytesWritten();

	socket_RD->disconnectFromHost();//�������������Ͽ��������Է����½�����ǰ�Ͽ�ԭ�����ӣ��˳���ԭ�е�socket��������
	socket_RD->waitForDisconnected();
	//socket_RD->abort();
}

/*��server����һ�����󣬶�ȡһ���ļ�*/
bool  sendReadFileName(QTcpSocket * socket_RD)
{
	cmd_type = READ_FILE;
	QByteArray block;
	QDataStream out(&block, QIODevice::ReadWrite);
	out.setVersion(QDataStream::Qt_5_5);

	struct send_Read_File_struct readFile;
	readFile.flag = 0x0001;
	extern QString exterStr;
	readFile.start_fileName = exterStr;

	out << cmd_type;
	out << readFile.flag;
	out << readFile.start_fileName;
	if (socket_RD->write(block))
	{
		return true;
	}
	else
	{
		return false;
	}

	socket_RD->waitForBytesWritten();//�ȴ�д��
	//socket_RD->abort();//д���Ͽ�
}



qint64 totalBytes = 0;  //����ܴ�С��Ϣ  
qint64 bytesReceived = 0;  //���յ����ݵĴ�С  
QByteArray inBlock = 0;   //���ݻ�����  
struct read_File_Content readFile;//����������ڲ����ڶ�δ�readyread���ôκ�����ʱ�򣬻ᵼ�³���������
bool readFileContent(QTcpSocket *socket)
{
	QByteArray inBlock;
	QDataStream in(socket);
	in.setVersion(QDataStream::Qt_5_5);

	//struct read_File_Content readFile;//�������������⣬��Ϊÿ�δ�readyread�������������µ��ڴ棬��Ϊ�˳�����������ͻ��ͷŵ�����

	if (bytesReceived <= sizeof(quint64) + sizeof(quint16) )//�ļ���С�ж�����ģ���ʵ�ʶ�Ӧ��С��qstring�ǹ̶�����
	{
		if (socket->bytesAvailable() >= sizeof(quint64))
		{
			in >> readFile.size >> readFile.flag >> readFile.fName;
			QDir dir;
			dir.mkdir("F:/receiveFromServerFile/");
			QString filename = readFile.fName;
			readFile.fileContent = new QFile("F:/receiveFromServerFile/" + filename);
			//QFile::rename("D:/yun/FPGA_c_pcb_m_all/Visual Studio 2013/my_project/receiveFromServerFile/r", "D:/yun/FPGA_c_pcb_m_all/Visual Studio 2013/my_project/receiveFromServerFile/readFile.fName");
			//readFile.fileContent->setFileName(readFile.fName);
			if (!readFile.fileContent->open(QFile::WriteOnly))
			{
				return false;
			}
			
		}

		bytesReceived += (sizeof(quint64)+sizeof(quint16) + readFile.fName.size());
	}
	if (bytesReceived < readFile.size && !readFile.fName.isEmpty())
	{
		bytesReceived += socket->bytesAvailable();
		inBlock = socket->readAll();
		//readFile.fileContent->write(inBlock);
		QTextStream textIn(readFile.fileContent);
		textIn << inBlock;

		inBlock.resize(0);
	}
	if (bytesReceived == readFile.size)
	{
		readFile.fileContent->close();
		socket->disconnectFromHost();
		socket->waitForDisconnected();
	}
}


