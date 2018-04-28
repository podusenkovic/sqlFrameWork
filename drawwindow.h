#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QPaintEvent>
#include <QTimer>
#include <QPainter>

class drawWindow : public QWidget
{
	Q_OBJECT
public:
	explicit drawWindow(QSqlDatabase &db, 
						QStringList tablesInDB,
						QSqlQuery *sql,
						QWidget *parent = nullptr);
	
	void paintEvent(QPaintEvent *event);
signals:
	
public slots:
	
	
private:
	QTimer *timer;
	
	QSqlDatabase db;
	QStringList tablesInDB;
	QSqlQuery *sql;
	
	QMap<QString, QVector<QString>> references;
	QMap<QString, QVector<QString>> tablesFields;
	
	QVector<QVector<QPoint>> topLeft;
	
	QVector<QPainterPath> refLines;
	QVector<QColor> refColors;
	
	int linesSize;
	int lineSize;
	
	int blockWidth;
	int shiftWidth;
	
	int blockHeight;
	int shiftHeight;
};

#endif // DRAWWINDOW_H
