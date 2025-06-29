//
//  text.h
//  rigidbodies-and-waves
//
//  Created by Dmitri Wamback on 2025-06-29.
//

#ifndef text_h
#define text_h

struct Character {
    unsigned int TextureID;
    glm::ivec2   Size;
    glm::ivec2   Bearing;
    unsigned int Advance;
};

class Text {
public:
    std::vector<Character> characters;
    static Text CreateText(unsigned char* text);
    void Render(Shader shader);
    glm::vec3 position;
public:
    uint32_t vertexArrayObject, vertexBufferObject;
};

Text Text::CreateText(unsigned char *text) {
    Text textObject = Text();
    
    textObject.position = glm::vec3(0.0f);
    
    glGenVertexArrays(1, &textObject.vertexArrayObject);
    glBindVertexArray(textObject.vertexArrayObject);
    
    
    glGenBuffers(1, &textObject.vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, textObject.vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    
    for (int i = 0; text[i] != '\0'; i++) {
        
        if (FT_Load_Char(face, text[i], FT_LOAD_RENDER)) {
            continue;
        }
        std::cout << "loaded " << text[i] << '\n';
        
        unsigned int texture;
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
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };
        
        textObject.characters.push_back(character);
    }
    
    return textObject;
}

void Text::Render(Shader shader) {
        
    shader.Use();
    glBindVertexArray(vertexArrayObject);

    float scale = 0.0015f;
    
    float x = position.x;
    float y = position.y;
    
    for (Character character : characters) {
        float xpos = x + character.Bearing.x * scale;
        float ypos = y + character.Bearing.y * scale;

        float w = character.Size.x * scale;
        float h = character.Size.y * scale;
        
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        
        float ndcX = xpos;
        float ndcY = ypos;
        float ndcW = w;
        float ndcH = h;

        float vertices[6][4] = {
            { ndcX,          ndcY - ndcH,  0.0f, 0.0f },
            { ndcX,          ndcY,         0.0f, 1.0f },
            { ndcX + ndcW,   ndcY,         1.0f, 1.0f },
            { ndcX,          ndcY - ndcH,  0.0f, 0.0f },
            { ndcX + ndcW,   ndcY,         1.0f, 1.0f },
            { ndcX + ndcW,   ndcY - ndcH,  1.0f, 0.0f }
        };
        
        glBindTexture(GL_TEXTURE_2D, character.TextureID);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (character.Advance >> 6) * scale;
        
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

#endif /* text_h */
