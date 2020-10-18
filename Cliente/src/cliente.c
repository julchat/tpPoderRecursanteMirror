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
	if(realizarHandshake()){
	pthread_t hiloConsola;
	pthread_create(&hiloConsola, 0, (void*)ejecutarConsola, NULL);
	pthread_join(hiloConsola,NULL);
	return 0;
	}
	else{
		printf("no anduvo la conexion");
		return -15;
	}
}

bool realizarHandshake(){
	int socket1, socket2, ressend1, ressend2, resrecv1, resrecv2;
	void* recibidoPrimerSocket = malloc(sizeof(t_paquete)+ sizeof(uint8_t) +sizeof(uint32_t) + sizeof(t_modulo) + sizeof(bool));
	void* recibidoSegundoSocket = malloc(sizeof(t_paquete)+ sizeof(uint8_t) +sizeof(uint32_t) + sizeof(t_modulo) + sizeof(bool));
	t_identificadorSocket* respuestaPrimerSocket;
	t_identificadorSocket* respuestaSegundoSocket;
	handshakeStruct* infoAMandar = malloc(sizeof(handshakeStruct));
	infoAMandar->idModulo = 4;
	infoAMandar->idCliente = configCliente->ID_CLIENTE;
	infoAMandar->tamanioId = strlen(infoAMandar->idCliente)+1;
	infoAMandar->posX = configCliente->POSICION_X;
	infoAMandar->posY = configCliente->POSICION_Y;
	t_message* paquete = malloc(sizeof(t_message));
	paquete->head = 16;
	paquete->size = sizeof(t_header) + sizeof(t_modulo) + infoAMandar->tamanioId + sizeof(uint32_t) + 2*sizeof(uint32_t);
	void* stream = malloc(paquete->size);
	int offset = 0;
	memcpy(stream + offset, &infoAMandar->idModulo, sizeof(t_modulo));
	offset += sizeof(uint8_t);
	memcpy(stream + offset, &infoAMandar->tamanioId, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, infoAMandar->idCliente, infoAMandar->tamanioId);
	offset += infoAMandar->tamanioId;
	memcpy(stream + offset, &infoAMandar->posX, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, &infoAMandar->posY, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	paquete->content= stream;
	socket1 = crear_conexion(configCliente->IP,configCliente->PUERTO);
	socket2 = crear_conexion(configCliente->IP,configCliente->PUERTO);
	recv(socket1);
	recv(socket2);
	ressend1 = send(socket1, &paquete->size, sizeof(size_t), 0);
	ressend2 = send(socket2, &paquete->size, sizeof(size_t), 0);
	validarConexion(ressend1, ressend2);
	ressend1 = send(socket1, &paquete->head,sizeof(t_header),0);
	ressend2 = send(socket2, &paquete->head,sizeof(t_header),0);
	validarConexion(ressend1, ressend2);
	ressend1 = send(socket1, paquete->content, paquete->size - sizeof(t_header),0);
	ressend2 = send(socket2, paquete->content, paquete->size - sizeof(t_header),0);
	validarConexion(ressend1, ressend2);
	free(paquete->content);
	free(paquete);
	recibidoPrimerSocket = recibirMensaje(socket1);
	recibidoSegundoSocket = recibirMensaje(socket2);
	respuestaPrimerSocket = deserealizarRespuestaHandshake(recibidoPrimerSocket);
	respuestaSegundoSocket = deserealizarRespuestaHandshake(recibidoSegundoSocket);
	if(respuestaPrimerSocket->escucha == 0 && respuestaSegundoSocket->escucha == 1){
		socketDeHabla = socket1;
		socketDeEscucha = socket2;
	}
	else if(respuestaPrimerSocket->escucha == 1 && respuestaSegundoSocket->escucha == 0){
		socketDeHabla = socket2;
		socketDeEscucha = socket1;
	}
	else{
		printf("la conexion aparentemente anduvo bien pero la respuesta no fue la pactada");
		return 0;
	}
	switch(respuestaPrimerSocket->moduloConectado){
		case APP:
			moduloConectado = APP;
			break;
		case RESTAURANTE:
			moduloConectado = RESTAURANTE;
			break;
		case SINDICATO:
			moduloConectado = SINDICATO;
			break;
		case COMANDA:
			moduloConectado = COMANDA;
			break;
		default:
			printf("no se conecto a un modulo valido");
	}
	free(infoAMandar);
	free(recibidoPrimerSocket);
	free(recibidoSegundoSocket);
	free(respuestaPrimerSocket);
	free(respuestaSegundoSocket);
	return 1;
}

void ejecutarConsola(){
	printf("ejecutando consola");
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
	paquete->content = serializarUnMensaje(paraMandar->parametros, &size);
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
	if(sintaxisYSemanticaValida(leido,codOp,destinatario,&parametros)){
		aMandar = malloc(sizeof(mensajeListoYSeparado));
		pthread_create(&hiloParaUnMensaje,0,(void*)procesarEntrada,aMandar);
	}
	list_add(hilosEnConsola,&hiloParaUnMensaje);

}

void escucharApp(){

}

void escucharRestaurante(){

}
