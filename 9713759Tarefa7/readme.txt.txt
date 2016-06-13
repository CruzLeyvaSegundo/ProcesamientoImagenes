El script bordasAjedres no necesita parametros
por lo que para ejecutar el codigo solo basta con 
llamarlo como una funcion en la consola de matLab.
>>bordasAjedrez

En este script se han usado:
*)Detectores de lineas horizontales para encontrar las lineas verdes y 4 lineas rojas horizontales.
  (Los puntos extremos de estas lineas son de color verde)

*)Detectores de lineas verticales para encontrar las lineas azules y 3 lineas rojas verticales
  (Los puntos extremos de estas lineas son de color azul)

*)El algoritmo detector de borda zerocross para encontrar la penultima linea horizontal roja ubicada 
  al extremo superior de la imagen.(Los puntos extremos de estas lineas son uno de color verde y el otro de rojo)

*)El algoritmo detector de borda canny para encontrar ultima linea vertical roja ubicada 
  al extremo derecho de la imagen.(Los puntos extremos de estas lineas son uno de color azul y el otro de rojo)