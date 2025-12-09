#include "Inventario.h"
#include "Utils.h"
#include <algorithm> // Para transformar texto a minusculas si quisieras mejorar busqueda

// --- METODOS AUXILIARES ---
int Inventario::buscarIndiceProducto(string nombreBusqueda) {
    for (size_t i = 0; i < listaProductos.size(); i++) {
        if (listaProductos[i].getNombre() == nombreBusqueda) {
            return i; // Retorna la posición si lo encuentra
        }
    }
    return -1; // Retorna -1 si no existe
}

// --- METODOS PUBLICOS ---

void Inventario::agregarProducto() {
    Utils::limpiarPantalla();
    Utils::dibujarEncabezado("REGISTRAR NUEVO PRODUCTO");

    string nom;
    cout << "Ingrese nombre del producto: ";
    cin.ignore();
    getline(cin, nom);

    // Validación básica para no repetir nombres
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

    string nom;
    cout << "Ingrese el nombre a buscar: ";
    cin.ignore();
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

void Inventario::eliminarProducto() {
    Utils::limpiarPantalla();
    Utils::dibujarEncabezado("ELIMINAR PRODUCTO");

    string nom;
    cout << "Nombre del producto a eliminar: ";
    cin.ignore();
    getline(cin, nom);

    int index = buscarIndiceProducto(nom);

    if (index != -1) {
        // Borrado del vector: es un poco tecnico, usa iteradores
        listaProductos.erase(listaProductos.begin() + index);
        cout << COLOR_GREEN << "\n[OK] Producto eliminado del sistema." << COLOR_RESET << endl;
    }
    else {
        cout << COLOR_RED << "\n[X] No se puede eliminar: Producto no existe." << COLOR_RESET << endl;
    }
    Utils::pausar();
}

void Inventario::editarProducto() {
    Utils::limpiarPantalla();
    Utils::dibujarEncabezado("MODIFICAR PRODUCTO");

    string nom;
    cout << "Nombre del producto a editar: ";
    cin.ignore();
    getline(cin, nom);

    int index = buscarIndiceProducto(nom);

    if (index != -1) {
        cout << "\nDatos actuales:" << endl;
        listaProductos[index].mostrarInformacion();

        cout << "\n1. Modificar Precio" << endl;
        cout << "2. Modificar Cantidad" << endl;
        int op = Utils::leerInt("Elija opcion: ");

        if (op == 1) {
            float nuevoP = Utils::leerFloat("Nuevo precio: $");
            listaProductos[index].setPrecio(nuevoP);
        }
        else if (op == 2) {
            int nuevaC = Utils::leerInt("Nueva cantidad: ");
            listaProductos[index].setCantidad(nuevaC);
        }
        cout << COLOR_GREEN << "\n[OK] Actualizacion completada." << COLOR_RESET << endl;
    }
    else {
        cout << COLOR_RED << "\n[X] Producto no existe." << COLOR_RESET << endl;
    }
    Utils::pausar();
}