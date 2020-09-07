# Trabajo Práctico 2c: PoderRecursante

# Integrantes
  - Maximiliano Berrutto
  - Cristian Cali
  - Juan Manuel Castagno
  - Ailen Eiroa
  - Victoria Guillosson

# Objetivos del Trabajo Práctico
Mediante la realización de este trabajo se espera que el alumno:
  - Adquiera conceptos prácticos del uso de las distintas herramientas de programación e interfaces (APIs) que brindan los sistemas operativos.
  - Entienda aspectos del diseño de un sistema operativo.
  - Afirme diversos conceptos teóricos de la materia mediante la implementación práctica de algunos de ellos.
  - Se familiarice con técnicas de programación de sistemas, como el empleo de makefiles, archivos de configuración y archivos de log.
  - Conozca con grado de detalle la operatoria de Linux mediante la utilización de un lenguaje de programación de relativamente bajo nivel como C.

# Hito 1: 12/09
  - Familiarizarse con Linux y su consola, el entorno de desarrollo y el repositorio.
  - Aplicar las Commons Libraries, principalmente las funciones para listas, archivos de conf y logs.
  - Definir el Protocolo de Comunicación.
  - Comenzar el desarrollo de las consolas del Cliente y Sindicato.

# Hito 2:  03/10
  - Proceso Cliente: Desarrollar consola y serialización de mensajes.
  - Proceso App: Desarrollar inicialización del módulo, permitir la planificación de forma FIFO.
  - Proceso Comanda: Desarrollar inicialización del módulo.
  - Proceso Sindicato: Finalizar consola del proceso.
  
# Hito 3: 24/10
  - Proceso Cliente: Finalización y cierre de detalles del módulo.
  - Proceso App: Desarrollo de planificación por HRRN y administración de movimientos de repartidores.
  - Proceso Restaurante: Desarrollar inicialización del módulo, permitir la planificación de forma FIFO sin Entrada/Salida.
  - Proceso Comanda: Implementación de sistema de memoria sin SWAP.
  - Proceso Sindicato: Desarrollar mensajes del módulo con datos de prueba (para permitir la inicialización del proceso Restaurante).

# Hito 4: 07/11
  - Proceso App: Finalización del módulo APP.
  - Proceso Restaurante: Desarrollar colas con Afinidad y RR.
  - Proceso Comanda: Comienzo de implementación de memoria con SWAP.
  - Proceso Sindicato: Manejo de estructura de árbol y del Bitmap. Permitir la escritura de archivos. Comienzo de desarrollo de lectura de archivo.

# Hito 5: 28/11 - 05/12 (o 12/12, a confirmar) - 19/12
  - Probar el TP en un entorno distribuido
  - Realizar pruebas intensivas
  - Finalizar el desarrollo de todos los procesos
  - Todos los componentes del TP ejecutan los requerimientos de forma integral, bajo escenarios de stress.
