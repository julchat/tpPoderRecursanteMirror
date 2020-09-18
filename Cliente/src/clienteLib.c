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

bool sintaxisValida(char* mensaje){
	char* operacion = obtenerOperacion(mensaje);
	char* destinatario = obtenerDestinatario(mensaje);
	char** parametros = obtenerParametros(mensaje);
	t_header codigoOperacion;
	t_dest moduloDestino;
	t_list* modulosCompatibles = list_create();
	int cantParametros;


	if(validarMatcheoOperacion(operacion, &codigoOperacion)){
		if(validarMatcheoDestinatario(destinatario, &moduloDestino)){
			obtenerModulosCompatiblesYcantParametrosRequerida(codigoOperacion,moduloDestino,&modulosCompatibles,&cantParametros);
			if(validarSemanticaMensaje(modulosCompatibles, cantParametros, destinatario, parametros)){
				return 1;
			}
		}
	}
	return 0;
}


bool validarMatcheoOperacion(char* operacion, t_header* codigoALlenar){
	if(strcmp(operacion, "consultarRestaurantes")==0){
		*codigoALlenar = 0;
		return 1;
	}else if(strcmp(operacion, "seleccionarRestaurantes")==0){
		*codigoALlenar = 1;
		return 1;
	}else if(strcmp(operacion, "obtenerRestaurante")==0){
		*codigoALlenar = 2;
		return 1;
	}else if(strcmp(operacion, "consultarPlatos")==0){
		*codigoALlenar = 3;
		return 1;
	}else if(strcmp(operacion, "crearPedido")==0){
		*codigoALlenar = 4;
		return 1;
	}else if(strcmp(operacion, "guardarPedido")==0){
		*codigoALlenar = 5;
		return 1;
	}else if(strcmp(operacion, "aniadirPlato")==0){
		*codigoALlenar = 6;
		return 1;
	}else if(strcmp(operacion, "guardarPlato")==0){
		*codigoALlenar = 7;
		return 1;
	}else if(strcmp(operacion, "confirmarPlato")==0){
		*codigoALlenar = 8;
		return 1;
	}else if(strcmp(operacion, "platoListo")==0){
		*codigoALlenar = 9;
		return 1;
	}else if(strcmp(operacion, "consultarPedido")==0){
		*codigoALlenar = 10;
		return 1;
	}else if(strcmp(operacion, "obtenerPedido")==0){
		*codigoALlenar = 11;
		return 1;
	}else if(strcmp(operacion, "finalizarPedido")==0){
		*codigoALlenar = 12;
		return 1;
	}else if(strcmp(operacion, "terminarPedido")==0){
		*codigoALlenar = 13;
		return 1;
	}else if(strcmp(operacion, "obtenerReceta")==0){
		*codigoALlenar = 14;
		return 1;
	}else{
		printf("No existe el mensaje especificado");
		*codigoALlenar = 15;
		return 0;
	}
}

bool validarMatcheoOperacion(char* destinatario, t_dest* moduloALlenar){
	if(strcmp(destinatario, "app")==0){
		*moduloALlenar = APP;
		return 1;
	}else if(strcmp(destinatario, "restaurante")==0){
		*moduloALlenar = RESTAURANTE;
		return 1;
	}else if(strcmp(destinatario, "sindicato")==0){
		*moduloALlenar = SINDICATO;
		return 1;
	}else if(strcmp(destinatario, "comanda")==0){
		*moduloALlenar = COMANDA;
		return 1;
	}else{
		printf("no existe el modulo especificado");
		*moduloALlenar = ERR;
		return 0;
	}
}

void obtenerModulosCompatiblesYcantParametrosRequerida(t_header codigoOperacion,t_dest moduloDestino,
		t_list** modulosCompatibles, int* cantParametros){
	t_dest unModuloCompatible;
	switch(codigoOperacion){
	case 0:
		*cantParametros = 0;
		unModuloCompatible = APP;
		list_add(*modulosCompatibles,&unModuloCompatible);
		break;
	case 1:
		*cantParametros = 2;
		unModuloCompatible = APP;
		list_add(*modulosCompatibles,&unModuloCompatible);
		break;
	case 2:
		*cantParametros = 1;
		unModuloCompatible = SINDICATO;
		list_add(*modulosCompatibles,&unModuloCompatible);
	}
	case 3:
		if(moduloDestino == SINDICATO){
			*cantParametros = 1;
		}else{
			*cantParametros = 0;
		}
		unModuloCompatible = APP;
		list_add(*modulosCompatibles, &unModuloCompatible);
		unModulo
}

