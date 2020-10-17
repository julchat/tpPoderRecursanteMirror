/*
 * appLib.c
 *
 *  Created on: 20 sep. 2020
 *      Author: utnso
 */

#include "appLib.h"

app_config* leerConfigApp(char* path) {

	t_config* configAux = config_create(path);
	app_config* appConfigAux = malloc(sizeof(app_config));

	appConfigAux->ALGORITMO_DE_PLANIFICACION = config_get_string_value(configAux, "ALGORITMO_DE_PLANIFICACION");
	appConfigAux->ALPHA = config_get_double_value(configAux, "ALPHA");
	appConfigAux->ARCHIVO_LOG = config_get_string_value(configAux, "ARCHIVO_LOG");
	appConfigAux->ESTIMACION_INICIAL = config_get_int_value(configAux, "ESTIMACION_INICIAL");
	appConfigAux->FRECUENCIA_DE_DESCANSO = config_get_array_value(configAux, "FRECUENCIA_DE_DESCANSO");
	appConfigAux->GRADO_DE_MULTIPROCESAMIENTO = config_get_int_value(configAux, "GRADO_DE_MULTIPROCESAMIENTO");
	appConfigAux->IP_COMANDA = config_get_string_value(configAux, "IP_COMANDA");
	appConfigAux->PLATOS_DEFAULT = config_get_array_value(configAux, "PLATOS_DEFAULT");
	appConfigAux->POSICION_REST_DEFAULT_X = config_get_int_value(configAux, "POSICION_REST_DEFAULT_X");
	appConfigAux->POSICION_REST_DEFAULT_Y = config_get_int_value(configAux, "POSICION_REST_DEFAULT_Y");
	appConfigAux->PUERTO_COMANDA = config_get_int_value(configAux, "PUERTO_COMANDA");
	appConfigAux->PUERTO_ESCUCHA = config_get_int_value(configAux, "PUERTO_ESCUCHA");
	appConfigAux->REPARTIDORES = config_get_array_value(configAux, "REPARTIDORES");
	appConfigAux->TIEMPO_DE_DESCANSO = config_get_array_value(configAux, "TIEMPO_DE_DESCANSO");

	return configAux;
}

t_log* loggerApp(char* path) {

	t_log* logAux = log_create(path, "App", 1, LOG_LEVEL_INFO);
	return logAux;
}

