/*
 * restauranteLib.c
 *
 *  Created on: 20 sep. 2020
 *      Author: utnso
 */

#include "restauranteLib.h"

void cargarConfiguraciones(char* pathConfig) {
	restauranteConf = leerConfig(pathConfig);
	restauranteConf = malloc(sizeof(restauranteConfig));

	restauranteConf->ALGORITMO_PLANIFICACION = config_get_string_value(restauranteConf,"ALGORITMO_PLANIFICACION");
	restauranteConf->ARCHIVO_LOG = config_get_string_value(restauranteConf,"ARCHIVO_LOG");
	restauranteConf->IP_APP = config_get_string_value(restauranteConf,"IP_APP");
	restauranteConf->IP_SINDICATO = config_get_string_value(restauranteConf,"IP_SINDICATO");
	restauranteConf->NOMBRE_RESTAURANTE = config_get_string_value(restauranteConf,"NOMBRE_RESTAURANTE");
	restauranteConf->PUERTO_APP = config_get_int_value(restauranteConf, "PUERTO_APP");
	restauranteConf->PUERTO_ESCUCHA = config_get_int_value(restauranteConf, "PUERTO_ESCUCHA");
	restauranteConf->PUERTO_SINDICATO = config_get_int_value(restauranteConf, "PUERTO_SINDICATO");
	restauranteConf->QUANTUM = config_get_int_value(restauranteConf, "QUANTUM");

}

t_config* leerConfig(char* pathConfig) {
	t_config * config = config_create(pathConfig);
		if (config == NULL) {
			printf("NO SE PUDO LEER EL ARCHIVO DE CONFIGURACION \n");
			exit(1);
		}
		return config;
}

void iniciarLogger(){
	loggerRestaurante = log_create(LOG_FILE, "Restaurante", 1, LOG_LEVEL_INFO);
}


