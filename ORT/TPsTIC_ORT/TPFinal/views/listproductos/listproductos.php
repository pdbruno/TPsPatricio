<script>
let contenedor = document.getElementById('contenedor');
let indicadores = document.getElementById('indicadores');
var request = $.ajax({
  url: "<?php echo $this->lista; ?>",
  type: "post",
});
request.done(function (respuesta){
  let myObj = JSON.parse(respuesta);
  let texto = "";
  for (let i = 0; i < myObj.length; i++) {
    if ((i % 3 === 0)) {
      texto += `<div class="item${(i === 0) ? ' active' : ''}">`;
      indicadores.innerHTML += `<li data-target="#myCarousel" data-slide-to="${parseInt(i/3)}" ${(i === 0) ? ' class="active"' : ''}></li>`;
    }
    texto +=
    `<div class="col-md-4">
      <div class="thumbnail">
        <img src="${<?php echo $this->imagen; ?>}" class="img-responsive">
          <div class="caption">
            <h4 class="pull-right">$${myObj[i].Precio}</h4>
            <h4><a href="#">${myObj[i].Nombre}</a></h4>
            <p>${myObj[i].Descripcion}</p>
          </div>
        <div class="space-ten"></div>
        <div class="btn-ground text-center">
          <a role="button" class="btn btn-primary" href="<?php echo URL; ?>producto/detalleprod/${myObj[i].Nombre}"><i class="fa fa-search"></i> Ver más</a>
        </div>
      </div>
    </div>  `;
    if ((i % 3 === 2)) {
      texto += `</div>`;
    }
  }
  contenedor.innerHTML += texto;
});

</script>
