#include "clienteLib.h"

/*void iniciar_logger_config(){

	t_config* config = config_create("./Cliente.config");
	logger = log_create("Cliente.log", "Cliente", 1, LOG_LEVEL_INFO);

	clientStruct->IP_COMANDA = config_get_string_value(config,"IP_COMANDA");
	clientStruct->PUERTO_COMANDA = config_get_int_value(config,"PUERTO_COMANDA");
	clientStruct->IP_RESTAURANTE = config_get_string_value(config,"IP_RESTAURANTE");
	clientStruct->PUERTO_RESTAURANTE = config_get_int_value(config,"PUERTO_RESTAURANTE");
	clientStruct->IP_SINDICATO = config_get_string_value(config,"IP_SINDICATO");
	clientStruct->PUERTO_SINDICATO = config_get_int_value(config,"PUERTO_SINDICATO");
	clientStruct->IP_APP = config_get_string_value(config,"IP_APP");
	clientStruct->PUERTO_APP = config_get_int_value(config,"PUERTO_APP");
	clientStruct->ARCHIVO_LOG = config_get_string_value(config,"ARCHIVO_LOG");
	clientStruct->POSICION_X = config_get_int_value(config,"POSICION_X");
	clientStruct->POSICION_Y = config_get_int_value(config,"POSICION_Y");

}*/

cliente_config* leer_config_cliente(){

	t_config* config_aux = config_create("./ArchivoConfig.config");
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



