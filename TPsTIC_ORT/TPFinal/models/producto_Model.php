<?php

class producto_Model extends Model {

  public function __construct() {
    parent::__construct();
  }


  public function verificarCodigo($Codigo, $Id) {
    $sql = "SELECT idProductos FROM productos WHERE Codigo=?s";
    $outp = $this->db->getOne($sql, $Codigo);
    if ($outp != false) {
      if ($outp === $Id) {
        return true;
      }else {
        return false;
      }
    }
    return true;
  }

  public function traerElemento($tipo, $Nombre) {
    $sql = "SELECT productos.*, categorias.Nombre as idCategorias
    FROM productos
    INNER JOIN categorias ON productos.idCategorias = categorias.idCategorias
    WHERE productos.Nombre=?s";
    $outp = $this->db->getAll($sql, $Nombre);
    return json_encode($outp);
  }

  public function borrarFoto($idProductos) {
    $sql = "SELECT Imagen FROM productos WHERE idProductos=?i";
    $outp = $this->db->getOne($sql, $idProductos);
    return unlink(substr($outp, 1));
  }

  public function filtrar($Nombre) {
      echo json_encode($this->db->getAll("SELECT productos.*, categorias.Nombre as idCategorias
        FROM productos
        INNER JOIN categorias ON productos.idCategorias = categorias.idCategorias
        WHERE productos.idCategorias = (SELECT idCategorias FROM categorias WHERE Nombre = ?s)", $Nombre));
  }

    public function listarProductos() {
      echo json_encode($this->db->getAll("SELECT productos.*, categorias.Nombre as idCategorias
        FROM productos
        INNER JOIN categorias ON productos.idCategorias = categorias.idCategorias"));
      }

      public function destacados() {
        echo json_encode($this->db->getAll("SELECT productos.*, categorias.Nombre as idCategorias
          FROM productos
          INNER JOIN categorias ON productos.idCategorias = categorias.idCategorias
          WHERE destacado = 1"));
        }
      }
