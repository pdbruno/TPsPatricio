package com.example.administrador.tp2;

import android.animation.TimeInterpolator;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.VectorDrawable;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.ListPopupWindow;
import android.text.style.TtsSpan;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ListAdapter;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import java.lang.ref.Reference;
import java.sql.Ref;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;
import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;

import android.widget.EditText;



public class MainActivity extends AppCompatActivity {
    // EN ALGUN LADO AVISAR SI SUPERO SU PUNTAJE (HAY QUE TRAER AL JUGADOR)
    Boton[] VecTodo = new Boton[9];
    int JuegoNuevo = 0;
    int CantDeJugadas = 0;
    int MaxJugadas;
    DataBaseAccess accesoBaseTP3;
    SQLiteDatabase baseDatos;

    Boton[] DeclararBotones()
    {
        Boton[] VecBotones;
        VecBotones = new Boton[9];
        for (int i = 0; i < 9; i++) {
            ImageButton hola;
            hola = new ImageButton(this);
            Boton Lindo = new Boton(Metodos.GeneradorDeNum(2) , hola);
            VecBotones[i] = Lindo;
        }
        VecBotones[0].ElBoton = (ImageButton) findViewById(R.id.Boton0);
        VecBotones[1].ElBoton = (ImageButton) findViewById(R.id.Boton1);
        VecBotones[2].ElBoton = (ImageButton) findViewById(R.id.Boton2);
        VecBotones[3].ElBoton = (ImageButton) findViewById(R.id.Boton3);
        VecBotones[4].ElBoton = (ImageButton) findViewById(R.id.Boton4);
        VecBotones[5].ElBoton = (ImageButton) findViewById(R.id.Boton5);
        VecBotones[6].ElBoton = (ImageButton) findViewById(R.id.Boton6);
        VecBotones[7].ElBoton = (ImageButton) findViewById(R.id.Boton7);
        VecBotones[8].ElBoton = (ImageButton) findViewById(R.id.Boton8);
        return VecBotones;
    }

    Boton[] Invertir(int bot1, int bot2, int bot3, int bot4,Boton[] VecTodo)
    {
        Boton[] VecNuevo = new Boton[4];
        VecNuevo[0]= VecTodo[bot1];
        VecNuevo[1]= VecTodo[bot2];
        VecNuevo[2]= VecTodo[bot3];
        VecNuevo[3]= VecTodo[bot4];

        for (int i = 0; i < 4; i++) {
            if (VecNuevo[i].LaImagen == 0) {
                VecNuevo[i].ElBoton.setImageResource(R.drawable.ussr);
                VecNuevo[i].LaImagen = 1;
            } else {
                VecNuevo[i].ElBoton.setImageResource(R.drawable.usa);
                VecNuevo[i].LaImagen = 0;
            }
        }
        VecTodo[bot1]=VecNuevo[0];
        VecTodo[bot2]=VecNuevo[1];
        VecTodo[bot3]=VecNuevo[2];
        VecTodo[bot4]=VecNuevo[3];
        return VecTodo;

    }

    Boton[] Invertir5(int bot1, int bot2, int bot3, int bot4, int bot5,Boton[] VecTodo)
    {
        Boton[] VecNuevo = new Boton[5];
        VecNuevo[0]= VecTodo[bot1];
        VecNuevo[1]= VecTodo[bot2];
        VecNuevo[2]= VecTodo[bot3];
        VecNuevo[3]= VecTodo[bot4];
        VecNuevo[4]= VecTodo[bot5];

        for (int i = 0; i < 5; i++) {
            if (VecNuevo[i].LaImagen == 0) {
                VecNuevo[i].ElBoton.setImageResource(R.drawable.ussr);
                VecNuevo[i].LaImagen = 1;
            } else {
                VecNuevo[i].ElBoton.setImageResource(R.drawable.usa);
                VecNuevo[i].LaImagen = 0;
            }
        }
        VecTodo[bot1]=VecNuevo[0];
        VecTodo[bot2]=VecNuevo[1];
        VecTodo[bot3]=VecNuevo[2];
        VecTodo[bot4]=VecNuevo[3];
        return VecTodo;
    }
    Jugador JActual;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        for (int i = 0; i < 9; i++) {
            ImageButton hola;
            hola = new ImageButton(this);
            Boton Lindo = new Boton(Metodos.GeneradorDeNum(2) , hola);
            VecTodo[i] = Lindo;
        }
        VecTodo = DeclararBotones();
        Metodos.AsignarImagenes(VecTodo);
        Intent Hola = getIntent();
        Bundle Datos = Hola.getExtras();
        JActual= new Jugador(Datos.getInt("Record"),Datos.getString("Nombre"), Datos.getInt("CantJuegos"));
    }

    public boolean AcasoUstedHaGanado(View v){
        String msj = "Ganaste en " + CantDeJugadas + " movimientos.";
        int caca = 0;
        boolean haGanado = false;
        for (int i = 0; i < 9; i++)
        {
            if (VecTodo[i].LaImagen == VecTodo[1].LaImagen)
            {
                caca++;
            }
            if(caca==9)
            {
                if (CantDeJugadas < JActual.CantJuegos)
                {
                    msj += "Ganaste en " + CantDeJugadas + " movimientos. Tu Record era de " + JActual.CantJuegos;
                }
                haGanado = true;
                PopUp(v,"Has ganado!", msj);
                if (Metodos.BaseDeDatosAbierta(accesoBaseTP3, this, baseDatos)) {

                    baseDatos.execSQL("UPDATE Jugadores SET Record = " + JActual.Record + ", CantJuegos = " + JActual.CantJuegos + " WHERE Nombre =" + JActual.Nombre, null);
                } else {
                    //No se pudo abrir la base de datos
                }
                JuegoNuevo = 1;
                MaxJugadas = CantDeJugadas;
                TextView Record;
                Record = (TextView)findViewById(R.id.Record);
                Record.setText("Record = "+ MaxJugadas);
            }
        }
        return haGanado;
    }

    public void PresionarBoton (View Apalapapa)
    {
        CantDeJugadas++;
        TextView Jugadas;
        Jugadas = (TextView)findViewById(R.id.Jugadas);
        if (CantDeJugadas<=MaxJugadas || MaxJugadas==0) {
            Jugadas.setText("Jugadas = "+ CantDeJugadas);
            ImageButton BotonPresionado;
            BotonPresionado = (ImageButton) Apalapapa;
            switch (BotonPresionado.getId()) {
                case R.id.Boton0:
                    VecTodo = Invertir(0, 1, 3, 4, VecTodo);
                    break;
                case R.id.Boton1:
                    VecTodo = Invertir(0, 1, 2, 4, VecTodo);
                    break;
                case R.id.Boton2:
                    VecTodo = Invertir(1, 2, 4, 5, VecTodo);
                    break;
                case R.id.Boton3:
                    VecTodo = Invertir(0, 3, 4, 6, VecTodo);
                    break;
                case R.id.Boton4:
                    VecTodo = Invertir5(1, 3, 4, 5, 7, VecTodo);
                    break;
                case R.id.Boton5:
                    VecTodo = Invertir(2, 4, 5, 8, VecTodo);
                    break;
                case R.id.Boton6:
                    VecTodo = Invertir(3, 4, 6, 7, VecTodo);
                    break;
                case R.id.Boton7:
                    VecTodo = Invertir(4, 6, 7, 8, VecTodo);
                    break;
                case R.id.Boton8:
                    VecTodo = Invertir(4, 5, 7, 8, VecTodo);
                    break;
            }
            AcasoUstedHaGanado(Apalapapa);
        }else{
            PopUp(Apalapapa,"Has Perdido!","Has superado el maximo de movimientos");
            JuegoNuevo = 1;
        }
    }

    public void Jugada(int minoria){
        List<Boton> ListaBotones = new ArrayList<Boton>();
        for (int i = 0; i < 9; i++) {
            if(VecTodo[i].LaImagen == minoria){
                ListaBotones.add(VecTodo[i]);
            }
        }
        for (Boton thatbuton: ListaBotones) {
            PresionarBoton(thatbuton.ElBoton);
        }
    }

    public int DeQueHayMenos(){
        int usa = 0;
        int ussr = 0;
        for (int i = 0; i <9; i++) {
            if(VecTodo[i].LaImagen == 1){
                ussr++;
            }else
            {
                usa++;
            }
        }
        if(usa < ussr){
            return 0;
        }else{
            return 1;
        }
    }

    public void JugadasInteligentes (final View Lola) {
        final int EsMenos;
        EsMenos = DeQueHayMenos();
        final Timer MiReloj;
        MiReloj = new Timer();
        TimerTask MiTareaARepetir;
        MiTareaARepetir = new TimerTask() {
            @Override
            public void run() {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Jugada(EsMenos);
                        if (JuegoNuevo == 1) {
                            MiReloj.cancel();
                        }
                    }
                });
            }

            ;
        };
        MiReloj.schedule(MiTareaARepetir, 0, 500);
    }

    public void JugadasAlAzar(final View Lola){
        final Timer MiReloj;
        MiReloj = new Timer();
        TimerTask MiTareaARepetir;
        MiTareaARepetir = new TimerTask() {
            @Override
            public void run() {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        PresionarBoton(VecTodo[Metodos.GeneradorDeNum(9)].ElBoton);
                        if (JuegoNuevo == 1) {
                            MiReloj.cancel();
                        }
                    }
                });
            }

            ;
        };
        MiReloj.schedule(MiTareaARepetir, 0, 500);
    }

    public void PopUp(View v, String Titulo,String Mensaje){
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage(Mensaje)
                .setTitle(Titulo)
                .setCancelable(false)
                .setNeutralButton("Aceptar",
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                VecTodo = Metodos.VolverAJugar(VecTodo);
                                JuegoNuevo = 0;
                                CantDeJugadas = 0;
                                dialog.cancel();
                            }
                        });
        AlertDialog alert = builder.create();
        alert.show();
    }


}


