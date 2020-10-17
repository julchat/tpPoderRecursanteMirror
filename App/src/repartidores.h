/*
 * repartidores.h
 *
 *  Created on: 17 oct. 2020
 *      Author: utnso
 */

#ifndef REPARTIDORES_H_
#define REPARTIDORES_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <semaphore.h>

#include "app.h"

typedef struct {

	t_list* repartidores;
	t_list* repartidoresReady;
	t_list* repartidoresDesocupados;
	t_list* hiloRepartidores;
	t_list* mapa;
	t_planificadores planificador;

}t_entrenadorApp;

#endif /* REPARTIDORES_H_ */
