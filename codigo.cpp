#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // Para system("cls") y system("pause")

using namespace std;

// CLASE 1: Representa un producto individual
class Producto {
private:
    int id;
    string nombre;
    float precio;
    int cantidad;

public:
    Producto(int i, string n, float p, int c) {
        id = i;
        nombre = n;
        precio = p;
        cantidad = c;
    }

    int getId() { return id; }
    string getNombre() { return nombre; }

    // Metodo para obtener la cantidad actual
    int getCantidad() { return cantidad; }

    // Metodo para actualizar la cantidad
    void setCantidad(int nuevaCantidad) {
        cantidad = nuevaCantidad;
    }

    void mostrarInfo() {
        cout << "ID: " << id
            << " | Producto: " << nombre
            << " | Precio: $" << precio
            << " | Stock: " << cantidad << endl;
    }
};

// CLASE 2: Representa el almacen
class Almacen {
private:
    vector<Producto> inventario;
    int contadorId;

public:
    Almacen() {
        contadorId = 1;
    }

    void agregarProducto() {
        string nombre;
        float precio;
        int cantidad;

        cout << "\n--- NUEVO PRODUCTO ---" << endl;
        cout << "Nombre (sin espacios): ";
        cin >> nombre;
        cout << "Precio: ";
        cin >> precio;
        cout << "Cantidad: ";
        cin >> cantidad;

        Producto nuevo(contadorId, nombre, precio, cantidad);
        inventario.push_back(nuevo);

        cout << ">> Producto guardado con ID: " << contadorId << endl;
        contadorId++;
    }

    void mostrarTodo() {
        cout << "\n--- INVENTARIO ACTUAL ---" << endl;
        if (inventario.empty()) {
            cout << "El almacen esta vacio." << endl;
        }
        else {
            for (int i = 0; i < inventario.size(); i++) {
                inventario[i].mostrarInfo();
            }
        }
    }

    // Funcion MODIFICADA para eliminar por cantidad
    void eliminarProducto() {
        // 1. Mostrar productos primero
        mostrarTodo();

        if (inventario.empty()) {
            return; // Si esta vacio, nos salimos
        }

        int idBusqueda;
        cout << "\nIngresa el ID del producto a modificar/eliminar: ";
        cin >> idBusqueda;

        bool encontrado = false;

        for (int i = 0; i < inventario.size(); i++) {
            // Buscamos el ID
            if (inventario[i].getId() == idBusqueda) {
                encontrado = true;
                int stockActual = inventario[i].getCantidad();
                int cantidadEliminar;

                cout << "Producto seleccionado: " << inventario[i].getNombre() << endl;
                cout << "Stock actual: " << stockActual << endl;
                cout << "Cuantos deseas eliminar? (Escribe el numero): ";
                cin >> cantidadEliminar;

                if (cantidadEliminar >= stockActual) {
                    // Si borras todo o mas de lo que hay, se elimina el registro completo
                    inventario.erase(inventario.begin() + i);
                    cout << ">> Se ha eliminado el producto del inventario por completo." << endl;
                }
                else {
                    // Si solo borras algunos, actualizamos la cantidad
                    int nuevaCantidad = stockActual - cantidadEliminar;
                    inventario[i].setCantidad(nuevaCantidad);
                    cout << ">> Stock actualizado. Ahora quedan: " << nuevaCantidad << " unidades." << endl;
                }
                break; // Terminamos el ciclo
            }
        }

        if (!encontrado) {
            cout << ">> Error: ID no encontrado." << endl;
        }
    }
};

// MENU PRINCIPAL
int main() {
    Almacen miTienda;
    int opcion = 0;

    while (opcion != 4) {
        system("cls");

        cout << "=== ABARROTES SYSTEM ===" << endl;
        cout << "1. Agregar Producto" << endl;
        cout << "2. Ver Inventario" << endl;
        cout << "3. Eliminar Producto / Reducir Stock" << endl;
        cout << "4. Salir" << endl;
        cout << "-----------------------" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            miTienda.agregarProducto();
            break;
        case 2:
            miTienda.mostrarTodo();
            break;
        case 3:
            miTienda.eliminarProducto();
            break;
        case 4:
            cout << "Cerrando sistema..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }

        if (opcion != 4) {
            cout << "\nPresiona Enter para continuar...";
            system("pause > 0");
        }
    }

    return 0;
}