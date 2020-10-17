/*
 * app.c
 *
 *  Created on: 20 sep. 2020
 *      Author: utnso
 */

#include "app.h"

int main(int argc, char *argv[]) {

	appConfiguracion = leerConfigApp(argv[1]);
	//loggerApp = loggerApp(appConfiguracion->ARCHIVO_LOG);

	pthread_t consultarRestaurantes;
	pthread_t seleccionarRestaurante;
	pthread_t consultarPlatos;
	pthread_t crearPedido;
	pthread_t anadirPlato;
	pthread_t platoListo;
	pthread_t confirmarPedido;
	pthread_t consultarPedido;

	pthread_create(&consultarRestaurantes, NULL, (void*) conexionAlModuloComanda, (void*) CONSULTAR_RESTAURANTES);
	pthread_detach(consultarRestaurantes);

	pthread_create(&seleccionarRestaurante, NULL, (void*) conexionAlModuloComanda, (void*) SELECCIONAR_RESTAURANTES);
	pthread_detach(seleccionarRestaurante);

	pthread_create(&consultarPlatos, NULL, (void*) conexionAlModuloComanda, (void*) CONSULTAR_PLATOS);
	pthread_detach(consultarPlatos);

	pthread_create(&crearPedido, NULL, (void*) conexionAlModuloComanda, (void*) CREAR_PEDIDO);
	pthread_detach(crearPedido);

	pthread_create(&anadirPlato, NULL, (void*) conexionAlModuloComanda, (void*) ANIADIR_PLATO);
	pthread_detach(anadirPlato);

	pthread_create(&platoListo, NULL, (void*) conexionAlModuloComanda, (void*) PLATO_LISTO);
	pthread_detach(platoListo);

	pthread_create(&confirmarPedido, NULL, (void*) conexionAlModuloComanda, (void*) CONFIRMAR_PEDIDO);
	pthread_detach(confirmarPedido);

	pthread_create(&consultarPedido, NULL, (void*) conexionAlModuloComanda, (void*) CONSULTAR_PEDIDO);
	pthread_detach(consultarPedido);


	//Luego socketEscucha para la conexion de modulo Restaurante
	colaServidor(appConfiguracion->PUERTO_ESCUCHA);

	//Obtener archivo de conf de los distintos repartidores con sus FRECUENCIAS y TIEMPOS DE DESCANSO.


	return 0;
}

void* conexionAlModuloComanda(void* cola) {
	//Primero se conecta al modulo COMANDA
	colaCliente(cola, appConfiguracion->IP_COMANDA, appConfiguracion->PUERTO_COMANDA);
}



