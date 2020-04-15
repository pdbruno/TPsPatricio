<?php

class usuario_Model extends Model {

  public function __construct() {
    parent::__construct();
  }

  public function autoLogIn() {
    $outp = $this->db->getOne("SELECT Nombre FROM usuarios WHERE idUsuarios = ?i", $_COOKIE['idUsuarios']);
    $_SESSION['logueado'] = true;
    $_SESSION['nombre'] = $outp;
  }

  public function logIn($Data)
  {
      $outp = $this->db->getRow("SELECT * FROM usuarios WHERE Nombre = ?s", $Data->Nombre);
      if (!$outp) {
        echo json_encode([array('Nombre' => 'Nombre', 'Texto' => 'El nombre de usuario no existe')]);
      }else {
        if (password_verify($Data->Password, $outp['Password'])) {
          $_SESSION['logueado'] = true;
          $_SESSION['nombre'] = $Data->Nombre;
          if ($Data->Recordar) {
            $this->recordarUsuario($outp['idUsuarios']);
          }else {
            $this->olvidarUsuario();
          }
        } else {
          echo json_encode([array('Nombre' => 'Password', 'Texto' => 'Contraseña incorrecta')]);
        }
      }

  }

  public function addUsuario($Data)
  {
      $Data->Password = password_hash($Data->Password, PASSWORD_DEFAULT);
      $outp = $this->db->query("INSERT INTO `usuarios`(`Nombre`, `Password`) VALUES (?s ,?s)", $Data->Nombre, $Data->Password);
      $_SESSION['logueado'] = true;
      $_SESSION['nombre'] = $Data->Nombre;
      if ($Data->Recordar) {
        $this->recordarUsuario($this->db->insertId());
      }else {
        $this->olvidarUsuario();
      }
  }

  private function recordarUsuario($Id)
  {
    setcookie("idUsuarios", $Id, strtotime( '+30 days' ));
  }

  public function olvidarUsuario()
  {
    setcookie('idUsuarios', '', 1);
  }

  public function checkNombre($Nombre)
  {
      echo $this->db->getOne("SELECT * FROM usuarios WHERE Nombre = ?s", $Nombre);
  }

}
