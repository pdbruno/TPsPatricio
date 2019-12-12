-- phpMyAdmin SQL Dump
-- version 4.7.4
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1:3306
-- Tiempo de generación: 04-11-2017 a las 17:26:00
-- Versión del servidor: 5.7.19
-- Versión de PHP: 7.1.9

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `db`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `categorias`
--

DROP TABLE IF EXISTS `categorias`;
CREATE TABLE IF NOT EXISTS `categorias` (
  `idCategorias` int(11) UNSIGNED NOT NULL AUTO_INCREMENT,
  `Nombre` text NOT NULL COMMENT 'Nombre',
  PRIMARY KEY (`idCategorias`)
) ENGINE=MyISAM AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `categorias`
--

INSERT INTO `categorias` (`idCategorias`, `Nombre`) VALUES
(1, 'Zapatillas'),
(2, 'Camperas'),
(3, 'prueba');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `productos`
--

DROP TABLE IF EXISTS `productos`;
CREATE TABLE IF NOT EXISTS `productos` (
  `idProductos` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `idCategorias` int(11) NOT NULL COMMENT 'Categoría',
  `Codigo` text NOT NULL COMMENT 'Código',
  `Nombre` text NOT NULL COMMENT 'Nombre',
  `Precio` decimal(10,0) NOT NULL COMMENT 'Precio',
  `Destacado` tinyint(4) NOT NULL DEFAULT '0' COMMENT 'Destacado',
  `Descripcion` text NOT NULL COMMENT 'Descripción',
  `Imagen` text NOT NULL COMMENT 'Imagen',
  PRIMARY KEY (`idProductos`),
  KEY `idCategorias` (`idCategorias`)
) ENGINE=MyISAM AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `productos`
--

INSERT INTO `productos` (`idProductos`, `idCategorias`, `Codigo`, `Nombre`, `Precio`, `Destacado`, `Descripcion`, `Imagen`) VALUES
(1, 1, '43562', 'Nike', '234', 1, 'Altas llantas', '../controllers/uploads/Stalin.png'),
(2, 2, '2645', 'La camperacheta', '456', 1, 'na', '../controllers/uploads/TioSam.png'),
(3, 1, 'er45', 'ProductoFalso', '567', 1, 'asdf', '../controllers/uploads/strat.jpg');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `usuarios`
--

DROP TABLE IF EXISTS `usuarios`;
CREATE TABLE IF NOT EXISTS `usuarios` (
  `idUsuarios` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `Nombre` text NOT NULL,
  `Password` text NOT NULL,
  PRIMARY KEY (`idUsuarios`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
