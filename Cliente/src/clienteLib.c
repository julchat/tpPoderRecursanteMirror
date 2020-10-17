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

bool sintaxisYSemanticaValida(char* mensaje, t_header* codigoOperacion, t_modulo* moduloDestino, t_list** parametros){
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

bool validarMatcheoDestinatario(char* destinatario, t_modulo* moduloALlenar){
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

void obtenerModulosCompatiblesYcantParametrosRequerida(t_header codigoOperacion,t_modulo moduloDestino,
		t_list** modulosCompatibles, int* cantParametros){
	t_modulo* moduloApp = malloc(sizeof(t_modulo));
	t_modulo* moduloRestaurante = malloc(sizeof(t_modulo));
	t_modulo* moduloSindicato = malloc(sizeof(t_modulo));
	t_modulo* moduloComanda = malloc(sizeof(t_modulo));
	t_modulo* moduloCliente = malloc(sizeof(t_modulo));
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

bool validarSemanticaMensaje(t_list* modulosCompatibles, int cantParametros, t_modulo destinatario, t_list* parametros){
	if(!(cantParametros == parametros->elements_count)){
		printf("SE ESPERABA QUE EL MENSAJE TENGA %d PARAMETROS, Y TUVO %d PARAMETROS", cantParametros,parametros->elements_count);
		return 0;
	}

	bool estaElDestEnLosCompatibles(t_modulo* unModuloDeLaLista){
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

void* serializarUnMensaje(t_list* parametros, int* size){
	int tamanio = 0;
	char* parametro;
	uint16_t tamanioParametro;
	for(int i = 0; i<parametros->elements_count; i++){
		tamanio += strlen(list_get(parametros,i))+1;
		tamanio += sizeof(uint16_t);
	}
	*size = tamanio;
	void* stream = malloc(tamanio);
	int offset = 0;
	for(int j = 0; j<parametros->elements_count;j++){
		parametro = list_get(parametros,j);
		tamanioParametro = strlen(parametro)+1;
		memcpy(stream + offset, &tamanioParametro, sizeof(uint16_t));
		offset = offset + sizeof(uint16_t);
		memcpy(stream + offset, parametro, strlen(parametro)+1);
		offset = offset + strlen(parametro)+1;
	}
	list_destroy_and_destroy_elements(parametros,free);
	return stream;
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

t_identificadorSocket* deserealizarRespuestaHandshake(t_message* paqueteRecibido){
	t_identificadorSocket* resultado = malloc(paqueteRecibido->size - sizeof(t_header));
	int offset = 0;
	memcpy(&resultado->moduloConectado, paqueteRecibido->content + offset, sizeof(t_modulo));
	offset += sizeof(t_modulo);
	memcpy(&resultado->escucha, paqueteRecibido->content + offset, sizeof(bool));
	offset += sizeof(bool);
	free(paqueteRecibido->content);
	free(paqueteRecibido);
	return resultado;
}

/*t_message* recibirMensaje(int socket){
	t_message * message = malloc(sizeof(t_message));

	int res = recv(socket,&message->size,sizeof(size_t),MSG_WAITALL);
	if (res <= 0 ){
		close(socket);
		free(message);
		return error(res);
	}

	void* buffer = malloc(message->size);
	res = recv(socket,buffer,message->size,MSG_WAITALL);


	if(res <= 0){
		close(socket);
		free(message);
		free(buffer);
		return error(res);
	}

	message->content = calloc(message->size - sizeof(t_header)+1,1);
	memcpy(&message->head, buffer, sizeof(t_header));
	memcpy(message->content,buffer + sizeof(t_header),message->size - sizeof(t_header));
	message->size = message->size - sizeof(t_header);

	free(buffer);
	return message;
}*/

void validarConexion(int socket1, int socket2){
	if(socket1 <= 0 || socket2 <= 0){
		printf("fallo el envio del handshake");
		exit(252);
	}
}
