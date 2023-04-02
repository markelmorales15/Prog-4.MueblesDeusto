#ifndef BBDD_CONSULTAS_H_
#define BBDD_CONSULTAS_H_

#include "sqlite3.h"
#include "../carrito.h"
#include "../categoria.h"
#include "../cliente.h"
#include "../producto.h"

int abrirBD(sqlite3 **db);
int crearTablaProducto(char *nombreBaseDatos);
int insertarProductoBD(sqlite3 *db, Producto p);
int mostrarProductosBD(sqlite3* db);
int modificarCantidadProductoBD(sqlite3 *db, char *cod_p, int nueva_cantidad);
int borrarProductoBD(sqlite3 *db, char *cod_p);
int obtenerProductosBD(sqlite3* db, ListaProductos* productosBD);
int volcarListaProductosABD(sqlite3* db, ListaProductos* lista);

#endif
