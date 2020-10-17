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
	ANIADIR_PLATO = 6,
	GUARDAR_PLATO = 7,
	CONFIRMAR_PEDIDO = 8,
	PLATO_LISTO = 9,
	CONSULTAR_PEDIDO = 10,
	OBTENER_PEDIDO = 11,
	FINALIZAR_PEDIDO = 12,
	TERMINAR_PEDIDO = 13,
	OBTENER_RECETA = 14,
	ERROR = 15,
	SUSCRIPCION = 16,
	SIN_CONEXION = 17
}t_header;

typedef struct{
	t_header head;
	size_t size;
	void* content;
}t_message;

typedef struct {
	t_header idColaSindicato;
	pid_t idSuscriptor;
} suscripcion;

typedef enum{
	APP = 0,
	RESTAURANTE = 1,
	SINDICATO = 2,
	COMANDA = 3,
	CLIENTE = 4,
	ERR = 5
}t_modulo;

//<<<<<<< HEAD


//=======
/*Funciones a implementar para manejo de mensajes
crear_mensaje
enviar_mensaje
recibir_mensaje
liberar_mensaje
  */
t_message* recibirMensaje(int socket);
t_message* crearMensaje(t_header head, size_t size,const void* content);
t_message* error(int res);
void liberarMensaje(t_message* message);
int enviarMensaje(int socket, t_header head,const void* content, size_t size);
//>>>>>>> 42a75a133c6244892ee4655a8bd21b6abcab1025
#endif /* MENSAJES_H_ */
