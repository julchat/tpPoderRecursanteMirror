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

	pthread_create(&consultarPlatosThread, NULL, (void*) colaCliente, (void*) CONSULTAR_PLATOS);
	pthread_detach(consultarPlatosThread);

	pthread_create(&crearPedidoThread, NULL, (void*) colaCliente, (void*) CONSULTAR_PLATOS);
	pthread_detach(crearPedidoThread);

	pthread_create(&anadirPedidoThread, NULL, (void*) colaCliente, (void*) CONSULTAR_PLATOS);
	pthread_detach(anadirPedidoThread);

	pthread_create(&confirmarPedidoThread, NULL, (void*) colaCliente, (void*) CONSULTAR_PLATOS);
	pthread_detach(confirmarPedidoThread);

	pthread_create(&consultarPedidoThread, NULL, (void*) colaCliente, (void*) CONSULTAR_PLATOS);
	pthread_detach(consultarPedidoThread);

	colaServidor();
	return 0;
}

void* colaServidor() { //modo servidor, a la escucha de una o varias conexiones
	socketEscucha = iniciarServidor(puertoRestaurante);
	log_info(loggerRestaurante, "SERVIDOR LEVANTADO! ESCUCHANDO EN %i", puertoRestaurante);
	struct sockaddr restauranteCliente;
		socklen_t len = sizeof(restauranteCliente);
		do {
			int socketRestaurante = accept(socketEscucha, &restauranteCliente, &len);
			if (socketRestaurante > 0) {
				log_info(loggerRestaurante, "NUEVA CONEXIÓN!");
				pthread_t restauranteThread;
				pthread_create(&restauranteThread, NULL, (void*) manejarSuscripciones, (void*) (socketRestaurante));
				pthread_detach(restauranteThread);
			} else {
				log_error(loggerRestaurante, "ERROR ACEPTANDO CONEXIONES: %s", strerror(errno));
			}
		} while (1);
}

void* colaCliente(void* cola) {//se conecta al modulo App
	uint32_t colaSuscriptor = (uint32_t) cola;
	while(1){
		int socketRestaurante = conexionServidor(ipRestaurante, puertoRestaurante, NULL);
		if(socketRestaurante != -errno){
			log_info(loggerRestaurante, "CONEXION EXITOSA CON EL RESTAURANTE");
			t_message mensaje;
			suscripcion content;
			content.idSuscriptor= getpid();
			content.idColaSindicato = colaSuscriptor;

			int bytes_escritos = 0;
			mensaje.content = malloc(sizeof(suscripcion));
			memcpy(mensaje.content+bytes_escritos, &content.idColaSindicato, sizeof(t_header));
			bytes_escritos += sizeof (uint32_t);
			memcpy(mensaje.content+bytes_escritos, &content.idSuscriptor, sizeof(pid_t));

			mensaje.head = SUSCRIPCION;
			mensaje.size = sizeof(suscripcion);
			enviarMensaje(socketRestaurante, mensaje.head,mensaje.content, mensaje.size);
			free(mensaje.content);
			manejarSuscripciones((void*) socketRestaurante);
		}
		sleep(10);
	}
	return NULL;
}

void* manejarSuscripciones() {
	int socketEnvio = (int) (socket);
	bool executing = true;

	while(executing){
		t_message* message = recibirMensaje(socketEnvio);
		switch(message->head){
			case CONSULTAR_PLATOS:{
				break;
			}

			case GUARDAR_PEDIDO:{
				break;
			}

			case GUARDAR_PLATO:{
				break;
			}

			case CONFIRMAR_PEDIDO:{
				break;
			}

			case OBTENER_PEDIDO:{
				break;
			}

			case OBTENER_RESTAURANTE:{
				break;
			}

			case PLATO_LISTO:{
				break;
			}

			case TERMINAR_PEDIDO:{
				break;
			}

			case OBTENER_RECETA:{
				break;
			}

			default:
				break;
		}
	}
	return NULL;
}


