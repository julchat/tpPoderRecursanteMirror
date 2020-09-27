/*
 * conexiones.h
 *
 *  Created on: 9 sep. 2020
 *      Author: utnso
 */

#ifndef CONEXIONES_H_
#define CONEXIONES_H_

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
#include <commons/log.h>

#define MAX_CLIENTS 128

char* ipSindicato;
int puertoSindicato;

char* ipRestaurante;
int puertoRestaurante;

char* ipApp;
int puertoApp;

char* ipCliente;
int puertoCliente;

char* ipComanda;
int puertoComanda;

int socketEscucha;
//int socket;
t_log* logger;

int conexionServidor(char* host, int port, void*(*callback)());
int iniciarServidor(int puerto);
int crearSocket();
void* colaServidor(int puerto);
void* colaCliente(void* cola, char* ip, int puerto);
void* manejarSuscripciones();

#endif /* CONEXIONES_H_ */
