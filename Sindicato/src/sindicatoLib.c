#include "sindicatoLib.h"

void iniciar_logger_config(){

	t_config* config = config_create("./Sindicato.config");
	logger = log_create("Sindicato.log", "Sindicato", 1, LOG_LEVEL_INFO);

	sindicatoStruct->PUERTO_ESCUCHA = config_get_int_value(config,"PUERTO_ESCUCHA");
	sindicatoStruct->PUNTO_MONTAJE = config_get_string_value(config,"PUNTO_MONTAJE");

}
