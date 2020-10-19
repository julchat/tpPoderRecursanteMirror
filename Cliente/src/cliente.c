#include "cliente.h"
#include <pthread.h>

cliente_config* configCliente;
t_log* loggerCliente;
int socketDeHabla;
int socketDeEscucha;
t_modulo moduloConectado;
int main(int argc, char *argv[]){
	configCliente = leer_config_cliente(argv[1]);
	printf("%s",configCliente->ARCHIVO_LOG);
	loggerCliente = crear_logger_cliente(configCliente->ARCHIVO_LOG);
	log_info(loggerCliente, "logger inicializado");
	if(realizarHandshake()){
	log_info(loggerCliente,"El handshake con el modulo %d ha sido exitoso",moduloConectado);
	pthread_t hiloConsola;
	pthread_create(&hiloConsola, 0, (void*)ejecutarConsola, NULL);
	pthread_join(hiloConsola,NULL);
	return 0;
	}
	else{
		log_error(loggerCliente, "El handshake con el modulo %d ha fracasado", moduloConectado);
		return -15;
	}
}

bool realizarHandshake(){
	log_info(loggerCliente, "iniciando handshake con ip %s y puerto %s", configCliente->IP, configCliente->PUERTO);
	int socket1, socket2, ressend1, ressend2, resrecv1, resrecv2;
	bool esNecesarioUnSegundoSocket;
	socket1 = crear_conexion(configCliente->IP, configCliente->PUERTO);
	log_info(loggerCliente, "se le ha asignado el valor %d al socket 1", socket1);
	socket2 = -1;
	t_modulo* moduloServidor = malloc(sizeof(t_modulo));
	t_modulo* moduloCliente = malloc(sizeof(t_modulo));
	t_modulo* moduloServidor2 = malloc(sizeof(t_modulo));
	*moduloCliente = CLIENTE;
	recv(socket1, moduloServidor, sizeof(t_modulo), MSG_WAITALL);
	log_info(loggerCliente, "se conecto con el modulo %d",*moduloServidor);
	esNecesarioUnSegundoSocket = consultarNecesidadSegundoSocket(*moduloCliente, *moduloServidor);
	if(esNecesarioUnSegundoSocket){
		log_info(loggerCliente, "se requiere crear un segundo socket, conectando...");
		socket2 = crear_conexion(configCliente->IP, configCliente->PUERTO);
		log_info(loggerCliente, "se le ha asignado el valor %d al socket 2", socket2);
		recv(socket2, moduloServidor2, sizeof(t_modulo), MSG_WAITALL);
		log_info(loggerCliente, "se conecto el socket 2 con el modulo %d", *moduloServidor);
		if(*moduloServidor != *moduloServidor2){
			log_error(loggerCliente, "No se recibio informacion consistente de quien es el servidor (modulo socket1 distinto al modulo socket2)");
			close(socket1);
			close(socket2);
			return 0;
		}
	}
	moduloConectado = *moduloServidor;
	handshakeStruct* infoAMandar = malloc(sizeof(handshakeStruct));
	infoAMandar->idModulo = 4;
	infoAMandar->idCliente = atoi(configCliente->ID_CLIENTE);
	infoAMandar->posX = configCliente->POSICION_X;
	infoAMandar->posY = configCliente->POSICION_Y;
	size_t tamanio = sizeof(size_t) + sizeof(t_header) + sizeof(t_modulo) + sizeof(uint32_t) + 2 * sizeof(uint32_t);
	void* aEnviar = malloc(tamanio);
	int offset=0;
	memcpy(aEnviar + offset, &tamanio, sizeof(tamanio));
	offset += sizeof(size_t);
	t_header operacionSus = SUSCRIPCION;
	memcpy(aEnviar + offset, &operacionSus, sizeof(t_header));
	offset += sizeof(t_header);
	memcpy(aEnviar + offset, &infoAMandar->idModulo, sizeof(t_modulo));
	offset += sizeof(t_modulo);
	memcpy(aEnviar + offset, &infoAMandar->idCliente, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(aEnviar + offset, &infoAMandar->posX, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(aEnviar + offset, &infoAMandar->posY, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	ressend1 = send(socket1, aEnviar, tamanio, 0);
	if(ressend1 != tamanio){
		log_error(loggerCliente, "se esperaban enviar %d bytes y se enviaron %d bytes por el socket 1", tamanio, ressend1);
		close(socket1);
		return 0;
	}
	log_info(loggerCliente, "se envio la información sobre este Cliente al modulo %d", *moduloServidor);
	if(socket2 >= 0){
		ressend2 = send(socket2, aEnviar, tamanio, 0);
		if(ressend2 != tamanio){
			log_error(loggerCliente, "se esperaban enviar %d bytes y se enviaron %d bytes por el socket 2", tamanio, ressend2);
			close(socket2);
		}
		log_info(loggerCliente, "se envio la información sobre este Cliente al modulo %d por socket 2", *moduloServidor);
	}
	char* usoPrimerSocket = malloc(sizeof(char));
	char* usoSegundoSocket = malloc(sizeof(char));
	*usoSegundoSocket = 'N';

	resrecv1 = recv(socket1, usoPrimerSocket, sizeof(char), MSG_WAITALL);
	if(resrecv1 != sizeof(char)){
		log_error(loggerCliente, "no se pudo recibir el caracter de uso del socket 1");
		close(socket1);
		return 0;
	}
	if(socket2 >= 0){
		resrecv2= recv(socket2, usoSegundoSocket, sizeof(char), MSG_WAITALL);
		if(resrecv2 != sizeof(char)){
				log_error(loggerCliente,"no se pudo recibir el caracter de uso del socket 2");
				close(socket2);
			}
	}

	switch(*usoPrimerSocket){
		case 'E':
			socketDeHabla = socket1;
			log_info(loggerCliente, "el socket %d se usara habla por el cliente", socket1);
			break;
		case 'H':
			socketDeEscucha = socket1;
			log_info(loggerCliente, "el socket %d se usara de escucha por el cliente", socket1);
			break;
		case 'I':
			log_error(loggerCliente, "el socket %d es innecesario, cerrando",socket1);
			close (socket1);
			return 0;
			break;
	}

	switch(*usoSegundoSocket){
		case 'E':
			socketDeHabla = socket2;
			log_info(loggerCliente, "el socket %d se usara habla por el cliente", socket2);
			break;
		case 'H':
			socketDeEscucha = socket2;
			log_info(loggerCliente, "el socket %d se usara de escucha por el cliente", socket2);
			break;
		case 'I':
			log_error(loggerCliente,"el socket %d es innecesario, cerrando ",socket2);
			close (socket2);
			break;
	}

	free(infoAMandar);
	free(aEnviar);
	free(moduloCliente);
	free(moduloServidor);
	free(moduloServidor2);
	free(usoPrimerSocket);
	free(usoSegundoSocket);
	return 1;
}

void ejecutarConsola(){
	printf("ejecutando consola");
	log_info(loggerCliente,"ejecutando consola");
	t_list* hilosEnConsola = list_create();
	char* leido;
	pthread_t* unHilo;
	leido = readline(">");
	while(strcmp(leido,"cerrar")){
		declararHiloYMeterloALaLista(hilosEnConsola, leido);
		free(leido);
		leido = readline(">");
	}
	free(leido);
	for(int j= 0; j<hilosEnConsola->elements_count;j++){
		unHilo = list_get(hilosEnConsola,j);
		pthread_join(*unHilo,NULL);
	}
	list_destroy(hilosEnConsola);
}

void procesarEntrada(mensajeListoYSeparado* paraMandar){
	t_message* paquete = malloc(sizeof(t_message));
	int size;
	paquete->head = *paraMandar->operacion;
	switch(*paraMandar->operacion){
	case SELECCIONAR_RESTAURANTES:
		break;
	case OBTENER_RESTAURANTE:
		break;
	case CONSULTAR_PLATOS:
		break;
	case CREAR_PEDIDO:
		break;
	case GUARDAR_PEDIDO:
		break;
	case ANIADIR_PLATO:
		break;
	case GUARDAR_PLATO:
		break;
	case CONFIRMAR_PEDIDO:
		break;
	case PLATO_LISTO:
		break;
	case CONSULTAR_PEDIDO:
		break;
	case OBTENER_PEDIDO:
		break;
	case FINALIZAR_PEDIDO:
		break;
	case OBTENER_RECETA:
		break;
	default:
		log_error(loggerCliente, "QUIEN SOS VOS?");
		break;
	}
	send(socketDeHabla, &paquete->size, sizeof(size_t), 0);
	send(socketDeHabla, &paquete->head, sizeof(t_header), 0);
	send(socketDeHabla, paquete->content, paquete->size - sizeof(t_header),0);
	free(paquete->content);
	free(paquete);
	free(paraMandar->destinatario);
	free(paraMandar);
}

void declararHiloYMeterloALaLista(t_list* hilosEnConsola, char* leido){
	t_header* codOp = malloc(sizeof(t_header));
	t_modulo* destinatario = malloc(sizeof(t_modulo));
	t_list* parametros = list_create();
	mensajeListoYSeparado* aMandar;
	pthread_t hiloParaUnMensaje;
	if(sintaxisYSemanticaValida(leido,codOp,destinatario,&parametros, *loggerCliente)){
		aMandar = malloc(sizeof(mensajeListoYSeparado));
		log_info(loggerCliente, "el mensaje \"%s\" es valido. Se procedera a crear un hilo para su envio",leido);
		pthread_create(&hiloParaUnMensaje,0,(void*)procesarEntrada,aMandar);
	}
	list_add(hilosEnConsola,&hiloParaUnMensaje);

}


