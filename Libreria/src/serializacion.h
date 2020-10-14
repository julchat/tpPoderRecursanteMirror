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

typedef struct{

}consultar_platos;

typedef struct{

}guardar_pedido;

typedef struct{

}guardar_plato;

typedef struct{

}confirmar_pedido;

typedef struct{

}obtener_pedido;

typedef struct{

}obtener_restaurante;

typedef struct{

}plato_listo;

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
t_identificadorSocket* deserealizarRespuestaHandshake(t_paquete*);
void* serializarConsultarPlatos();
void* serializarGuardarPedido();
void* serializarGuardarPlato();
void* serializarConfirmarPedido();
void* serializarObtenerPedido();
void* serializarObtenerRestaurante();
void* serializarPlatoListo();
void* serializarTerminarPedido();
void* serializarObtenerReceta();
t_buffer* serializarUnMensaje(t_list* parametros);

#endif /* SERIALIZACION_H_ */
