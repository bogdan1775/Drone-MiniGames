#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{
    Mesh* CreateDrona(const std::string& name, glm::vec3 color1, glm::vec3 color2);
    Mesh* CreateElice(const std::string& name, glm::vec3 color);
    Mesh* CreateTeren(const std::string& name, int m,int n,glm::vec3 color);
    Mesh* CreateCopac(const std::string& name, glm::vec3 color1, glm::vec3 color2);
    Mesh* CreateCladire(const std::string& name, glm::vec3 color1, glm::vec3 color2);
    Mesh* CreatePachet(const std::string& name, glm::vec3 color);
    Mesh* CreateLocLivrare(const std::string& name, glm::vec3 color1, glm::vec3 color2);
    Mesh* CreateSageata(const std::string& name, glm::vec3 color);
}
