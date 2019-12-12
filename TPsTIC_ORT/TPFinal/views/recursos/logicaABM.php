<script>
var ElemForm = {
  checkboxes: document.getElementById("Formu").getElementsByClassName("checkbox"),
  intros: document.getElementById("Formu").getElementsByClassName("intro"),
  $BtnAceptar: $("#BtnAceptar"),
  $BtnAgregar: $("#BtnAgregar"),
  $BtnModificar: $("#BtnModificar"),
  $BtnEliminar: $("#BtnEliminar"),
  $Tabla: $('#Tabla'),
  Columns: [],
  Formu: document.getElementById("Formu"),
  alertdiv: "",
  modal: $("#ModalPropiedades")
};

function crearCampos(myObj, Formulario = ElemForm.Formu){
  let l = myObj.length;
  for (var i = 0; i < l; i++) {
    let listgroupitem = document.createElement("li");
    listgroupitem.className = "list-group-item";
    let formgroup = document.createElement("div");
    formgroup.className = "form-group";
    formgroup.id = myObj[i].COLUMN_NAME + "Group";

    let controllabel = document.createElement("label");
    controllabel.className = "col-sm-2 control-label";
    controllabel.innerHTML = myObj[i].COLUMN_COMMENT;

    let col10 = document.createElement("div");
    col10.className = "col-sm-10";

    let formcontrolstatic = document.createElement("p");
    formcontrolstatic.id = myObj[i].COLUMN_NAME;
    if (myObj[i].DATA_TYPE=="tinyint") {
      formcontrolstatic.className = "intro hidden";
    }else{
      formcontrolstatic.className = "form-control-static";
    }
    let formcontrol = document.createElement("input");
    formcontrol.name = myObj[i].COLUMN_NAME;
    formcontrol.id = myObj[i].COLUMN_NAME + "Form";
    formcontrol.placeholder = myObj[i].COLUMN_COMMENT;
    let select;
    switch (myObj[i].DATA_TYPE) {
      case "tinyint":
      formcontrol.type = 'checkbox';
      formcontrol.className = "checkbox hidden";
      formcontrol.disabled = true;
      break;
      case "date":
      formcontrol.className = "form-control date hidden";
      formcontrol.type = 'text';
      formcontrol.disabled = true;
      break;
      case "text":
      formcontrol.className = "form-control hidden";
      formcontrol.disabled = true;
      formcontrol.type = 'text';
      if (myObj[i].COLUMN_NAME == "Imagen") {
        formcontrol.type = 'file';
        formcontrol.accept = 'image/*';
        formcontrol.className = "hidden";
        formcontrolstatic = document.createElement("img");
        formcontrolstatic.id = myObj[i].COLUMN_NAME;
        formcontrolstatic.style="width:304px;height:228px;"
      }
      break;
      case "int":
      case "decimal":
      formcontrol.disabled = true;
      formcontrol.type = 'number';
      formcontrol.className = "form-control hidden";

      switch (myObj[i].COLUMN_KEY) {
        case "MUL":
        formcontrol.className = "form-control hidden";
        formcontrol.type = 'text';
        formcontrol.style.display = 'none';
        formcontrol.style.visibility = 'hidden';
        select = document.createElement("select");
        hacemeUnDropdown(myObj[i].COLUMN_NAME, select);
        select.className = "form-control hidden";
        select.id = myObj[i].COLUMN_NAME + "Select";
        break;
        case "PRI":
        formcontrol.className = "form-control hidden";
        formcontrol.type = 'text';
        listgroupitem.className = 'list-group-item hidden';
      }
    }

    if (myObj[i].COLUMN_KEY == 'MUL') {
      col10.appendChild(formcontrolstatic);
      col10.appendChild(select);
      col10.appendChild(formcontrol);
    }else {
      col10.appendChild(formcontrolstatic);
      col10.appendChild(formcontrol);
    }
    if (myObj[i].IS_NULLABLE === "NO"  && myObj[i].COLUMN_KEY != "PRI") {
      let errorlabel = document.createElement("label");
      errorlabel.id = myObj[i].COLUMN_NAME + "Error";
      errorlabel.className = "control-label hidden";
      errorlabel.innerHTML = "Este campo es obligatorio";
      col10.appendChild(errorlabel);
    }
    formgroup.appendChild(controllabel);
    formgroup.appendChild(col10);
    listgroupitem.appendChild(formgroup);
    Formulario.appendChild(listgroupitem);
    setProp(myObj[i]);
  }
}
function hacemeUnDropdown(nombre, select){
  let request = $.ajax({
    url: "<?php echo URL; ?>" + nombre.substr(2, nombre.length-3).toLowerCase() + "/dropdown/" + nombre,
    type: "post"
  });
  request.done(function (respuesta){
    respuesta = JSON.parse(respuesta);
    select.innerHTML = optionCrear(respuesta[0]);
    if (respuesta[1] == 2) {
      select.innerHTML += "<option onclick=\"addOpt('" + nombre + "')\">+Agregar</option>";
      let isChrome = !!window.chrome && !!window.chrome.webstore;
      if (isChrome) {
        select.addEventListener("change", function() {
          this.options[this.selectedIndex].onclick();
        });
      }
    }
  });
}
function addOpt(nombre){
  let nuevaopcion = prompt("Ingrese la nueva opción");
  if (nuevaopcion != null) {
    var request = $.ajax({
      url: "<?php echo URL; ?>" + nombre.substr(2, nombre.length-3).toLowerCase() + "/agregarModificarElemento/" + nombre.substr(2).toLowerCase(),
      type: "post",
      data: "data=" + JSON.stringify({Nombre : nuevaopcion}),
    });
    request.done(function (respuesta){
      hacemeUnDropdown(nombre, document.getElementById(nombre + "Select"));
    });
  }
}
function setProp(myObj){
  ElemForm.Columns.push(myObj);
  ElemForm[myObj.COLUMN_NAME + "Select"] = $("#" + myObj.COLUMN_NAME + "Select");
  ElemForm[myObj.COLUMN_NAME] = $("#" + myObj.COLUMN_NAME);
  ElemForm[myObj.COLUMN_NAME + "Form"] = $("#" + myObj.COLUMN_NAME + "Form");
  ElemForm[myObj.COLUMN_NAME + "Group"] = $("#" + myObj.COLUMN_NAME + "Group");
  ElemForm[myObj.COLUMN_NAME + "Error"] = $("#" + myObj.COLUMN_NAME+ "Error");
}

function optionCrear(vec) {
  let txt="<option disabled selected value>Seleccione una opción</option>";
  let l = vec.length;
  for (let i = 0; i < l; i++) {
    txt += "<option value='" + vec[i].id + "'>" + vec[i].Nombre + "</option>";
  }
  return txt;
}


function clickFila(obj){
  $("#noti").remove();
  for (x in obj) {
    if (x == "Imagen") {
      ElemForm[x].attr("src", obj[x]);
    }else {
      ElemForm[x].text(obj[x]);
      if (ElemForm[x + "Form"].attr("type") == 'checkbox') {
        if (obj[x] == 1) {
          ElemForm[x + "Form"].attr("checked", true);
        } else {
          ElemForm[x + "Form"].attr("checked", false);
        }
      } else {
        ElemForm[x + "Form"].val(obj[x]);
      }
    }
    ElemForm[x + "Group"].removeClass("has-error");
    ElemForm[x + "Error"].addClass("hidden");
    ElemForm[x + "Select"].addClass("hidden");
    ElemForm[x + "Form"].addClass("hidden");
    ElemForm[x].removeClass("hidden");
  }
  let l = ElemForm.intros.length;
  if (l>0) {
    for (let i = 0; i < l; i++) {
      $("#" + ElemForm.checkboxes[i].id).removeClass("hidden");
      ElemForm.checkboxes[i].disabled = true;
      if (ElemForm.intros[i].innerHTML == 1 || ElemForm.intros[i].innerHTML == "YES") {
        ElemForm.checkboxes[i].checked = true;
      } else {
        ElemForm.checkboxes[i].checked = false;
      }
      $("#" + ElemForm.intros[i].id).addClass("hidden");
    }
  }
  $('#ModalPropiedades').modal('show');
  ElemForm.$BtnAceptar.addClass("hidden");
  ElemForm.$BtnAgregar.removeClass("hidden");
  ElemForm.$BtnModificar.removeClass("hidden");
  ElemForm.$BtnEliminar.removeClass("hidden");
}
function afterEnviar(){
  let l = ElemForm.Columns.length;
  for (var i = 0; i < l; i++) {
    ElemForm[ElemForm.Columns[i].COLUMN_NAME + "Select"].addClass("hidden");
    ElemForm[ElemForm.Columns[i].COLUMN_NAME].removeClass("hidden").html("");
    ElemForm[ElemForm.Columns[i].COLUMN_NAME + "Form"].addClass("hidden");
  }
  l = ElemForm.checkboxes.length;
  if (l>0) {
    for (var i = 0; i < l; i++) {
      ElemForm.checkboxes[i].disabled = true;
    }
  }
  ElemForm.modal.modal('hide');
  ElemForm.$BtnAceptar.addClass("hidden");
  ElemForm.$BtnAgregar.removeClass("hidden");
  ElemForm.$BtnModificar.addClass("hidden");
  ElemForm.$BtnEliminar.addClass("hidden");
  ElemForm.$Tabla.bootstrapTable('refresh');
}
function beforeEnviar(){
  let mal = false;
  let l = ElemForm.checkboxes.length;
  if (l>0) {
    for (var i = 0; i < l; i++) {
      ElemForm.checkboxes[i].value = (ElemForm.checkboxes[i].checked) ? 1 : 0;
    }
  }
  l = ElemForm.Columns.length;
  for (var i = 0; i < l; i++) {
    ElemForm[ElemForm.Columns[i].COLUMN_NAME + "Group"].removeClass("has-error");
    ElemForm[ElemForm.Columns[i].COLUMN_NAME + "Error"].addClass("hidden");

    let sel = document.getElementById(ElemForm.Columns[i].COLUMN_NAME + "Select");
    if ( sel != null) {
      ElemForm[ElemForm.Columns[i].COLUMN_NAME + "Form"].val(sel.value);
    }
    if (ElemForm[ElemForm.Columns[i].COLUMN_NAME + "Form"].val() === "") {
      if (ElemForm.Columns[i].IS_NULLABLE === 'NO' && ElemForm.Columns[i].DATA_TYPE != "tinyint" && ElemForm.Columns[i].COLUMN_KEY != "PRI") {
        ElemForm[ElemForm.Columns[i].COLUMN_NAME + "Group"].addClass("has-error");
        ElemForm[ElemForm.Columns[i].COLUMN_NAME + "Error"].removeClass("hidden");
        mal = true;
      }else {
        ElemForm[ElemForm.Columns[i].COLUMN_NAME + "Form"].val(null);
      }
    }
  }
  if (mal) {
    if(document.getElementById("noti") == null){
      ElemForm.modal.append('<div id="noti" class="alert col-lg-6 col-lg-offset-3 col alert-danger alert-dismissible fade in" role="alert">\
    <button type="button" class="close" data-dismiss="alert" aria-label="Close"><span aria-hidden="true">&times;</span></button>\
    <strong>Alto ahi vaquero/a!</strong> Hay campos obligatorios sin llenar.\
  </div>');
    }
    return 'no';

  }else {
    return new FormData(ElemForm.Formu);
  }
}

function eliminarError(respuesta){
  afterEnviar();
  if (respuesta != "") {
    alert("Como existen registros que hacen referencia a este elemento, éste no se puede eliminar.\n\ Calma: esto no es un error ni una falla.");
  }
}

function modoFormulario(modo){
  if (modo == "Agregar") {
    $('#ModalPropiedades').modal('show');
  }
  ElemForm.$BtnAceptar.removeClass("hidden");
  ElemForm.$BtnModificar.addClass("hidden");
  ElemForm.$BtnEliminar.addClass("hidden");
  let l = ElemForm.Columns.length;
  for (var i = 0; i < l; i++) {
    ElemForm[ElemForm.Columns[i].COLUMN_NAME + "Group"].removeClass("has-error");
    ElemForm[ElemForm.Columns[i].COLUMN_NAME + "Error"].addClass("hidden");
    ElemForm[ElemForm.Columns[i].COLUMN_NAME + "Select"].removeClass("hidden").prop("selectedIndex", 0);
    ElemForm[ElemForm.Columns[i].COLUMN_NAME].addClass("hidden");
    ElemForm[ElemForm.Columns[i].COLUMN_NAME + "Form"].removeClass("hidden").attr('disabled', false);
    if (modo == "Agregar") {
      ElemForm[ElemForm.Columns[i].COLUMN_NAME + "Form"].val(null);
    }else {
      let select = document.getElementById(ElemForm.Columns[i].COLUMN_NAME + "Select");
      if (select != null) {
        let opciones = select.options;
        let l = select.length;
        for (let j = 0; j < l; j++) {
          if (opciones[j].text == ElemForm[ElemForm.Columns[i].COLUMN_NAME + "Form"].val()) {
            select.selectedIndex = j;
            break;
          }
        }
      }
    }
  }
}
</script>
