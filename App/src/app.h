/*
 * app.h
 *
 *  Created on: 20 sep. 2020
 *      Author: utnso
 */

#ifndef APP_H_
#define APP_H_

#include "appLib.h"

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
#include <pthread.h>

#include "commons/config.h"
#include "commons/log.h"

#include "appLib.h"

typedef enum {
	FIFO,
	HRRN,
	SJF_SD
} t_planificadores;

app_config* appConfiguracion;
t_log* loggerApp;
int socketEscucha;


void* conexionAlModuloComanda(void* cola);

#endif /* APP_H_ */
