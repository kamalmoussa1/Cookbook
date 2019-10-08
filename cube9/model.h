#ifndef LOADMODEL_H
#define LOADMODEL_H

#include <vector>
#include  <glm/glm.hpp>

class Model
{
  public:
    Model(){}
    ~Model(){}

    bool load(const char * path,
              std::vector<unsigned short> & indices,
              std::vector<glm::vec3> & vertices,
              std::vector<glm::vec2> & uvs,
              std::vector<glm::vec3> & normals);
};

#endif // LOADMODEL_H

