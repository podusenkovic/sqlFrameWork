#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "winfornewdb.h"
#include "drawwindow.h"

#include <QMainWindow>
#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QTime>

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
	
	void openScheme();
	
	void commandToShowAll();
	void commandToShowOnly();
	void commandToShowTables();
	void commandToInsert();
	void commandToDelete();
	
public:
	explicit MainWindow(QWidget *parent = 0);
	
	
	~MainWindow();
	
private:
	QSqlDatabase db;
	QStringList tablesInDB;
	QSqlQuery *sql = nullptr;
	winForNewDB *win = nullptr;
	drawWindow *sWin = nullptr;
	Ui::MainWindow *ui = nullptr;	
};

#endif // MAINWINDOW_H
