<script>

var request = $.ajax({
  url: "<?php echo $this->tabla; ?>",
  type: "post",
});
request.done(function (respuesta){
  let myObj = JSON.parse(respuesta);
  crearCampos(myObj);
});
document.getElementById("BtnAgregar").addEventListener("click", function() {
  modoFormulario('Agregar');
});
document.getElementById("BtnModificar").addEventListener("click", function() {
  modoFormulario('Modificar');
});
document.getElementById("BtnAceptar").addEventListener("click", function() {
  let vec = beforeEnviar();
  if (vec != 'no') {
    var request = new XMLHttpRequest();
    request.addEventListener("load", function (aEvt) {
      if (request.readyState == 4 && request.status == 200) {
         if (request.responseText == "El código ingresado está siendo usado por otro producto") {
           ElemForm["CodigoGroup"].addClass("has-error");
           ElemForm["CodigoError"].removeClass("hidden").text(request.responseText);
             ElemForm.modal.append('<div id="noti" class="alert col-lg-6 col-lg-offset-3 col alert-danger alert-dismissible fade in" role="alert">\
           <button type="button" class="close" data-dismiss="alert" aria-label="Close"><span aria-hidden="true">&times;</span></button>\
           <strong>Alto ahi vaquero/a!</strong> Hay campos obligatorios sin llenar.\
         </div>');
         }else {
           afterEnviar();
         }
      }
    });
    request.open("POST", "<?php echo $this->agregarModificar; ?>");
    request.send(vec);
  }
});
document.getElementById("BtnEliminar").addEventListener("click", function() {
  var r = confirm("Estás muy recontra segurísima/o que querés borrar este elemento?");
  if (r == true) {
    request = $.ajax({
      url: "<?php echo $this->eliminar; ?>",
      type: "post",
      data: "data=" + document.getElementById("id<?php echo $this->titmodal; ?>s").innerHTML,
    });
    request.done(function (respuesta){
      eliminarError(respuesta);
    });
  }
});
$('#Tabla').on('click-row.bs.table', function (row, $element, field) {
  $('.success').removeClass('success');
  $(field).addClass('success');
  var request = $.ajax({
    url: "<?php echo $this->traer; ?>",
    type: "post",
    data: "data=" + $element.id<?php echo $this->titmodal; ?>s,
  });
  request.done(function (respuesta){
    clickFila(JSON.parse(respuesta)[0]);
  });
});

</script>
