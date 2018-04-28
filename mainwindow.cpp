#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	QTime time;
	srand(time.msecsSinceStartOfDay());
	
	connect(ui->button_connect, SIGNAL(clicked(bool)),
			this, SLOT(openConnectWin()));
	connect(ui->button_to_command, SIGNAL(clicked(bool)),
			this, SLOT(sendCommand()));

	connect(ui->button_scheme, SIGNAL(clicked(bool)),
			this, SLOT(openScheme()));
	
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

void MainWindow::openConnectWin(){
	if (win)
		win->close();
	delete win;
	
	win = new winForNewDB();
	win->show();
	connect(win, SIGNAL(accepted()),
			this, SLOT(openNewConnection()));
}

void MainWindow::openNewConnection(){
	QString data = win->getData();
	win->hide();
	
	db.close();
	
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
		ui->label_with_result->append(QString::number(i + 1) + ") " + tablesInDB[i]);
	
	sql = new QSqlQuery();
}


void MainWindow::sendCommand(){
	ui->label_commands->append(ui->command_line->text());
	
	sql->exec(ui->command_line->text());
	if (sql->isActive()) {
		ui->label_with_result->setText("There is result of request: \n");
		QSqlRecord rec = sql->record();
		QString fields = "";
		for (int i = 0; i < rec.count(); i++)
			fields += rec.fieldName(i).leftJustified(15) + "\t";	
		ui->label_with_result->append(fields);
		ui->label_with_result->append("\n");
		while (sql->next()) {
			QString data = "";
			for (int i = 0; i < rec.count(); i++)
				data += sql->value(i).toString().leftJustified(15) + "\t";
				ui->label_with_result->append(data);
			ui->label_with_result->append("\n");
		}
	}
	else ui->label_with_result->setText("Something gone wrong, check command\n");
}


void MainWindow::commandToShowAll(){
	ui->command_line->setText(QString("SELECT * FROM %1")
							  .arg(ui->line_w_table_to_get_data->text()));
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

void MainWindow::openScheme(){
	if (sWin)
		sWin->close();
	delete sWin;
	sWin = new drawWindow(db, tablesInDB, sql);
	sWin->show();
}


