/*
 * sindicatoLib.h
 *
 *  Created on: 6 sep. 2020
 *      Author: utnso
 */

#ifndef SINDICATOLIB_H_
#define SINDICATOLIB_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "mensajes.h"

typedef struct{

	int PUERTO_ESCUCHA;
	char* PUNTO_MONTAJE;

}sindicato_config;

sindicato_config* sindicatoStruct;
t_log* logger;

void iniciar_logger_config();

#endif /* SINDICATOLIB_H_ */
