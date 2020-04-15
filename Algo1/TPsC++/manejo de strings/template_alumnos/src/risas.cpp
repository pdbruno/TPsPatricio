#include <string>
#include <vector>
#include "risas.h"
#include <iostream>
#include <fstream>

using namespace std;

/* Utiles */
vector<char> leerDatos(string s) {
    vector<char> vec;
    ifstream archivo;
    char n;
    archivo.open(s, ios::in);
    while (!archivo.eof()){
        archivo >> n;
        vec.push_back(n);
    }
    archivo.close();
    return vec;
}

int leerLargoReal(string filename){
    int val = -1;
    ifstream archivo;
    int n;
    archivo.open(filename, ios::in);
    while (!archivo.eof()){
        archivo >> val;
    }
    archivo.close();
    return val;
}
/* Utiles */

/* RESOLUCION ALUMNOS */
int risaMasLarga(vector<char> s)
{
    int largo = 0;
    for (int i = 0; i < s.size(); ++i) {

    }
    return largo;
}
/* RESOLUCION ALUMNOS */