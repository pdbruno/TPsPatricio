#include "ejercicios.h"

/* Para compilar */

using namespace std;

vector<string> split(string s, char delim){
    vector<string> v;
    string almacenar;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] != delim){
            almacenar += s[i];
        }else if (s[i] == delim && almacenar != ""){
            v.push_back(almacenar);
            almacenar.clear();
        }

    }
    if(almacenar != ""){
        v.push_back(almacenar);
        almacenar.clear();
    }
    return v;
}

string darVueltaPalabra(string s){
    string res = "";
    vector<string> vec = split(s, ' ');
    for (int i = vec.size()-1; i > -1 ; --i) {
        res += vec[i] + " ";
    }
    if(res != ""){
        res.pop_back();
    }
    return res;
}

// Decidir si s1 es substring o subsecuencia de s2
bool subsecuencia(string s1, string s2) {
    int cont = 0;
    for (int i = 0; i < s2.size(); ++i) {
        if(cont == s1.size()-1){
            break;
        }

        if(s1[cont] == s2[i]){
            cont++;
        }
    }
    if(s1 == "" && s2 == ""){
        cont = -1;
    }
    return cont == s1.size()-1;
}

bool perteneceString(const string& list, const char& p){
    int i = 0;
    while (i < list.size() && list[i] != p){
        i++;
    }
    return i < list.size();
}

bool perteneceVecString(const vector<string>& list, const string& p){
    int i = 0;
    while (i < list.size() && list[i] != p){
        i++;
    }
    return i < list.size();
}

bool igualesStrings(const string &A, const string &B){
    bool res = true;
    if(A.size() != B.size()){
        res = false;
    } else {
        for (int i = 0; i < A.size(); ++i) {
            res &= (perteneceString(B, A[i]) && perteneceString(A, B[i]));
        }
    }
    return res;
}

bool igualesVecStrings(const vector<string> &A, const vector<string> &B){
    bool res = true;
    if(A.size() != B.size()){
        res = false;
    } else {
        for (int i = 0; i < A.size(); ++i) {
            res &= (perteneceVecString(B, A[i]) && perteneceVecString(A, B[i]));
        }
    }
    return res;
}

bool perteneceInt(const vector<int>& list, const int& x){
    int i = 0;
    while (i < list.size() && list[i] != x){
        i++;
    }
    return i < list.size();
}

vector<vector<string>> quitarRepetidos(const vector<vector<string>> &A){
    vector<vector<string>> res;
    vector<int> posRedun;
    for (int i = 0; i < A.size(); ++i) {
        for (int j = i+1; j < A.size(); ++j) {
            if(igualesVecStrings(A[i], A[j])){
                posRedun.push_back(j);
            }
        }
    }
    for (int i = 0; i < A.size(); ++i) {
        if(!perteneceInt(posRedun, i)){
            res.push_back(A[i]);
        }
    }
    return res;
}


// Mismo orden relativo de conjunto de anagramas y dentro de cada vector y con repetidos
vector<vector<string> > agruparAnagramas(vector<string> v){
    vector<vector<string> > res;
    vector<string> temp;
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v.size(); ++j) {
            if(igualesStrings(v[i], v[j])){
                temp.push_back(v[j]);
            }
        }
        res.push_back(temp);
        temp.clear();
    }

    res = quitarRepetidos(res);
    return res;
}

bool esPalindromo(string s){
    bool cumple = true;
    for (int i = 0; i < s.size(); ++i) {
        cumple &= s[i] == s[s.size()-1-i];
    }
    return cumple;
}

int contApariciones(string s, char c){
    int res = 0;
    for (int i = 0; i < s.size(); ++i) {
        if(s[i] == c){
            res++;
        }
    }
    return res;
}

bool tieneRepetidos(string s){
    bool distinto = false;
    for (int i = 0; i < s.size(); ++i) {
        distinto |= (contApariciones(s, s[i]) > 1);
    }
    return distinto;
}

string rotar(string s, int j){
    string res;
    if(s == ""){
        res = "";
    } else {
        int pos = (j % s.size());
        res = s;
        string temp;
        for (int i = 0; i < j; ++i) {
            temp.push_back(res[s.size()-1]);
            res.pop_back();
            temp += res;
            res = temp;
            temp.clear();
        }
    }

    return res;
}

// no se puede usar substring

string darVueltaK(string s, int k){
    string res;

    //una paja

    return res;
}

string abueloLaino(string s){
    string res;
    return res;
}

int cantidadDeFelicitaciones(vector<string> v){
    int res;
    return res;
}

int middleOut(string s, string t){

    return 0;
}