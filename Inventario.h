#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <vector>
#include "Producto.h"

class Inventario {
private:
    vector<Producto> listaProductos;

    // Método privado auxiliar para encontrar el índice de un producto
    int buscarIndiceProducto(string nombreBusqueda);

public:
    void agregarProducto();
    void mostrarInventario();
    void buscarProducto();    // NUEVO
    void editarProducto();    // NUEVO
    void eliminarProducto();  // NUEVO
};

#endif