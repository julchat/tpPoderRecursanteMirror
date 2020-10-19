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
//PRIMERO VAN LOS UINT32_Ts y DESPUÉS LOS PARES DE TAMAÑO DE CHAR* CON SU CHAR*

void* serializarSeleccionarRestaurante(t_seleccionarRestaurante info){
	void* content = malloc(sizeof(uint32_t) + sizeof(uint32_t) + strlen(info.nombreRestaurante)+1);
	int offset = 0;
	uint32_t tamanioRestaurante = strlen(info.nombreRestaurante) +1;
	memcpy(content, &info.idCliente, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(content, &tamanioRestaurante, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(content, info.nombreRestaurante, tamanioRestaurante);
	offset += tamanioRestaurante;
	free(info.nombreRestaurante);
	return content;
}
void* serializarObtenerRestaurante(char* nombreRestaurante){
	void* content = malloc(sizeof(uint32_t)+strlen(nombreRestaurante)+1);
	int offset = 0;
	uint32_t tamanioRestaurante = strlen(nombreRestaurante)+1;
	memcpy(content, &tamanioRestaurante, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(content, nombreRestaurante, tamanioRestaurante);
	offset += tamanioRestaurante;
	free(nombreRestaurante);
	return content;
}
void* serializarConsultarPlatos(char* nombreRestaurante){
	void* content = malloc(sizeof(uint32_t)+strlen(nombreRestaurante)+1);
	int offset = 0;
	uint32_t tamanioRestaurante = strlen(nombreRestaurante)+1;
	memcpy(content, &tamanioRestaurante, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(content, nombreRestaurante, tamanioRestaurante);
	offset += tamanioRestaurante;
	free(nombreRestaurante);
	return content;
}

void* serializarGuardarPedido(t_guardarPedido info){
	void* content = malloc(sizeof(uint32_t) + sizeof(uint32_t) + strlen(info.nombreRestaurante)+1);
	int offset = 0;
	uint32_t tamanioRestaurante = strlen(info.nombreRestaurante) +1;
	memcpy(content, &info.idPedido, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(content, &tamanioRestaurante, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(content, info.nombreRestaurante, tamanioRestaurante);
	offset += tamanioRestaurante;
	free(info.nombreRestaurante);
	return content;
}
void* serializarAniadirPlato(t_aniadirPlato info){
	void* content = malloc(sizeof(uint32_t) + sizeof(uint32_t) + strlen(info.plato)+1);
	int offset = 0;
	uint32_t tamanioPlato = strlen(info.plato) +1;
	memcpy(content, &info.idPedido, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(content, &tamanioPlato, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(content, info.plato, tamanioPlato);
	offset += tamanioPlato;
	free(info.plato);
	return content;
}
void* serializarGuardarPlato(t_guardarPlato info){
	void* content = malloc(sizeof(uint32_t) + strlen(info.nombreRestaurante)+1 + sizeof(uint32_t) + sizeof(uint32_t) + strlen(info.platoParaAgregar)+1 + sizeof(uint32_t));
	int offset = 0;
	uint32_t tamanioRestaurante = strlen(info.nombreRestaurante)+1;
	uint32_t tamanioPlato = strlen(info.platoParaAgregar)+1;
	memcpy(content, &info.idPedido, sizeof(uint32_t));
	offset+= sizeof(uint32_t);
	memcpy(content, &info.cantidad, sizeof(uint32_t));
	offset+= sizeof(uint32_t);
	memcpy(content, &tamanioRestaurante, sizeof(uint32_t));
	offset+= sizeof(uint32_t);
	memcpy(content, info.nombreRestaurante, tamanioRestaurante);
	offset+= tamanioRestaurante;
	memcpy(content, &tamanioPlato, sizeof(uint32_t));
	offset+= sizeof(uint32_t);
	memcpy(content, info.platoParaAgregar, tamanioPlato);
	offset+= tamanioPlato;
	free(info.nombreRestaurante);
	free(info.platoParaAgregar);
	return content;
}
void* serializarConfirmarPedido(t_confirmarPedido info){
	void* content = malloc(sizeof(uint32_t) + sizeof(uint32_t) + strlen(info.nombreRestaurante)+1);
	int offset = 0;
	uint32_t tamanioRestaurante = strlen(info.nombreRestaurante) +1;
	memcpy(content, &info.idPedido, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(content, &tamanioRestaurante, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(content, info.nombreRestaurante, tamanioRestaurante);
	offset += tamanioRestaurante;
	free(info.nombreRestaurante);
	return content;
}
void* serializarPlatoListo(t_platoListo info){
	void* content = malloc(sizeof(uint32_t) + sizeof(uint32_t) + strlen(info.nombreRestaurante)+1 + sizeof(uint32_t) + strlen(info.platoListo) + 1);
	int offset = 0;
	uint32_t tamanioRestaurante = strlen(info.nombreRestaurante)+1;
	uint32_t tamanioPlato = strlen(info.platoListo)+1;
	memcpy(content, &info.idPedido, sizeof(uint32_t));
	offset+= sizeof(uint32_t);
	memcpy(content, &tamanioRestaurante, sizeof(uint32_t));
	offset+= sizeof(uint32_t);
	memcpy(content, info.nombreRestaurante, tamanioRestaurante);
	offset+= tamanioRestaurante;
	memcpy(content, &tamanioPlato, sizeof(uint32_t));
	offset+= sizeof(uint32_t);
	memcpy(content, info.platoListo, tamanioPlato);
	offset+= tamanioPlato;
	free(info.nombreRestaurante);
	free(info.platoListo);
	return content;
}
void* serializarConsultarPedido(uint32_t idPedido){
	void* content = malloc(sizeof(uint32_t));
	int offset = 0;
	memcpy(content, &idPedido, sizeof(uint32_t));
	offset+= sizeof(uint32_t);
	return content;
}
void* serializarObtenerPedido(t_obtenerPedido info){
	void* content = malloc(sizeof(uint32_t) + sizeof(uint32_t) + strlen(info.nombreRestaurante)+1);
	int offset = 0;
	uint32_t tamanioRestaurante = strlen(info.nombreRestaurante) +1;
	memcpy(content, &info.idPedido, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(content, &tamanioRestaurante, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(content, info.nombreRestaurante, tamanioRestaurante);
	offset += tamanioRestaurante;
	free(info.nombreRestaurante);
	return content;
}
void* serializarFinalizarPedido(t_finalizarPedido info){
	void* content = malloc(sizeof(uint32_t) + sizeof(uint32_t) + strlen(info.nombreRestaurante)+1);
	int offset = 0;
	uint32_t tamanioRestaurante = strlen(info.nombreRestaurante) +1;
	memcpy(content, &info.idPedido, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(content, &tamanioRestaurante, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(content, info.nombreRestaurante, tamanioRestaurante);
	offset += tamanioRestaurante;
	free(info.nombreRestaurante);
	return content;
}
void* serializarTerminarPedido(t_terminarPedido info){
	void* content = malloc(sizeof(uint32_t) + sizeof(uint32_t) + strlen(info.nombreRestaurante)+1);
	int offset = 0;
	uint32_t tamanioRestaurante = strlen(info.nombreRestaurante) +1;
	memcpy(content, &info.idPedido, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(content, &tamanioRestaurante, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(content, info.nombreRestaurante, tamanioRestaurante);
	offset += tamanioRestaurante;
	free(info.nombreRestaurante);
	return content;
}
void* serializarObtenerReceta(char* nombrePlato){
	void* content = malloc(sizeof(uint32_t) + strlen(nombrePlato) +1);
	int offset = 0;
	uint32_t tamanioReceta = strlen(nombrePlato) +1;
	memcpy(content, &tamanioReceta, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(content, nombrePlato, tamanioReceta);
	offset += tamanioReceta;
	free(nombrePlato);
	return content;
}

/*t_buffer* serializarUnMensaje(t_list* parametros){
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
}*/

/*t_identificadorSocket* deserealizarRespuestaHandshake(t_message* paqueteRecibido){
	t_identificadorSocket* resultado = malloc(paqueteRecibido->size - sizeof(t_header));
	int offset = 0;
	memcpy(&resultado->moduloConectado, paqueteRecibido->content + offset, sizeof(t_modulo));
	offset += sizeof(t_modulo);
	memcpy(&resultado->escucha, paqueteRecibido->content + offset, sizeof(bool));
	offset += sizeof(bool);
	free(paqueteRecibido->content);
	free(paqueteRecibido);
	return resultado;
}*/

