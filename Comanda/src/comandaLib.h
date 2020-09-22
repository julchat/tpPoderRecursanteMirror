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
	int TAMANO_SWAP;
	int FRECUENCIA_COMPACTACION;
	char* ALGORITMO_REEMPLAZO;
	char* ARCHIVO_LOG;

}comanda_config;

comanda_config* leer_config_comanda(char*);
t_log* crear_logger_comanda(char*);

#endif /* TP0_H_ */
