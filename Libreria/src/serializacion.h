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
#include "conexiones.h"


// Estructuras de mensajes

typedef struct{
	uint32_t idCliente;
	char* nombreRestaurante;
}t_seleccionarRestaurante;

typedef struct{
	uint32_t idPedido;
	char* plato;
}t_aniadirPlato;


typedef struct {
	uint32_t idPedido;
	char* nombreRestaurante;
}t_guardarPedido,t_obtenerPedido,t_confirmarPedido,t_finalizarPedido, t_terminarPedido;

typedef struct{
	uint32_t idPedido;
	uint32_t cantidad;
	char* nombreRestaurante;
	char* platoParaAgregar;


}t_guardarPlato;

typedef struct{
	uint32_t idPedido;
	char* nombreRestaurante;
	char* platoListo;

}t_platoListo;

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
void* serializarSeleccionarRestaurante(t_seleccionarRestaurante);
void* serializarObtenerRestaurante(char* nombreRestaurante);
void* serializarConsultarPlatos(char* nombreRestaurante);
void* serializarGuardarPedido(t_guardarPedido);
void* serializarAniadirPlato(t_aniadirPlato);
void* serializarGuardarPlato(t_guardarPlato);
void* serializarConfirmarPedido(t_confirmarPedido);
void* serializarPlatoListo(t_platoListo);
void* serializarConsultarPedido(uint32_t idPedido);
void* serializarObtenerPedido(t_obtenerPedido);
void* serializarFinalizarPedido(t_finalizarPedido);
void* serializarTerminarPedido(t_terminarPedido);
void* serializarObtenerReceta(char* nombrePlato);
//t_buffer* serializarUnMensaje(t_list* parametros);

#endif /* SERIALIZACION_H_ */
