#include "../Headers/Shader.hpp"

namespace MSet {

    Shader::Shader(const char* VertexPath_, const char* FragmentPath_) {
        VertexPath   = VertexPath_;
        FragmentPath = FragmentPath_;
    }

    void Shader::init() {

        std::string VertexCode;
        std::string FragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        
        // Ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try {
            // Open files
            vShaderFile.open(VertexPath);
            fShaderFile.open(FragmentPath);
            
            std::stringstream vShaderStream, fShaderStream;
            // Read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();       
            
            // Close file handlers
            vShaderFile.close();
            fShaderFile.close();
            
            // Convert stream into string
            VertexCode   = vShaderStream.str();
            FragmentCode = fShaderStream.str();     
        }
        catch(std::ifstream::failure e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }

        const char* VertexShaderSource = VertexCode.c_str();
        const char* FragmentShaderSource = FragmentCode.c_str();


        // Vertex shader
        unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(VertexShader, 1, &VertexShaderSource, NULL);
        glCompileShader(VertexShader);

        // Check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // Fragment shader
        unsigned int FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(FragmentShader, 1, &FragmentShaderSource, NULL);
        glCompileShader(FragmentShader);

        // Check for shader compile errors
        glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // Link shaders
        ID = glCreateProgram();
        glAttachShader(ID, VertexShader);
        glAttachShader(ID, FragmentShader);
        glLinkProgram(ID);

        // Check for linking errors
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(VertexShader);
        glDeleteShader(FragmentShader);
    }

    // Use/activate the shader
    void Shader::use() const {
        glUseProgram(ID);
    }

    void Shader::set_matrix(glm::mat4& Matrix) const {
        unsigned int transformLoc = glGetUniformLocation(ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(Matrix));
    }
}