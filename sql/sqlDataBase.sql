CREATE DATABASE shittydatabase;

USE shittydatabase;

CREATE TABLE Providers (
	provID int NOT NULL,
	name varchar(255) NOT NULL,
	phone varchar(16) NOT NULL,
	address varchar(255),
	PRIMARY KEY (provID)
);

CREATE TABLE ProstoTakTable (
	prostoID int NOT NULL,
	notName varchar(255) NOT NULL,
	iPhone varchar(16) NOT NULL,
	mamkyNaidy varchar(255),
	PRIMARY KEY (prostoID)
);


CREATE TABLE Positions (
	positionID int NOT NULL,
	positionName varchar(255),
	PRIMARY KEY (positionID)
);

CREATE TABLE Units(
	unitID int NOT NULL,
	unitName varchar(255) NOT NULL,
	PRIMARY KEY (unitID)
);

CREATE TABLE Categories (
	categoryID int NOT NULL,
	categoryName varchar(255) NOT NULL,
	PRIMARY KEY (categoryID)
);

CREATE TABLE Brands (
	brandID int NOT NULL,
	brandName varchar(255) NOT NULL,
	address varchar(255),
	phone varchar(16) NOT NULL,
	PRIMARY KEY (brandID)
);

CREATE TABLE Workers (
	workerID int NOT NULL,
	name varchar(255) NOT NULL,
	position int NOT NULL,
	address varchar(255),
	phone varchar(16) NOT NULL,
	PRIMARY KEY (workerID),
	FOREIGN KEY (position) REFERENCES Positions (positionID)
);

CREATE TABLE Sale (
	saleID int NOT NULL,
	dateSale varchar(16) NOT NULL,
	responsable int NOT NULL,
	salePrice int NOT NULL,
	discount int,
	toPay int NOT NULL,
	paid int NOT NULL,
	changeVal int NOT NULL,
	PRIMARY KEY (saleID),
	FOREIGN KEY (responsable) REFERENCES Workers(workerID)
);

CREATE TABLE Goods (
	goodID int NOT NULL,
	name varchar(255),
	amInWH int NOT NULL,
	unit int NOT NULL,
	salePrice int NOT NULL,
	category int,
	description varchar(1024),
	brand int NOT NULL,
	PRIMARY KEY (goodID),
	FOREIGN KEY (unit) REFERENCES Units (unitID),
	FOREIGN KEY (category) REFERENCES Categories (categoryID),
	FOREIGN KEY (brand) REFERENCES Brands (brandID)
);	
	
CREATE TABLE Shippings (
	shipID int NOT NULL,
	provID int NOT NULL,
	goodID int NOT NULL,
	priceDel int NOT NULL,
	dateDel varchar(16) NOT NULL,
	amount int NOT NULL,
	billNum int NOT NULL,
	responsable int NOT NULL,
	PRIMARY KEY (shipID),
	FOREIGN KEY (provID) REFERENCES Providers(provID),
	FOREIGN KEY (goodID) REFERENCES Goods(goodID),
	FOREIGN KEY (responsable) REFERENCES Workers(workerID)
);

CREATE TABLE Sold (
	id int NOT NULL,
	saleID int NOT NULL,
	goodID int NOT NULL,
	amount int NOT NULL,
	PRIMARY KEY (id),
	FOREIGN KEY (saleID) REFERENCES Sale (saleID),
	FOREIGN KEY (goodID) REFERENCES ProstoTakTable (prostoID)
);
	
	