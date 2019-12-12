<?php
session_start();
spl_autoload_register(function ($class) {
    include 'libs/' . $class . '.php';
});
require_once 'config/paths.php';
$Bootstrap = new Bootstrap();
if (isset($_COOKIE['idUsuarios'])) {
  echo "string";
  $UsuarioModel = new usuario_Model();
  $UsuarioModel->autoLogIn();
}
