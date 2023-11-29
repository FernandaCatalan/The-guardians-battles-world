# Proyecto 2: Juego de Guardianes

## Descripción del Proyecto

Este proyecto consiste en la implementación de un juego de guardianes donde los jugadores asumen el papel de guardianes con el objetivo de alcanzar el top de los mejores guardianes del reino. Las batallas se llevan a cabo en diferentes ciudades, y los jugadores acumulan puntos de victoria en función de los resultados de las batallas.

## Link video


## Reglas del Juego

### Niveles de Poder

- Cada guardián tiene un nivel de poder que determina su fuerza en las batallas.
- Solo un guardián puede tener un nivel de poder de 100.
- Solo tres guardianes pueden tener niveles de poder entre 90 y 99.

### Batallas

- Los jugadores pueden participar en batallas en diferentes ciudades del reino.
- Al ganar una batalla:
  - Contra un Maestro: +5 puntos.
  - Contra un Aprendiz: +3 puntos.

### Top de Guardianes

- El juego mantiene un top de guardianes que se actualiza según los puntos acumulados en las batallas.

### Restricciones

- Solo un guardián puede tener un nivel de poder de 100.
- Solo tres guardianes pueden tener niveles de poder entre 90 y 99.

### Juego
Al iniciar a jugar los usuarios pueden elegir entre diferentes opciones, como ver la lista de candidatos, información detallada del guardián, conocer el reino y participar en las batallas.

### Top Guardianes
El top de los guardianes de actualiza despues de cada batalla, los mejores se muestran en ella junto a sus puntos obtenidos.

## Funciones Especificas

### 1. verListaCandidatos
Mostrar la lista de candidatos cuyo nivel de poder está en el rango de 90 a 99.

### 2. verGuardian
Mostrar información detallada sobre un guardián específico.

### 3. conocerReino
Mostrar información general sobre el reino, incluyendo el número de ciudades y guardianes.

### 4. presenciarBatalla
Simular una batalla con un guardián retador en una ciudad seleccionada.

## Estructuras

### 1. Ciudad
Propósito: Estructura que representa una ciudad en el juego.
Atributos:
nombre: Nombre de la ciudad.

### 2. Guardian
Propósito: Estructura que representa a un guardián en el juego.
Atributos:
  -nombre: Nombre del guardián.
  -nivelPoder: Nivel de poder del guardián.
  -maestro: Nombre del maestro del guardián.
  -indiceCiudad: Índice de la ciudad en el grafo a la que el guardián pertenece.

### 3. Grafo
Propósito: Clase que representa el grafo del reino.
Métodos Principales:
  -agregarCiudad: Agrega una ciudad al grafo.
  -agregarConexion: Agrega una conexión entre dos ciudades en el grafo.
  -obtenerIndiceCiudad: Obtiene el índice de una ciudad dada su nombre.
  -agregarGuardian: Agrega un guardián al grafo.
  -mostrarListaAdyacencia: Muestra la lista de adyacencia del grafo.
  -mostrarMatrizAdyacencia: Muestra la matriz de adyacencia del grafo.
  -mostrarGuardianes: Muestra la información de los guardianes en el grafo.
  -verListaCandidatos: Muestra la lista de candidatos en el rango de nivel de poder especificado.
  -verGuardian: Muestra la información detallada de un guardián específico.
  -conocerReino: Muestra información general sobre el reino.
  -presenciarBatalla: Simula la presencia en una batalla.

### 4. Otras Funciones

-hayCamino: Método privado en la clase Grafo que verifica si hay un camino entre dos ciudades.
-existeCamino: Método público en la clase Grafo que verifica si existe un camino entre dos ciudades.
-agregarNuevoCamino: Método en la clase Grafo que agrega un nuevo camino entre dos ciudades.
-mostrarCaminosExistentes: Método en la clase Grafo que muestra los caminos existentes en el grafo.
-existeCaminoEntreCiudades: Método en la clase Grafo que verifica si existe un camino entre dos ciudades.








