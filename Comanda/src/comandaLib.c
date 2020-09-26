#include "comandaLib.h"

comanda_config* leer_config_comanda(char* path){


	t_config* config_aux = config_create(path);
	comanda_config* config_comanda_aux = malloc(sizeof(comanda_config));

	config_comanda_aux->PUERTO_ESCUCHA = config_get_int_value(config_aux,"PUERTO_ESCUCHA");
	config_comanda_aux->TAMANIO_MEMORIA = config_get_int_value(config_aux,"TAMANIO_MEMORIA");
	config_comanda_aux->TAMANIO_SWAP = config_get_int_value(config_aux,"TAMANIO_SWAP");
	config_comanda_aux->ALGORITMO_REEMPLAZO = config_get_string_value(config_aux,"ALGORITMO_REEMPLAZO");
	config_comanda_aux->ARCHIVO_LOG = config_get_string_value(config_aux,"ARCHIVO_LOG ");


	return config_comanda_aux;
}


t_log* crear_logger_comanda(char* path){ // Como le meto el path al log?

	t_log* log_aux = log_create("Comanda.log","Comanda",1,LOG_LEVEL_INFO);
	return log_aux;
}
