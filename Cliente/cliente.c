#include "clienteLib.h"



int main(void){ // con argv y argc

char* nombre_prueba = "ejemplo.config"; // Hay que ver como setear esto desde los parametros del main o consola

configuracion_cliente = leer_config_cliente();


/*while(1){
	esperar_conexion();
}


void esperar_conexion(int socket_cliente){
int cliente = aceptar_cliente(socket_cliente);
log_info(logger,"Se conecto un cliente con el socket numero %d", cliente);
pthread_t hilo_nuevo_cliente;
	if(pthread_create(&hilo_nuevo_cliente,NULL,(void*)atender_cliente,(void*)cliente)!=0){
		log_error(logger,"Error al crear el hilo de cliente");
		}
	pthread_detach(hilo_nuevo_cliente);
	//close(cliente);
}


int aceptar_cliente(int servidor){
struct sockaddr_in direccion_cliente;
uint32_t tamanio_direccion = sizeof(struct sockaddr_in);
uint32_t cliente;
cliente = accept(servidor,(void*) &direccion_cliente, &tamanio_direccion);
return cliente;
}*/










































}
