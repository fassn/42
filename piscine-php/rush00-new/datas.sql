use db_rush ;

LOCK TABLES `cart` WRITE;
/*!40000 ALTER TABLE `cart` DISABLE KEYS */;
INSERT INTO `cart` VALUES (1,'gael','Star Trek Discovery Disco Baseball Hat',3,20.00,60.00,'../img/Star Trek Discovery Disco Baseball Hat.jpg'),(2,'gael','Star Trek Discovery Property Of Baseball Hat',3,20.00,60.00,'../img/Star Trek Discovery Property Of Baseball Hat.jpg'),(3,'gael','Modele reduit U.S.S. Enterprise NCC-1701-D - 22 cm',3,50.00,150.00,'../img/Modele reduit U.S.S. Enterprise NCC-1701-D - 22 cm.jpg');
/*!40000 ALTER TABLE `cart` ENABLE KEYS */;
UNLOCK TABLES;

LOCK TABLES `categories` WRITE;
/*!40000 ALTER TABLE `categories` DISABLE KEYS */;
INSERT INTO `categories` VALUES (3,'Vetements'),(4,'Maquettes'),(5,'Accessoires');
/*!40000 ALTER TABLE `categories` ENABLE KEYS */;
UNLOCK TABLES;

LOCK TABLES `products` WRITE;
/*!40000 ALTER TABLE `products` DISABLE KEYS */;
INSERT INTO `products` VALUES (6,'Modele reduit U.S.S. Enterprise NCC-1701-D - 22 cm','Maquettes','Nouvelle Generation',50.00,'img/Modele reduit U.S.S. Enterprise NCC-1701-D - 22 cm.jpg','Modele reduit de l&#039;U.S.S. Enterprise NCC-1701-D - 22 cm',10),(7,'Romulien Oiseau-de-Guerre Modele','Maquettes','Nouvelle Generation',50.00,'img/Romulen Oiseau-de-Guerre Modele.jpg','Romulien Oiseau-de-Guerre Modele',10),(8,'Star Trek Discovery Command Training Program Women&#039;s T-Shirt','Vetements','Femmes',30.00,'img/Star Trek Discovery Command Training Program Womens T-Shirt.jpg','Star Trek Discovery Command Training Program Women&#039;s T-Shirt',10),(10,'Star Trek Discovery Disco Baseball Hat','Accessoires','Hommes',20.00,'img/Star Trek Discovery Disco Baseball Hat.jpg','Star Trek Discovery Disco Baseball Hat',10),(11,'Star Trek Discovery Property Of Baseball Hat','Accessoires','Hommes',20.00,'img/Star Trek Discovery Property Of Baseball Hat.jpg','Star Trek Discovery Property Of Baseball Hat',10),(12,'Star Trek Discovery Varsity Zip Hoodie','Vetements','Hommes',30.00,'img/Star Trek Discovery Varsity Zip Hoodie.jpg','Star Trek Discovery Varsity Zip Hoodie',10),(13,'Star Trek Starfleet Academy Varsity Women&#039;s T-Shirt','Vetements','Femmes',30.00,'img/Star Trek Starfleet Academy Varsity Womens T-Shirt.jpg','Star Trek Starfleet Academy Varsity Women&#039;s T-Shirt',10),(14,'Star Trek Starfleet Academy Varsity Zip Hoodie','Vetements','Hommes',30.00,'img/Star Trek Starfleet Academy Varsity Zip Hoodie.jpg','Star Trek Starfleet Academy Varsity Zip Hoodie',10),(15,'Star Trek Starfleet Command Beanie','Accessoires','Hommes',20.00,'img/Star Trek Starfleet Command Beanie.jpg','Star Trek Starfleet Command Beanie',10),(16,'Star Trek Vulcan Salute Pullover Hoodie','Vetements','Hommes',30.00,'img/Star Trek Vulcan Salute Pullover Hoodie.jpg','Star Trek Vulcan Salute Pullover Hoodie',10),(17,'Star Trek Vulcan Salute Women&#039;s Dolman T-Shirt','Vetements','Femmes',30.00,'img/Star Trek Vulcan Salute Womens Dolman T-Shirt.jpg','Star Trek Vulcan Salute Women&#039;s Dolman T-Shirt',10),(18,'Vaisseau Cube Tactique Borg','Maquettes','Nouvelle Generation',50.00,'img/Vaisseau Cube Tactique Borg.jpg','Vaisseau Cube Tactique Borg',10),(19,'Vaisseau I.S.S Enterprise-D (Univers-Miroir)','Maquettes','Nouvelle Generation',50.00,'img/Vaisseau I.S.S Enterprise-D (Univers-Miroir).jpg','Vaisseau I.S.S Enterprise-D (Univers-Miroir)',10),(20,'Vaisseau Meduse de Spock','Maquettes','Films',50.00,'img/Vaisseau Meduse de Spock.jpg','Vaisseau Meduse de Spock',10),(21,'Vaisseau NCC 1701-E U.S.S Enterprise - 27 cm','Maquettes','Nouvelle Generation',50.00,'img/Vaisseau NCC 1701-E U.S.S Enterprise - 27 cm.jpg','Vaisseau NCC 1701-E U.S.S Enterprise - 27 cm',10),(22,'Vaisseau U.S.S Enterprise NCC-1701 (Discovery)','Maquettes','Discovery',50.00,'img/Vaisseau U.S.S Enterprise NCC-1701 (Discovery).jpg','Vaisseau U.S.S Enterprise NCC-1701 (Discovery)',10),(23,'Vaisseau U.S.S Enterprise NCC-1701','Maquettes','Films',50.00,'img/Vaisseau U.S.S Enterprise NCC-1701.jpg','Vaisseau U.S.S Enterprise NCC-1701',10);
/*!40000 ALTER TABLE `products` ENABLE KEYS */;
UNLOCK TABLES;

LOCK TABLES `subcategories` WRITE;
/*!40000 ALTER TABLE `subcategories` DISABLE KEYS */;
INSERT INTO `subcategories` VALUES (1,'Hommes'),(2,'Femmes'),(4,'Nouvelle Generation'),(5,'Films'),(6,'Discovery');
/*!40000 ALTER TABLE `subcategories` ENABLE KEYS */;
UNLOCK TABLES;