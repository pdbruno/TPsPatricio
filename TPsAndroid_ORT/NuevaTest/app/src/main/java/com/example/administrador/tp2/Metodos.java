package com.example.administrador.tp2;

import java.lang.ref.Reference;
import java.sql.Ref;
import java.util.Random;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.widget.TextView;
import android.widget.EditText;
import android.view.View;
/**
 * Created by 42662090 on 11/5/2017.
 */
public class Metodos {
    public static void AsignarImagenes(Boton[] VecTodo)
    {
        for (int i = 0; i < 9 ; i++)
        {
            if (VecTodo[i].LaImagen == 1)
            {
                VecTodo[i].ElBoton.setImageResource(R.drawable.ussr);
            }
            else
            {
                VecTodo[i].ElBoton.setImageResource(R.drawable.usa);
            }
        }
    }
    public static int GeneradorDeNum(int Maximo)
    {

        Random GeneradorDeAzar;
        GeneradorDeAzar = new Random();
        int Num = 0;
        Num = GeneradorDeAzar.nextInt(Maximo);
        return Num;
    }
    public static Boton[] VolverAJugar(Boton[]VecTodo){
        for (int i = 0; i < 9; i++) {
            VecTodo[i].LaImagen = Metodos.GeneradorDeNum(2);
        }
        Metodos.AsignarImagenes(VecTodo);
        return VecTodo;
    }

    public static void CrearLogIn(TextView Num1, TextView Num2, EditText Nombre) {
        Num1.setText(String.valueOf(Metodos.GeneradorDeNum(10)));
        Num2.setText(String.valueOf(Metodos.GeneradorDeNum(10)));
        Nombre.setText("");
    }
    public static Boolean BaseDeDatosAbierta(DataBaseAccess Acceso, Context c, SQLiteDatabase baseDatos)
    {
        Boolean responder;
        Acceso = new DataBaseAccess(c, "Tp3DB", null, 1);
        baseDatos = Acceso.getWritableDatabase();
        if (baseDatos!=null)
        {
            responder = true;
        }else{
            responder = false;
        }
        return responder;


    }



}
