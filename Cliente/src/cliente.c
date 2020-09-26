#include "cliente.h"
#include <pthread.h>

cliente_config* configCliente;
t_log* logger;

int main(int argc, char *argv[]){

	configCliente = leer_config_cliente(argv[1]);
	//logger = log_create("Cliente.log", "Cliente", 1, LOG_LEVEL_INFO);


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


void ejecutarConsola(){
	printf("ejecutando consola");
	char* leido;
	leido = readline(">");
	while(strcmp(leido,"cerrar")){
		if(sintaxisYSemanticaValida(leido)){
			//realizarEnvioMensaje(leido);
		}
		free(leido);
		leido = readline(">");
	}
	free(leido);
}

/*void realizarEnvioMensaje(char* leido){
	char* operacion;
	char* destinatario;
	t_list* parametros = list_create();
	dividirMensajeEnPartes(&operacion,&destinatario,&parametros, leido);

	mensajeASerializar* estructuraASerializar = malloc(sizeof(mensajeASerializar));
	estructuraASerializar->codOp

}*/
