#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include <map>
#include FT_FREETYPE_H

// Structure pour stocker les informations d'un caractère
struct Character {
    GLuint     textureID;  // ID de la texture du caractère
    glm::ivec2 size;       // Taille du glyph
    glm::ivec2 bearing;    // Offset du glyph
    GLuint     advance;    // Avance vers le prochain glyph
};

std::map<GLchar, Character> characters;

// Fonction pour charger une police
void loadFont(const char* fontPath, GLuint fontSize) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cerr << "Erreur : Impossible d'initialiser FreeType" << std::endl;
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, fontPath, 0, &face)) {
        std::cerr << "Erreur : Impossible de charger la police" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Désactiver l'alignement des bytes

    for (GLubyte c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cerr << "Erreur : Impossible de charger le caractère " << c << std::endl;
            continue;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // Paramètres de la texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Stocker les informations du caractère
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<GLuint>(face->glyph->advance.x)
        };
        characters.insert(std::pair<GLchar, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

GLuint VAO, VBO;

// test
void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, GLuint shaderProgram) {
    // Activer le shader
    glUseProgram(shaderProgram);

    // Passer la couleur du texte
    glUniform3f(glGetUniformLocation(shaderProgram, "textColor"), color.x, color.y, color.z);

    // Activer la texture
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // Itérer à travers chaque caractère
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Character ch = characters[*c];

        GLfloat xpos = x + ch.bearing.x * scale;
        GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

        GLfloat w = ch.size.x * scale;
        GLfloat h = ch.size.y * scale;

        // Coordonnées des sommets
        GLfloat vertices[6][4] = {
            { xpos,     ypos + h, 0.0, 0.0 },
            { xpos,     ypos,     0.0, 1.0 },
            { xpos + w, ypos,     1.0, 1.0 },

            { xpos,     ypos + h, 0.0, 0.0 },
            { xpos + w, ypos,     1.0, 1.0 },
            { xpos + w, ypos + h, 1.0, 0.0 }
        };

        // Mettre à jour le VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Dessiner le caractère
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Avancer à la position suivante
        x += (ch.advance >> 6) * scale;
    }
}