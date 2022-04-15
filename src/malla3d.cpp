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
    radius = 2*d_max;
    height = 2*radius;
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
    // std::cout << normals.size() << std::endl;
    // std::cout << centroid.x << ", " << centroid.y << ", " << centroid.z << std::endl;
    // std::cout << d_max << std::endl;
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
    // std::cout << normals.size() << std::endl;
    // std::cout << centroid.x << ", " << centroid.y << ", " << centroid.z << std::endl;
    // std::cout << d_max << std::endl;

    scale_to_unit();

    return true;
}

bool Malla3D::RayIntersectsTriangle(glm::vec3 rayOrigin, 
                                    glm::vec3 rayVector, 
                                    std::vector<glm::vec3> inTridegree,
                                    glm::vec3& outIntersectionPoint){
    const float EPSILON = 0.0000001;
    glm::vec3 vertex0 = inTridegree[0];
    glm::vec3 vertex1 = inTridegree[1];
    glm::vec3 vertex2 = inTridegree[2];
    glm::vec3 edge1, edge2, h, s, q;
    float a,f,u,v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = glm::cross(rayVector,edge2);
    a = glm::dot(edge1,h);

    if (a > -EPSILON && a < EPSILON){
        return false;
    }

    f = 1.0/a;
    s = rayOrigin - vertex0;
    u = f * glm::dot(s,h);

    if (u < 0.0 || u > 1.0){
        return false;
    }

    q = glm::cross(s,edge1);
    v = f * glm::dot(rayVector,q);

    if (v < 0.0 || u + v > 1.0){
        return false;
    }
        
    float t = f * glm::dot(edge2,q);

    if (t > EPSILON){
        outIntersectionPoint = rayOrigin + rayVector * t;
        return true;
    }
    else{
        return false;
    }
        
}

glm::vec3 Malla3D::get_orig(Axis axis, float v, int angle){
    glm::vec3 orig;

    switch (axis)
    {
    case X:
        orig.x = centroid.x - height/2 + v * height/B;
        orig.y = centroid.y + radius * cos(angle);
        orig.z = centroid.z + radius * sin(angle);
        break;

    case Y:
        orig.x = centroid.x + radius * cos(angle);
        orig.y = centroid.y - height/2 + v * height/B;
        orig.z = centroid.z + radius * sin(angle);
        break;

    case Z:
        orig.x = centroid.x + radius * cos(angle);
        orig.y = centroid.y + radius * sin(angle);
        orig.z = centroid.z - height/2 + v * height/B;
        break;
    }

    return orig;
}

glm::vec3 Malla3D::get_dir(Axis axis, int angle){
    glm::vec3 dir;
        switch (axis)
    {
    case X:
        dir.x = 0.0;
        dir.y = -1 * radius * cos(angle);
        dir.z = -1 * radius * sin(angle);
        break;

    case Y:
        dir.x = -1 * radius * cos(angle);
        dir.y = 0.0;
        dir.z = -1 * radius * sin(angle);
        break;

    case Z:
        dir.x = -1 * radius * cos(angle);
        dir.y = -1 * radius * sin(angle);
        dir.z = 0.0;
        break;
    }

    return glm::normalize(dir);
}

std::vector<std::vector<int>> Malla3D::filter_faces(Axis axis, float v, float threshold){
    float v_height = height/B;
    float coord_axis;
    std::vector<std::vector<int>> facesIndex_filter;

    for(int i = 0; i < facesIndex.size(); i++){
        for(int j = 0; j < facesIndex[i].size(); j++){
            switch (axis)
            {
            case X:
                coord_axis = vertexs[facesIndex[i][j]].x;
                break;

            case Y:
                coord_axis = vertexs[facesIndex[i][j]].y;
                break;

            case Z:
                coord_axis = vertexs[facesIndex[i][j]].z;
                break;  
            }
            
            if((coord_axis >= (v - threshold*v_height)) &&
               (coord_axis <= (v + threshold*v_height))){
                facesIndex_filter.push_back(facesIndex[i]);
                j = facesIndex[i].size();
            }
            
            // std::cout << "Coord: " << coord_axis << std::endl;
            // std::cout << "V: " << v << std::endl;
            // std::cout << "V min: " << v - threshold*v_height << std::endl;
            // std::cout << "V max: " << v + threshold*v_height << std::endl;
            

        }
    }

    return facesIndex_filter;

}

std::vector<float> Malla3D::feature_map(Map map, 
                                        Axis axis, 
                                        std::vector<glm::vec3> origins, 
                                        std::vector<glm::vec3> directions){
    std::vector<float> row;

    float v;
    switch (axis)
    {
    case X:
        v = origins[0].x;
        break;

    case Y:
        v = origins[0].y;
        break;

    case Z:
        v = origins[0].z;
        break;  
    }

    // std::cout << v << std::endl;
    // std::cout << origins[i].x << ", " << origins[i].y << ", " << origins[i].z << std::endl;
    std::vector<std::vector<int>> facesIndex_filter = filter_faces(axis, v, 1);
    // std::vector<std::vector<int>> facesIndex_filter = facesIndex;
    std::cout << "Filtrado de caras: " << facesIndex_filter.size() << std::endl;

    switch (map)
    {
    case SDM:
    
        for(int i = 0; i < origins.size(); i++){
            // std::cout << i << std::endl;

            omp_set_num_threads(10);
            #pragma omp parallel for
            for(int j = 0; j < facesIndex_filter.size(); j++){
                glm::vec3 hit_point;
                glm::vec2 hit;
                float dist;
                std::vector<glm::vec3> triangle_points;
                for(int k = 0; k < facesIndex_filter[j].size(); k++){
                    triangle_points.push_back(vertexs[facesIndex_filter[j][k]]);
                }
                if(RayIntersectsTriangle(origins[i], directions[i], triangle_points, hit_point)){
                // if(glm::intersectRayTriangle(origins[i], directions[i], triangle_points[0], triangle_points[1], triangle_points[2], hit, dist)){
                    //std::cout << hit_point.x << ", " << hit_point.y << ", " << hit_point.z << std::endl;
                    //std::cout << dist << std::endl;
                } else {
                    //std::cout << i << ", " << j << std::endl;
                }
            }
        }
        break;
    
    case NDM:
        /* code */
        break;
    }
}

void Malla3D::calculatePanorama(Map map, Axis axis, float precision, int power){
    std::vector<std::vector<float>> panorama;

    for(float v = 0; v < B; v += precision){
        std::vector<glm::vec3> directions;
        std::vector<glm::vec3> origins;

        for(float u = 0; u < 2*B; u += precision){
            float angle = u*2*M_PI / (2*B);
            origins.push_back(get_orig(axis,v,angle));
            // std::cout << get_orig(axis,v,angle).x << ", " << get_orig(axis,v,angle).y << ", " << get_orig(axis,v,angle).z << std::endl;
            directions.push_back(get_dir(axis,angle));
        }

        std::vector<float> row = feature_map(map, axis, origins, directions);

    }
}

