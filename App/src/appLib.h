/*
 * appLib.h
 *
 *  Created on: 20 sep. 2020
 *      Author: utnso
 */

#ifndef APPLIB_H_
#define APPLIB_H_

#include "conexiones.h"
#include "mensajes.h"

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<commons/collections/list.h>

#include "conexiones.h"
#include "mensajes.h"
#include <pthread.h>

typedef struct {
	char* IP_COMANDA;
	int PUERTO_COMANDA;
	int PUERTO_ESCUCHA;
	int GRADO_DE_MULTIPROCESAMIENTO;
	char* ALGORITMO_DE_PLANIFICACION;
	double ALPHA;
	int ESTIMACION_INICIAL;
	t_list* REPARTIDORES;
	t_list* FRECUENCIA_DE_DESCANSO;
	t_list* TIEMPO_DE_DESCANSO;
	char* ARCHIVO_LOG;
	t_list* PLATOS_DEFAULT;
	int POSICION_REST_DEFAULT_X;
	int POSICION_REST_DEFAULT_Y;
}app_config;


#endif /* APPLIB_H_ */
