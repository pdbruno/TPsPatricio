package com.example.administrador.tp2;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

/**
 * Created by 42662090 on 11/5/2017.
 */
public class DataBaseAccess extends SQLiteOpenHelper {
    public DataBaseAccess(Context context, String Nombre, SQLiteDatabase.CursorFactory fabrica, int Version )
    {
        super(context, Nombre, fabrica,Version);
    }
    public void onCreate(SQLiteDatabase BaseDatos){
        String sqlCrearTablaJugadores;
        sqlCrearTablaJugadores = "create table Jugadores(Nombre text, Record int, CantJuegos int)";
        BaseDatos.execSQL(sqlCrearTablaJugadores);
    }
    public void onUpgrade(SQLiteDatabase BaseDatos, int VersionAnterior, int VersionActuañl){

    }
}
