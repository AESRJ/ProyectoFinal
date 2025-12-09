#include <iostream>
#include "Inventario.h"
#include "Utils.h"

using namespace std;

// Función auxiliar para el menú de inicio
void menuInicio(Inventario& tienda) {
    Utils::limpiarPantalla();
    cout << COLOR_CYAN << "=== INICIANDO SISTEMA ===" << COLOR_RESET << endl;

    // Intenta cargar automáticamente sin preguntar
    if (tienda.cargarInventario()) {
        cout << COLOR_GREEN << ">> [AUTO] Archivo de respaldo encontrado." << endl;
        cout << ">> Inventario cargado exitosamente." << COLOR_RESET << endl;
    }
    else {
        cout << COLOR_YELLOW << ">> [INFO] No se encontro archivo previo." << endl;
        cout << ">> Iniciando sistema con inventario vacio." << COLOR_RESET << endl;
    }

    // Pequeña pausa para que el usuario pueda leer el estado de la carga
    Utils::pausar();
}

int main() {
    Inventario miTienda;

    // 1. Preguntar si cargar o crear nuevo al iniciar
    menuInicio(miTienda);

    // 2. Ciclo normal del programa
    int opcion;
    do {
        Utils::limpiarPantalla();
        cout << COLOR_CYAN << " __  __            _        _   " << endl;
        cout << "|  \\/  | __ _ _ __| | _____| |_ " << endl;
        cout << "| |\\/| |/ _` | '__| |/ / _ \\ __|" << endl;
        cout << "| |  | | (_| | |  |   <  __/ |_ " << endl;
        cout << "|_|  |_|\\__,_|_|  |_|\\_\\___|\\__|" << COLOR_RESET << endl;
        cout << "     SISTEMA DE INVENTARIO V3.0   " << endl;
        cout << "\n===================================" << endl;
        cout << "1. " << COLOR_GREEN << "Registrar Producto" << COLOR_RESET << endl;
        cout << "2. Consultar Inventario" << endl;
        cout << "3. Buscar Producto" << endl;
        cout << "4. Modificar Existencias/Precio" << endl;
        cout << "5. " << COLOR_RED << "Eliminar Producto" << COLOR_RESET << endl;
        cout << "6. " << COLOR_YELLOW << "Guardar Inventario en Archivo" << COLOR_RESET << endl; // NUEVA OPCIÓN
        cout << "7. Salir" << endl;
        cout << "===================================" << endl;

        opcion = Utils::leerInt("Seleccione una opcion: ");

        switch (opcion) {
        case 1: miTienda.agregarProducto(); break;
        case 2: miTienda.mostrarInventario(); break;
        case 3: miTienda.buscarProducto(); break;
        case 4: miTienda.editarProducto(); break;
        case 5: miTienda.eliminarProducto(); break;
        case 6: miTienda.guardarInventario(); break; // Llamada a guardar
        case 7:
            // Opción de autoguardado al salir (Opcional, buena práctica)
            char guardar;
            cout << "¿Desea guardar antes de salir? (s/n): ";
            cin >> guardar;
            if (guardar == 's' || guardar == 'S') {
                miTienda.guardarInventario();
            }
            cout << "\nCerrando sistema... Hasta luego!" << endl;
            break;
        default:
            cout << COLOR_RED << "Opcion no valida." << COLOR_RESET << endl;
            Utils::pausar();
        }
    } while (opcion != 7);

    return 0;
}