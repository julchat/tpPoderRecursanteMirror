/*
 * comandaLib.h
 *
 *  Created on: 22 sep. 2020
 *      Author: utnso
 */

#ifndef TP0_H_
#define TP0_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<commons/collections/list.h>

#include "utils.h"
#include "conexiones.h"
#include "mensajes.h"
#include <pthread.h>
typedef struct{

	int PUERTO_ESCUCHA;
	int TAMANIO_MEMORIA;
	int TAMANIO_SWAP;
	char* ALGORITMO_REEMPLAZO;
	char* ARCHIVO_LOG;

}comanda_config;

typedef struct{

	uint32_t size_nombre;
	char* nombre;

}t_nombre;

typedef struct {

	t_nombre nombre_restaurante;
	uint32_t id_pedido;

}t_guardar_pedido,t_obtener_pedido,t_confirmar_pedido,t_finalizar_pedido;

typedef struct{

	t_nombre nombre_restaurante;
	uint32_t id_pedido;
	t_nombre plato_a_agregar;
	uint32_t cantidad;

}t_guardar_plato;

typedef struct{

	t_nombre nombre_restaurante;
	uint32_t id_pedido;
	t_nombre plato_que_esta_listo;

}t_plato_listo;


comanda_config* leer_config_comanda(char*);
t_log* crear_logger_comanda(char*);

void* esperar_conexion(int,int*,t_log*);
int iniciar_servidor(int);
void* manejar_suscripciones(int*);
t_message* recibir_mensaje(int);

void* deserializar_guardar_pedido(void*);
void* deserializar_guardar_plato(void*);

#endif /* TP0_H_ */
