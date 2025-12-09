#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <limits> // Para numeric_limits

using namespace std;


#define COLOR_RESET   "\033[0m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_RED     "\033[31m"
#define COLOR_YELLOW  "\033[33m"
#define BOLD          "\033[1m"

class Utils {
public:
    static void limpiarPantalla() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    static void dibujarEncabezado(string titulo) {
        cout << COLOR_CYAN << "====================================================" << COLOR_RESET << endl;
        cout << "   " << BOLD << titulo << COLOR_RESET << endl;
        cout << COLOR_CYAN << "====================================================" << COLOR_RESET << endl;
    }

    static void pausar() {
        cout << "\nPresione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    // Validación de entrada para evitar crashes
    static float leerFloat(string mensaje) {
        float valor;
        while (true) {
            cout << mensaje;
            if (cin >> valor) {
                break;
            }
            else {
                cout << COLOR_RED << ">> Entrada invalida. Ingrese un numero." << COLOR_RESET << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        return valor;
    }

    static int leerInt(string mensaje) {
        int valor;
        while (true) {
            cout << mensaje;
            if (cin >> valor) {
                break;
            }
            else {
                cout << COLOR_RED << ">> Entrada invalida. Ingrese un numero entero." << COLOR_RESET << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        return valor;
    }
};

#endif
