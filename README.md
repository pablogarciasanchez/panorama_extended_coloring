# panorama_extended_coloring

Este repositorio es un fork de [panorama_extended](https://github.com/Alexmnzlms/panorama_extended), para colorear modelos 3D a partir de los mapas de relevancia 2D de cada una de sus vistas.

## Uso

El siguiente ejemplo muestra cómo inicializar y ejecutar el script panorama_extended para colorear un modelo 3D basado en mapas de relevancia 2D

```bash
make init
bin/panorama_extended [nombre del modelo] [ruta relativa al modelo 3D] [ruta mapa de relevancia 2D X] [ruta mapa de relevancia 2D Y] [ruta mapa de relevancia 2D Z] [directorio salida modelo 3D coloreado]
```

## Ejemplo

```bash
make init
bin/panorama_extended 14_Izq ./14_Izq.obj ./Smoothgrad_cnnX.png ./Smoothgrad_cnnY.png ./Smoothgrad_cnnZ.png 14_Izq_coloreado
```
