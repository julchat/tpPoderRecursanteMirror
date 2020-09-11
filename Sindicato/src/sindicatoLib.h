/*
 * sindicatoLib.h
 *
 *  Created on: 6 sep. 2020
 *      Author: utnso
 */

#ifndef SINDICATOLIB_H_
#define SINDICATOLIB_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "mensajes.h"

typedef struct{

	int PUERTO_ESCUCHA;
	char* PUNTO_MONTAJE;

}sindicato_config;

//chequear las estructuras, en muchas seguro se pasan a t_list*
typedef struct{

	int cantidadCocineros;
	int posicionX;
	int posicionY;
	char* afinidadCocineros;
	char* platos;
	int precioPlatos;
	int cantidadHornos;

}info_restaurante;

typedef struct{

	char* estadoPedido;
	char* listaPlatos;
	int cantidadPlatos;
	int cantidadLista;
	int precioTotal;

}pedidos;

typedef struct{

	char* pasos;
	int tiempoPasos;

}receta;

typedef struct{

	info_restaurante infoRestaurante;
	pedidos pedidosRestaurante;
	receta recetaRestaurante;
}restaurante; // no se si es correcto hacer esto, de ultima se saca despues


sindicato_config* sindicatoStruct;
t_log* logger;

void iniciar_logger_config();

#endif /* SINDICATOLIB_H_ */
