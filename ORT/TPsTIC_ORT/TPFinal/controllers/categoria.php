<?php

class categoria extends Controller {

  function abm() {
    $this->checkPriv();
    $this->view->lista = URL . "categoria/listarElementos/Categorias";
    $this->view->tabla = URL . "categoria/tabla/Categorias";
    $this->view->agregarModificar = URL . "categoria/agregarModificarElemento/Categorias";
    $this->view->eliminar = URL . "categoria/eliminarElemento";
    $this->view->traer = URL . "categoria/traerElemento/Categorias";
    $this->view->titmodal ="Categoria";
    $this->view->th = "<th data-field='Nombre' data-sortable='true'>Nombre</th>";
    $this->view->renderTabla(null, true);
  }

  public function __construct() {
    parent::__construct();
  }

  public function eliminarElemento() {
    $this->checkPriv();
    $this->model->eliminar("Categorias",  $_POST['data']);
  }

  public function agregarModificarElemento() {
    $this->checkPriv();
    $this->model->agregarModificar("Categorias", json_decode($_POST['data'], TRUE));
  }

}
