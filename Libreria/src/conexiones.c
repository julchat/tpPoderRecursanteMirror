/*
 * conexiones.c
 *
 *  Created on: 9 sep. 2020
 *      Author: utnso
 */
#include "conexiones.h"

int conexion_servidor(char* host, int port, void*(*callback)()){

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


int crear_socket(){
	return socket(AF_INET, SOCK_STREAM, 0);
}
