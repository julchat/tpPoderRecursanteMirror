#include "cliente.h"
#include "conexiones.c"
#include <pthread.h>
cliente_config* configCliente;
int main(int argc, char *argv[]){
	configCliente = leer_config_cliente(argv[1]);
	pthread_t hiloConsola;
	pthread_create(hiloConsola,0,ejecutarConsola,NULL);
	/*//iniciar_logger_config(); si uso esa funcion no se si sirve los argumentos que recibe el main!!!!!!
	config = config_create("Cliente.config");
	logger = log_create("Cliente.log", "Cliente", 1, LOG_LEVEL_INFO);

	conexion_servidor();
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
		if(sintaxisValida(leido) && semanticaValida(leido)){
			realizarEnvioMensaje(leido);
		}else{
			//aca quizas es logear en vez de printear
			printf("mensaje invalido");
		}
		free(leido);
		leido = readline(">");
	}
	free(leido);
}





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
