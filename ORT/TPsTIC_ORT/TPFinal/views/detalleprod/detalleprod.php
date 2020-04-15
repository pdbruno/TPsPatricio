<script>
let contenedor = document.getElementById('contenedor');
let indicadores = document.getElementById('indicadores');
var request = $.ajax({
  url: "<?php echo URL; ?>producto/traerElemento/Productos",
  data: "data=<?php echo $this->Nombre; ?>",
  type: "post",
});
request.done(function (respuesta){
  let myObj = JSON.parse(respuesta);
  for (x in myObj[0]) {
    let y = document.getElementById(x);
    if (y) {
      y.innerHTML = myObj[0][x];
    }
  }
  document.getElementById("Imagen").src = "../" + myObj[0]["Imagen"]
  document.getElementById("CatNombre").href = "<?php echo URL; ?>producto/filtrarProductos/" + myObj[0].idCategorias;
});

</script>
