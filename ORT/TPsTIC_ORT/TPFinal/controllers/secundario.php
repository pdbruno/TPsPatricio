<?php

class secundario extends Controller {
  function __construct() {
    parent::__construct();
  }

  function quienesSomos() {
    $this->view->render('quienessomos', true);
  }

  function contacto() {
    $this->view->render('contacto', true);
  }


}
