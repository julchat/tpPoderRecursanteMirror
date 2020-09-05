/*
 * libreriaCompartida.h
 *
 *  Created on: 5 sep. 2020
 *      Author: utnso
 */

#ifndef LIBRERIACOMPARTIDA_H_
#define LIBRERIACOMPARTIDA_H_

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>

int crear_conexion(char *ip, char* puerto);


#endif /* LIBRERIACOMPARTIDA_H_ */
