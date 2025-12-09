#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>
#include <iostream>
#include <iomanip>
#include "Utils.h" 

using namespace std;

class Producto {
private:
    string nombre;
    float precio;
    int cantidad;

public:
    Producto(string _nombre, float _precio, int _cantidad);

    // Getters
    string getNombre() const;
    float getPrecio() const;
    int getCantidad() const;

    // Setters (NUEVOS: Para editar)
    void setPrecio(float nuevoPrecio);
    void setCantidad(int nuevaCantidad);

    void mostrarInformacion() const;
};

#endif