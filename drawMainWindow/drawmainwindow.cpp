#include "drawmainwindow.h"
#include "readdatadialog.h"
#include "testcomdialog.h"
#include "QThread"


drawMainWindow::drawMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	
	ui = new Ui::drawMainWindowClass;
	ui->setupUi(this);
	ui->statusBar->showMessage("Ready");
	//receiveReadSignalFileNameSlot("akldgn"); //������ʾok
	QObject::connect(ui->menu_readData, SIGNAL(aboutToShow()), this, SLOT(readDataDialogSlot()));
	QObject::connect(ui->actionTestCommandDialog, SIGNAL(triggered()), this, SLOT(testComDialogSlot()));
	
			
}
//extern QString quanjuString;//ȫ�ֱ�����ʾ�ļ����ݷ�ʽ
drawMainWindow::~drawMainWindow()
{

}

void drawMainWindow::readDataDialogSlot()
{
	/*�õ�һ����ģ̬����*/  //���ļ��б�ݴ���
	//hide();  //�Ƿ�Ӱ�������ڣ�����
	readDataDialog *rDataDialog = new readDataDialog();
	QThread::msleep(10); 
	//�źźͲ۵ķ�ʽ����dialogҪ�����ļ���ʾ��mainwindow���� 
	connect(rDataDialog, SIGNAL(sendFileNameSignal(const QString &)), this, SLOT(receiveReadSignalFileNameSlot(const QString &)));
	connect(rDataDialog, SIGNAL(closeDialogEventSignal(const QString&)), this, SLOT(receiveReadSignalFileNameSlot(const QString&)));
	rDataDialog->exec();
}

void drawMainWindow::testComDialogSlot()
{
	testComDialog tComDialog;
	tComDialog.exec();
}

void drawMainWindow::showReadFileInfoSlot()
{	

	//QMessageBox::information(this, "test", );
}


/*�źźͲ۵ķ�ʽ���ն�ȡ�ļ���Ȼ���ȡ����Ŀ¼�ļ�����ʾ����*/
void drawMainWindow::receiveReadSignalFileNameSlot(const QString &fileName)
{
	
}

void drawMainWindow::showQuanjuStringSlot()
{

	ui->textEdit->setText(readdata);
	if (readdata == "")
	{
		QMessageBox::information(this, "tips", QString::fromLocal8Bit("δ���ļ������"));
	}
}