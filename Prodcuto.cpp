#include "Producto.h"

Producto::Producto(string _nombre, float _precio, int _cantidad) {
    nombre = _nombre;
    precio = _precio;
    cantidad = _cantidad;
}

string Producto::getNombre() const { return nombre; }
float Producto::getPrecio() const { return precio; }
int Producto::getCantidad() const { return cantidad; }

// Implementación de Setters
void Producto::setPrecio(float nuevoPrecio) { precio = nuevoPrecio; }
void Producto::setCantidad(int nuevaCantidad) { cantidad = nuevaCantidad; }

void Producto::mostrarInformacion() const {
    // Formato tipo tabla con bordes
    cout << "| " << left << setw(20) << nombre
        << "| " << COLOR_GREEN << "$" << right << setw(10) << fixed << setprecision(2) << precio << COLOR_RESET
        << " | " << right << setw(8) << cantidad << " u. |" << endl;
}