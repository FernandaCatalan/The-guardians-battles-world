# Proyecto 2: Juego de Guardianes

## Descripción del Proyecto

Este proyecto consiste en la implementación de un juego de guardianes donde los jugadores asumen el papel de guardianes con el objetivo de alcanzar el top de los mejores guardianes del reino. Las batallas se llevan a cabo en diferentes ciudades, y los jugadores acumulan puntos de victoria en función de los resultados de las batallas.

## Link video
https://youtu.be/j1JFd91ov4k

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

## Funcionalidades

### Grafo

#### Clase `Grafo`

La clase `Grafo` representa el reino y proporciona las siguientes funcionalidades:

- **Agregar Ciudad:** Agrega una ciudad al reino con su lista de guardianes.
- **Obtener Guardianes de una Ciudad:** Obtiene la lista de guardianes asociados a una ciudad.
- **Obtener Ciudades:** Obtiene la lista de todas las ciudades en el reino.
- **Agregar Camino:** Agrega un camino entre dos ciudades con una distancia específica.
- **Buscar Guardian:** Busca un guardián en el reino.

#### Método `conocerReino`

Muestra un menú interactivo que permite al usuario explorar el reino, viajar entre ciudades y consultar los caminos existentes.

### Árboles

#### Clase `ArbolGeneral`

Representa un árbol general que organiza a los guardianes según sus relaciones maestro-aprendiz.

- **Insertar Guardián:** Inserta un guardián en el árbol.
- **Buscar Guardián:** Busca un guardián en el árbol.
- **Recorrer en Profundidad:** Realiza un recorrido en profundidad del árbol.

#### Clase `ArbolBinario`

Representa un árbol binario que organiza a los guardianes.

- **Insertar Guardián:** Inserta un guardián en el árbol.
- **Buscar Guardián:** Busca un guardián en el árbol.
- **Recorrer en Orden:** Realiza un recorrido en orden del árbol.

### Guardianes y Batallas

- **Estructura `Guardian`:** Almacena información sobre un guardián, incluyendo nombre, nivel de poder, maestro y ciudad.
- **Función `leerGuardianesDesdeArchivo`:** Lee los guardianes desde un archivo y los almacena en un mapa.
- **Función `presenciarBatalla`:** Simula una batalla entre dos guardianes y actualiza sus niveles de poder.