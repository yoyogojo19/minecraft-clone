#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

class Shader {
public:
    GLuint ID;

    Shader(const char* vertexPath, const char* fragmentPath) {
        // 1. Lire le code des shaders depuis les fichiers
        std::string vertexCode = readFile(vertexPath);
        std::string fragmentCode = readFile(fragmentPath);
        const char* vertexShaderSource = vertexCode.c_str();
        const char* fragmentShaderSource = fragmentCode.c_str();

        // 2. Compiler les shaders
        unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
        unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

        // 3. Créer le programme de shader
        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);

        // 4. Vérifier les erreurs de linkage
        int success;
        char infoLog[512];
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cerr << "ERREUR::SHADER::LINKAGE\n" << infoLog << std::endl;
        }

        // 5. Supprimer les shaders intermédiaires
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    Shader(const char* vertexPath, const char* geomatryPath, const char* fragmentPath) {
        // 1. Lire le code des shaders depuis les fichiers
        std::string vertexCode = readFile(vertexPath);
        std::string geomatryCode = readFile(vertexPath);
        std::string fragmentCode = readFile(fragmentPath);
        const char* vertexShaderSource = vertexCode.c_str();
        const char* geomatryShaderSource = vertexCode.c_str();
        const char* fragmentShaderSource = fragmentCode.c_str();

        // 2. Compiler les shaders
        unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
        unsigned int geomatryShader = compileShader(GL_GEOMETRY_SHADER, geomatryShaderSource);
        unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

        // 3. Créer le programme de shader
        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, geomatryShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);

        // 4. Vérifier les erreurs de linkage
        int success;
        char infoLog[512];
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cerr << "ERREUR::SHADER::LINKAGE\n" << infoLog << std::endl;
        }

        // 5. Supprimer les shaders intermédiaires
        glDeleteShader(vertexShader);
        glDeleteShader(geomatryShader);
        glDeleteShader(fragmentShader);
    }

    void use() {
        glUseProgram(ID);
    }

private:
    std::string readFile(const char* filePath) {
        std::string content;
        std::ifstream fileStream(filePath, std::ios::in);
        if (!fileStream.is_open()) {
            std::cerr << "ERREUR::SHADER::FICHIER_INTROUVABLE: " << filePath << std::endl;
            return "";
        }
        std::stringstream stream;
        stream << fileStream.rdbuf();
        content = stream.str();
        fileStream.close();

        return content;
    }

    unsigned int compileShader(unsigned int type, const char* source) {
        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);

        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cerr << "ERREUR::SHADER::COMPILATION\n" << infoLog << std::endl;
        }
        return shader;
    }
};

#endif