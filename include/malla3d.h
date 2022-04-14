#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED
#include <vector>

class Malla3D{
public:
   Malla3D();

protected:
   void calcular_normales();
   
   std::vector<std::vector<float>> v ;
   std::vector<std::vector<int>> f ;
   std::vector<std::vector<float>> nv ;
} ;


#endif
