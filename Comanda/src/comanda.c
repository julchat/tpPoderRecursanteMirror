#include "comanda.h"

// PARA EL QUE ME QUIERA TOCAR LA CONVENCION DE GUIONES BAJOS
// https://em.wattpad.com/69a0e4855c827e7debd7ced78f41ca7002308c6a/68747470733a2f2f73332e616d617a6f6e6177732e636f6d2f776174747061642d6d656469612d736572766963652f53746f7279496d6167652f4f627a47794e5f4a2d6a584756513d3d2d3134352e313630656430353730626130663665303930363034393734353930352e6a7067?s=fit&w=720&h=720
// ESTA AVISADO - Juanma


int main(int argc, char *argv[]){


	comanda_configuracion = leer_config_comanda(argv[1]);
	logger_comanda = crear_logger_comanda(comanda_configuracion->ARCHIVO_LOG);


	void* memoria_principal = malloc(sizeof(comanda_configuracion->TAMANIO_MEMORIA));
	void* memoria_swap = malloc(sizeof(comanda_configuracion->TAMANIO_SWAP));

	//t_list* restaurantes = list_create();

	esperar_conexion(comanda_configuracion->PUERTO_ESCUCHA,&socket_escucha,logger_comanda);





	return 0;
}
