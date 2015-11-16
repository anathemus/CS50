-- MySQL dump 10.13  Distrib 5.5.46, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.46-0ubuntu0.14.04.2-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `id` int(10) NOT NULL,
  `transaction` varchar(200) COLLATE utf8_unicode_ci NOT NULL,
  `time` datetime NOT NULL,
  `symbol` varchar(200) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(11) NOT NULL,
  `price` decimal(65,4) NOT NULL,
  KEY `id` (`id`,`time`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
INSERT INTO `history` VALUES (9,'BUY','0000-00-00 00:00:00','DIS',50,114.8400),(9,'BUY','0000-00-00 00:00:00','TWX',50,69.9300),(9,'SELL','0000-00-00 00:00:00','DIS',50,114.8400),(9,'SELL','0000-00-00 00:00:00','TWX',50,69.9300),(9,'BUY','0000-00-00 00:00:00','DIS',50,114.8400),(9,'BUY','0000-00-00 00:00:00','TWX',50,69.9300),(9,'SELL','0000-00-00 00:00:00','DIS',50,114.8400),(9,'SELL','0000-00-00 00:00:00','TWX',50,69.9300),(9,'BUY','0000-00-00 00:00:00','DIS',50,114.8400),(9,'SELL','0000-00-00 00:00:00','DIS',50,114.8400),(9,'BUY','0000-00-00 00:00:00','DIS',50,114.8400),(9,'SELL','0000-00-00 00:00:00','DIS',50,114.8400),(9,'BUY','0000-00-00 00:00:00','DIS',50,114.8400),(9,'SELL','0000-00-00 00:00:00','DIS',50,114.8400),(9,'BUY','0000-00-00 00:00:00','DIS',50,114.8400),(9,'SELL','0000-00-00 00:00:00','DIS',50,114.8400),(9,'BUY','0000-00-00 00:00:00','DIS',50,114.8400),(9,'SELL','0000-00-00 00:00:00','DIS',50,114.8400),(9,'BUY','0000-00-00 00:00:00','DIS',50,114.8400),(9,'SELL','0000-00-00 00:00:00','DIS',50,114.8400),(9,'BUY','0000-00-00 00:00:00','DIS',50,114.8400),(9,'SELL','0000-00-00 00:00:00','DIS',50,114.3400),(9,'BUY','0000-00-00 00:00:00','DIS',50,114.4000),(9,'SELL','0000-00-00 00:00:00','DIS',50,113.9400),(9,'BUY','0000-00-00 00:00:00','DIS',50,113.9700),(9,'SELL','0000-00-00 00:00:00','DIS',50,114.2450),(9,'BUY','0000-00-00 00:00:00','DIS',50,114.1800),(9,'SELL','0000-00-00 00:00:00','DIS',50,114.0600),(9,'BUY','0000-00-00 00:00:00','DIS',50,114.0700),(9,'BUY','0000-00-00 00:00:00','DIS',1,114.1100),(9,'BUY','0000-00-00 00:00:00','DIS',1,114.0950),(9,'SELL','0000-00-00 00:00:00','DIS',50,114.1800),(9,'BUY','0000-00-00 00:00:00','DIS',50,114.2900),(9,'SELL','0000-00-00 00:00:00','DIS',50,114.5200),(9,'BUY','0000-00-00 00:00:00','DIS',50,114.4700),(9,'BUY','0000-00-00 00:00:00','DIS',1,114.6901),(9,'BUY','0000-00-00 00:00:00','DIS',1,114.4800),(9,'SELL','0000-00-00 00:00:00','DIS',50,114.4170),(9,'BUY','0000-00-00 00:00:00','DIS',50,114.4500),(9,'BUY','0000-00-00 00:00:00','DIS',1,114.5500),(9,'BUY','0000-00-00 00:00:00','DIS',1,114.5700),(9,'BUY','0000-00-00 00:00:00','DIS',1,114.4700),(9,'BUY','0000-00-00 00:00:00','DIS',1,114.4300),(9,'BUY','0000-00-00 00:00:00','DIS',1,114.5600),(9,'BUY','0000-00-00 00:00:00','DIS',1,114.6000),(9,'BUY','0000-00-00 00:00:00','DIS',1,114.5800),(9,'BUY','0000-00-00 00:00:00','DIS',1,114.6300),(9,'BUY','0000-00-00 00:00:00','DIS',1,114.5800),(9,'BUY','0000-00-00 00:00:00','DIS',1,114.5200),(9,'BUY','0000-00-00 00:00:00','DIS',1,114.4900),(9,'BUY','0000-00-00 00:00:00','DIS',1,114.4800),(9,'BUY','0000-00-00 00:00:00','DIS',1,114.3600),(9,'BUY','0000-00-00 00:00:00','DIS',1,114.4368),(9,'SELL','0000-00-00 00:00:00','DIS',50,114.3800),(9,'BUY','0000-00-00 00:00:00','TWX',1,69.9800),(9,'BUY','0000-00-00 00:00:00','TWX',1,70.0098),(9,'SELL','0000-00-00 00:00:00','TWX',1,69.9500),(9,'BUY','0000-00-00 00:00:00','TWX',50,69.9700),(9,'BUY','0000-00-00 00:00:00','TWX',1,70.0050),(9,'SELL','0000-00-00 00:00:00','TWX',50,70.1300),(9,'BUY','0000-00-00 00:00:00','AAPL',100,113.4600),(9,'SELL','0000-00-00 00:00:00','AAPL',100,113.5490),(9,'BUY','0000-00-00 00:00:00','AAPL',100,113.5200),(9,'BUY','2015-11-16 01:06:11','AAPL',100,113.2800),(9,'BUY','2015-11-16 01:08:34','AAPL',1000,113.2700),(9,'BUY','2015-11-16 01:15:40','AAPL',1000,113.3700),(9,'BUY','2015-11-16 01:18:51','AAPL',1000,113.3300),(9,'BUY','2015-11-16 01:20:37','AAPL',1000,113.4500);
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `portfolio`
--

DROP TABLE IF EXISTS `portfolio`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `portfolio` (
  `id` int(10) NOT NULL,
  `symbol` varchar(200) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(11) NOT NULL,
  `price` decimal(65,4) NOT NULL,
  KEY `id` (`id`,`symbol`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `portfolio`
--

LOCK TABLES `portfolio` WRITE;
/*!40000 ALTER TABLE `portfolio` DISABLE KEYS */;
INSERT INTO `portfolio` VALUES (9,'AAPL',1000,113.4500);
/*!40000 ALTER TABLE `portfolio` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `hash` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `email` varchar(100) COLLATE utf8_unicode_ci NOT NULL,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'belindazeng','$1$50$oxJEDBo9KDStnrhtnSzir0','anathemus@gmail.com',10000.0000),(2,'caesar','$1$50$GHABNWBNE/o4VL7QjmQ6x0','anathemus@gmail.com',10000.0000),(3,'jharvard','$1$50$RX3wnAMNrGIbgzbRYrxM1/','anathemus@gmail.com',10000.0000),(4,'malan','$1$50$lJS9HiGK6sphej8c4bnbX.','anathemus@gmail.com',500000000000000.0000),(5,'rob','$1$HA$l5llES7AEaz8ndmSo5Ig41','anathemus@gmail.com',900000000.0000),(6,'skroob','$1$50$euBi4ugiJmbpIbvTTfmfI.','anathemus@gmail.com',21484.0000),(7,'zamyla','$1$50$uwfqB45ANW.9.6qaQ.DcF.','anathemus@gmail.com',900000000.0000),(9,'anathemus','$1$Ey7DXYEK$TJSM/jUGL4a1SxNFXB8Kb.','anathemus@gmail.com',99750591.1000);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-11-16 13:41:59
