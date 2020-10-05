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
#include <arpa/inet.h>

#include "commons/config.h"
#include "commons/log.h"

#include "clienteLib.h"
#include <serializacion.h>
#include <conexiones.h>

t_config* config;
t_log* logger;

typedef struct{
	t_header* operacion;
	t_dest* destinatario;
	t_list* parametros;
}mensajeListoYSeparado;

int connect_to_server(char* host,int port, void*(*callback)());
int create_socket();
void wait_connection(int socket_client);
int accept_client(int servidor);
void ejecutarConsola();
void procesarEntrada(mensajeListoYSeparado*);
void declararHiloYMeterloALaLista(t_list* hilosEnConsola, char* leido);
bool realizarHandshake();

#endif /* CLIENTE_H_ */
