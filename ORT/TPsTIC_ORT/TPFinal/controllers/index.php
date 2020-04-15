<?php

class index extends Controller {
  function __construct() {
    parent::__construct();
  }

  function index() {
    $this->view->lista = URL . "producto/destacados";
    $this->view->imagen ="myObj[i].Imagen.substr(1)";
    $this->view->titulo ="Productos Destacados";
    $this->view->render('listproductos');
    }

}
