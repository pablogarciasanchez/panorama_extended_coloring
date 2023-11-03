# panorama_extended_coloring

Este repositorio es la implementación del preprocesador de modelos 3D a imagenes 2D mediante proyección cilíndrica presentado en el articulo [Ensemble of PANORAMA-based convolutional neural networks for 3D model classification and retrieval](https://www.sciencedirect.com/science/article/pii/S0097849317301978)

Este código forma parte del Trabajo de Fin de Grado de Alejandro Manzanares Lemus para el Grado de Ingeniería Informática de la Universidad de Granada.

La funcionalidad extendida (panorama_extended_coloring) permite el coloreo de modelos 3D a partir de mapas de relevancia 2D.

## Uso
```bash
make init
bin/panorama_extended [nombre del modelo] [ruta relativa al modelo 3D] [ruta mapa de relevancia 2D X] [ruta mapa de relevancia 2D Y] [ruta mapa de relevancia 2D Z] [directorio salida modelo 3D coloreado]
```
