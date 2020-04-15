<script type="text/javascript">
var Elementos = {
  NombreForm: document.getElementById("NombreForm"),
  NombreError: document.getElementById("NombreError"),
  NombreGroup: document.getElementById("NombreGroup"),
  PasswordForm: document.getElementById("PasswordForm"),
  PasswordError: document.getElementById("PasswordError"),
  PasswordGroup: document.getElementById("PasswordGroup"),
  Recordar: document.getElementById("Recordar"),
  BtnAceptar: document.getElementById("BtnAceptar"),
};

Elementos.BtnAceptar.addEventListener("click", function() {
  let mal = false;
  Elementos.PasswordGroup.className = "form-group";
  Elementos.NombreGroup.className = "form-group";
  Elementos.NombreError.classList.add("hidden");
  Elementos.PasswordError.classList.add("hidden");
  Elementos.NombreError.innerHTML = "";
  Elementos.PasswordError.innerHTML = "";

  if (Elementos.PasswordForm.value == "") {
    Elementos.PasswordError.innerHTML = "Ingrese una Contraseña";
    Elementos.PasswordError.classList.remove("hidden");
    Elementos.PasswordGroup.classList.add("has-warning");
    mal = true;
  }

  if (Elementos.NombreForm.value == "") {
    Elementos.NombreError.innerHTML = "Ingrese un Nombre";
    Elementos.NombreError.classList.remove("hidden");
    Elementos.NombreGroup.classList.add("has-warning");
    mal = true;
  }

  if (!mal) {
    let xhr = new XMLHttpRequest();
    xhr.open("POST", "<?php echo $this->URL; ?>");
    xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhr.onreadystatechange = function () {
      if(xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {
        if (xhr.responseText != "") {
          let myObj = JSON.parse(xhr.responseText);
          for (var i = 0; i < myObj.length; i++) {
            Elementos[myObj[i].Nombre + "Error"].innerHTML = myObj[i].Texto;
            Elementos[myObj[i].Nombre + "Error"].classList.remove("hidden");
            Elementos[myObj[i].Nombre + "Group"].classList.add("has-error");
          }
        }else {
          window.location.replace("<?php echo URL; ?>");
        }
      }
    };
    xhr.send("data=" + JSON.stringify({Nombre: Elementos.NombreForm.value, Password: Elementos.PasswordForm.value, Recordar: Elementos.Recordar.checked}));
  }
});
</script>
