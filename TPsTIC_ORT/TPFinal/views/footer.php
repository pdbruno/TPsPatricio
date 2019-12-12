
</div>
</div>
<!-- Metis Menu Plugin JavaScript -->
<script>
request = $.ajax({
  url: "<?php echo URL; ?>categoria/listarElementos/Categorias",
  type: "post",
});
request.done(function (respuesta){
  let myObj = JSON.parse(respuesta);
  let texto = "";
  for (let i = 0; i < myObj.length; i++) {
    texto += `<li>
      <a href="<?php echo URL; ?>producto/filtrarProductos/${myObj[i].Nombre}"> ${myObj[i].Nombre}</a>
    </li>`;
  }
  document.getElementById('categorias').innerHTML += texto;
});
</script>
<script src="<?php echo URL; ?>views/recursos/vendor/metisMenu/metisMenu.min.js"></script>
<!-- Custom Theme JavaScript -->
<script src="<?php echo URL; ?>views/recursos/dist/js/sb-admin-2.min.js"></script>
</body>
</html>
