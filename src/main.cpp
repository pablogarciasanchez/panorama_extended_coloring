#include "mesh3d.h"
#include <map>
#include <string>

/** @file main.cpp
 * 	@author [Alejandro Manzanares Lemus](https://github.com/Alexmnzlms)
 */

// Estructura para los datos asociados a cada muestra
struct DatosMuestra {
    double Edad;
    double Edad_predicha;
    double Diferencia;
    int Indicador;
    double ponderacionX;
    double ponderacionY;
    double ponderacionZ;
};

int main(int argc, char * argv[]) {

	srand (time(NULL));

	if(argc != 7){
		std::cout << "Wrong parameters" << std::endl;
		std::cout << "bin/panorama_extended [name] [relive route to 3D model]"
		<< " [relive route to saliency map X]" << " [route to saliency map Y] " << " [route to saliency map Y] "
		<< "[output folder]" << std::endl;
		exit(-1);
	}

	std::string name = argv[1];
	std::string path = argv[2];
	std::string path_X = argv[3];
	std::string path_Y = argv[4];
    std::string path_Z = argv[5];
	std::string output = argv[6];

	std::cout << "Loading " << name << "\tPath: " << path << "..." << std::endl;
    
    // Nombre del archivo
    std::string filename = "./predicciones.csv";

    // Abre el archivo para lectura
    std::ifstream inFile(filename);

    // Verifica si el archivo se abrió correctamente
    if (!inFile) {
        std::cerr << "No se pudo abrir el archivo " << filename << std::endl;
        return 1;
    }
    
    // Mapa para relacionar cada nombre de muestra con sus datos
    std::map<std::string, DatosMuestra> diccionario;

    // Leer el archivo línea por línea
    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream stream(line);
        std::string token;

        // Leer el nombre de la muestra
        std::getline(stream, token, ',');
        std::string nombre_muestra = token;
        
        // Leer el resto de los datos
        DatosMuestra datos;
        stream >> datos.Edad;
        stream.ignore(1, ',');
        stream >> datos.Edad_predicha;
        stream.ignore(1, ',');
        stream >> datos.Diferencia;
        stream.ignore(1, ',');
        stream >> datos.Indicador;
        stream.ignore(1, ',');
        stream >> datos.ponderacionX;
        stream.ignore(1, ',');
        stream >> datos.ponderacionY;
        stream.ignore(1, ',');
        stream >> datos.ponderacionZ;

        // Insertar los datos en el diccionario
        diccionario[nombre_muestra] = datos;
    }
    
    // Cierra el archivo
    inFile.close();

    // Ahora puedes acceder a los datos usando el nombre de la muestra
    DatosMuestra muestra = diccionario[name];
    std::cout << "Nombre: " << name << std::endl;
    std::cout << "Edad: " << muestra.Edad << std::endl;
    std::cout << "Edad_predicha: " << muestra.Edad_predicha << std::endl;
    std::cout << "Importancia de la vista X: " << muestra.ponderacionX << std::endl;
    std::cout << "Importancia de la vista Y: " << muestra.ponderacionY << std::endl;
    std::cout << "Importancia de la vista Z: " << muestra.ponderacionZ << std::endl;
    
    Axis axis;
    
    Mesh3D mallaX(name, path, true);  // Carga de la malla desde el archivo original para vista X
    if (mallaX.num_vertexs() > 0) {
        std::cout << "Loaded " << mallaX.get_name() << std::endl;

        std::cout << "Coloring: " << path_X << "..." << std::endl;
        axis = X;
        mallaX.color_3d_model(path_X, axis);
        mallaX.export_obj(output + "/" + name + "_X_colored.obj", true);
    
    }
    
    // Coloreando vista Y
    Mesh3D mallaY(name, path, true);  // Carga de la malla desde el archivo original para vista Y
    if (mallaY.num_vertexs() > 0) {
        std::cout << "Loaded " << mallaY.get_name() << std::endl;

        std::cout << "Coloring: " << path_Y << "..." << std::endl;
        axis = Y;
        mallaY.color_3d_model(path_Y, axis);
        mallaY.export_obj(output + "/" + name + "_Y_colored.obj", true);
    }
    
    // Coloreando vista Z
    Mesh3D mallaZ(name, path, true);  // Carga de la malla desde el archivo original para vista Z
    if (mallaZ.num_vertexs() > 0) {
        std::cout << "Loaded " << mallaZ.get_name() << std::endl;

        std::cout << "Coloring: " << path_Z << "..." << std::endl;
        axis = Z;
        mallaZ.color_3d_model(path_Z, axis);
        mallaZ.export_obj(output + "/" + name + "_Z_colored.obj", true);
    }
    
    Mesh3D combinedMesh(name,path,true);
    combinedMesh.combine_mesh(mallaX, mallaY, mallaZ, muestra.ponderacionX, muestra.ponderacionY, muestra.ponderacionZ);
    combinedMesh.export_obj(output + "/" + name + "_combined_colored.obj", true);
    
	return 0;
}
