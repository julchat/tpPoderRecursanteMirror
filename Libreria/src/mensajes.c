#include "mensajes.h"

/*
 * mensajes.c
 *
 *  Created on: 11 sep. 2020
 *      Author: utnso
 */

int enviarMensaje(int socket, t_header head,const void* content, size_t size){
	t_message* message = crearMensaje(head,size,content);
	int res = send(socket, &(message->size) , sizeof(size_t), 0);

	if(res >= 0){
		void* buffer = malloc(message->size);
		memcpy(buffer,&message->head,sizeof(t_header));
		memcpy(buffer + sizeof(t_header),message->content,size);
		res = send(socket,buffer,message->size,0);
		if(res <0){
			perror("ERROR ENVIANDO MENSAJE");
			res = -errno;
		}
		free(buffer);
	}else{
		perror("ERROR ENVIANDO MENSAJE");
		res = -errno;
	}
	liberarMensaje(message);

	return res;

}

void liberarMensaje(t_message* message){
	if(message != NULL){
		if(message->content != NULL){
			free(message->content);
		}
		free(message);
	}
}

t_message* recibirMensaje(int socket){
	t_message * message = malloc(sizeof(t_message));

	int res = recv(socket,&message->size,sizeof(size_t),MSG_WAITALL);
	if (res <= 0 ){
		close(socket);
		free(message);
		return error(res);
	}

	void* buffer = malloc(message->size);
	res = recv(socket,buffer,message->size,MSG_WAITALL);


	if(res <= 0){
		close(socket);
		free(message);
		free(buffer);
		return error(res);
	}

	message->content = calloc(message->size - sizeof(t_header)+1,1);
	memcpy(&message->head, buffer, sizeof(t_header));
	memcpy(message->content,buffer + sizeof(t_header),message->size - sizeof(t_header));
	message->size = message->size - sizeof(t_header);

	free(buffer);
	return message;
}

t_message* crearMensaje(t_header head, size_t size,const void* content){
	t_message* message = (t_message*)malloc(sizeof(t_message));
	message->head = head;
	message->content = malloc(size);
	message->size = size + sizeof(head);

	memset(message->content, 0, size);
	memcpy(message->content,content,size);

	return message;
}

t_message* error(int res){
	t_header header = res == 0? SIN_CONEXION : ERROR;
	int32_t err = -errno;
	return crearMensaje(header,sizeof(err),&err);
}
/*int send_status(int sock,t_header head, int status){
	return send_message(sock,status,&status,sizeof(int32_t));
}
int get_status(t_message* message){
	return *((int*)message->content);
}*/

