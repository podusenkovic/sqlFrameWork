USE mydatabase;

INSERT INTO Positions (positionID, positionName)
	VALUES  (1, 'CEO'),
			(2, 'Manager'),
			(3, 'Cleaner'),
			(4, 'Seller');
			
INSERT INTO Providers (provID, name, phone, address)
	VALUES  (1, 'Vova', '+79123456765', 'Moscow'),
			(2, 'Anton', '+79543214521', 'Zelenograd'),
			(3, 'Pasha', '+79675223456', 'London'),
			(4, 'Sasha', '+79863123212', 'New York');

INSERT INTO Units (unitID, unitName)
	VALUES  (1, 'Pieces'),
			(2, 'Kilos'),
			(3, 'Meters');
			
INSERT INTO Categories (categoryID, categoryName)
	VALUES  (1, 'Food'),
			(2, 'Clothes'),
			(3, 'Technic'),
			(4, 'Cars');
			
INSERT INTO Brands (brandID, brandName, address, phone)
	VALUES  (1, 'HP', 'California', '+79674354567'),
			(2, 'McDonalds', 'New York', '+79524323456'),
			(3, 'LC WAIKIKI', 'Turkey', '+79632123235'),
			(4, 'Lamborgini', 'USA', '+796745832222');

INSERT INTO Workers (workerID, name, position, address, phone)
	VALUES  (1, 'Dima', 1, 'Moscow City', '+78962135439'),
			(2, 'Nikita', 2, 'Istanbul', '+79675225789'),
			(3, 'Nastya', 4, 'Zelenograd', '+79657842345'),
			(4, 'Egor', 4, 'Chikago', '+79675326789'),
			(5, 'Sasha', 3, 'Hostel', '+79678525678');

INSERT INTO Sale (saleID, dateSale, responsable, salePrice, discount, toPay, paid, changeVal)
	VALUES  (1, '17/12/2017', 3, 400, 0, 400, 400, 0),
			(2, '14/02/2018', 4, 1000, 200, 800, 1000, 200),
			(3, '20/01/2018', 4, 1700, 0, 1700, 2000, 300),
			(4, '13/04/2017', 1, 100500, 500, 100000, 100000, 0);

INSERT INTO Goods (goodID, name, amInWH, unit, salePrice, category, description, brand)
	VALUES  (1, 'Big Mac', 100, 1, 120, 1, 'Tasty burger', 2),
			(2, 'Jacket', 10, 1, 1000, 2, 'Pretty jacket', 3),
			(3, 'Pavilion g6', 25, 1, 10000, 1, 3, 'Fast gaming laptop', 1),
			(4, 'Lambo', 5, 1, 23000000, 4, 'Very cool car', 4),
			(5, 'Big Tasty', 100, 1, 240, 1, 'Very big and tasty burger', 2);
	
INSERT INTO Shippings (shipId, provID, goodID, priceDel, dateDel, amount, billNum, responsable)
	VALUES  (1, 1, 3, 100, '20/03/2018', 1, 12345, 2),
			(2, 3, 2, 100, '03/04/2018', 1, 98673, 3),
			(3, 2, 1, 100, '10/11/2017', 1, 75321, 2),
			(4, 1, 4, 100, '26/12/2017', 1, 23023, 1);

INSERT INTO Sold (id, saleID, goodID, amount)
	VALUES  (1, 3, 3, 1),
			(2, 4, 1, 2),
			(3, 2, 5, 3),
			(4, 1, 2, 2);