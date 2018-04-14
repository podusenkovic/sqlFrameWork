#include "winfornewdb.h"
#include "ui_winfornewdb.h"

winForNewDB::winForNewDB(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::winForNewDB)
{
	ui->setupUi(this);
}

winForNewDB::~winForNewDB()
{
	delete ui;
}


QString winForNewDB::getData(){
	return ui->line_hostname->text() + ":" +
		   ui->line_db_name->text() + ":" +
		   ui->line_username->text() + ":" +
		   ui->line_password->text();
}
