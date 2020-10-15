/*
 * serializacion.h
 *
 *  Created on: 11 sep. 2020
 *      Author: utnso
 */

#ifndef SERIALIZACION_H_
#define SERIALIZACION_H_

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commons/collections/list.h>
#include "mensajes.h"


// Estructuras de mensajes

typedef struct {

	char* nombre_restaurante;
	int id_pedido;

}t_guardar_pedido,t_obtener_pedido,t_confirmar_pedido,t_finalizar_pedido;

typedef struct{

	char* nombre_restaurante;
	int id_pedido;
	char* plato_a_agregar;
	int cantidad;

}t_guardar_plato;

typedef struct{

	char* nombre_restaurante;
	int id_pedido;
	char* plato_que_esta_listo;

}t_plato_listo;

typedef struct{

}terminar_pedido;

typedef struct{

}obtener_receta;

typedef struct
{
	uint32_t size;
	void* stream;
} t_buffer;

typedef struct
{
	uint8_t codOp;
	t_buffer* buffer;
} t_paquete;

typedef struct
{
t_modulo moduloConectado;
bool escucha;
} t_identificadorSocket;
//t_identificadorSocket* deserealizarRespuestaHandshake(t_message*);
void* serializarConsultarPlatos();
void* serializarGuardarPedido();
void* serializarGuardarPlato();
void* serializarConfirmarPedido();
void* serializarObtenerPedido();
void* serializarObtenerRestaurante();
void* serializarPlatoListo();
void* serializarTerminarPedido();
void* serializarObtenerReceta();
//t_buffer* serializarUnMensaje(t_list* parametros);

#endif /* SERIALIZACION_H_ */
