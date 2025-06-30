//
//  debug_triangle.h
//  rigidbodies-and-waves
//
//  Created by Dmitri Wamback on 2025-06-29.
//

#ifndef debug_triangle_h
#define debug_triangle_h

class Debug2DTriangle: public PhysicsObject2D {
public:
    
    Force normalForce, gravitationalForce;
    
    static PhysicsObject2D* Create(float width, float height, float friction);
    void Render(Shader shader)                      override;
    void RenderNormal(Shader shader)                override;
    void UpdateGeometry(float width, float height)  override;
    void CalculateForces()                          override;
    glm::vec3 GetRotationDegrees()                  override;
};

PhysicsObject2D* Debug2DTriangle::Create(float width, float height, float friction = 0.0f) {
    PhysicsObject2D* triangle = new Debug2DTriangle();
    
    triangle->scale         = glm::vec3(1.0f);
    triangle->position      = glm::vec3(0.0f, 0.0f, -1.0f);
    triangle->rotation      = glm::vec3(0.0f, 0.0f, 0.0f);
    triangle->physicsType   = InclinedPlane;
    
    glGenVertexArrays(1, &triangle->vertexArrayObject);
    glGenVertexArrays(1, &triangle->normalVertexArrayObject);
    glGenVertexArrays(1, &triangle->gravityVertexArrayObject);
    
    glGenBuffers(1, &triangle->vertexBufferObject);
    glGenBuffers(1, &triangle->normalVertexBufferObject);
    glGenBuffers(1, &triangle->gravityVertexBufferObject);
    
    triangle->UpdateGeometry(width, height);
    
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
        textShader.SetVector3("color", glm::vec3(0.7f, 0.7f, 0.7f));
        forceLabels[0].position = normalVertices[1].vertex;
        forceLabels[0].Render(textShader, "N = mgcosC = " + std::to_string(normalForce.newtons) + "N");
        
        forceLabels[1].position = gravityVertices[1].vertex;
        forceLabels[1].Render(textShader, "F = -mgsinC = " + std::to_string(-gravitationalForce.newtons) + "N");
    }
    
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);
}

glm::vec3 Debug2DTriangle::GetRotationDegrees() {
    float zAngle = RadiansToDegrees(atan(height/width));
    return glm::vec3(0.0f, 0.0f, zAngle);
}

void Debug2DTriangle::CalculateForces() {
    
    float deltaWidth = (vertices[0].vertex.x + vertices[1].vertex.x)/2.0f;
    float deltaHeight = (vertices[0].vertex.y + vertices[2].vertex.y)/2.0f;
    
    glm::vec3 center = glm::vec3(deltaWidth, deltaHeight, 0.0f);
    
    glm::vec3 inclination = GetRotationDegrees() + glm::vec3(0.0f, 0.0f, rotation.z);
    
    {
        normalForce = ComputeNormalForceFromPlane(0.5f, inclination);
        
        normalVertices = {
            Vertex(center + position, glm::vec3(0.0f), glm::vec2(0.0f)),
            Vertex(normalForce.direction * 0.5f + center + position, glm::vec3(0.0f), glm::vec2(0.0f))
        };
        
        if (forceLabels.size() != 2) {
            Text text = Text::CreateText();
            forceLabels.push_back(text);
        }
    }
    {
        gravitationalForce = ComputeGravitationalForceFromPlane(0.5f, inclination);
        
        gravityVertices = {
            Vertex(center + position, glm::vec3(0.0f), glm::vec2(0.0f)),
            Vertex(gravitationalForce.direction * 0.5f + center + position, glm::vec3(0.0f), glm::vec2(0.0f))
        };
        
        if (forceLabels.size() != 2) {
            Text text = Text::CreateText();
            forceLabels.push_back(text);
        }
    }
    
    UploadVertices(normalVertices,  normalVertexArrayObject,    normalVertexBufferObject);
    UploadVertices(gravityVertices, gravityVertexArrayObject,   gravityVertexBufferObject);
}

void Debug2DTriangle::RenderNormal(Shader shader) {}


#endif /* debug_triangle_h */
