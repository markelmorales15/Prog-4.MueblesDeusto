#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cliente.h"
#include "menus.h"
#include "producto.h"
#include "carrito.h"
#include "bbdd/consultas.h"

int main(void) {
	// Abrir la base de datos
	sqlite3 *db;

	Cliente nuevoCliente;
	Cliente inicio;

	ListaProductos productosBD;
	ListaProductos lp1;

	Producto nombreProducto;
	Producto codProd;
	Producto nuevoProducto;

	ListaClientes lc;
	lc.numC = 0;
	ListaClientes admin;

	int opcion = 10, opcion2 = 10, opcion3 = 10, opcion4 = 10;
	int i, clienteExiste = 0, adminExiste = 0, cat, nuevaCantidad = 0;
	int resultado = 0;
	char get[20] = "";
	char nombd[50];

	leerConfig("Configuracion.conf", nombd);
	int rc = sqlite3_open(nombd, &db);
	if (rc != SQLITE_OK) {
		printf("Error abriendo la base de datos: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_close(db);
		return 1;
	}

	//PRODUCTOS - BBDD
	volcarAListaProductosBD(db, &productosBD);

	//Productos - FICHERO
	volcarFicheroAListaProductos(&lp1, "Productos.txt");

	//CLIENTES
	volcarFicheroAListaClientes(&lc, "Clientes.txt");

	//ADMINISTRADORES
	volcarFicheroAListaClientes(&admin, "Administradores.txt");

	sqlite3_close(db);

	do {
		//Abrimos el menú de inicio
		opcion = menuInicio();
		switch (opcion) {
		case 1:
			nuevoCliente = registro();
			for (i = 0; i < lc.numC; i++) {
				if (strcmp(nuevoCliente.dni, lc.aClientes[i].dni) == 0) { //Compramos el dni del cliente nuevo con el resto de nuestros clientes
					clienteExiste = 1;
					break;
				}
			}

			if (clienteExiste) {
				printf("\nEl cliente ya existe en la lista. \n");
				fflush(stdout);
			} else {
				printf("\nUsuario registrado con exito. \n");
				fflush(stdout);
				anadirClientesALista(&lc, nuevoCliente);
				volcarListaClientesAFichero(&lc, "Clientes.txt");
				fflush(stdout);
			}
			break;
		case 2:
			inicio = inicioSesion();
			for (i = 0; i < lc.numC; i++) {
				if ((strcmp(inicio.usuario, lc.aClientes[i].usuario) == 0)
						&& (strcmp(inicio.contrasena,
								lc.aClientes[i].contrasena) == 0)) {
					clienteExiste = 1;
					break;
				}
			}
			if (clienteExiste) {
				printf("\n¡Bienvenido a MueblesDeusto! \n");
				fflush(stdout);
				strcpy(inicio.dni, buscarDniUsuario(lc, inicio.usuario));
				Carrito *carritocliente = malloc(sizeof(Carrito));
				carritocliente->aProductos = NULL;
				carritocliente->numProductos = 0;
				strcpy(carritocliente->dni, inicio.dni);
				carritocliente->importeTotal = 0;

				do {
					opcion2 = menuCliente();
					switch (opcion2) {
					case 1:
						opcion3 = mostrarCarrito(carritocliente);
						break;
					case 2:
						imprimirListaProductos(productosBD);
						codProd = nombreProductoDevolver();
						devolverProducto(&productosBD, codProd);
						imprimirListaProductos(productosBD);
						sqlite3_open(nombd, &db);
						devolverProductoBD(db, codProd);
						sqlite3_close(db);
						break;
					case 3:
						imprimirListaProductos(productosBD);
						break;
					case 4:
						cat = imprimirListaCategorias();
						sqlite3_open(nombd, &db);
						mostrarProductosCategoriaBD(db, cat);
						imprimirCarrito(*carritocliente);
						opcion4 = menuBuscar(carritocliente, productosBD);
						sqlite3_close(db);
						break;
					case 0:
						printf("\nAgur! \n\n");
						fflush(stdout);
						break;
					}

				} while (opcion2 != 0);
			} else {
				for (i = 0; i < admin.numC; i++) {
					if ((strcmp(inicio.usuario, admin.aClientes[i].usuario) == 0)
							&& (strcmp(inicio.contrasena,
									admin.aClientes[i].contrasena) == 0)) {
						adminExiste = 1;
						break;
					}
				}
				if (adminExiste) {
					printf("\n¡Bienvenido a MueblesDeusto! \n");
					fflush(stdout);
					do {
						opcion2 = menuAdmin();
						switch (opcion2) {
						case 1:
							sqlite3_open(nombd, &db);
							nuevoProducto = anadirProductoBD();
							insertarProductoBD(db, nuevoProducto);
							sqlite3_close(db);
							break;
						case 2:
							sqlite3_open(nombd, &db);
							mostrarProductosBD(db);
							sqlite3_close(db);
							printf(
									"\nEstás seguro de querer modificar un producto?(si: 1, no: 0): ");
							fflush(stdout);
							fflush(stdin);
							fgets(get, sizeof(get), stdin);
							sscanf(get, "%d", &resultado);
							if (resultado == 1) {
								nombreProducto = codigoProductoModificar();
								nuevaCantidad = nuevaCantidadProducto();
								sqlite3_open(nombd, &db);
								modificarCantidadProductoBD(db,
										nombreProducto.cod_p, nuevaCantidad);
								sqlite3_close(db);
								break;
							}

							break;
						case 3:
							sqlite3_open(nombd, &db);
							mostrarProductosBD(db);
							sqlite3_close(db);
							printf(
									"\nEstás seguro de querer eliminar un producto?(si: 1, no: 0): ");
							fflush(stdout);
							fflush(stdin);
							fgets(get, sizeof(get), stdin);
							sscanf(get, "%d", &resultado);
							if (resultado == 1) {
								nombreProducto = codigoProductoBorrar();
								sqlite3_open(nombd, &db);
								borrarProductoBD(db, nombreProducto.cod_p);
								sqlite3_close(db);
							}
							break;
						case 4:
							sqlite3_open(nombd, &db);
							mostrarProductosBD(db);
							sqlite3_close(db);
							break;
						case 5:
							sqlite3_open(nombd, &db);
							printf("\nProducto más caro de la tienda: \n");
							fflush(stdout);
							buscarProductoCaro(db);
							sqlite3_close(db);

							sqlite3_open(nombd, &db);
							printf(
									"\nEl número de productos en cada categoria es el siguiente: \n");
							fflush(stdout);
							numeroProductosCategoria(db);
							sqlite3_close(db);

							sqlite3_open(nombd, &db);
							printf(
									"\nEl producto con mayor cantidad en la tienda es el siguiente: \n");
							fflush(stdout);
							productoMayorCantidad(db);
							sqlite3_close(db);

							break;
						case 0:
							printf("\nAgur! \n\n");
							fflush(stdout);
							break;
						}

					} while (opcion2 != 0);

				} else {
					printf("\nAntes debe registrarse \n");
					fflush(stdout);
				}
			}
			break;
		case 0:
			printf("\nAgur! \n");
			fflush(stdout);
			break;
		default:
			printf("Error! \n");
			fflush(stdout);
			break;
		}
	} while (opcion != 0);

	liberarMemoria(&lc);
	liberarMemoria(&admin);

	return 0;
}
