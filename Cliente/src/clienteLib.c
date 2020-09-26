#include "clienteLib.h"

cliente_config* leer_config_cliente(char* path){

	t_config* config_aux = config_create(path);
	cliente_config* config_cliente_aux = malloc(sizeof(cliente_config));

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

t_log* crear_logger_cliente(char* path){
	t_log* log_aux = log_create(path,"cliente",1,LOG_LEVEL_INFO);
	return log_aux;
}

bool sintaxisYSemanticaValida(char* mensaje){
	char* operacion;
	char* destinatario;
	t_list* parametros = list_create();
	dividirMensajeEnPartes(&operacion,&destinatario,&parametros, mensaje);
	t_header codigoOperacion;
	t_dest moduloDestino;
	t_list* modulosCompatibles = list_create();
	int cantParametros;

	if(validarMatcheoOperacion(operacion, &codigoOperacion)){
		if(validarMatcheoDestinatario(destinatario, &moduloDestino)){
			obtenerModulosCompatiblesYcantParametrosRequerida(codigoOperacion,moduloDestino,&modulosCompatibles,&cantParametros);
			if(validarSemanticaMensaje(modulosCompatibles, cantParametros, moduloDestino, parametros)){
				list_destroy_and_destroy_elements(modulosCompatibles,(void*) free);
				return 1;
			}
		}

	}
	list_destroy_and_destroy_elements(modulosCompatibles,(void*) free);
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
		printf("NO EXISTE EL MENSAJE ESPECIFICADO");
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
		printf("NO EXISTE EL MODULO ESPECIFICADO");
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
		break;
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
		printf("ERROR EN VALIDACION SINTACTICA,NO SE DEBERIA HABER LLEGADO AQUI!");
	}
}

bool validarSemanticaMensaje(t_list* modulosCompatibles, int cantParametros, t_dest destinatario, t_list* parametros){
	if(!(cantParametros == parametros->elements_count)){
		printf("SE ESPERABA QUE EL MENSAJE TENGA %d PARAMETROS, Y TUVO %d PARAMETROS", cantParametros,parametros->elements_count);
		return 0;
	}
	if(!(estaEnLaLista(&destinatario, modulosCompatibles))){
		printf("EL MENSAJE NO SE PUEDE MANDAR AL MODULO ESPECIFICADO");
		return 0;
	}
		return 1;

}



void dividirMensajeEnPartes(char** operacion,char** destinatario,t_list** parametros,char* mensaje){
	char** mensajeSeparado = string_split(mensaje," ");
	if(*mensajeSeparado != NULL){
		*operacion = *mensajeSeparado;
	}
	else{
		*operacion = "operacionNoEspecificada";
	}
	if(*(mensajeSeparado+1) != NULL){
		*destinatario = *(mensajeSeparado+1);
	}
	else{
		*destinatario = "moduloNoEspecificado";
	}
	if(*(mensajeSeparado+2)!=NULL){
		char* parametrosSinMeterEnLista = *(mensajeSeparado+2);
		char** parametrosEnArray = string_split(parametrosSinMeterEnLista,",");
		int i = 0;
		i=0;
		while(i<5 && *(parametrosEnArray+i)!=NULL){
			list_add(*parametros,parametrosEnArray+i);
			i++;
		}
	}
}

bool estaEnLaLista(t_dest* unElemento, t_list* unaLista){
	for(int i = 0; i<unaLista->elements_count;i++){
		if((list_get(unaLista,i)) == (unElemento)){
			return 1;
		}
	}
	return 0;
}
