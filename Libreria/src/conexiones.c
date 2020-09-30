/*
 * conexiones.c
 *
 *  Created on: 9 sep. 2020
 *      Author: utnso
 */
#include "conexiones.h"

int conexionServidor(char* host, int port, void*(*callback)()){

	int socket;
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(host);
	server_addr.sin_port = htons(port);

	socket = crearSocket();
	if(connect(socket,(struct sockaddr *)&server_addr, sizeof(server_addr))< 0){
			perror("ERROR AL CONECTAR SERVIDOR");
			return -errno;
		}
		if(callback != NULL)
			callback();
		return socket;
}

int iniciarServidor(int puerto){
	int  socket;
	int val = 1;
	struct sockaddr_in servaddr;

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr =INADDR_ANY;
	servaddr.sin_port = htons(puerto);

	socket = crearSocket();
	if (socket < 0) {
		char* error = strerror(errno);
		perror(error);
		free(error);
		return EXIT_FAILURE;
	}

	setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

	if (bind(socket,(struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
		return EXIT_FAILURE;
	}
	if (listen(socket, MAX_CLIENTS)< 0) {
		return EXIT_FAILURE;
	}

	return socket;

}

int crearSocket(){
	return socket(AF_INET, SOCK_STREAM, 0);
}

void* colaServidor(int puerto) { //modo servidor, a la escucha de una o varias conexiones
	socketEscucha = iniciarServidor(puerto);
	log_info(logger, "SERVIDOR LEVANTADO! ESCUCHANDO EN %i", puertoRestaurante);
	struct sockaddr cliente;
		socklen_t len = sizeof(cliente);
		do {
			int socketRestaurante = accept(socketEscucha, &cliente, &len);
			if (socketRestaurante > 0) {
				log_info(logger, "NUEVA CONEXIÓN!");
				pthread_t thread;
				pthread_create(&thread, NULL, (void*) manejarSuscripciones, (void*) (socketRestaurante));
				pthread_detach(thread);
			} else {
				log_error(logger, "ERROR ACEPTANDO CONEXIONES: %s", strerror(errno));
			}
		} while (1);
}

void* colaCliente(void* cola, char* ip, int puerto) {//te conectas a un modulo
	uint32_t colaSuscriptor = (uint32_t) cola;
	while(1){
		int socketCliente = conexionServidor(ip, puerto, NULL);
		if(socketCliente != -errno){
			log_info(logger, "CONEXION EXITOSA CON EL MODULO");
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
			enviarMensaje(socketCliente, mensaje.head,mensaje.content, mensaje.size);
			free(mensaje.content);
			manejarSuscripciones((void*) socketCliente);
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
			case CONSULTAR_RESTAURANTES:{
				break;
			}

			case ANIADIR_PLATO:{
				break;
			}

			case FINALIZAR_PEDIDO:{
				break;
			}

			case CONSULTAR_PEDIDO:{
				break;
			}

			case CREAR_PEDIDO:{
				break;
			}

			case SELECCIONAR_RESTAURANTES:{
				break;
			}

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

			case SUSCRIPCION:{
				break;
			}

			default:
				break;
		}
	}
	return NULL;
}

int crear_conexion(char *ip, char* puerto){
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	int socket_cliente = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	if(connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1)
		printf("error");

	freeaddrinfo(server_info);

	return socket_cliente;
}


