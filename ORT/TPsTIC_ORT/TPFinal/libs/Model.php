<?php

class Model {

  function __construct() {
    $opts = array(
      'user' => 'root',
      'pass' => '12345',
      'db' => 'db',
      'charset' => 'utf8'
    );
    $this->db = new SafeMySQL($opts);
  }
  public function listado($tipo) {
    echo json_encode($this->db->getAll("SELECT ?n , Nombre FROM ?n", 'id' . $tipo, strtolower($tipo)));
  }

  public function dropdown($tipo) {
    $outp[] = $this->db->getAll("SELECT ?n as id, Nombre FROM ?n", $tipo, strtolower(substr($tipo, 2)));
    $outp[] = $this->db->getAll("SELECT COUNT(*) FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_SCHEMA = 'db' AND TABLE_NAME = ?s", strtolower(substr($tipo, 2)))[0]['COUNT(*)'];
    echo json_encode($outp);
  }

  public function traerElemento($tipo, $id) {
    echo json_encode($this->db->getAll("SELECT * FROM ?n WHERE ?n = ?i", strtolower($tipo), 'id' . $tipo, $id));
  }

  public function agregarModificar($tipo,$data) {
    $this->db->query("INSERT INTO ?n SET ?u ON DUPLICATE KEY UPDATE ?u", strtolower($tipo), $data, $data);
  }

  public function eliminar($tipo, $id) {
    try {
      $this->db->query("DELETE FROM ?n WHERE ?n = ?i", strtolower($tipo), 'id' . $tipo, $id);
    } catch (Exception $e) {
      var_dump($e);
    }

  }

  public function tabla($tabla) {
    echo json_encode($this->db->getAll("SELECT COLUMN_NAME, DATA_TYPE, COLUMN_COMMENT, COLUMN_KEY, IS_NULLABLE FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_SCHEMA = 'db' AND TABLE_NAME = ?s", $tabla));
  }


}
