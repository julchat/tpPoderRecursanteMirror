#include "clienteLib.h"

cliente_config* leer_config_cliente(char* path){

	t_config* config_aux = config_create(path);
	cliente_config* config_cliente_aux;

	config_cliente_aux->IP_COMANDA = config_get_string_value(config_aux,"IP_COMANDA");
	config_cliente_aux->PUERTO_COMANDA = config_get_int_value(config_aux,"PUERTO_COMANDA");
	config_cliente_aux->IP_RESTAURANTE = config_get_string_value(config_aux,"IP_RESTAURANTE");
	config_cliente_aux->PUERTO_RESTAURANTE = config_get_int_value(config_aux,"PUERTO_RESTAURANTE");
	config_cliente_aux->IP_SINDICATO = config_get_string_value(config_aux,"IP_SINDICATO");
	config_cliente_aux->PUERTO_SINDICATO = config_get_int_value(config_aux,"PUERTO_SINDICATO");
	config_cliente_aux->IP_APP = config_get_string_value(config_aux,"IP_APP");
	config_cliente_aux->PUERTO_APP = config_get_int_value(config_aux,"PUERTO_APP");
	config_cliente_aux->ARCHIVO_LOG = config_get_string_value(config_aux,"ARCHIVO_LOG");
	config_cliente_aux->POSICION_X = config_get_int_value(config_aux,"POSICION_X");
	config_cliente_aux->POSICION_Y = config_get_int_value(config_aux,"POSICION_Y");

	return config_cliente_aux;

}



