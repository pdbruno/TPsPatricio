package com.example.administrador.tp2;

import android.content.ContentValues;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;
import java.util.ArrayList;
import java.util.List;
import com.example.administrador.tp2.Metodos;

public class JugadorActivity extends AppCompatActivity {
    List<Jugador> ListaNombre = new ArrayList<>();
    TextView Num1;
    TextView Num2;
    LinearLayout LogIn;
    LinearLayout Datos;
    EditText textoNombre;
    DataBaseAccess accesoBaseTP3;
    SQLiteDatabase baseDatos;
    TextView CantJuegos;
    TextView Nombre;
    TextView Record;

    Jugador JActual = new Jugador(0, textoNombre.getText().toString(), 0);
    boolean Existe = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_jugador);
        LogIn = (LinearLayout)findViewById(R.id.LogIn);
        Datos = (LinearLayout)findViewById(R.id.Datos);
        Num1 = (TextView)findViewById(R.id.Numero1);
        Num2 = (TextView)findViewById(R.id.Numero2);
        CantJuegos = (TextView)findViewById(R.id.CantJuegos);
        Record = (TextView)findViewById(R.id.Record);
        Nombre = (TextView)findViewById(R.id.Nombre);

        textoNombre = (EditText)findViewById(R.id.TextoNombre);
        Metodos.CrearLogIn(Num1, Num2, textoNombre);//NEcesitamos pasar una vista y no podemos, bueeeeeno "quiero"(martinsaied)
    }



    public void IngresarNombre (View Apalapapa)
    {
        int Comparador;
        String nada = "";
        Comparador = textoNombre.getText().toString().compareTo(nada);
        EditText Resultado;
        Resultado = (EditText)findViewById(R.id.Resultado);
        //Compara el resultado del capcha con lo que puso el usuario
        if (Comparador > 0 && Integer.parseInt(Resultado.getText().toString()) == Integer.parseInt(Num1.getText().toString()) + Integer.parseInt(Num2.getText().toString())) {
            ListaNombre.add(JActual);

            accesoBaseTP3 = new DataBaseAccess(this, "Tp3DB", null, 1);
            baseDatos = accesoBaseTP3.getWritableDatabase();
            if (Metodos.BaseDeDatosAbierta(accesoBaseTP3, this, baseDatos)) {
                Cursor conjuntoDeRegistros;
                //EL INSERT NO FUNCIONA DE LA FORMA ANTERIOR Y TAMPOCO DE ESTA FORMA
                conjuntoDeRegistros = baseDatos.rawQuery("select * from jugadores", null);
                if (conjuntoDeRegistros.moveToFirst()) {
                    do {
                        Jugador JTraido = new Jugador(0, textoNombre.getText().toString(), 0);
                        JTraido.Nombre = conjuntoDeRegistros.getString(0);
                        JTraido.Record = conjuntoDeRegistros.getInt(1);
                        JTraido.CantJuegos = conjuntoDeRegistros.getInt(2);
                        if (JActual.Nombre.compareTo(JTraido.Nombre) == 0) {
                            JActual = JTraido;
                            Existe = true;
                            CantJuegos.setText("Has jugado " + JActual.CantJuegos + " veces");
                            CantJuegos.setText("Su récord es de " + JActual.Record + " jugadas");
                            CantJuegos.setText("Bienvenido, " + JActual.Nombre);
                            break;
                        }

                    } while (conjuntoDeRegistros.moveToNext());
                    //PopUp(Apalapapa, "Look at this man", JActual.Nombre + JActual.Record + JActual.CantJuegos, JActual);

                }
                if(Existe==false)
                {
                    ContentValues nuevoRegistro;
                    nuevoRegistro = new ContentValues();
                    nuevoRegistro.put("Nombre", JActual.Nombre);
                    nuevoRegistro.put("Record", JActual.Record);
                    nuevoRegistro.put("CantJuegos", JActual.CantJuegos);
                    baseDatos.insert("Jugadores", null, nuevoRegistro);
                    baseDatos.close();
                    CantJuegos.setText("Este es tu primer juego");}
                    CantJuegos.setText("Bienvenido, " + JActual.Nombre);

            }

            } else {
                //No se pudo abrir la base de datos
            }
            LogIn.setVisibility(View.INVISIBLE);
            Datos.setVisibility(View.VISIBLE);
        }

    public void MainActGo (View v)
    {
        Intent GoToMain = new Intent();
        Bundle ElJugador = new Bundle();
        JActual.CantJuegos++;
        ElJugador.putString("Nombre",JActual.Nombre);
        ElJugador.putInt("Record",JActual.Record);
        ElJugador.putInt("CantJuegos",JActual.CantJuegos);
        GoToMain.putExtra("Jugador", ElJugador);
        GoToMain = new Intent(this, MainActivity.class);
        startActivity(GoToMain);
    }
    public void Salir (View v){
        LogIn.setVisibility(View.VISIBLE);
        Datos.setVisibility(View.INVISIBLE);
        Metodos.CrearLogIn(Num1, Num2, textoNombre);

    }
    public void BorrarJugador (View v){

        if (Metodos.BaseDeDatosAbierta(accesoBaseTP3, this, baseDatos)) {
            baseDatos.delete("Jugadores", "Nombre =" + JActual.Nombre, null);
            Salir(v);

        } else {
            //No se pudo abrir la base de datos
        }

        }
    public void PopUp(View v, String Titulo,String Mensaje, Jugador Jug){
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage(Mensaje)
                .setTitle(Titulo)
                .setCancelable(false)
                .setNeutralButton("Aceptar",
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                //El mensaje que pase era solo una prueba, fijat la consigna
                                //Le paso como parametro al jugardor para pasarlo con el bundle
                                //aca va el intent
                                //opcion de delete jugador (otro boton aca)
                                dialog.cancel();
                            }
                        });
        AlertDialog alert = builder.create();
        alert.show();
    }
}
