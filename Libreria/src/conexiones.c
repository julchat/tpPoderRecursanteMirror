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

	socket = crear_socket();
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
