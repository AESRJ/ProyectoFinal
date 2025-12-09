#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <vector>
#include <fstream> 
#include <sstream> 
#include "Producto.h"

class Inventario {
private:
    vector<Producto> listaProductos;
    string nombreArchivo = "inventario.txt"; // Nombre del archivo por defecto

    int buscarIndiceProducto(string nombreBusqueda);

public:
    void agregarProducto();
    void mostrarInventario();
    void buscarProducto();
    void editarProducto();
    void eliminarProducto();
    
    
    void guardarInventario();
    bool cargarInventario(); // Retorna true si cargó con éxito
};

#endif