-- phpMyAdmin SQL Dump
-- version 4.9.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Oct 18, 2019 at 01:39 PM
-- Server version: 8.0.17
-- PHP Version: 7.3.10

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `ledaim`
--

-- --------------------------------------------------------

--
-- Table structure for table `categories`
--

CREATE TABLE `categories` (
  `id_cat` int(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `creation_date` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `categories`
--

INSERT INTO `categories` (`id_cat`, `name`, `creation_date`) VALUES
(1, 'Daim', '2019-10-15'),
(2, 'Cuir', '2019-10-15'),
(3, 'Simili Cuir', '2019-10-15');

-- --------------------------------------------------------

--
-- Table structure for table `orders`
--

CREATE TABLE `orders` (
  `id_order` int(255) NOT NULL,
  `id_user` int(255) NOT NULL,
  `id_product` int(255) NOT NULL,
  `amount` decimal(6,2) NOT NULL,
  `order_date` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `products`
--

CREATE TABLE `products` (
  `id_prod` int(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `description` varchar(10000) NOT NULL,
  `img` varchar(255) NOT NULL,
  `price` decimal(6,2) NOT NULL,
  `creation_date` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `products`
--

INSERT INTO `products` (`id_prod`, `name`, `description`, `img`, `price`, `creation_date`) VALUES
(2, 'Veste trucker en daim', 'Veste Trucker en daim Merchant Store Superdry Homme. Veste en daim de qualité supérieure avec col en sherpa, fermeture à boutons-pression et quatre poches avant. Poche intérieure pratique, poignets à bouton-pression et doublure à imprimé écossais. Badge en cuir subtil sur la manche et badge en métal sur la poche.', 'https://cdn.laredoute.com/products/680by680/2/b/9/2b9b6e977aef53424ba1ed620b8a6944.jpg', '249.95', '2019-10-15'),
(3, 'Veste en cuir daim', 'Cette veste en daim est dotée d\'une coupe confortable et de poches sur la poitrine et les côtés pour garder votre téléphone et vos clefs en lieu sûr. Sa structure de qualité vous permettra de la porter durant des années.', 'https://cdn.laredoute.com/products/680by680/9/6/5/965b41257a864e821ea6b289230b85ca.jpg', '249.99', '2019-10-15'),
(4, 'Veste en daim classique marron', 'Veste en daim classique couleur marron\n100 % Cuir de vachette velours\nDoublure 100% Polyester\nCuir véritable de premier choix\nFermeture centrale avec trois boutons\nDeux poches ouvertes en biais\nTrois poches intérieures dont une zippée\nCol à revers\nEffet vintage', 'https://cdn.laredoute.com/products/680by680/c/8/0/c806e0f96d6bd2226d87ff0e9acdfe94.jpg', '300.00', '2019-10-15'),
(5, 'Veste Daim synthétique', '- Veste en daim synthétique', 'https://cdn.laredoute.com/products/680by680/1/2/8/1288c22605e2775c9a093e8a9a7c1efb.jpg', '119.99', '2019-10-15'),
(6, 'Blouson aviateur daim marron', 'Collection Smart, Coupe courte, Style aviateur, 100 % daim, Surpiqûres décoratives, Col classique, Deux poches zippées sur le devant, Manches longues, Bords élastiques, Bords côtelés contrastants, Fermeture Éclair avec boutons, Doublure matelassée, Poche intérieure', 'https://cdn.laredoute.com/products/680by680/3/1/a/31a172c9b4fb02f13dbf5a43e9e9457a.jpg', '169.99', '2019-10-15');

-- --------------------------------------------------------

--
-- Table structure for table `product_categories`
--

CREATE TABLE `product_categories` (
  `id` int(255) NOT NULL,
  `id_prod` int(255) NOT NULL,
  `id_cat` int(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `id` int(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `email` varchar(255) NOT NULL,
  `pw` varchar(255) NOT NULL,
  `privilege` enum('standard','admin') NOT NULL DEFAULT 'standard',
  `creation_date` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `name`, `email`, `pw`, `privilege`, `creation_date`) VALUES
(1, 'chris', 'chris@chris.fr', '$2y$10$n/1OdiCGiwb2BcyQL7VrU.1PQTChyusldXod1dsf2vK7aHUuYu1cG', 'standard', '2019-10-18'),
(2, 'admin', 'admin@chris.fr', '$2y$10$A6lxYTNt0vf235m60Co5f.h.1dd3Z2g2x6X00I.yWDhV91x/ofAi6', 'admin', '2019-10-18');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `categories`
--
ALTER TABLE `categories`
  ADD PRIMARY KEY (`id_cat`);

--
-- Indexes for table `orders`
--
ALTER TABLE `orders`
  ADD PRIMARY KEY (`id_order`);

--
-- Indexes for table `products`
--
ALTER TABLE `products`
  ADD PRIMARY KEY (`id_prod`);

--
-- Indexes for table `product_categories`
--
ALTER TABLE `product_categories`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `categories`
--
ALTER TABLE `categories`
  MODIFY `id_cat` int(255) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `orders`
--
ALTER TABLE `orders`
  MODIFY `id_order` int(255) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `products`
--
ALTER TABLE `products`
  MODIFY `id_prod` int(255) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT for table `product_categories`
--
ALTER TABLE `product_categories`
  MODIFY `id` int(255) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(255) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
