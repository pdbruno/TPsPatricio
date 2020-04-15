<?php

class usuario extends Controller {

  function __construct() {
    parent::__construct();
  }


  public function logIn() {
    $this->view->Titulo = 'LogIn';
    $this->view->URL = URL . 'usuario/checkLogin';
    $this->view->render('usuariotemplate');
  }

  public function registracion() {
    $this->view->Titulo = 'Registración';
    $this->view->URL = URL . 'usuario/addUsuario';
    $this->view->render('usuariotemplate');
  }

  public function checkLogin() {
    $this->model->logIn(json_decode($_POST['data']));
  }

  public function addUsuario() {
    $Data = json_decode($_POST['data']);

    if ($this->model->checkNombre($Data->Nombre)) {
      echo json_encode([array('Nombre' => 'Nombre', 'Texto' => 'El nombre de usuario ya existe')]);
    } else {
      if (strlen($Data->Nombre) < 6 && strlen($Data->Nombre) > 8 ) {
        echo json_encode([array('Nombre' => 'Password', 'Texto' => 'La contraseña debe tener entre 6 y 8 caracteres')]);
      }else {
        $this->model->addUsuario($Data);
      }
    }
  }

  public function logOut() {
    $this->destroySession();
    $this->model->olvidarUsuario();
    header('Location: ' . URL);
  }

}
