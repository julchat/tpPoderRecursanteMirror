#include "auxiliaresListas.h"


bool estaEnLaLista(void* unElemento, t_list* unaLista){
	for(int i = 0; i<unaLista->elements_count;i++){
		if(list_get(unaLista,i) == unElemento){
			return 1;
		}
	}
	return 0;
}

/*
 * auxiliaresListas.c
 *
 *  Created on: 18 sep. 2020
 *      Author: utnso
 */


