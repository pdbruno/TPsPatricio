<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="utf-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <!-- Bootstrap Core CSS -->
  <link href="<?php echo URL; ?>views/recursos/vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">
  <!-- MetisMenu CSS -->
  <link href="<?php echo URL; ?>views/recursos/vendor/metisMenu/metisMenu.min.css" rel="stylesheet">
  <!-- Custom CSS -->
  <link href="<?php echo URL; ?>views/recursos/dist/css/sb-admin-2.min.css" rel="stylesheet">
  <!-- Custom Fonts -->
  <link href="<?php echo URL; ?>views/recursos/vendor/font-awesome/css/font-awesome.min.css" rel="stylesheet" type="text/css">
  <!-- jQuery -->
  <script src="<?php echo URL; ?>views/recursos/vendor/jquery/jquery.min.js"></script>
  <!-- Bootstrap Core JavaScript -->
  <script src="<?php echo URL; ?>views/recursos/vendor/bootstrap/js/bootstrap.min.js"></script>
  <style media="screen">
  .product_view .modal-dialog{max-width: 800px; width: 100%;}
  .pre-cost{text-decoration: line-through; color: #a5a5a5;}
  .space-ten{padding: 10px 0;}
  </style>

  <title>Hola</title>
</head>
<body>
  <div id="wrapper" style="height: 100vh;">
    <!-- Navigation -->
    <nav class="navbar navbar-default navbar-static-top" role="navigation" style="margin-bottom: 0">
      <div class="navbar-header">
        <a class="navbar-brand" href="<?php echo URL; ?>">TPFinal TIC <small><?php if (isset($_SESSION['nombre'])) {echo "Hola, " . $_SESSION['nombre'];}?> </small></a>
      </div>
      <!-- /.navbar-header -->
      <div class="navbar-default sidebar" role="navigation">
        <div class="sidebar-nav navbar-collapse">
          <ul class="nav" id="side-menu">
            <?php if (!isset($_SESSION['logueado']) || $_SESSION['logueado'] == false): ?>
              <li>
                <a href="<?php echo URL; ?>usuario/login"><i class="fa fa-sign-in fa-fw"></i> LogIn</a>
              </li>
              <li>
                <a href="<?php echo URL; ?>usuario/registracion"><i class="fa fa-sign-in fa-fw"></i> Registrarse</a>
              </li>
            <?php else: ?>
              <li>
                <a href="<?php echo URL; ?>usuario/logout"><i class="fa fa-sign-out fa-fw"></i> LogOut</a>
              </li>
              <li>
                <a href="#"><i class="fa fa-question fa-fw"></i> Top Secret<span class="fa arrow"></span></a>
                <ul class="nav nav-second-level">
                  <li>
                    <a href="<?php echo URL; ?>producto/abm"><i class="fa fa-gear fa-fw"></i> ABMProductos</a>
                  </li>
                  <li>
                    <a href="<?php echo URL; ?>categoria/abm"><i class="fa fa-gear fa-fw"></i> ABMCategorias</a>
                  </li>
                </ul>
                <!-- /.nav-second-level -->
              </li>
            <?php endif; ?>
            <li>
              <a href="<?php echo URL; ?>producto/"><i class="fa fa-dropbox fa-fw"></i> Productos</a>
            </li>
            <li>
              <a href="#"><i class="fa fa-list fa-fw"></i> Categorías<span class="fa arrow"></span></a>
              <ul class="nav nav-second-level" id="categorias">

              </ul>
              <!-- /.nav-second-level -->
            </li>
            <li>
              <a href="<?php echo URL; ?>secundario/quienesSomos"><i class="fa fa-question fa-fw"></i> Quiénes somos</a>
            </li>
            <li>
              <a href="<?php echo URL; ?>secundario/contacto"><i class="fa fa-at fa-fw"></i> Contacto</a>
            </li>
          </ul>
        </div>
        <!-- /.sidebar-collapse -->
      </div>
      <!-- /.navbar-static-side -->
    </nav>
    <div id="page-wrapper" style="height: 92vh">
