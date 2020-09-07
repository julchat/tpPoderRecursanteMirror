#include "cliente.h"
//#include "libreriaCompartida.h"

int main(int argc, char *argv[]){

	//iniciar_logger_config(); si uso esa funcion no se si sirve los argumentos que recibe el main!!!!!!
	config = config_create("Cliente.config");
	logger = log_create("Cliente.log", "Cliente", 1, LOG_LEVEL_INFO);

	//configuracion_cliente = leer_config_cliente();

/*while(1){
	esperar_conexion();
}*/
	return 0;
}

int connect_to_server(char* host,int port, void*(*callback)()){

	int socket;
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(host);
	server_addr.sin_port = htons(port);

	socket = create_socket();
	if(connect(socket,(struct sockaddr *)&server_addr, sizeof(server_addr))< 0){
		perror("ERROR CONECTAR SERVIDOR");
		return -errno;
	}

	if(callback != NULL)
		callback();
	return socket;

}

int create_socket(){

	return socket(AF_INET, SOCK_STREAM, 0);
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
