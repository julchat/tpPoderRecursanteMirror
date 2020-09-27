/*
 * restaurante.c
 *
 *  Created on: 20 sep. 2020
 *      Author: utnso
 */

#include "restaurante.h"

int main (int argc, char*argv[]) {
	int size = strlen(argv[1]);
	char* pathConfig = malloc(size+1);
	strcpy(pathConfig,argv[1]);

	cargarConfiguraciones(pathConfig);
	iniciarLogger();
	free(pathConfig);

	pthread_t consultarPlatosThread;
	pthread_t crearPedidoThread;
	pthread_t anadirPedidoThread;
	pthread_t confirmarPedidoThread;
	pthread_t consultarPedidoThread;

	pthread_create(&consultarPlatosThread, NULL, (void*) conexionAlModulo, (void*) CONSULTAR_PLATOS);
	pthread_detach(consultarPlatosThread);

	pthread_create(&crearPedidoThread, NULL, (void*) conexionAlModulo, (void*) CONSULTAR_PLATOS);
	pthread_detach(crearPedidoThread);

	pthread_create(&anadirPedidoThread, NULL, (void*) conexionAlModulo, (void*) CONSULTAR_PLATOS);
	pthread_detach(anadirPedidoThread);

	pthread_create(&confirmarPedidoThread, NULL, (void*) conexionAlModulo, (void*) CONSULTAR_PLATOS);
	pthread_detach(confirmarPedidoThread);

	pthread_create(&consultarPedidoThread, NULL, (void*) conexionAlModulo, (void*) CONSULTAR_PLATOS);
	pthread_detach(consultarPedidoThread);

	modoServidor();
	return 0;
}

void* conexionAlModulo(void* cola){
	colaCliente(cola, ipApp, puertoApp);
}

void* modoServidor(){
	colaServidor(puertoRestaurante);
}

