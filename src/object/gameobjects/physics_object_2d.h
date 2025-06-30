//
//  physics_object_2d.h
//  rigidbodies-and-waves
//
//  Created by Dmitri Wamback on 2025-06-29.
//

#ifndef physics_object_2d_h
#define physics_object_2d_h

enum PhysicsObjectType {
    InclinedPlane,
    FallingObject
};

class PhysicsObject2D {
public:
    float width, height, friction;
    glm::vec3 position, scale, rotation;
    
    PhysicsObjectType physicsType;
    
    static PhysicsObject2D* Create(float width, float height, float friction);
    virtual void Render(Shader shader){}
    virtual void RenderNormal(Shader shader){}
    virtual void UpdateGeometry(float width, float height){}
    virtual void CalculateForces(){}
    virtual glm::vec3 GetRotationDegrees(){return glm::vec3(0.0f);}
    
    glm::mat4 CreateModelMatrix();
    void UploadVertices(std::vector<Vertex> points, uint32_t vao, uint32_t vbo);
    
    std::vector<Vertex> vertices, normalVertices, gravityVertices;
    uint32_t vertexArrayObject, vertexBufferObject,
             normalVertexArrayObject, normalVertexBufferObject,
             gravityVertexArrayObject, gravityVertexBufferObject;
    std::vector<Text> forceLabels;
};

void PhysicsObject2D::UploadVertices(std::vector<Vertex> points, uint32_t vao, uint32_t vbo) {
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

glm::mat4 PhysicsObject2D::CreateModelMatrix() {
    
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

#endif /* physics_object_2d_h */
