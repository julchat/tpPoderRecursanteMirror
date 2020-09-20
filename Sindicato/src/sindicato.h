#ifndef SINDICATO_H_
#define SINDICATO_H_


#include "time.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/socket.h>

#include <commons/config.h>
#include <commons/log.h>
#include <commons/collections/list.h>
#include <commons/string.h>
#include <commons/bitarray.h>
#include <commons/collections/queue.h>

#include "sindicatoLib.h"

int socketEscucha;

void* colaServidor();
void* colaCliente(void* cola);
void* manejarSuscripciones();
void terminarPrograma();

#endif /* SINDICATO_H_ */
