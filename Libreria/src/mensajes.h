/*
 * mensajes.h
 *
 *  Created on: 11 sep. 2020
 *      Author: utnso
 */

#ifndef MENSAJES_H_
#define MENSAJES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

typedef struct{
	CONSULTAR_PLATOS, // @suppress("Type cannot be resolved")
	GUARDAR_PEDIDO,
	GUARDAR_PLATO,
	CONFIRMAR_PEDIDO,
	OBTENER_PEDIDO,
	OBTENER_RESTAURANTE,
	PLATO_LISTO,
	TERMINAR_PEDIDO,
	OBTENER_RECETA,
	ERROR;
}t_header;

typedef struct{
	t_header head;
	size_t size;
	void* content;
}t_message; //pensando en memoria

/*Funciones a implementar para manejo de mensajes
crear_mensaje
enviar_mensaje
recibir_mensaje
liberar_mensaje
  */
#endif /* MENSAJES_H_ */
