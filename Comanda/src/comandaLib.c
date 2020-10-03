#include "comandaLib.h"

comanda_config* leer_config_comanda(char* path){


	t_config* config_aux = config_create(path);
	comanda_config* config_comanda_aux = malloc(sizeof(comanda_config));

	config_comanda_aux->PUERTO_ESCUCHA = config_get_int_value(config_aux,"PUERTO_ESCUCHA");
	config_comanda_aux->TAMANIO_MEMORIA = config_get_int_value(config_aux,"TAMANIO_MEMORIA");
	config_comanda_aux->TAMANIO_SWAP = config_get_int_value(config_aux,"TAMANIO_SWAP");
	config_comanda_aux->ALGORITMO_REEMPLAZO = config_get_string_value(config_aux,"ALGORITMO_REEMPLAZO");
	config_comanda_aux->ARCHIVO_LOG = config_get_string_value(config_aux,"ARCHIVO_LOG");

	return config_comanda_aux;
}


t_log* crear_logger_comanda(char* path){

	t_log* log_aux = log_create(path,"comanda",1,LOG_LEVEL_INFO);
	return log_aux;
}


void* esperar_conexion(int puerto){
	socket_escucha = iniciar_servidor(puerto);
		log_info(logger_comanda, "SERVIDOR LEVANTADO! ESCUCHANDO EN %i",comanda_configuracion->PUERTO_ESCUCHA);
		struct sockaddr cliente;
			socklen_t len = sizeof(cliente);
			do {
				int socket_comanda = accept(socket_escucha, &cliente, &len);
				if (socket_comanda > 0) {
					log_info(logger_comanda, "NUEVA CONEXIÓN!");
					pthread_t thread;
					pthread_create(&thread, NULL, (void*) manejarSuscripciones, (void*) (socketRestaurante));
					pthread_detach(thread);
				} else {
					log_error(logger_comanda, "ERROR ACEPTANDO CONEXIONES: %s", strerror(errno));
				}
			} while (1);


}


int iniciar_servidor(int puerto){
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
