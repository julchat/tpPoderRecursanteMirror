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

	char* IP;
	char* PUERTO;
	char* ARCHIVO_LOG;
	int POSICION_X;
	int POSICION_Y;
	char* ID_CLIENTE;
}cliente_config;

//cliente_config* clientStruct;



typedef struct{
	t_modulo idModulo;
	uint32_t idCliente;
	uint32_t posX;
	uint32_t posY;
}handshakeStruct;

void* serializarUnMensaje(t_list* parametros, int* tamanio);
int crear_conexion(char *ip, char* puerto);
t_log* crear_logger_cliente(char*);
cliente_config* leer_config_cliente(char*);
t_list* dividirMensajeEnPartes(char** operacion,char** destinatario,char* mensaje);
void terminar_programa(int, t_log*, t_config*);
bool sintaxisYSemanticaValida(char* mensaje, t_header* codigoOperacion, t_modulo* moduloDestino, t_list** parametros, t_log loggerCliente);
bool validarMatcheoOperacion(char* operacion, t_header* codigoPasadoPorReferencia);
bool validarMatcheoDestinatario(char* destinatario, t_modulo* moduloALlenar);
void obtenerModulosCompatiblesYcantParametrosRequerida(t_header codigoOperacion,t_modulo moduloDestino,
t_list** modulosCompatibles, int* cantParametros);
bool validarSemanticaMensaje(t_list* modulosCompatibles, int cantParametros, t_modulo destinatario, t_list* parametros, t_log loggerCliente);
bool estaEnLaLista(t_modulo* unElemento, t_list* unaLista);
t_identificadorSocket* deserealizarRespuestaHandshake(t_message* paqueteRecibido);
//t_message* recibirMensaje(int socket);
void validarConexion(int socket1, int socket2);
#endif /* TP0_H_ */
