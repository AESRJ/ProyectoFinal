#include <iostream>
#include "Inventario.h"
#include "Utils.h"

using namespace std;

int main() {
    Inventario miTienda;
    int opcion;

    do {
        Utils::limpiarPantalla();
        cout << COLOR_CYAN << " __  __            _        _   " << endl;
        cout << "|  \\/  | __ _ _ __| | _____| |_ " << endl;
        cout << "| |\\/| |/ _` | '__| |/ / _ \\ __|" << endl;
        cout << "| |  | | (_| | |  |   <  __/ |_ " << endl;
        cout << "|_|  |_|\\__,_|_|  |_|\\_\\___|\\__|" << COLOR_RESET << endl;
        cout << "     SISTEMA DE INVENTARIO V2.0   " << endl;
        cout << "\n===================================" << endl;
        cout << "1. " << COLOR_GREEN << "Registrar Producto" << COLOR_RESET << endl;
        cout << "2. Consultar Inventario" << endl;
        cout << "3. Buscar Producto" << endl;
        cout << "4. Modificar Existencias/Precio" << endl;
        cout << "5. " << COLOR_RED << "Eliminar Producto" << COLOR_RESET << endl;
        cout << "6. Salir" << endl;
        cout << "===================================" << endl;

        opcion = Utils::leerInt("Seleccione una opcion: ");

        switch (opcion) {
        case 1: miTienda.agregarProducto(); break;
        case 2: miTienda.mostrarInventario(); break;
        case 3: miTienda.buscarProducto(); break;
        case 4: miTienda.editarProducto(); break;
        case 5: miTienda.eliminarProducto(); break;
        case 6: cout << "\nCerrando sistema... Hasta luego!" << endl; break;
        default:
            cout << COLOR_RED << "Opcion no valida." << COLOR_RESET << endl;
            Utils::pausar();
        }
    } while (opcion != 6);

    return 0;
}