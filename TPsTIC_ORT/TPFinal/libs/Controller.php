<?php

class Controller {

  function __construct() {
    $this->view = new View();
  }

  protected function destroySession(){
    session_unset();
    session_destroy();
  }

  protected function checkPriv(){
    if (!isset($_SESSION['logueado']) || $_SESSION['logueado'] == false) {
      $this->view->titpag = "Dónde pensas que vas bebé?";
      $this->view->msg = "Usted no tiene permiso para acceder a esta página. JAJA.";
      $this->view->render('error');
      exit;
    }
  }

  public function dropdown($tipo) {
    echo $this->model->dropdown($tipo);
  }

  public function listarElementos($tipo) {
    echo $datos = $this->model->listado($tipo);
  }

  public function loadModel($name) {
    $path = 'models/' . $name . '_model.php';
    if (file_exists($path)) {
      require $path;
      $modelName = $name . '_Model';
      $this->model = new $modelName();
    }
  }

  public function tabla($tipo) {
    $this->model->tabla($tipo);
  }

  public function traerElemento($tipo) {
    echo $this->model->traerElemento($tipo, $_POST['data']);
  }

}
