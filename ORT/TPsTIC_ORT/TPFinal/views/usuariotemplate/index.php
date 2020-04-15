<div class="row">
  <div class="col-md-4 col-md-offset-4">
    <div class="login-panel panel panel-default">
      <div class="panel-heading">
        <h3 class="panel-title"><?php echo $this->Titulo; ?></h3>
      </div>
      <div class="panel-body">
        <form role="form">
          <fieldset>
            <div class="form-group" id="NombreGroup">
              <label class="control-label hidden" id="NombreError"></label>
              <input class="form-control" placeholder="Nombre" id="NombreForm" type="text" autofocus>
            </div>

            <div class="form-group" id="PasswordGroup">
              <label class="control-label hidden" id="PasswordError"></label>
              <input class="form-control" placeholder="Contraseña" id="PasswordForm" type="password" value="">
            </div>
            <div class="checkbox">
              <label>
                <input id="Recordar" type="checkbox" checked value="Recordar">Recordarme
              </label>
            </div>
            <!-- Change this to a button or input when using this as a form -->
            <button type="button" id="BtnAceptar" class="btn btn-lg btn-success btn-block">Aceptar</button>
          </fieldset>
        </form>
      </div>
    </div>
  </div>
</div>
