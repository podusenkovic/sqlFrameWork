#include "drawwindow.h"

int abs(int a){
	return (a >= 0) ? a : -a;	
}

int sign(int a){
	if (a > 0)
		return 1;
	else if (a < 0)
		return -1;
	else return 0;
}


void addArcTo(QPainterPath &path, QPointF a){
	QPointF pos = path.currentPosition();
	
	if (pos.x() > a.x() && pos.y() > a.y())
		path.arcTo(a.x(), a.y(), (pos.x() - a.x()), (pos.y() - a.y()), 270 * 16, -90 * 16);
	
	else if (pos.x() > a.x() && pos.y() < a.y())
		path.arcTo(a.x(), pos.y(), (pos.x() - a.x()), (a.y() - pos.y()), 180 * 16, -90 * 16);
	
	else if (pos.x() < a.x() && pos.y() < a.y())
		path.arcTo(pos.x(), pos.y(), (a.x() - pos.x()), (a.y() - pos.y()), 0, 90 * 16);
	
	else if (pos.x() < a.x() && pos.y() > a.y())
		path.arcTo(pos.x(), a.y(), (a.x() - pos.x()), (pos.y() - a.y()), 0, -90 * 16);
}


drawWindow::drawWindow(QSqlDatabase &_db, 
					   QStringList _tablesInDB,
					   QSqlQuery *_sql, QWidget *parent) : 
	QWidget(parent),
	db(_db), tablesInDB(_tablesInDB), sql(_sql)
{
	this->setFixedSize(1300, 700);
	references.clear();
	for (int i = 0; i < tablesInDB.size(); i++){
		QString request =  QString("SELECT TABLE_NAME,COLUMN_NAME,CONSTRAINT_NAME, " 
								   "REFERENCED_TABLE_NAME,REFERENCED_COLUMN_NAME " 
								   "FROM INFORMATION_SCHEMA.KEY_COLUMN_USAGE "
								   "WHERE REFERENCED_TABLE_SCHEMA = '%1' AND REFERENCED_TABLE_NAME = '%2'")
						   .arg(db.databaseName()).arg(tablesInDB[i]);
		sql->exec(request);
		while(sql->next()){
			references[sql->value(0).toString()]
					.push_back(sql->value(1).toString() + ":" + 
							   sql->value(3).toString() + ":" + 
							   sql->value(4).toString());
		}
	}
	
	for (int i = 0; i < tablesInDB.size(); i++){
		QString request = QString("SELECT * FROM %1")
						  .arg(tablesInDB[i]);
		sql->exec(request);
		QSqlRecord rec = sql->record();
		
		for (int j = 0; j < rec.count(); j++)
			tablesFields[tablesInDB[i]].push_back(rec.fieldName(j));
	}
	
	if (tablesInDB.size() % 5 == 0)
		linesSize = tablesInDB.size() / 5;
	else linesSize = tablesInDB.size() / 5 + 1;
	
	if (tablesInDB.size() % linesSize == 0)
		lineSize = tablesInDB.size() / linesSize;
	else lineSize = tablesInDB.size() / linesSize + 1;
	
	qDebug() << linesSize << lineSize;
	
	blockWidth = this->width() * 1 / (lineSize * 4/3 + 1);
	shiftWidth = blockWidth / 3;
	
	blockHeight = this->height() * 1 / (linesSize * 4/3 + 1);
	shiftHeight = blockHeight / 3;
	
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(100);	
	
	int x = shiftWidth, y = shiftHeight;
	int index = 0;
	for (int i = 0; i < linesSize; i++){
		for (int j = 0; j < lineSize; j++){
			topLeft.push_back(QVector<QPoint>());
			if (index == tablesInDB.size())
				break;
			topLeft[index].push_back(QPoint(x, y));
			x += shiftWidth + blockWidth;
			index++;
		}
		x = shiftWidth; y += shiftHeight + blockHeight;
	}
	x = shiftWidth; y = shiftHeight;
	index = 0;	
	for (int i = 0; i < linesSize; i++){
		for (int j = 0; j < lineSize; j++){
			if (index >= tablesInDB.size())
				break;
			int textShift = blockHeight / tablesFields[tablesInDB[index]].size();
			for (int k = 0; k < tablesFields[tablesInDB[index]].size(); k++)
				topLeft[index].push_back(QPoint(10 + x,20  + y + k * textShift));
			x += shiftWidth + blockWidth;
			index++;
		}
		x = shiftWidth; y += shiftHeight + blockHeight;
	}
	
	
	for (int i = 0; i < references.keys().size(); i++){
		int xOff = 0, yOff = 0;
		for (int j = 0; j < references[references.keys()[i]].size(); j++){
			xOff = rand() % (shiftWidth * 4/5);
			yOff = rand() % (shiftHeight * 2/3) - shiftHeight / 2;
			QPoint p1, p2;
			for (int k = 0; k < tablesInDB.size(); k++)
				if (references.keys()[i] == tablesInDB[k])
					for (int c = 0; c < tablesFields[tablesInDB[k]].size(); c++)
						if (references[references.keys()[i]][j].split(":")[0] == tablesFields[tablesInDB[k]][c]){
							p1 = topLeft[k][c + 1];
							break;
						}
			for (int k = 0; k < tablesInDB.size(); k++)
				if (references[references.keys()[i]][j].split(":")[1] == tablesInDB[k])
					for (int c = 0; c < tablesFields[tablesInDB[k]].size(); c++)
						if (references[references.keys()[i]][j].split(":")[2] == tablesFields[tablesInDB[k]][c]){
							p2 = topLeft[k][c + 1]; // ERROR ERROR
							//qDebug() << p2
							break;
						}
			int shift = 10;		
			int yLine;
			if (linesSize % 2 == 0)
				yLine = height() / 2;
			else yLine = height() - shiftHeight;
			
			
			QPainterPath refPath;
			refPath.moveTo(QPoint(p1.x(), p1.y() - 6));
			
			QPolygon triangle; int triSize = 5;
			QPointF cur = refPath.currentPosition();
			triangle.push_back(QPoint(cur.x() - triSize,cur.y()));
			triangle.push_back(QPoint(cur.x(),cur.y() + triSize));
			triangle.push_back(QPoint(cur.x(),cur.y() - triSize));
			triangle.push_back(QPoint(cur.x() - triSize,cur.y()));	
			refPath.addPolygon(triangle);
			
			refPath.lineTo(QPoint(p1.x() - shiftWidth / 5 - xOff + shift, p1.y() - 6));
			refPath.lineTo(QPoint(p1.x() - shiftWidth / 5 - xOff, p1.y() - 6 - shift*sign(p1.y() - yLine)));
			refPath.lineTo(QPoint(p1.x() - shiftWidth / 5 - xOff, yLine + yOff + shift*sign(p1.y() - yLine)));
			refPath.lineTo(QPoint(p1.x() - shiftWidth / 5 - xOff + shift*sign(p2.x() - p1.x()), yLine + yOff));
			
			refPath.lineTo(QPoint(p2.x() - shiftWidth / 5 - xOff - shift*sign(p2.x() - p1.x()), yLine + yOff));
			refPath.lineTo(QPoint(p2.x() - shiftWidth / 5 - xOff, yLine + yOff + shift*sign(p2.y() - yLine)));
			refPath.lineTo(QPoint(p2.x() - shiftWidth / 5 - xOff, p2.y() - 6 - shift*sign(p2.y() - yLine)));
			refPath.lineTo(QPoint(p2.x() - shiftWidth / 5 - xOff + shift, p2.y() - 6));
			refPath.lineTo(QPoint(p2.x(), p2.y() - 6));
			QPointF temp = refPath.currentPosition();
			temp.setX(temp.x() - 4);
			refPath.addEllipse(temp, 4, 4);
			
			refLines.push_back(refPath);
			refColors.push_back(QColor(rand()%170, rand()%170, rand()%170));
			//qDebug() << references.keys()[i] << ":" << references[references.keys()[i]][j];
		}
	}
	
}


void drawWindow::paintEvent(QPaintEvent *event){
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(QPen(QColor(0,0,0), 2));
	for (int i = 0; i < tablesInDB.size(); i++){
		painter.drawRoundedRect(topLeft[i][0].x(), topLeft[i][0].y(), 
				blockWidth, blockHeight, 
				shiftWidth / 4, shiftHeight / 4);
	}
	for (int i = 0; i < tablesInDB.size(); i++){
		painter.setFont(QFont("Times", 12, 75));
		painter.drawText(10 + topLeft[i][0].x(), topLeft[i][0].y() - 20, tablesInDB[i].toUpper());
		painter.setFont(QFont("Times", 12));
		for (int j = 0; j < topLeft[i].size() - 1; j++){
			painter.drawText(topLeft[i][j + 1].x(), topLeft[i][j + 1].y(), 
							 tablesFields[tablesInDB[i]][j]);
		}
	}
	for (int i = 0; i < refLines.size(); i++){
		painter.setPen(QPen(refColors[i], 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		painter.drawPath(refLines[i]);
	}
}
