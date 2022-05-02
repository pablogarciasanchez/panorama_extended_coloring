#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED
#include <fstream>
#include <cstdio>
#include <stdio.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "panorama.h"

/** @file malla3d.h
 *  @brief Implementation of class Malla3D
 * 	@author [Alejandro Manzanares Lemus](https://github.com/Alexmnzlms)
 * 
 */

/** @brief This class contains the information about the 3D model
 * 
 * This class implements the functions related to the PANORAMA representation 
 * (extended version) and the SYNPAN pose estimation algorithm.
 * 
 * It provides the methods for loading and exporting models, as well as the 
 * necessary transformations on the 3D mesh.
 * 
 * Main functionality is described in @link calculate_panorama() @endlink and
 * @link mesh_pose_norm() @endlink
 * 
 * @note PANORAMA extended method is extended by the use of the NDM gradient. 
 * However, for simplicity in the documentation and implementation we use an 
 * attribute \link panorama_extended \endlink that contains the 
 * PANORAMA representation extended 1.5 times. Any reference to the 
 * PANORAMA or PANORAMA extended representation is understood to mean 
 * PANORAMA extended in the sense of the use of the GNDM feature map
 * regardless of whether the size is extended or not..
 *  
 * 
 * @see Ensemble of PANORAMA-based convolutional neural networks for 3D model 
 * classification and retrieval @cite SFIKAS2018208
 */

class Malla3D{
public:
	Malla3D();
	Malla3D(const std::string path);
	~Malla3D();
	void export_obj(const std::string path);
	void rotate_mesh(Axis axis_rot, float angle);
	void calculate_panorama(Map map, Axis axis, float precision, int power = 4);
	void export_panorama(Map map, Axis axis, std::string output, bool extended = true);
	void mesh_pose_norm(Axis rot, Map map, Axis axis, std::string output, int angle_pass = 1,
						float precision = 1, int power = 4);
						
private:
	/** @brief Vertexs of the mesh */
	std::vector<glm::vec3> vertexs; 
	/** @brief Faces of the mesh */
	std::vector<std::vector<int>> facesIndex; 
	/** @brief Mesh faces divided according to height and sector to which they belong */
	std::vector<std::vector<std::vector<int>>> facesIndex_filter; 

	/** @brief PANORAMA representation of loaded mesh */
	std::vector<std::vector<float>> panorama; 
	/** @brief Extended PANORAMA representation of loaded mesh */
	std::vector<std::vector<float>> panorama_extended; 

	/** @brief Normals of mesh faces */
	std::vector<glm::vec3> normals; 
	/** @brief Centroid of the mesh */
	glm::vec3 centroid; 
	/** @brief Max distance from centroid to mesh */
	double d_max; 
	/** @brief Height of the cylinder */
	double height; 
	/** @brief Radius of the cylinder */
	double radius; 
	/** @brief Number of divisions of the cylinder height
	 * 
	 * Is set by default to 180 divisions
	 */
	int B = 180;

	void calc_normals();
	void calc_centroid();
	void calc_distance();
	void scale_to_unit();

	bool load_obj(const std::string path);

	bool RayIntersectsTriangle(glm::vec3 rayOrigin, 
								glm::vec3 rayVector, 
								glm::vec3 vertex0,
								glm::vec3 vertex1,
								glm::vec3 vertex2,
								glm::vec3& outIntersectionPoint);

	glm::vec3 get_orig(Axis axis, float v, float precision);
	glm::vec3 get_dir(Axis axis, float angle);
	float get_height(Axis axis, float v, float precision);
	int get_sector(glm::vec2 point);
	int get_sector(float angle);

	void filter_faces(Axis axis, float precision);
	float feature_map(Map map, Axis axis, float precision, int power, glm::vec3 origin,
						glm::vec3 direction, std::vector<glm::vec3> &colisiones,
						std::vector<int> &faces_hit);

	float compute_panorama_symetry();
} ;


#endif
