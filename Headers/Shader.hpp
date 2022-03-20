#pragma once

#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>

namespace MSet {

	class Shader
    {
    private:
        // The shader ID
        unsigned int ID;
        const char* VertexPath;
        const char* FragmentPath;
      
    public:
        Shader(const char* VertexPath_, const char* FragmentPath_);

        void init();
    
        // Use/activate the shader
        void use() const;

        void set_matrix(glm::mat4& Matrix) const;
    };
}
