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

bool sintaxisYSemanticaValida(char* mensaje){
	char* operacion = obtenerOperacion(mensaje);
	char* destinatario = obtenerDestinatario(mensaje);
	t_list* parametros = obtenerParametros(mensaje);
	t_header codigoOperacion;
	t_dest moduloDestino;
	t_list* modulosCompatibles = list_create();
	int cantParametros;
	if(validarMatcheoOperacion(operacion, &codigoOperacion)){
		if(validarMatcheoDestinatario(destinatario, &moduloDestino)){
			obtenerModulosCompatiblesYcantParametrosRequerida(codigoOperacion,moduloDestino,&modulosCompatibles,&cantParametros);
			if(validarSemanticaMensaje(modulosCompatibles, cantParametros, moduloDestino, parametros)){
				return 1;
			}
		}

	}
	list_destroy(modulosCompatibles);
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

bool validarMatcheoDestinatario(char* destinatario, t_dest* moduloALlenar){
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
	}else if(strcmp(destinatario, "cliente")==0){
		*moduloALlenar = CLIENTE;
		return 1;
	}else{
		printf("no existe el modulo especificado");
		*moduloALlenar = ERR;
		return 0;
	}
}

void obtenerModulosCompatiblesYcantParametrosRequerida(t_header codigoOperacion,t_dest moduloDestino,
		t_list** modulosCompatibles, int* cantParametros){
	t_dest moduloApp = APP;
	t_dest moduloRestaurante = RESTAURANTE;
	t_dest moduloSindicato = SINDICATO;
	t_dest moduloComanda = COMANDA;
	t_dest moduloCliente = CLIENTE;
	switch(codigoOperacion){
	case CONSULTAR_RESTAURANTES:
		*cantParametros = 0;
		list_add(*modulosCompatibles,&moduloApp);
		break;
	case SELECCIONAR_RESTAURANTES:
		*cantParametros = 2;
		list_add(*modulosCompatibles,&moduloApp);
		break;
	case OBTENER_RESTAURANTE:
		*cantParametros = 1;
		list_add(*modulosCompatibles,&moduloSindicato);
		break;
	case CONSULTAR_PLATOS:
		*cantParametros = 1;
		list_add(*modulosCompatibles, &moduloApp);
		list_add(*modulosCompatibles, &moduloRestaurante);
		list_add(*modulosCompatibles, &moduloSindicato);
		break;
	case CREAR_PEDIDO:
		*cantParametros = 0;
		list_add(*modulosCompatibles, &moduloApp);
		list_add(*modulosCompatibles, &moduloRestaurante);
		break;
	case GUARDAR_PEDIDO:
		*cantParametros = 2;
		list_add(*modulosCompatibles, &moduloSindicato);
		list_add(*modulosCompatibles, &moduloComanda);
		break;
	case ANIADIR_PLATO:
		*cantParametros = 2;
		list_add(*modulosCompatibles, &moduloApp);
		list_add(*modulosCompatibles, &moduloRestaurante);
		break;
	case GUARDAR_PLATO:
		*cantParametros = 4;
		list_add(*modulosCompatibles, &moduloSindicato);
		list_add(*modulosCompatibles, &moduloComanda);
		break;
	case CONFIRMAR_PEDIDO:
		*cantParametros = 1;
		list_add(*modulosCompatibles, &moduloApp);
		list_add(*modulosCompatibles, &moduloRestaurante);
		list_add(*modulosCompatibles, &moduloSindicato);
		list_add(*modulosCompatibles, &moduloComanda);
		break;
	case PLATO_LISTO:
		*cantParametros = 3;
		list_add(*modulosCompatibles, &moduloApp);
		list_add(*modulosCompatibles, &moduloSindicato);
		list_add(*modulosCompatibles, &moduloComanda);
	case CONSULTAR_PEDIDO:
		*cantParametros = 1;
		list_add(*modulosCompatibles, &moduloApp);
		list_add(*modulosCompatibles, &moduloRestaurante);
		break;
	case OBTENER_PEDIDO:
		*cantParametros = 2;
		list_add(*modulosCompatibles, &moduloSindicato);
		list_add(*modulosCompatibles, &moduloComanda);
		break;
	case FINALIZAR_PEDIDO:
		*cantParametros = 2;
		list_add(*modulosCompatibles, &moduloComanda);
		list_add(*modulosCompatibles, &moduloCliente);
		break;
	case TERMINAR_PEDIDO:
		*cantParametros = 2;
		list_add(*modulosCompatibles, &moduloSindicato);
		break;
	case OBTENER_RECETA:
		*cantParametros = 1;
		list_add(*modulosCompatibles, &moduloSindicato);
		break;
	default:
		printf("error en la validacion sintactica, no se deberia haber llegado aqui");
	}
}

bool validarSemanticaMensaje(t_list* modulosCompatibles, int cantParametros, t_dest destinatario, t_list* parametros){
	if(!(cantParametros == parametros->elements_count)){
		printf("se esperaba que el mensaje tuviera %d parametros, y tuvo %d parametros", parametros->elements_count, cantParametros);
		return 0;
	}
	if(!(estaEnLaLista(destinatario, modulosCompatibles))){
		printf("el mensaje especificado no se puede mandar a tal modulo");
		return 0;
	}
		return 1;

}

char* obtenerOperacion(char* textoLeido){
	char* token;
	token = strtok(textoLeido," ");
	if(token == NULL){
			token = "error";
	}
	return token;
}

char* obtenerDestinatario(char* textoLeido){
	char* token;
	token = strtok(textoLeido, " ");
	token = strtok(NULL, " ");
	if(token == NULL){
		token = "error";
	}
	return token;
}

t_list* obtenerParametros(char* textoLeido){
	t_list* parametros = list_create();
	char* token;
	token = strtok(textoLeido, " ");
	token = strtok(NULL, " ");
	token = strtok(NULL, " ");
	token = strtok(token,",");
	while(token!=NULL){
		list_add(parametros,&token);
		token = strtok(NULL,",");
	}
	return parametros;
}
