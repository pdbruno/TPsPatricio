<?php

class producto extends Controller {

  function abm() {
    $this->checkPriv();
    $this->view->lista = URL . "producto/listarElementos/Productos";
    $this->view->tabla = URL . "producto/tabla/productos";
    $this->view->agregarModificar = URL . "producto/agregarModificarElemento/Productos";
    $this->view->eliminar = URL . "producto/eliminarElemento";
    $this->view->traer = URL . "producto/traerElemento/Productos";
    $this->view->titmodal ="Producto";
    $this->view->th = "<th data-field='Nombre' data-sortable='true'>Nombre</th>";
    $this->view->renderTabla(null, true);
  }

  public function destacados() {
    $this->model->destacados();
  }
  public function index() {
    $this->view->lista = URL . "producto/listarProductos";
    $this->view->imagen ="myObj[i].Imagen";
    $this->view->titulo ="Productos";
    $this->view->render('listproductos');
  }


  public function detalleprod($Nombre) {
    $this->view->Nombre = $Nombre;
    $this->view->render('detalleprod');
  }


  public function filtrar($Nombre) {
    $this->model->filtrar($Nombre);
  }

  public function filtrarProductos($Nombre) {
    $this->view->lista = URL . 'producto/filtrar/' . $Nombre;
    $this->view->imagen =" '../' + myObj[i].Imagen";
    $this->view->titulo = 'Productos: ' . $Nombre;
    $this->view->render('listproductos');
  }

  public function eliminarElemento() {
    $this->checkPriv();
    if ($this->model->borrarFoto($_POST['data'])) {
      $this->model->eliminar("Productos",  $_POST['data']);
    }
  }

  public function listarProductos() {
    $this->model->listarProductos();
  }

  public function __construct() {
    parent::__construct();
  }

  public function agregarModificarElemento() {
    $this->checkPriv();
    if (!$this->model->verificarCodigo($_POST["Codigo"], $_POST["idProductos"])) {
      echo "El código ingresado está siendo usado por otro producto";
    }else {

      $target_dir = "controllers/uploads/";
      $target_file = $target_dir . basename($_FILES["Imagen"]["name"]);
      $uploadOk = 1;
      $imageFileType = pathinfo($target_file,PATHINFO_EXTENSION);
      // Check if image file is a actual image or fake image
      if(isset($_POST["submit"])) {
        $check = getimagesize($_FILES["Imagen"]["tmp_name"]);
        if($check !== false) {
          echo "File is an image - " . $check["mime"] . ".";
          $uploadOk = 1;
        } else {
          echo "File is not an image.";
          $uploadOk = 0;
        }
      }
      // Check if file already exists
      if (file_exists($target_file)) {
        echo "Sorry, file already exists.";
        $uploadOk = 0;
      }

      // Allow certain file formats
      if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
      && $imageFileType != "gif" ) {
        echo "Sorry, only JPG, JPEG, PNG & GIF files are allowed.";
        $uploadOk = 0;
      }
      // Check if $uploadOk is set to 0 by an error
      if ($uploadOk == 0) {
        echo "Sorry, your file was not uploaded.";
        // if everything is ok, try to upload file
      } else {
        if (move_uploaded_file($_FILES["Imagen"]["tmp_name"], "$target_file")) {
          $_POST["Imagen"] = '../' . $target_file;
          $this->model->agregarModificar("Productos", $_POST);
        } else {
          echo "Sorry, there was an error uploading your file.";
        }
      }
    }
  }

}
