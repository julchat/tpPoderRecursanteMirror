#include "cliente.h"
#include <pthread.h>

cliente_config* configCliente;
t_log* logger_config;

int main(int argc, char *argv[]){

	configCliente = leer_config_cliente(argv[1]);
	//logger_config = log_create("Cliente.log", "Cliente", 1, LOG_LEVEL_INFO);


	pthread_t hiloConsola;
	pthread_create(&hiloConsola,0,ejecutarConsola,NULL);


	/*conexion_servidor();
	crear_socket();

	//configuracion_cliente = leer_config_cliente();

while(1){
	esperar_conexion();
}*/


	return 0;
}


void ejecutarConsola(){
	char* leido;
	leido = readline(">");
	while(strcmp(leido,"")){
		if(sintaxisYSemanticaValida(leido)){
			//realizarEnvioMensaje(leido);
		}
		free(leido);
		leido = readline(">");
	}
	free(leido);
}






/*void wait_connection(int socket_client){

	int cliente = accept_client(socket_client);
	log_info(logger, "Se conecto un Cliente con el socket numero %d:", cliente);

	pthread_t client_thread;
	if(pthread_create(&client_thread, NULL, (void*)atender_cliente, (void*)cliente)!=0){
		log_error(logger, "Error al crear el hilo del cliente");
	}
	pthread_detach(client_thread);
	//close(cliente);
}

int accept_client(int servidor){
	struct sockaddr_in client_addr;
	uint32_t addr_size = sizeof(struct sockaddr_in);
	uint32_t cliente;

	cliente = accept(servidor,(void*) &client_addr, &addr_size);
	return cliente;
}*/
