/*
 * ClienteLib.h
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#ifndef TP0_H_
#define TP0_H_

config_cliente configuracion_cliente;

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "utils.h"
#include "clienteLib.c"
#include "estructuras.h"
#include "../libreriaGeneral.h"

t_log* iniciar_logger(void);
t_config* leer_config_cliente();
void leer_consola(t_log*);
void paquete(int);
void terminar_programa(int, t_log*, t_config*);

#endif /* TP0_H_ */
