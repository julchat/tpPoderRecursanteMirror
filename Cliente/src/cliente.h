/*
 * cliente.h
 *
 *  Created on: 6 sep. 2020
 *      Author: utnso
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

#include "commons/config.h"
#include "commons/log.h"

#include "clienteLib.c"

t_config* config;
t_log* logger;

int connect_to_server(char* host,int port, void*(*callback)());
int create_socket();
void wait_connection(int socket_client);
int accept_client(int servidor);
void ejecutarConsola();

typedef enum{
	APP = 0,
	RESTAURANTE = 1,
	SINDICATO = 2,
	COMANDA = 3
}t_dest;

typedef struct{
	t_header codOp;
	t_dest destinatario;
	t_param parametros;
}parserMensaje;

#endif /* CLIENTE_H_ */
