#include "cliente.h"
#include <pthread.h>

cliente_config* configCliente;
t_log* loggerCliente;

int main(int argc, char *argv[]){

	configCliente = leer_config_cliente(argv[1]);
	//loggerCliente = crear_logger_cliente(configCliente->ARCHIVO_LOG);
	pthread_t hiloConsola;
	pthread_create(&hiloConsola, 0, (void*)ejecutarConsola, NULL);
	pthread_join(hiloConsola,NULL);
	/*conexion_servidor();
	crear_socket();
	//configuracion_cliente = leer_config_cliente();
while(1){
	esperar_conexion();
}*/
	return 0;
}


/*void ejecutarConsola(){
	printf("ejecutando consola");
	char* leido;
	t_dest moduloDestino;
	t_header codOp;
	t_list* parametros;
	leido = readline(">");
	while(strcmp(leido,"cerrar")){
		if(sintaxisYSemanticaValida(leido,&codOp,&moduloDestino,&parametros)){
			//realizarEnvioMensaje(leido);
		}
		free(leido);
		leido = readline(">");
	}
	free(leido);
}*/

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
	int socketDeHabla = crear_conexion(configCliente->IP,configCliente->PUERTO);
	int socketDeEscucha = crear_conexion(configCliente->IP,configCliente->PUERTO);
	t_paquete* paquete = malloc(sizeof(t_paquete));
	paquete->codOp = paraMandar->operacion;
	paquete->buffer = serializarUnMensaje(paraMandar->parametros);
	void* a_enviar = malloc(sizeof(uint8_t) + paquete->buffer->size);
	int offset = 0;
	memcpy(a_enviar + offset, &(paquete->codOp), sizeof(uint8_t));
	offset = offset + sizeof(uint8_t);
	memcpy(a_enviar + offset, &(paquete->buffer->size), sizeof(uint32_t));
	offset = offset + sizeof(uint32_t);
	memcpy(a_enviar + offset, paquete->buffer->stream, paquete->buffer->size);
	offset = offset + paquete->buffer->size;
	send(socketDeHabla, a_enviar, paquete->buffer->size + sizeof(uint8_t), 0);
	free(a_enviar);
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
	free(paraMandar->destinatario);
	free(paraMandar);
}

void declararHiloYMeterloALaLista(t_list* hilosEnConsola, char* leido){
	t_header* codOp = malloc(sizeof(t_header));
	t_dest* destinatario = malloc(sizeof(t_dest));
	t_list* parametros = list_create();
	mensajeListoYSeparado* aMandar;
	pthread_t hiloParaUnMensaje;
	if(sintaxisYSemanticaValida(leido,codOp,destinatario,&parametros)){
		aMandar = malloc(sizeof(mensajeListoYSeparado));
		pthread_create(&hiloParaUnMensaje,0,(void*)procesarEntrada,aMandar);
	}
	list_add(hilosEnConsola,&hiloParaUnMensaje);

}

/*void realizarEnvioMensaje(char* leido){
	char* operacion;
	char* destinatario;
	t_list* parametros = list_create();
	dividirMensajeEnPartes(&operacion,&destinatario,&parametros, leido);

	mensajeASerializar* estructuraASerializar = malloc(sizeof(mensajeASerializar));
	estructuraASerializar->codOp

}*/
