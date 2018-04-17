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

	connect(ui->button_table_model, SIGNAL(clicked(bool)),
			this, SLOT(openTableModel()));
	
	connect(ui->button_show_all_data, SIGNAL(clicked(bool)),
			this, SLOT(commandToShowAll()));
	connect(ui->button_show_only, SIGNAL(clicked(bool)),
			this, SLOT(commandToShowOnly()));
	connect(ui->button_show_tables, SIGNAL(clicked(bool)),
			this, SLOT(commandToShowTables()));
	connect(ui->button_insert_data, SIGNAL(clicked(bool)),
			this, SLOT(commandToInsert()));
	connect(ui->button_delete, SIGNAL(clicked(bool)),
			this, SLOT(commandToDelete()));
	
	
	ui->label_with_result->setText("");
	
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::openTableModel(){
	/*
	 * 
	 * TODO 
	 * PRETTY
	 * OUTPUT
	 * OF DB (table model)
	 * 
	 */	
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

	ui->label_with_result->setText(QString("In this database %1 tables").arg(tablesInDB.size()) + "\n");
	for (int i = 0; i < tablesInDB.size(); i++)
		ui->label_with_result->setText(ui->label_with_result->text() + QString::number(i + 1) + ") " + tablesInDB[i] + "\n");
	
	sql = new QSqlQuery();	
}


void MainWindow::sendCommand(){
	ui->label_commands->append(ui->command_line->text());
	
	sql->exec(ui->command_line->text());
	if (sql->isActive()) {
		ui->label_with_result->setText("There is result of request: \n");
		QSqlRecord rec = sql->record();
		for (int i = 0; i < rec.count(); i++)
			ui->label_with_result->setText(ui->label_with_result->text() + rec.fieldName(i) + "\t");
		ui->label_with_result->setText(ui->label_with_result->text() + "\n");
		while (sql->next()) {
			for (int i = 0; i < rec.count(); i++)
				ui->label_with_result->setText(ui->label_with_result->text() + 
											   sql->value(i).toString() + "\t");
			ui->label_with_result->setText(ui->label_with_result->text() + "\n");
		}
	}
}



void MainWindow::commandToShowAll(){
	ui->command_line->setText(QString("SELECT * FROM %1").arg(ui->line_w_table_to_get_data->text()));
}

void MainWindow::commandToShowOnly(){
	ui->command_line->setText(QString("SELECT %1 FROM %2")
							  .arg(ui->line_w_col->text())
							  .arg(ui->line_w_table->text()));
}

void MainWindow::commandToShowTables(){
	ui->command_line->setText(QString("SHOW TABLES FROM %1")
							  .arg(db.databaseName()));
}

void MainWindow::commandToInsert(){
	QString values = ui->line_ins_values->text();
	QString cols = "";
	sql->exec(QString("SELECT * FROM %1").arg(ui->line_ins_table->text()));
	QSqlRecord rec = sql->record();
	for (int i = 0; i < rec.count(); i++)
		cols = cols + "," + rec.fieldName(i);
	cols.remove(0,1);
	ui->command_line->setText(QString("INSERT INTO %1 (%2) values (%3)")
							  .arg(ui->line_ins_table->text())
							  .arg(cols).arg(values));	
}

void MainWindow::commandToDelete(){
	ui->command_line->setText(QString("DELETE FROM %1 WHERE PK = %2")
							  .arg(ui->line_del_table->text())
							  .arg(ui->line_del_pk->text()));
}



