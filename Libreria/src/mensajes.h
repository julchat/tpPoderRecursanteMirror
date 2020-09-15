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


typedef enum{
	CONSULTAR_RESTAURANTES = 0,
	SELECCIONAR_RESTAURANTES = 1,
	OBTENER_RESTAURANTE = 2,
	CONSULTAR_PLATOS = 3,
	CREAR_PEDIDO = 4,
	GUARDAR_PEDIDO = 5,
	AÑADIR_PLATO = 6,
	GUARDAR_PLATO = 7,
	CONFIRMAR_PEDIDO = 8,
	PLATO_LISTO = 9,
	CONSULTAR_PEDIDO = 10,
	OBTENER_PEDIDO = 11,
	FINALIZAR_PEDIDO = 12,
	TERMINAR_PEDIDO = 13,
	OBTENER_RECETA = 14,
	ERROR = 15
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
