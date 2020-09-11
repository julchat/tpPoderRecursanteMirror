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

void* serializarConsultarPlatos();
void* serializarGuardarPedido();
void* serializarGuardarPlato();
void* serializarConfirmarPedido();
void* serializarObtenerPedido();
void* serializarObtenerRestaurante();
void* serializarPlatoListo();
void* serializarTerminarPedido();
void* serializarObtenerReceta();

#endif /* SERIALIZACION_H_ */
