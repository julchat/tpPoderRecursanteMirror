#include "sindicato.h"

int main(void){

	iniciar_logger_config();

	pthread_t consultarPlatosThread;
	pthread_t guardarPedidoThread;
	pthread_t guardarPlatoThread;
	pthread_t confirmarPedidoThread;
	pthread_t obtenerPedidoThread;
	pthread_t obtenerRestauranteThread;
	pthread_t platoListoThread;
	pthread_t terminarPedidoThread;
	pthread_t obtenerRecetaThread;

	pthread_create(&consultarPlatosThread, NULL, (void*) colaCliente, (void*) CONSULTAR_PLATOS);
	pthread_detach(consultarPlatosThread);

	pthread_create(&guardarPedidoThread, NULL, (void*) colaCliente, (void*) CONSULTAR_PLATOS);
	pthread_detach(guardarPedidoThread);

	pthread_create(&guardarPlatoThread, NULL, (void*) colaCliente, (void*) CONSULTAR_PLATOS);
	pthread_detach(guardarPlatoThread);

	pthread_create(&confirmarPedidoThread, NULL, (void*) colaCliente, (void*) CONSULTAR_PLATOS);
	pthread_detach(confirmarPedidoThread);

	pthread_create(&obtenerPedidoThread, NULL, (void*) colaCliente, (void*) CONSULTAR_PLATOS);
	pthread_detach(obtenerPedidoThread);

	pthread_create(&obtenerRestauranteThread, NULL, (void*) colaCliente, (void*) CONSULTAR_PLATOS);
	pthread_detach(obtenerRestauranteThread);

	pthread_create(&platoListoThread, NULL, (void*) colaCliente, (void*) CONSULTAR_PLATOS);
	pthread_detach(platoListoThread);

	pthread_create(&terminarPedidoThread, NULL, (void*) colaCliente, (void*) CONSULTAR_PLATOS);
	pthread_detach(terminarPedidoThread);

	pthread_create(&obtenerRecetaThread, NULL, (void*) colaCliente, (void*) CONSULTAR_PLATOS);
	pthread_detach(obtenerRecetaThread);

	colaServidor();

	terminarPrograma();
	return EXIT_SUCCESS;

}

void* colaServidor() { //modo servidor, a la escucha de una o varias conexiones
	socketEscucha = iniciarServidor(puertoSindicato);
	log_info(loggerSindicato, "SERVIDOR LEVANTADO! ESCUCHANDO EN %i", puertoSindicato);
	struct sockaddr sindicatoCliente;
		socklen_t len = sizeof(sindicatoCliente);
		do {
			int socketSindicato = accept(socketEscucha, &sindicatoCliente, &len);
			if (socketSindicato > 0) {
				log_info(loggerSindicato, "NUEVA CONEXIÓN!");
				pthread_t sindicatoThread;
				pthread_create(&sindicatoThread, NULL, (void*) manejarSuscripciones, (void*) (socketSindicato));
				pthread_detach(sindicatoThread);
			} else {
				log_error(loggerSindicato, "ERROR ACEPTANDO CONEXIONES: %s", strerror(errno));
			}
		} while (1);
}

void* colaCliente(void* cola) {//se conecta al restaurante
	uint32_t colaSuscriptor = (uint32_t) cola;
	while(1){
		int socketSindicato = conexionServidor(ipRestaurante, puertoRestaurante, NULL);
		if(socketSindicato != -errno){
			log_info(loggerSindicato, "CONEXION EXITOSA CON EL RESTAURANTE");
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
			enviarMensaje(socketSindicato, mensaje.head,mensaje.content, mensaje.size);
			free(mensaje.content);
			manejarSuscripciones((void*) socketSindicato);
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

void terminarPrograma(){
	log_destroy(loggerSindicato);

}
