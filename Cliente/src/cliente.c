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
	bool esNecesarioUnSegundoSocket;
	socket1 = crear_conexion(configCliente->IP, configCliente->PUERTO);
	socket2 = -1;
	t_modulo* moduloServidor = malloc(sizeof(t_modulo));
	t_modulo* moduloCliente = malloc(sizeof(t_modulo));
	t_modulo* moduloServidor2 = malloc(sizeof(t_modulo));
	*moduloCliente = CLIENTE;
	recv(socket1, moduloServidor, sizeof(t_modulo), MSG_WAITALL);
	esNecesarioUnSegundoSocket = consultarNecesidadSegundoSocket(*moduloCliente, *moduloServidor);
	if(esNecesarioUnSegundoSocket){
		socket2 = crear_conexion(configCliente->IP, configCliente->PUERTO);
		recv(socket2, moduloServidor2, sizeof(t_modulo), MSG_WAITALL);
		if(*moduloServidor != *moduloServidor2){
			printf("No se recibio informacion consistente de quien es el servidor (modulo socket1 distinto al modulo socket2)");
			close(socket1);
			close(socket2);
			return 0;
		}
	}
	moduloConectado = *moduloServidor;
	handshakeStruct* infoAMandar = malloc(sizeof(handshakeStruct));
	infoAMandar->idModulo = 4;
	infoAMandar->idCliente = configCliente->ID_CLIENTE;
	infoAMandar->tamanioId = strlen(infoAMandar->idCliente)+1;
	infoAMandar->posX = configCliente->POSICION_X;
	infoAMandar->posY = configCliente->POSICION_Y;
	size_t tamanio = sizeof(size_t) + sizeof(t_header) + sizeof(t_modulo) + sizeof(uint32_t) + infoAMandar->tamanioId + 2 * sizeof(uint32_t);
	void* aEnviar = malloc(tamanio);
	int offset=0;
	memcpy(aEnviar + offset, &tamanio, sizeof(tamanio));
	offset += sizeof(size_t);
	t_header operacionSus = SUSCRIPCION;
	memcpy(aEnviar + offset, &operacionSus, sizeof(t_header));
	offset += sizeof(t_header);
	memcpy(aEnviar + offset, &infoAMandar->idModulo, sizeof(t_modulo));
	offset += sizeof(t_modulo);
	memcpy(aEnviar + offset, &infoAMandar->tamanioId, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(aEnviar + offset, infoAMandar->idCliente, infoAMandar->tamanioId);
	offset += infoAMandar->tamanioId;
	memcpy(aEnviar + offset, &infoAMandar->posX, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(aEnviar + offset, &infoAMandar->posY, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	ressend1 = send(socket1, aEnviar, tamanio, 0);
	if(ressend1 != tamanio){
		printf("se esperaban enviar %d bytes y se enviaron %d bytes por el socket 1", tamanio, ressend1);
		close(socket1);
		return 0;
	}
	if(socket2 >= 0){
		ressend2 = send(socket2, aEnviar, tamanio, 0);
		if(ressend2 != tamanio){
			printf("se esperaban enviar %d bytes y se enviaron %d bytes por el socket 2", tamanio, ressend2);
			close(socket2);
		}
	}
	char* usoPrimerSocket = malloc(sizeof(char));
	char* usoSegundoSocket = malloc(sizeof(char));
	*usoSegundoSocket = 'N';

	resrecv1 = recv(socket1, usoPrimerSocket, sizeof(char), MSG_WAITALL);
	if(resrecv1 != sizeof(char)){
		printf("no se pudo recibir el caracter de uso del socket 1");
		close(socket1);
		return 0;
	}
	if(socket2 >= 0){
		resrecv2= recv(socket2, usoSegundoSocket, sizeof(char), MSG_WAITALL);
		if(resrecv2 != sizeof(char)){
				printf("no se pudo recibir el caracter de uso del socket 2");
				close(socket2);
			}
	}

	switch(*usoPrimerSocket){
		case 'E':
			socketDeHabla = socket1;
			break;
		case 'H':
			socketDeEscucha = socket1;
			break;
		case 'I':
			printf("el socket %d es innecesario",socket1);
			close (socket1);
			return 0;
			break;
	}

	switch(*usoSegundoSocket){
		case 'E':
			socketDeHabla = socket2;
			break;
		case 'H':
			socketDeEscucha = socket2;
			break;
		case 'I':
			printf("el socket %d es innecesario",socket2);
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
