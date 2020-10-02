#include "serializacion.h"
/*
 * serializacion.c
 *
 *  Created on: 11 sep. 2020
 *      Author: utnso
 */

//void* serializarConsultarPlatos(consultar_platos parametros){

	//int bytes_escritos = 0;
	//void* contenido = malloc(sizeof(uint32_t)/*(*n)*/); n cant de parametros de la estructura

	//memcpy (contenido + bytes_escritos, &parametros/*(.n1)*/, sizeof(uint32_t)); //n1 parametro de la estrc
	//bytes_escritos += sizeof(uint32_t);

	//return contenido;
//}
//void* serializarGuardarPedido(){

//}
//void* serializarGuardarPlato(){

//}
//void* serializarConfirmarPedido(){

//}
//void* serializarObtenerPedido(){

//}
//void* serializarObtenerRestaurante(){

//}
//void* serializarPlatoListo(){

//}
///void* serializarTerminarPedido(){

//}
//void* serializarObtenerReceta(){

//}

t_buffer* serializarUnMensaje(t_list* parametros){
	t_buffer* buffer = malloc(sizeof(t_buffer));
	int size = 0;
	char* parametro;
	uint16_t tamanioParametro;
	for(int i = 0; i<parametros->elements_count; i++){
		size += strlen(list_get(parametros,i))+1;
	}
	buffer->size = size;
	void* stream = malloc(buffer->size);
	int offset = 0;
	for(int j = 0; j<parametros->elements_count;j++){
		parametro = list_get(parametros,j);
		tamanioParametro = strlen(parametro)+1;
		memcpy(stream + offset, &tamanioParametro, sizeof(uint16_t));
		offset = offset + sizeof(uint16_t);
		memcpy(stream + offset, parametro, strlen(parametro)+1);
		offset = offset + strlen(parametro)+1;
	}
	buffer->stream= stream;
	list_destroy_and_destroy_elements(parametros,free);
	return buffer;
}



