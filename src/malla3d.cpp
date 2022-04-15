#include "malla3d.h"



Malla3D::Malla3D(){}


void Malla3D::calc_centroid(){
    float sum_x, sum_y, sum_z;
    sum_x = sum_y = sum_z = 0.0;
    
    for(int i = 0; i < vertexs.size(); i++){
        sum_x += vertexs[i].x;
        sum_y += vertexs[i].y;
        sum_z += vertexs[i].z;
    }

    sum_x /= vertexs.size();
    sum_y /= vertexs.size();
    sum_z /= vertexs.size();

    centroid.x = sum_x;
    centroid.y = sum_y;
    centroid.z = sum_z;
}

void Malla3D::calc_normals(){
    normals.clear();
    glm::vec3 v1, v2, v3;
    for(int i = 0; i < facesIndex.size(); i++){
        v1 = vertexs[facesIndex[i][0]];
        v2 = vertexs[facesIndex[i][1]];
        v3 = vertexs[facesIndex[i][2]];

        glm::vec3 cross_p = glm::cross((v2-v1), (v3-v1));

        cross_p = glm::normalize(cross_p);

        normals.push_back(cross_p);
    }
}

void Malla3D::calc_distance(){
    float dist;
    float max = glm::distance(vertexs[0],centroid);
    for(int i = 1; i < vertexs.size(); i++){
        dist = glm::distance(vertexs[i],centroid);
        if (dist > max){
            max = dist;
        }
    }

    d_max = max;
}

void Malla3D::scale_to_unit(){
    std::vector<glm::vec3> v_unit;

    for(int i = 0; i < vertexs.size(); i++){
        glm::vec3 v_orig = vertexs[i] - centroid;
        glm::vec3 v_scale = v_orig;
        v_scale.x = v_scale.x / d_max;
        v_scale.y = v_scale.y / d_max;
        v_scale.z = v_scale.z / d_max;

        v_unit.push_back(v_scale);
    }

    vertexs = v_unit;
    centroid.x = 0.0;
    centroid.y = 0.0;
    centroid.z = 0.0;
    calc_normals();
    calc_distance();

    std::cout << vertexs.size() << std::endl;
    std::cout << facesIndex.size() << std::endl;
    std::cout << normals.size() << std::endl;
    std::cout << centroid.x << ", " << centroid.y << ", " << centroid.z << std::endl;
    std::cout << d_max << std::endl;
}

void Malla3D::rotate_mesh(float angle){
    std::vector<glm::vec3> mesh_rotate;
    glm::vec3 rotate_vertex;
    for(int i = 0; i < vertexs.size(); i++){
        rotate_vertex.x = vertexs[i].x;
        rotate_vertex.y = vertexs[i].y*cos(angle) - vertexs[i].z*sin(angle);
        rotate_vertex.z = vertexs[i].y*sin(angle) + vertexs[i].z*cos(angle);

        mesh_rotate.push_back(rotate_vertex);
        

    }
    vertexs = mesh_rotate;
    calc_normals();
    calc_distance();
}

bool Malla3D::load_obj(const std::string path){
    std::vector< unsigned int > vertexIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::ifstream file;
    std::string line;
    std::string header;
    std::string face_line;
    std::string face;
    std::string delimiter = "/";
    file.open(path);

    if( !file.is_open() ){
        std::cout << "Impossible to open the file !" << std::endl;
        return false;
    }

    while(std::getline(file,line)){
        //std::cout << line << std::endl;
        file >> header;
        //std::cout << header << std::endl;
        if(header == "v"){
            // std::cout << header << line << std::endl;
            glm::vec3 vertex;
            file >> vertex.x;
            file >> vertex.y;
            file >> vertex.z;
            vertexs.push_back(vertex);
        } else if (header == "f"){
            std::string vertex1, vertex2, vertex3;
            std::vector<int> vertexIndex;
            file >> face_line;
            vertex1 = face_line.substr(0, face_line.find(delimiter));
            vertexIndex.push_back(std::stoi(vertex1));

            file >> face_line;
            vertex2 = face_line.substr(0, face_line.find(delimiter));
            vertexIndex.push_back(std::stoi(vertex2));

            file >> face_line;
            vertex3 = face_line.substr(0, face_line.find(delimiter));
            vertexIndex.push_back(std::stoi(vertex3));

            facesIndex.push_back(vertexIndex);
        }
    }

    // for(int i = 0; i < vertexIndices.size(); i++){
    //     unsigned int vertexIndex = vertexIndices[i];
    //     //std::cout << vertexIndices[i] << std::endl;
    //     glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
    //     vertexs.push_back(vertex);
    // }

    // for(int i = 0; i < vertexs.size(); i++){
    //     std::cout << vertexs[i].x << ", " << vertexs[i].y << ", " << vertexs[i].z << std::endl;
    // }

    // for(int i = 0; i < facesIndex.size(); i++){
    //     std::cout << facesIndex[i][0] << ", " << facesIndex[i][1] << ", " << facesIndex[i][2] << std::endl;
    // }

    calc_centroid();
    calc_normals();
    calc_distance();

    std::cout << vertexs.size() << std::endl;
    std::cout << facesIndex.size() << std::endl;
    std::cout << normals.size() << std::endl;
    std::cout << centroid.x << ", " << centroid.y << ", " << centroid.z << std::endl;
    std::cout << d_max << std::endl;

    scale_to_unit();

    return true;
}
