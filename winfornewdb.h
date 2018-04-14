#ifndef WINFORNEWDB_H
#define WINFORNEWDB_H

#include <QDialog>

namespace Ui {
	class winForNewDB;
}

class winForNewDB : public QDialog
{
	Q_OBJECT
	
public:
	explicit winForNewDB(QWidget *parent = 0);
	~winForNewDB();
	
	QString getData();
	
private:
	Ui::winForNewDB *ui;
};

#endif // WINFORNEWDB_H
