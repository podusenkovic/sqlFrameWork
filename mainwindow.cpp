#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	
	connect(ui->button_connect, SIGNAL(clicked(bool)),
			this, SLOT(openConnectWin()));
	connect(ui->button_to_command, SIGNAL(clicked(bool)),
			this, SLOT(sendCommand()));
			
	ui->label_with_result->setText("");
}

MainWindow::~MainWindow()
{
	delete ui;
}



void MainWindow::openConnectWin(){
	win = new winForNewDB();
	win->show();
	connect(win, SIGNAL(accepted()),
			this, SLOT(openNewConnection()));
}

void MainWindow::openNewConnection(){
	QString data = win->getData();
	win->hide();
	qDebug() << data;
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName(data.split(":")[0]);
	db.setDatabaseName(data.split(":")[1]);
	db.setUserName(data.split(":")[2]);
	db.setPassword(data.split(":")[3]);
	
	
	bool ok = db.open();
	qDebug() << ok;
	tablesInDB = db.tables(QSql::Tables);
	
	//QSqlQuery sql = QSqlQuery();
	ui->label_with_result->setText(QString("In this database %1 tables").arg(tablesInDB.size()) + "\n");
	for (int i = 0; i < tablesInDB.size(); i++)
		ui->label_with_result->setText(ui->label_with_result->text() + QString::number(i + 1) + ") " + tablesInDB[i] + "\n");
}


void MainWindow::sendCommand(){
	ui->label_commands->setText(ui->label_commands->text() + "\n" + ui->command_line->text());
	sql = new QSqlQuery();
	sql->exec(ui->command_line->text());
	if (sql->isActive()) {
		ui->label_with_result->setText("There is result of request: \n");
		QSqlRecord rec = sql->record();
		for (int i = 0; i < rec.count(); i++)
			ui->label_with_result->setText(ui->label_with_result->text() + rec.fieldName(i) + "\t");
		ui->label_with_result->setText(ui->label_with_result->text() + "\n");
		
		while (sql->next()) {
			for (int i =0; i < rec.count(); i++)
				ui->label_with_result->setText(ui->label_with_result->text() + 
											   sql->value(i).toString() + "\t");
			ui->label_with_result->setText(ui->label_with_result->text() + "\n");
		}
	}
}
