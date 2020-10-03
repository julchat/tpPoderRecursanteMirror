#include "clienteLib.h"

cliente_config* leer_config_cliente(char* path){

	t_config* config_aux = config_create(path);
	cliente_config* config_cliente_aux = malloc(sizeof(cliente_config));

	config_cliente_aux->IP= config_get_string_value(config_aux,"IP");
	config_cliente_aux->PUERTO= config_get_string_value(config_aux,"PUERTO");
	config_cliente_aux->ARCHIVO_LOG = config_get_string_value(config_aux,"ARCHIVO_LOG");
	config_cliente_aux->POSICION_X = config_get_int_value(config_aux,"POSICION_X");
	config_cliente_aux->POSICION_Y = config_get_int_value(config_aux,"POSICION_Y");
	config_cliente_aux->ID_CLIENTE = config_get_string_value(config_aux,"ID_CLIENTE");
	return config_cliente_aux;

}

t_log* crear_logger_cliente(char* path){
	t_log* log_aux = log_create(path,"cliente",1,LOG_LEVEL_INFO);
	return log_aux;
}

bool sintaxisYSemanticaValida(char* mensaje, t_header* codigoOperacion, t_dest* moduloDestino, t_list** parametros){
	char* operacion;
	char* destinatario;
	*parametros = dividirMensajeEnPartes(&operacion,&destinatario,mensaje);
	t_list* modulosCompatibles = list_create();
	int cantParametros;
	if(validarMatcheoOperacion(operacion, codigoOperacion)){
		if(validarMatcheoDestinatario(destinatario, moduloDestino)){
			obtenerModulosCompatiblesYcantParametrosRequerida(*codigoOperacion,*moduloDestino,&modulosCompatibles,&cantParametros);
			if(validarSemanticaMensaje(modulosCompatibles, cantParametros, *moduloDestino, *parametros)){
				list_destroy_and_destroy_elements(modulosCompatibles, free);
				return 1;
			}
		}

	}
	list_destroy_and_destroy_elements(modulosCompatibles, free);
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
	t_dest* moduloApp = malloc(sizeof(t_dest));
	t_dest* moduloRestaurante = malloc(sizeof(t_dest));
	t_dest* moduloSindicato = malloc(sizeof(t_dest));
	t_dest* moduloComanda = malloc(sizeof(t_dest));
	t_dest* moduloCliente = malloc(sizeof(t_dest));
	*moduloApp = APP;
	*moduloRestaurante = RESTAURANTE;
	*moduloSindicato = SINDICATO;
	*moduloComanda = COMANDA;
	*moduloCliente = CLIENTE;
	switch(codigoOperacion){
	case CONSULTAR_RESTAURANTES:
		*cantParametros = 0;
		list_add(*modulosCompatibles,moduloApp);
		free(moduloRestaurante);
		free(moduloSindicato);
		free(moduloComanda);
		free(moduloCliente);
		break;
	case SELECCIONAR_RESTAURANTES:
		*cantParametros = 2;
		list_add(*modulosCompatibles,moduloApp);
		free(moduloRestaurante);
		free(moduloSindicato);
		free(moduloComanda);
		free(moduloCliente);
		break;
	case OBTENER_RESTAURANTE:
		*cantParametros = 1;
		list_add(*modulosCompatibles,moduloSindicato);
		free(moduloRestaurante);
		free(moduloApp);
		free(moduloComanda);
		free(moduloCliente);
		break;
	case CONSULTAR_PLATOS:
		*cantParametros = 1;
		list_add(*modulosCompatibles, moduloApp);
		list_add(*modulosCompatibles, moduloRestaurante);
		list_add(*modulosCompatibles, moduloSindicato);
		free(moduloComanda);
		free(moduloCliente);
		break;
	case CREAR_PEDIDO:
		*cantParametros = 0;
		list_add(*modulosCompatibles, moduloApp);
		list_add(*modulosCompatibles, moduloRestaurante);
		free(moduloSindicato);
		free(moduloComanda);
		free(moduloCliente);
		break;
	case GUARDAR_PEDIDO:
		*cantParametros = 2;
		list_add(*modulosCompatibles, moduloSindicato);
		list_add(*modulosCompatibles, moduloComanda);
		free(moduloRestaurante);
		free(moduloApp);
		free(moduloCliente);
		break;
	case ANIADIR_PLATO:
		*cantParametros = 2;
		list_add(*modulosCompatibles, moduloApp);
		list_add(*modulosCompatibles, moduloRestaurante);
		free(moduloSindicato);
		free(moduloComanda);
		free(moduloCliente);
		break;
	case GUARDAR_PLATO:
		*cantParametros = 4;
		list_add(*modulosCompatibles, moduloSindicato);
		list_add(*modulosCompatibles, moduloComanda);
		free(moduloCliente);
		free(moduloApp);
		free(moduloRestaurante);
		break;
	case CONFIRMAR_PEDIDO:
		*cantParametros = 1;
		list_add(*modulosCompatibles, moduloApp);
		list_add(*modulosCompatibles, moduloRestaurante);
		list_add(*modulosCompatibles, moduloSindicato);
		list_add(*modulosCompatibles, moduloComanda);
		free(moduloCliente);
		break;
	case PLATO_LISTO:
		*cantParametros = 3;
		list_add(*modulosCompatibles, moduloApp);
		list_add(*modulosCompatibles, moduloSindicato);
		list_add(*modulosCompatibles, moduloComanda);
		free(moduloRestaurante);
		free(moduloCliente);
		break;
	case CONSULTAR_PEDIDO:
		*cantParametros = 1;
		list_add(*modulosCompatibles, moduloApp);
		list_add(*modulosCompatibles, moduloRestaurante);
		free(moduloSindicato);
		free(moduloComanda);
		free(moduloCliente);
		break;
	case OBTENER_PEDIDO:
		*cantParametros = 2;
		list_add(*modulosCompatibles, moduloSindicato);
		list_add(*modulosCompatibles, moduloComanda);
		free(moduloRestaurante);
		free(moduloApp);
		free(moduloCliente);
		break;
	case FINALIZAR_PEDIDO:
		*cantParametros = 2;
		list_add(*modulosCompatibles, moduloComanda);
		list_add(*modulosCompatibles, moduloCliente);
		free(moduloRestaurante);
		free(moduloSindicato);
		free(moduloApp);
		break;
	case TERMINAR_PEDIDO:
		*cantParametros = 2;
		list_add(*modulosCompatibles, moduloSindicato);
		free(moduloRestaurante);
		free(moduloApp);
		free(moduloComanda);
		free(moduloCliente);
		break;
	case OBTENER_RECETA:
		*cantParametros = 1;
		list_add(*modulosCompatibles, moduloSindicato);
		free(moduloRestaurante);
		free(moduloApp);
		free(moduloComanda);
		free(moduloCliente);
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

	bool estaElDestEnLosCompatibles(t_dest* unModuloDeLaLista){
		return *unModuloDeLaLista == destinatario;
	}
	if(!(list_any_satisfy(modulosCompatibles, (bool*) estaElDestEnLosCompatibles))){
		printf("EL MENSAJE NO SE PUEDE MANDAR AL MODULO ESPECIFICADO");
		return 0;
	}
		return 1;

}



t_list* dividirMensajeEnPartes(char** operacion,char** destinatario,char* mensaje){
	char** mensajeSeparado = string_split(mensaje," ");
	t_list* parametros = list_create();
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
			list_add(parametros,*(parametrosEnArray+i));
			i++;
		}
	}
	return parametros;
}

t_buffer* serializarUnMensaje(t_list* parametros){
	t_buffer* buffer = malloc(sizeof(t_buffer));
	int size = 0;
	char* parametro;
	uint16_t tamanioParametro;
	for(int i = 0; i<parametros->elements_count; i++){
		size += strlen(list_get(parametros,i))+1;
	}
	buffer->size = size;
	void* stream = malloc(buffer->size);
	int offset = 0;
	for(int j = 0; j<parametros->elements_count;j++){
		parametro = list_get(parametros,j);
		tamanioParametro = strlen(parametro)+1;
		memcpy(stream + offset, &tamanioParametro, sizeof(uint16_t));
		offset = offset + sizeof(uint16_t);
		memcpy(stream + offset, parametro, strlen(parametro)+1);
		offset = offset + strlen(parametro)+1;
	}
	buffer->stream= stream;
	list_destroy_and_destroy_elements(parametros,free);
	return buffer;
}

int crear_conexion(char *ip, char* puerto){
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	int socket_cliente = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	if(connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1)
		printf("error");

	freeaddrinfo(server_info);

	return socket_cliente;
}

/*bool estaEnLaLista(t_dest* unElemento, t_list* unaLista){
	for(int i = 0; i<unaLista->elements_count;i++){
		if((list_get(unaLista,i)) == (unElemento)){
			return 1;
		}
	}
	return 0;
}*/
