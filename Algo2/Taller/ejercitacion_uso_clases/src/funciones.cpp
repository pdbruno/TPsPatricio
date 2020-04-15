#include <vector>
#include "algobot.h"

using namespace std;

bool contiene(vector<int> s, int x, int i = 0) {
    if (i<0 || i >= s.size()){
        return false;
    }

    while (i < s.size() && s[i]!= x) {
        ++i;
    }

    return i < s.size();
}

// Ejercicio 1
vector<int> quitar_repetidos(vector<int> s) {
    vector<int> res;
    for (int i = 0; i < s.size(); ++i) {
        if(!contiene(s, s[i], i+1)){
            res.push_back(s[i]);
        }
    }
    return res;
}

// Ejercicio 2
vector<int> quitar_repetidos_v2(vector<int> s) {
    set<int> presentes;
    vector<int> res;

    for (int n : s) {
        presentes.insert(n);
    }
    for (int n : presentes) {
        res.push_back(n);
    }
    return res;
}

// Ejercicio 3
bool mismos_elementos(vector<int> a, vector<int> b) {
    bool res = true;
    for (int n : a) {
        res &= contiene(b, n);
    }
    for (int n : b) {
        res &= contiene(a, n);
    }

    return res;
}

// Ejercicio 4
bool mismos_elementos_v2(vector<int> a, vector<int> b) {
    set<int> setA;
    set<int> setB;
    for (int n : a) {
        setA.insert(n);
    }
    for (int n : b) {
        setB.insert(n);
    }

    return setA == setB;
}

// Ejercicio 5
map<int, int> contar_apariciones(vector<int> s) {
    map<int, int> res;
    for (int n : s) {
        if(res.count(n) == 0){
            res[n] = 1;
        } else {
            res[n]++;
        }
    }
    return res;
}

// Ejercicio 6
vector<int> filtrar_repetidos(vector<int> s) {
    map<int, int> apar = contar_apariciones(s);
    vector<int> res;
    for (pair<int, int> p : apar) {
        if (p.second == 1){
            res.push_back(p.first);
        }
    }
    return res;
}

// Ejercicio 7
template<class T>
set<T> interseccion(set<T> a, set<T> b) {
    set<T> res;
    for (T n : a) {
        if(b.count(n) == 1){
            res.insert(n);
        }
    }
    return res;
}

// Ejercicio 8
map<int, set<int>> agrupar_por_unidades(vector<int> s) {
    map<int, set<int>> res;
    for (int n : s) {
        int rem = n % 10;
        if(res.count(rem) == 0){
            set<int> s = {n};
            res[rem] = s;
        } else {
            res[rem].insert(n);
        }
    }
    return res;
}

// Ejercicio 9
vector<char> traducir(vector<pair<char, char>> tr, vector<char> str) {
    vector<char> res;
    map<char, char> dic;

    for (pair<char, char> p : tr) {
        dic[p.first] = p.second;
    }

    for (char n : str) {
        if(dic.count(n) == 0){
            res.push_back(n);
        } else {
            res.push_back(dic[n]);
        }
    }
    return res;
}

// Ejercicio 10
bool integrantes_repetidos(vector<Mail> s) {
    bool res = true;
    for (int i = 0; i < s.size(); ++i) {
        for (int j = i + 1; j < s.size(); ++j) {
            bool sonIguales = s[i].libretas() == s[j].libretas();
            bool sinInterseccion = interseccion(s[i].libretas(), s[j].libretas()).empty();
            res &= sonIguales || sinInterseccion;
        }
    }
    return !res;
}

// Ejercicio 11
map<set<LU>, Mail> entregas_finales(vector<Mail> s) {
    map<set<LU>, Mail> res;
    for(Mail m: s){
        if (m.adjunto()){
            res[m.libretas()] = m;
        }
    }
  return res;
}
