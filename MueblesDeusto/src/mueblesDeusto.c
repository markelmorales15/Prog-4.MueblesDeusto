#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cliente.h"
#include "menus.h"
#include "producto.h"

int main(void) {

	int opcion, opcion2, opcion3;
	int i, clienteExiste = 0, adminExiste=0;
	//, pos = 0, enc = 0�
	//esto mas adelante harbria que meterlo en el txt para lectura de ficheros
//	Cliente c1 = { "111A", "A", "111" };
//	Cliente c2 = { "222B", "B", "222" };
//	Cliente c3 = { "333C", "C", "333" };
//	Cliente c4 = { "444D", "D", "444" };
	ListaClientes lc;
	ListaClientes admin;
	lc.numC = 0;
	ListaProductos lp;
	lp.numProductos = 0;
//	printf("Lista de clientes vacía: \n");
//	fflush(stdout);
//	imprimirListaClientes(lc);
	volcarFicheroAListaClientes(&lc, "Clientes.txt");
	volcarFicheroAListaClientes(&admin, "Administradores.txt");
//	imprimirListaClientes(admin);
//	printf("Lista de clientes con los del fichero: \n");
//	fflush(stdout);
//	imprimirListaClientes(lc);
//
//
//	printf("LISTA DE PRODUCTOS VACÍA: \n");
//	fflush(stdout);
//	imprimirListaProductos(lp);
//	volcarFicheroAListaProductos(&lp, "Productos.txt");
//	printf("LISTA DE PRODUCTOS CON LOS DEL FICHERO: \n");
//	fflush(stdout);
//	imprimirListaProductos(lp);

//	lc.numC = 4;
//	lc.aClientes = malloc(sizeof(Cliente) * 4);
//	lc.aClientes[0] = c1;
//	lc.aClientes[1] = c2;
//	lc.aClientes[2] = c3;
//	lc.aClientes[3] = c4;
	//Escribir admins en un fichero y volcarlos. Volcar del array al fichero los clientes. y al revés.
	Cliente nuevoCliente;
	Cliente inicio;
	do {
		//Abrimos el menú de inicio
		opcion = menuInicio();
		switch (opcion) {
		case 1:	//Registrase
			nuevoCliente = registro();//Si el usuario no existe ya en la lista de clientes
			//Comprobamos si el usuario ya está registrado o no
			for (i = 0; i < lc.numC; i++) {
				if (strcmp(nuevoCliente.dni, lc.aClientes[i].dni) == 0) {//Compramos el dni del cliente nuevo con el resto de nuestros clientes
					clienteExiste = 1;
					break;
				}
			}
			//Si el cliente ya está registrado (ya existe en la lista de clientes):
			if (clienteExiste) {
				printf("\nEl cliente ya existe en la lista. \n");
				fflush(stdout);
				//Si el cliente no existe en la lista:
			} else {
				printf("\nBienvenido a MueblesDeusto. \n");
				//Añadimos el cliente a la lista
				anadirClientesALista(&lc, nuevoCliente);
				volcarListaClientesAFichero(&lc, "Clientes.txt");
				fflush(stdout);
				//Llamamos al menú cliente:
				opcion2 = menuCliente();
			}
			//Si el registro es correcto:
			switch (opcion2) {
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 0:	//Salir
				printf("\nAgur! \n\n");
				fflush(stdout);
				break;
			}
			break;
		case 2:	//Iniciar sesión
				//Tenemos que recorrer las dos listas: admin y clientes
				//Si el admin ya se conoce, se abre el menú de admin y si no el de cliente
			inicio = inicioSesion();
			//Comprobamos si el usuario ya está registrado o no
			for (i = 0; i < lc.numC; i++) {
				if (strcmp(nuevoCliente.dni, lc.aClientes[i].dni) == 0) {//Compramos el dni del cliente nuevo con el resto de nuestros clientes
					clienteExiste = 1;
					break;
				} else if(strcmp(nuevoCliente.dni, admin.aClientes[i].dni) == 0){
					adminExiste = 1;
				}
			}
			if (clienteExiste) {
				printf("\n¡Bienvenido a MueblesDeusto! \n");
				fflush(stdout);
				opcion3 = menuCliente();
				//Si el cliente no existe en la lista:
			} else if(adminExiste){
				printf("\n¡Bienvenido a MueblesDeusto! \n");
				fflush(stdout);
				opcion3 = menuAdmin();
			} else {
				printf("\nAntes debe registrarse \n");
				fflush(stdout);
			}

			switch (opcion3) {
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 0:
				break;
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
	return 0;

}
