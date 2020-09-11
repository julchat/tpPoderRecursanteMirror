#include "sindicato.h"

int main(void){

	iniciar_logger_config();

	pthread_t consultarPlatosThread;
	pthread_t guardarPedidoThread;
	pthread_t guardarPlatoThread;
	pthread_t confirmarPedidoThread;
	pthread_t obtenerPedidoThread;
	pthread_t obtenerRestauranteThread;
	pthread_t platoListoThread;
	pthread_t terminarPedidoThread;
	pthread_t obtenerRecetaThread;

	//pthread_create(&consultarPlatosThread, NULL, (void*) funcion, (void*) CONSULTAR_PLATOS);
	//pthread_detach(consultarPlatosThread);

	// no sigo completando xq no estoy segura si se usa multihilos o no.

	terminarPrograma();
	return EXIT_SUCCESS;

}

void terminarPrograma(){

	close(socket);
	log_destroy(logger);

}
