//
//  debug_triangle.h
//  rigidbodies-and-waves
//
//  Created by Dmitri Wamback on 2025-06-29.
//

#ifndef debug_triangle_h
#define debug_triangle_h

class Debug2DTriangle {
public:
    float width, height, friction;
    glm::vec3 position, scale, rotation;
    
    static Debug2DTriangle Create(float width, float height, float friction);
    void Render(Shader shader);
    void RenderNormal(Shader shader);
    void UpdateGeometry(float width, float height);
    void CalculateForces();
    glm::vec3 GetRotationDegrees();
    glm::mat4 CreateModelMatrix();
private:
    void UploadVertices(std::vector<Vertex> points, uint32_t vao, uint32_t vbo);
    std::vector<Vertex> vertices, normalVertices, gravityVertices;
    uint32_t vertexArrayObject, vertexBufferObject,
             normalVertexArrayObject, normalVertexBufferObject,
             gravityVertexArrayObject, gravityVertexBufferObject;
    std::vector<Text> forceLabels;
};

Debug2DTriangle Debug2DTriangle::Create(float width, float height, float friction = 0.0f) {
    Debug2DTriangle triangle;
    
    triangle.scale = glm::vec3(1.0f);
    triangle.position = glm::vec3(0.0f, 0.0f, -1.0f);
    triangle.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    
    glGenVertexArrays(1, &triangle.vertexArrayObject);
    glGenVertexArrays(1, &triangle.normalVertexArrayObject);
    glGenVertexArrays(1, &triangle.gravityVertexArrayObject);
    
    glGenBuffers(1, &triangle.vertexBufferObject);
    glGenBuffers(1, &triangle.normalVertexBufferObject);
    glGenBuffers(1, &triangle.gravityVertexBufferObject);
    
    triangle.UpdateGeometry(width, height);
    
    return triangle;
}

void Debug2DTriangle::UpdateGeometry(float width, float height) {
    this->width = glm::max(width/4.0f, 0.05f);
    this->height = glm::max(height/4.0f, 0.05f);
    
    float xOffset = this->width/2.0f;
    float yOffset = this->height/2.0f;
    
    vertices = {
        Vertex(glm::vec3(-xOffset,            -yOffset,             0.0f),  glm::vec3(0.0f), glm::vec2(0.0f)),
        Vertex(glm::vec3(this->width-xOffset, -yOffset,             0.0f),  glm::vec3(0.0f), glm::vec2(0.0f)),
        Vertex(glm::vec3(this->width-xOffset, this->height-yOffset, 0.0f),  glm::vec4(0.0f), glm::vec2(0.0f))
    };
    
    CalculateForces();
    
    UploadVertices(vertices, vertexBufferObject, vertexArrayObject);
}

void Debug2DTriangle::UploadVertices(std::vector<Vertex> points, uint32_t vao, uint32_t vbo) {
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(Vertex), points.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, vertex));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
}

void Debug2DTriangle::Render(Shader shader) {
    
    shader.Use();
    
    glm::mat4 model = CreateModelMatrix();
    CalculateForces();
    
    glDisable(GL_DEPTH_TEST);
    
    shader.SetMatrix4("model", model);
    
    {
        glBindVertexArray(vertexArrayObject);
        
        shader.SetVector3("color", glm::vec3(1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    
    model = glm::mat4(1.0f);
    shader.SetMatrix4("model", model);
    {
        glBindVertexArray(normalVertexArrayObject);
        
        shader.SetVector3("color", glm::vec3(0.0f, 1.0f, 0.0f));
        glDrawArrays(GL_POINTS, 0, 2);
        glDrawArrays(GL_LINES, 0, 2);
    }
    {
        glBindVertexArray(gravityVertexArrayObject);
        
        shader.SetVector3("color", glm::vec3(1.0f, 0.0f, 0.0f));
        glDrawArrays(GL_POINTS, 0, 2);
        glDrawArrays(GL_LINES, 0, 2);
    }
    
    {
        textShader.Use();
        textShader.SetMatrix4("projection", testProjection);
        textShader.SetVector3("color", glm::vec3(1.0f, 1.0f, 1.0f));
        forceLabels[0].position = normalVertices[1].vertex;
        forceLabels[0].Render(textShader);
        
        forceLabels[1].position = gravityVertices[1].vertex;
        forceLabels[1].Render(textShader);
    }
    
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);
}

glm::vec3 Debug2DTriangle::GetRotationDegrees() {
    float zAngle = RadiansToDegrees(atan(height/width));
    return glm::vec3(0.0f, 0.0f, zAngle);
}


glm::mat4 Debug2DTriangle::CreateModelMatrix() {
    
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translationMatrix = glm::mat4(1.0f);
    translationMatrix = glm::translate(translationMatrix, position);
    
    glm::mat4 scaleMatrix = glm::mat4(1.0f);
    scaleMatrix = glm::scale(scaleMatrix, scale);
    
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0)) *
                               glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0)) *
                               glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0, 0, 1));
    
    model = translationMatrix * rotationMatrix * scaleMatrix;
    
    return model;
}

void Debug2DTriangle::CalculateForces() {
    
    float deltaWidth = (vertices[0].vertex.x + vertices[1].vertex.x)/2.0f;
    float deltaHeight = (vertices[0].vertex.y + vertices[2].vertex.y)/2.0f;
    
    glm::vec3 center = glm::vec3(deltaWidth, deltaHeight, 0.0f);
    
    glm::vec3 inclination = GetRotationDegrees() + glm::vec3(0.0f, 0.0f, rotation.z);
    
    {
        Force normalForce = ComputeNormalForceFromPlane(0.5f, inclination);
        
        normalVertices = {
            Vertex(center + position, glm::vec3(0.0f), glm::vec2(0.0f)),
            Vertex(normalForce.direction + center + position, glm::vec3(0.0f), glm::vec2(0.0f))
        };
        
        if (forceLabels.size() != 2) {
            Text text = Text::CreateText((unsigned char*)"N = mgcosC");
            forceLabels.push_back(text);
        }
    }
    {
        Force gravitationalForce = ComputeGravitationalForceFromPlane(0.5f, inclination);
        
        gravityVertices = {
            Vertex(center + position, glm::vec3(0.0f), glm::vec2(0.0f)),
            Vertex(gravitationalForce.direction + center + position, glm::vec3(0.0f), glm::vec2(0.0f))
        };
        
        if (forceLabels.size() != 2) {
            Text text = Text::CreateText((unsigned char*)"F = -mgsinC");
            forceLabels.push_back(text);
        }
    }
    
    UploadVertices(normalVertices,  normalVertexArrayObject,    normalVertexBufferObject);
    UploadVertices(gravityVertices, gravityVertexArrayObject,   gravityVertexBufferObject);
}


#endif /* debug_triangle_h */
