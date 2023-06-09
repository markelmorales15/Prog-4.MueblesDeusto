#include "cliente.h"
#include <stdio.h>
#include <string.h>
#include "menus.h"

int menuInicio() {
	char get[2] = "";
	int opcion = 0;
	printf("\nMENÚ INICIO: \n");
	printf("---------------------- \n");
	printf("1. Registrarse \n");
	printf("2. Iniciar sesion \n");
	printf("0. Salir \n");
	printf("Selecciona una opción: ");
	fflush(stdout);
	fflush(stdin);
	fgets(get, 2, stdin);
	sscanf(get, "%d", &opcion);
	return opcion;
}

int menuAdmin() {
	char get[2] = "";
	int opcion = 0;
	printf("\nMENÚ ADMIN: \n");
	printf("---------------------- \n");
	printf("1. Anadir un producto \n");
	printf("2. Modificar un producto \n");
	printf("3. Eliminar un producto \n");
	printf("4. Mostrar almacen \n");
	printf("5. Estadisticas \n");
	printf("0. Salir \n");
	printf("Selecciona una opción: ");
	fflush(stdout);
	fflush(stdin);
	fgets(get, 2, stdin);
	sscanf(get, "%d", &opcion);
	return opcion;
}
int menuCliente() {
	int opcion = 0;
	char get[2] = "";
	printf("\nMENÚ CLIENTE: \n");
	printf("---------------------- \n");
	printf("1. Visualizar el carrito de la compra \n");
	printf("2. Devolver un producto \n");
	printf("3. Visualizar los productos de la tienda \n");
	printf("4. Buscar un producto \n");
	printf("0. Salir \n");
	printf("Selecciona una opción: ");
	fflush(stdout);
	fflush(stdin);
	fgets(get, 2, stdin);
	sscanf(get, "%d", &opcion);
	return opcion;
}

Cliente inicioSesion() {
	char get[2] = "";
	Cliente c;
	printf("\nIntroduce el nombre de usuario: ");
	fflush(stdout);
	fflush(stdin);
	fgets(get, sizeof(c.usuario), stdin);
	sscanf(get, "%s", c.usuario);
	printf("Introduce la contrasenya: ");
	fflush(stdout);
	fflush(stdin);
	fgets(get, sizeof(c.contrasena), stdin);
	sscanf(get, "%s", c.contrasena);
	return c;
}

void leerConfig(char * nomfich, char *nombd){
	FILE *pf;

	pf = fopen(nomfich,"r");
	if(pf!=(FILE*)NULL){
		fscanf(pf,"%s",nombd);
		fclose(pf);
	}
}
