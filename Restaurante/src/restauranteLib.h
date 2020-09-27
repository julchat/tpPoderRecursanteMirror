/*
 * restauranteLib.h
 *
 *  Created on: 20 sep. 2020
 *      Author: utnso
 */

#ifndef RESTAURANTELIB_H_
#define RESTAURANTELIB_H_

#include <commons/config.h>
#include <commons/log.h>
#include <commons/collections/list.h>
#include <stdio.h>
#include <stdlib.h>
#include <commons/string.h>

#include "conexiones.h"
#include "mensajes.h"

typedef struct{
	int PUERTO_ESCUCHA;
	char* IP_SINDICATO;
	int PUERTO_SINDICATO;
	char* IP_APP;
	int PUERTO_APP;
	int QUANTUM;
	char* ARCHIVO_LOG;
	char* ALGORITMO_PLANIFICACION;
	char* NOMBRE_RESTAURANTE;
}restauranteConfig;

restauranteConfig* restauranteConf;
t_log* loggerRestaurante;
char* LOG_FILE;

void iniciarLogger();
void cargarConfiguraciones(char* pathConfig);
t_config* leerConfig(char* pathConfig);

#endif /* RESTAURANTELIB_H_ */
