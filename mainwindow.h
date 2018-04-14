#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "winfornewdb.h"

#include <QMainWindow>
#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
private slots:
	void openConnectWin();
	void openNewConnection();
	void sendCommand();
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	
private:
	QSqlDatabase db;
	QStringList tablesInDB;
	QSqlQuery *sql;
	winForNewDB *win;
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
