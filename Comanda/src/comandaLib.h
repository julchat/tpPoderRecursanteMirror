/*
 * comandaLib.h
 *
 *  Created on: 22 sep. 2020
 *      Author: utnso
 */

#ifndef TP0_H_
#define TP0_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include <commons/collections/list.h>

#include "utils.h"
#include "conexiones.h"
#include "mensajes.h"

typedef struct{

	int PUERTO_ESCUCHA;
	int TAMANIO_MEMORIA;
	int TAMANIO_SWAP;
	char* ALGORITMO_REEMPLAZO;
	char* ARCHIVO_LOG;

}comanda_config;

comanda_config* leer_config_comanda(char*);
t_log* crear_logger_comanda(char*);

void* esperar_conexion(int);
int iniciar_servidor(int);

#endif /* TP0_H_ */
