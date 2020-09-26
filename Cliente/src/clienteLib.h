/*
 * ClienteLib.h
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#ifndef TP0_H_
#define TP0_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include <commons/collections/list.h>

#include "utils.h"
#include "conexiones.h"
#include "mensajes.h"

typedef struct {

	char* IP_COMANDA;
	int PUERTO_COMANDA;
	char* IP_RESTAURANTE;
	int PUERTO_RESTAURANTE;
	char* IP_SINDICATO;
	int PUERTO_SINDICATO;
	char* IP_APP;
	int PUERTO_APP;
	char* ARCHIVO_LOG;
	int POSICION_X;
	int POSICION_Y;

}cliente_config;

//cliente_config* clientStruct;

typedef enum{
	APP = 0,
	RESTAURANTE = 1,
	SINDICATO = 2,
	COMANDA = 3,
	CLIENTE = 4,
	ERR = 5
}t_dest;

typedef struct{
	t_header codOp;
	t_dest destinatario;
	char** parametros;
}parserMensaje;


t_log* crear_logger_cliente(char*);
cliente_config* leer_config_cliente(char*);
void leer_consola(t_log*);
void paquete(int);
void terminar_programa(int, t_log*, t_config*);
bool sintaxisYSemanticaValida(char* mensaje);
bool validarMatcheoOperacion(char* operacion, t_header* codigoPasadoPorReferencia);
bool validarMatcheoDestinatario(char* destinatario, t_dest* moduloALlenar);
void obtenerModulosCompatiblesYcantParametrosRequerida(t_header codigoOperacion,t_dest moduloDestino,
t_list** modulosCompatibles, int* cantParametros);
bool validarSemanticaMensaje(t_list* modulosCompatibles, int cantParametros, t_dest destinatario, t_list* parametros);
void dividirMensajeEnPartes(char** operacion,char** destinatario,t_list** parametros, char*);
bool estaEnLaLista(t_dest* unElemento, t_list* unaLista);
#endif /* TP0_H_ */
