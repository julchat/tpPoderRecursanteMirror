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
#include<readline/readline.h>

#include "utils.h"
#include "conexiones.h"

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

cliente_config* clientStruct;

//void iniciar_logger_config();

t_log* iniciar_logger(void);
cliente_config* leer_config_cliente();
void leer_consola(t_log*);
void paquete(int);
void terminar_programa(int, t_log*, t_config*);

#endif /* TP0_H_ */
