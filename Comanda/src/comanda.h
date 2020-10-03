/*
 * comanda.h
 *
 *  Created on: 22 sep. 2020
 *      Author: utnso
 */

#ifndef COMANDA_H_
#define COMANDA_H_

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

#include "comandaLib.h"

comanda_config* comanda_configuracion;
t_log* logger_comanda;
int socket_escucha;

#endif /* COMANDA_H_ */
