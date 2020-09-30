#include "cliente.h"
#include <pthread.h>

cliente_config* configCliente;
t_log* loggerCliente;

int main(int argc, char *argv[]){

	//configCliente = leer_config_cliente(argv[1]);
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
		wait(10);
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
	int socketDeHabla;
	int socketDeEscucha;
	switch(*(paraMandar->destinatario)){
		case(APP):
		socketDeHabla = crear_conexion(configCliente->IP_APP,configCliente->PUERTO_APP);
		socketDeEscucha = crear_conexion(configCliente->IP_APP,configCliente->PUERTO_APP);
		break;
		case(RESTAURANTE):
		socketDeHabla = crear_conexion(configCliente->IP_RESTAURANTE,configCliente->PUERTO_RESTAURANTE);
		socketDeEscucha = crear_conexion(configCliente->IP_RESTAURANTE,configCliente->PUERTO_RESTAURANTE);
		break;
		case(COMANDA):
		socketDeHabla = crear_conexion(configCliente->IP_COMANDA,configCliente->PUERTO_COMANDA);
		socketDeEscucha = crear_conexion(configCliente->IP_COMANDA,configCliente->PUERTO_COMANDA);
		break;
		case(SINDICATO):
		socketDeHabla = crear_conexion(configCliente->IP_SINDICATO,configCliente->PUERTO_SINDICATO);
		socketDeEscucha = crear_conexion(configCliente->IP_SINDICATO,configCliente->PUERTO_SINDICATO);
		break;
		case(CLIENTE):
		socketDeHabla = crear_conexion(configCliente->IP_APP,configCliente->PUERTO_APP);
		socketDeEscucha = crear_conexion(configCliente->IP_APP,configCliente->PUERTO_APP);
		break;
		case(ERR):
		//log?
		break;
	}

	free(paraMandar->operacion);
	free(paraMandar->destinatario);
	list_destroy_and_destroy_elements(paraMandar->parametros,free);
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
