#include "comandaLib.h"

comanda_config* leer_config_comanda(char* path){


	t_config* config_aux = config_create(path);
	comanda_config* config_comanda_aux = malloc(sizeof(comanda_config));

	config_comanda_aux->PUERTO_ESCUCHA = config_get_int_value(config_aux,"PUERTO_ESCUCHA");
	config_comanda_aux->TAMANIO_MEMORIA = config_get_int_value(config_aux,"TAMANIO_MEMORIA");
	config_comanda_aux->TAMANIO_SWAP = config_get_int_value(config_aux,"TAMANIO_SWAP");
	config_comanda_aux->ALGORITMO_REEMPLAZO = config_get_string_value(config_aux,"ALGORITMO_REEMPLAZO");
	config_comanda_aux->ARCHIVO_LOG = config_get_string_value(config_aux,"ARCHIVO_LOG");

	return config_comanda_aux;
}


t_log* crear_logger_comanda(char* path){

	t_log* log_aux = log_create(path,"comanda",1,LOG_LEVEL_INFO);
	return log_aux;
}


void* esperar_conexion(int puerto,int* socket_escucha, t_log* logger_comanda){ // ESTO ESTA FEO, NO ME TOMA LAS GLOBALES
	t_list* hilos = list_create();
	socket_escucha = malloc(sizeof(int));
	*socket_escucha = iniciar_servidor(puerto);
	int* socket_comanda = malloc(sizeof(int));
		log_info(logger_comanda, "SERVIDOR LEVANTADO! ESCUCHANDO EN %i",puerto);
		struct sockaddr cliente;
			socklen_t len = sizeof(cliente);
			do {
				*socket_comanda = accept(*socket_escucha, &cliente, &len);
				if (*socket_comanda > 0) {
					log_info(logger_comanda, "NUEVA CONEXIÓN!");
					crear_hilo_para_manejar_suscripciones(&hilos, *socket_comanda);
					//pthread_t thread;
					//pthread_create(&thread, NULL, (void*) manejar_suscripciones, socket_comanda);
				} else {
					log_error(logger_comanda, "ERROR ACEPTANDO CONEXIONES: %s", strerror(errno));
				}
			} while (1);
}


int iniciar_servidor(int puerto){
	int  socket_v;
	int val = 1;
	struct sockaddr_in servaddr;

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr =INADDR_ANY;
	servaddr.sin_port = htons(puerto);

	socket_v = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_v < 0) {
		char* error = strerror(errno);
		perror(error);
		free(error);
		return EXIT_FAILURE;
	}

	setsockopt(socket_v, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

	if (bind(socket_v,(struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
		return EXIT_FAILURE;
	}
	if (listen(socket_v, MAX_CLIENTS)< 0) {
		return EXIT_FAILURE;
	}

	return socket_v;
}


void* manejar_suscripciones(int* socket_envio) {
	//int socket_envio = (int) (socket);
	bool executing = true;
	mandar_tipo_socket(*socket_envio);
	while(executing){
		t_message* message = recibir_mensaje(*socket_envio);
		switch(message->head){
			case CONSULTAR_RESTAURANTES:{
				break;
			}

			case ANIADIR_PLATO:{
				break;
			}

			case FINALIZAR_PEDIDO:{
				break;
			}

			case CONSULTAR_PEDIDO:{
				break;
			}

			case CREAR_PEDIDO:{
				break;
			}

			case SELECCIONAR_RESTAURANTES:{
				break;
			}

			case CONSULTAR_PLATOS:{
				break;
			}

			case GUARDAR_PEDIDO:{
				t_guardar_pedido* guardar_pedido = deserializar_guardar_pedido(message->content);




				//acordarse de liberal los mallocs dentro de los deserializadores (TODOS)

				break;
			}

			case GUARDAR_PLATO:{
				break;
			}

			case CONFIRMAR_PEDIDO:{
				break;
			}

			case OBTENER_PEDIDO:{
				break;
			}

			case OBTENER_RESTAURANTE:{
				break;
			}

			case PLATO_LISTO:{
				break;
			}

			case TERMINAR_PEDIDO:{
				break;
			}

			case OBTENER_RECETA:{
				break;
			}

			case SUSCRIPCION:{
			printf("funciono la conexion me llego el mensaje del handshake");
				break;
			}

			default:
				break;
		}

		free(message->content);
		free(message);
	}
	return NULL;
}

t_message* recibir_mensaje(int socket){
	t_message * message = malloc(sizeof(t_message));

	int res = recv(socket,&message->size,sizeof(size_t),MSG_WAITALL);
	if (res <= 0 ){
		close(socket);
		free(message);
		return error(res);
	}

	message->size = message->size - sizeof(t_header);
	res = recv(socket,&message->head,sizeof(t_header),MSG_WAITALL);

	if(res <= 0){
		close(socket);
		free(message);
		return error(res);
	}

	message->content = malloc(message->size);
	res = recv(socket,message->content,message->size, MSG_WAITALL);

	if(res <= 0){
		close(socket);
		free(message->content);
		free(message);
		return error(res);
	}

	return message;
}

// Sirve para guardar_pedido - obtener_pedido - confirmar_pedido - finalizar_pedido pues comparten struct

void* deserializar_guardar_pedido(void* contenido){

	t_guardar_pedido* guardar_pedido = malloc(sizeof(t_guardar_pedido));

	void* stream = contenido;

	memcpy(&(guardar_pedido->nombre_restaurante.size_nombre),stream,sizeof(uint32_t));
	stream += sizeof(uint32_t);
	guardar_pedido->nombre_restaurante.nombre = malloc(guardar_pedido->nombre_restaurante.size_nombre);
	memcpy((guardar_pedido->nombre_restaurante.nombre),stream,guardar_pedido->nombre_restaurante.size_nombre);
	stream += guardar_pedido->nombre_restaurante.size_nombre;
	memcpy(&(guardar_pedido->id_pedido),stream,sizeof(uint32_t));
	stream += sizeof(uint32_t);

	return guardar_pedido;


}

void* deserializar_guardar_plato(void* contenido){

	t_guardar_plato* plato_guardado = malloc(sizeof(t_guardar_plato));

		void* stream = contenido;

			memcpy(&(plato_guardado->nombre_restaurante.size_nombre),stream,sizeof(uint32_t));
			stream += sizeof(uint32_t);
			plato_guardado->nombre_restaurante.nombre = malloc(plato_guardado->nombre_restaurante.size_nombre);
			memcpy(&(plato_guardado->nombre_restaurante.nombre),stream,plato_guardado->nombre_restaurante.size_nombre);
			stream += plato_guardado->nombre_restaurante.size_nombre;
			memcpy(&(plato_guardado->id_pedido),stream,sizeof(uint32_t));
			stream += sizeof(uint32_t);
			memcpy(&(plato_guardado->plato_a_agregar.size_nombre),stream,sizeof(uint32_t));
			stream += sizeof(uint32_t);
			plato_guardado->plato_a_agregar.nombre = malloc(plato_guardado->plato_a_agregar.size_nombre);
			memcpy(&(plato_guardado->plato_a_agregar.nombre),stream,plato_guardado->plato_a_agregar.size_nombre);
			stream += plato_guardado->plato_a_agregar.size_nombre;
			memcpy(&(plato_guardado->cantidad),stream,sizeof(uint32_t));
			stream += sizeof(uint32_t);

			return plato_guardado;

}

void* deserializar_plato_listo(void* contenido){

	t_plato_listo* plato_listo = malloc(sizeof(t_plato_listo));

	void* stream = contenido;

		memcpy(&(plato_listo->nombre_restaurante.size_nombre),stream,sizeof(uint32_t));
		stream += sizeof(uint32_t);
		plato_listo->nombre_restaurante.nombre = malloc(plato_listo->nombre_restaurante.size_nombre);
		memcpy(&(plato_listo->nombre_restaurante.nombre),stream,plato_listo->nombre_restaurante.size_nombre);
		stream += plato_listo->nombre_restaurante.size_nombre;
		memcpy(&(plato_listo->id_pedido),stream,sizeof(uint32_t));
		stream += sizeof(uint32_t);
		memcpy(&(plato_listo->plato_que_esta_listo.size_nombre),stream,sizeof(uint32_t));
		stream += sizeof(uint32_t);
		plato_listo->plato_que_esta_listo.nombre = malloc(plato_listo->plato_que_esta_listo.size_nombre);
		memcpy(&(plato_listo->plato_que_esta_listo.nombre),stream,plato_listo->plato_que_esta_listo.size_nombre);
		stream += plato_listo->plato_que_esta_listo.size_nombre;

		return plato_listo;
}

void crear_hilo_para_manejar_suscripciones(t_list** lista_hilos, int socket){
	pthread_t hilo_conectado;
	pthread_create(&hilo_conectado , NULL, (void*) manejar_suscripciones, &socket);
	list_add(*lista_hilos, &hilo_conectado);
}


t_list* inicializar_frames(int tamanio_memoria){
	int cantidad_frames = tamanio_memoria / 32;
	t_list* frames = list_create();
	int offset = 0;
	for(int i=0; i<cantidad_frames; i++){

		t_frame_en_memoria* un_frame = malloc(sizeof(t_frame_en_memoria));
		un_frame->inicio = memoria_principal + offset;
		un_frame->pagina_a_la_que_pertenece = NULL;
		list_add(frames,un_frame);
	}
	printf("La memoria principal comienza en %i,el ultimo frame está en %i",(int)memoria_principal);
	return frames;
}


