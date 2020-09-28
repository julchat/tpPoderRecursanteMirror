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
	char* leido;
	leido = readline(">");
	while(strcmp(leido,"cerrar")){
		procesarEntrada(leido);
		free(leido);
		leido = readline(">");
	}
	free(leido);
}

void procesarEntrada(char* mensajeLeido){
	t_header* codOp = malloc(sizeof(t_header));
	t_dest* destinatario = malloc(sizeof(t_dest));
	t_list* parametros = list_create();
	if(sintaxisYSemanticaValida(mensajeLeido,codOp,destinatario,&parametros)){
		//mandarMensaje();
	}
	free(codOp);
	free(destinatario);
	list_destroy_and_destroy_elements(parametros,free);
}
/*void realizarEnvioMensaje(char* leido){
	char* operacion;
	char* destinatario;
	t_list* parametros = list_create();
	dividirMensajeEnPartes(&operacion,&destinatario,&parametros, leido);

	mensajeASerializar* estructuraASerializar = malloc(sizeof(mensajeASerializar));
	estructuraASerializar->codOp

}*/
