# panorama_extended

Este repositorio es la implementación del preprocesador de modelos 3D a imagenes 2D mediante proyección cilíndrica presentado en el articulo [Ensemble of PANORAMA-based convolutional neural networks for 3D model classification and retrieval](https://www.sciencedirect.com/science/article/pii/S0097849317301978)

Este código forma parte del Trabajo de Fin de Grado de Alejandro Manzanares Lemus para el Grado de Ingeniería Informática de la Universidad de Granada

## Uso
```bash
make init
bin/panorama_extended [nombre del modelo] [ruta relativa al modelo 3D] [carpeta de salida PANORAMA extended] [carpeta de salida feature map]
```

This repository is the implementation of the preprocessor of 3D models to 2D images by cylindrical projection presented in the paper [Ensemble of PANORAMA-based convolutional neural networks for 3D model classification and retrieval](https://www.sciencedirect.com/science/article/pii/S0097849317301978)

This code is part of the Final Degree Project of Alejandro Manzanares Lemus for the Degree in Computer Science at the University of Granada.

Documentation is avaliable in: [https://alexmnzlms.github.io/panorama_extended/](https://alexmnzlms.github.io/panorama_extended/)

## Usage
```bash
make init
bin/panorama_extended_coloring [model name] [relive route to 3D model] [heatmap_X] [heatmap_Y] [heatmap_Z] [output folder colored 3D model]
```
