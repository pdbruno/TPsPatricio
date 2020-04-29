#include "gtest-1.8.1/gtest.h"
#include "../src/Libreta.h"
#include "../src/Truco.h"
#include <map>
#include <cmath>

using namespace std;

// Ejercicio 4
TEST(Aritmetica, suma) {
    int calculada = 5+55;
    int resultado = 60;
    EXPECT_EQ(calculada, resultado);
}

// Ejercicio 5
TEST(Aritmetica, potencia) {
    float calculada = pow(81, 0.5);
    float resultado = 9;
    EXPECT_EQ(calculada, resultado);
}
TEST(Aritmetica, potencia_general) {
    for (int i = -5; i <= 5; ++i) {
        if (i != 0) {
            EXPECT_EQ(pow(i, 2), i * i);
        }
    }
}

// Ejercicios 6..9
