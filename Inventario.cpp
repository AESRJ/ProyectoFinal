#include "Inventario.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

using namespace std;

// --- MÉTODO PRIVADO ---
int Inventario::buscarIndiceProducto(string nombreBusqueda) {
    for (size_t i = 0; i < listaProductos.size(); i++) {
        if (listaProductos[i].getNombre() == nombreBusqueda) {
            return i;
        }
    }
    return -1;
}

// --- MÉTODOS PÚBLICOS ---

void Inventario::agregarProducto() {
    Utils::limpiarPantalla();
    Utils::dibujarEncabezado("REGISTRAR NUEVO PRODUCTO");

    string nom;
    cout << "Ingrese nombre del producto: ";
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, nom);

    if (buscarIndiceProducto(nom) != -1) {
        cout << COLOR_RED << "\n[!] Error: Ya existe un producto con ese nombre." << COLOR_RESET << endl;
        Utils::pausar();
        return;
    }

    float pre = Utils::leerFloat("Ingrese precio unitario: $");
    int cant = Utils::leerInt("Ingrese cantidad inicial: ");

    Producto nuevoProducto(nom, pre, cant);
    listaProductos.push_back(nuevoProducto);

    cout << COLOR_GREEN << "\n[OK] Producto registrado exitosamente." << COLOR_RESET << endl;
    Utils::pausar();
}

void Inventario::mostrarInventario() {
    Utils::limpiarPantalla();
    Utils::dibujarEncabezado("REPORTE DE INVENTARIO GENERAL");

    if (listaProductos.empty()) {
        cout << COLOR_YELLOW << "[!] El inventario esta vacio." << COLOR_RESET << endl;
        Utils::pausar();
        return;
    }

    cout << "----------------------------------------------------" << endl;
    cout << "| " << left << setw(20) << "NOMBRE"
        << "| " << right << setw(11) << "PRECIO"
        << " | " << right << setw(11) << "CANTIDAD" << " |" << endl;
    cout << "----------------------------------------------------" << endl;

    for (const auto& prod : listaProductos) {
        prod.mostrarInformacion();
    }
    cout << "----------------------------------------------------" << endl;
    cout << "Total de items registrados: " << listaProductos.size() << endl;
    Utils::pausar();
}

void Inventario::buscarProducto() {
    Utils::limpiarPantalla();
    Utils::dibujarEncabezado("BUSQUEDA DE PRODUCTOS");

    if (listaProductos.empty()) {
        cout << COLOR_YELLOW << "[!] No hay productos para buscar." << COLOR_RESET << endl;
        Utils::pausar();
        return;
    }

    // Lista rápida para ayuda visual
    cout << COLOR_CYAN << "Productos disponibles:" << COLOR_RESET << endl;
    for (const auto& prod : listaProductos) {
        cout << " -> " << prod.getNombre() << endl;
    }
    cout << "--------------------------------" << endl;

    string nom;
    cout << "Ingrese el nombre a buscar (Exacto): ";
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, nom);

    int index = buscarIndiceProducto(nom);

    if (index != -1) {
        cout << "\n" << COLOR_GREEN << ">> Producto Encontrado:" << COLOR_RESET << endl;
        cout << "----------------------------------------------------" << endl;
        listaProductos[index].mostrarInformacion();
        cout << "----------------------------------------------------" << endl;
    }
    else {
        cout << COLOR_RED << "\n[X] Producto no encontrado." << COLOR_RESET << endl;
    }
    Utils::pausar();
}

void Inventario::editarProducto() {
    Utils::limpiarPantalla();
    Utils::dibujarEncabezado("MODIFICAR PRODUCTO");

    if (listaProductos.empty()) {
        cout << COLOR_YELLOW << "[!] No hay productos para editar." << COLOR_RESET << endl;
        Utils::pausar();
        return;
    }

    string nom;
    cout << "Nombre del producto a editar: ";
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, nom);

    int index = buscarIndiceProducto(nom);

    if (index != -1) {
        cout << "\nDatos actuales:" << endl;
        listaProductos[index].mostrarInformacion();

        cout << "\n1. Modificar Precio" << endl;
        cout << "2. Modificar Cantidad" << endl;
        cout << "3. Cancelar" << endl;
        int op = Utils::leerInt("Elija opcion: ");

        if (op == 1) {
            float nuevoP = Utils::leerFloat("Nuevo precio: $");
            listaProductos[index].setPrecio(nuevoP);
            cout << COLOR_GREEN << "\n[OK] Precio actualizado." << COLOR_RESET << endl;
        }
        else if (op == 2) {
            int nuevaC = Utils::leerInt("Nueva cantidad: ");
            listaProductos[index].setCantidad(nuevaC);
            cout << COLOR_GREEN << "\n[OK] Cantidad actualizada." << COLOR_RESET << endl;
        }
        else {
            cout << "\n[!] Operacion cancelada." << endl;
        }
    }
    else {
        cout << COLOR_RED << "\n[X] Producto no existe." << COLOR_RESET << endl;
    }
    Utils::pausar();
}

void Inventario::eliminarProducto() {
    Utils::limpiarPantalla();
    Utils::dibujarEncabezado("ELIMINAR PRODUCTO");

    if (listaProductos.empty()) {
        cout << COLOR_YELLOW << "[!] No hay productos para eliminar." << COLOR_RESET << endl;
        Utils::pausar();
        return;
    }

    // Lista con Stock para asegurar qué borramos
    cout << "Lista actual de productos:" << endl;
    cout << "--------------------------------" << endl;
    for (const auto& prod : listaProductos) {
        cout << "| " << left << setw(20) << prod.getNombre()
            << "| Stock: " << prod.getCantidad() << endl;
    }
    cout << "--------------------------------" << endl;

    string nom;
    cout << "Escriba el nombre del producto a eliminar: ";
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, nom);

    int index = buscarIndiceProducto(nom);

    if (index != -1) {
        cout << COLOR_RED << "¿Seguro que desea eliminar '" << nom << "'? (1: Si / 0: No): " << COLOR_RESET;
        int confirm;
        cin >> confirm;

        if (confirm == 1) {
            listaProductos.erase(listaProductos.begin() + index);
            cout << COLOR_GREEN << "\n[OK] Producto eliminado permanentemente." << COLOR_RESET << endl;
        }
        else {
            cout << "\nOperacion cancelada." << endl;
        }
    }
    else {
        cout << COLOR_RED << "\n[X] No se puede eliminar: El nombre no coincide con la lista." << COLOR_RESET << endl;
    }
    Utils::pausar();
}

void Inventario::guardarInventario() {
    Utils::limpiarPantalla();
    Utils::dibujarEncabezado("GUARDANDO INVENTARIO...");

    ofstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        for (const auto& prod : listaProductos) {
            archivo << prod.getNombre() << "|"
                << prod.getPrecio() << "|"
                << prod.getCantidad() << endl;
        }
        archivo.close();
        cout << COLOR_GREEN << "\n[OK] Datos guardados correctamente en '" << nombreArchivo << "'." << COLOR_RESET << endl;
    }
    else {
        cout << COLOR_RED << "\n[Error] No se pudo abrir el archivo para guardar." << COLOR_RESET << endl;
    }
    Utils::pausar();
}

bool Inventario::cargarInventario() {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) return false;

    listaProductos.clear();
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string segmento;
        string nombre;
        float precio;
        int cantidad;

        if (getline(ss, nombre, '|')) {
            if (getline(ss, segmento, '|')) {
                try {
                    precio = stof(segmento);
                    if (getline(ss, segmento, '|')) {
                        cantidad = stoi(segmento);
                        Producto p(nombre, precio, cantidad);
                        listaProductos.push_back(p);
                    }
                }
                catch (...) { continue; }
            }
        }
    }
    archivo.close();
    return true;
}
