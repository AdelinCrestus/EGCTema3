#include "lab_m1/Tema3/Tema3.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema3::Tema3()
{
}


Tema3::~Tema3()
{
}


void Tema3::Init()
{
    const string sourceTextureDir = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "textures");
    lastZ = lastX = lastY = 0;
    angularStepSkier = 0;
    /*
    // Load textures
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "grass_bilboard.png").c_str(), GL_REPEAT);
        mapTextures["grass"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "crate.jpg").c_str(), GL_REPEAT);
        mapTextures["crate"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "earth.png").c_str(), GL_CLAMP_TO_BORDER);
        mapTextures["earth"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation", "bamboo", "bamboo.png").c_str(), GL_REPEAT);
        mapTextures["bamboo"] = texture;
    }

    {
        mapTextures["random"] = CreateRandomTexture(25, 25);
    }

    // Load meshes
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("bamboo");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation", "bamboo"), "bamboo.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a simple quad
    {
        vector<glm::vec3> vertices
        {
            glm::vec3(0.5f,   0.5f, 0.0f),    // top right
            glm::vec3(0.5f,  -0.5f, 0.0f),    // bottom right
            glm::vec3(-0.5f, -0.5f, 0.0f),    // bottom left
            glm::vec3(-0.5f,  0.5f, 0.0f),    // top left
        };

        vector<glm::vec3> normals
        {
            glm::vec3(0, 1, 1),
            glm::vec3(1, 0, 1),
            glm::vec3(1, 0, 0),
            glm::vec3(0, 1, 0)
        };

        vector<glm::vec2> textureCoords
        {
            // TODO(student): Complete texture coordinates for the square
            glm::vec2(0.0f, 0.0f),
            glm::vec2(0.0f, 1.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(1.0f, 0.0f)

        };

        vector<unsigned int> indices =
        {
            0, 1, 3,
            1, 2, 3
        };

        Mesh* mesh = new Mesh("square");
        mesh->InitFromData(vertices, normals, textureCoords, indices);
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader *shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    */


    // Create a simple quad for snow
    {
    vector<glm::vec3> vertices
    {
        glm::vec3(75,   0.0f,75),    // top right
        glm::vec3(75,  0.0f, -75),    // bottom right
        glm::vec3(-75, 0.0f, -75),    // bottom left
        glm::vec3(-75,  0.0f, 75),    // top left
    };

    vector<glm::vec3> normals
    {
        glm::vec3(0, 1, 1),
        glm::vec3(1, 0, 1),
        glm::vec3(1, 0, 0),
        glm::vec3(0, 1, 0)
    };

    vector<glm::vec2> textureCoords
    {
        // TODO(student): Complete texture coordinates for the square
        glm::vec2(0.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, 0.0f)

    };

    vector<unsigned int> indices =
    {
        0, 1, 3,
        1, 2, 3
    };

    Mesh* mesh = new Mesh("quad_snow");
    mesh->InitFromData(vertices, normals, textureCoords, indices);
    meshes[mesh->GetMeshID()] = mesh;
    }


    // Load textures
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "snow_texture.jpg").c_str(), GL_REPEAT);
        mapTextures["snow"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "rom_texture.jpg").c_str(), GL_REPEAT);
        mapTextures["romania"] = texture;
    }


    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("Tema3Shader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    //Create skier
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    scaleXBody = 0.2f;
    scaleYBody = 0.4f;
    scaleZBody = 0.2f;
    scaleXSKIs = 0.05f;
    scaleYSKIs = 0.0001f;
    scaleZSKIs = 1.0f;

    angleSlope = RADIANS(30);

    translateX = translateY = translateZ = 0;
    timeY = timeX = 0;
    //GetSceneCamera()->SetPosition(glm::vec3(0, 1, 3 * sqrt(3)));
    //glm::vec3 eulerAngles = glm::vec3(RADIANS(-30), 0, 0);
    //GetSceneCamera()->SetRotation(glm::quat(eulerAngles));
    //GetSceneCamera()->m_transform->SetLocalPosition();
    //GetSceneCamera()->m_transform->RotateLocalOX(RADIANS(-30));
    GetSceneCamera()->m_transform->SetWorldPosition(glm::vec3(0, 4.0f/3.0f, 8.0f/ sqrt(3)));
    GetSceneCamera()->m_transform->SetWorldRotation(glm::vec3(-30, 0, 0));
    GetSceneCamera()->Update();
}


void Tema3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema3::Update(float deltaTimeSeconds)
{

    
    /*// TODO(student): Choose an object and add a second texture to it.
    // For example, for the sphere, you can have the "earth" texture
    // and the "random" texture, and you will use the `mix` function
    // in the fragment shader to mix these two textures.
    //
    // However, you may have the unpleasant surprise that the "random"
    // texture now appears onto all objects in the scene, even though
    // you are only passing the second texture for a single object!
    // Why does this happen? How can you solve it?
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 1, -3));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(2));
        RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix, mapTextures["earth"]);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.5f, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 0, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, mapTextures["crate"]);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0.5f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(75.0f), glm::vec3(1, 1, 0));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, mapTextures["random"]);
    }

    {
        quad = 1;
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.5f, 0.0f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        RenderSimpleMesh(meshes["square"], shaders["LabShader"], modelMatrix, mapTextures["grass"], mapTextures["random"]);
        quad = 0;
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, -0.5f, -3));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderSimpleMesh(meshes["bamboo"], shaders["LabShader"], modelMatrix, mapTextures["bamboo"]);
    }
    */
    //Render snow
    timeY += deltaTimeSeconds;
    translateZ += deltaTimeSeconds;
    
    
    {
        
    translateY = -translateZ * tan(angleSlope);
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1), glm::vec3(translateX, translateY , translateZ));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f, 0.1f, 0.1f));
    modelMatrix = glm::rotate(modelMatrix, angleSlope, glm::vec3(1, 0, 0));
    
    quad = 1;
    RenderSimpleMesh(meshes["quad_snow"], shaders["Tema3Shader"], modelMatrix, mapTextures["snow"]);
    quad = 0;
    
    }

    
    //Render skier
    {
        translateX += cos(angularStepSkier - RADIANS(90)) * deltaTimeSeconds;
        timeX += cos(angularStepSkier - RADIANS(90)) * deltaTimeSeconds;
        if (translateX == 0)
        {
            angleGoDown = angleSlope;
        }
        else
        {
            glm::vec3 dir = glm::vec3(translateX - lastX, translateY- lastY, translateZ- lastZ);
            dir = glm::normalize(dir);
            angleGoDown = acos(glm::dot(dir, glm::normalize(glm::vec3(dir.x, 0, dir.z))));
            angleRotateDown = acos(glm::dot(dir, glm::normalize(glm::vec3(0, dir.y, dir.z))));
        }
        glm::mat4 modelMatrixSkier = glm::translate(glm::mat4(1), glm::vec3(translateX, -translateZ * tan(angleSlope) + 0.2f, translateZ));
        modelMatrixSkier = glm::rotate(modelMatrixSkier, angularStepSkier, glm::vec3(0, 1, 0));
        //modelMatrixSkier = glm::rotate(modelMatrixSkier,angleRotateDown, glm::vec3(0,0,1)) ;
        modelMatrixSkier = glm::rotate(modelMatrixSkier,angleSlope, glm::vec3(1,0,0)) ;
        modelMatrixSkier = glm::rotate(modelMatrixSkier, RADIANS(180), glm::vec3(0, 1, 0));
        glm::mat4 modelMatrixBody = glm::translate(modelMatrixSkier, glm::vec3(0, scaleYBody / 2, 0));
         modelMatrixBody = glm::scale(modelMatrixBody, glm::vec3(scaleXBody, scaleYBody, scaleZBody));
        
        RenderSimpleMesh(meshes["box"], shaders["Tema3Shader"], modelMatrixBody, mapTextures["romania"]);

        glm::mat4 modelMatrixSKIL = modelMatrixSkier;
        modelMatrixSKIL = glm::translate(modelMatrixSKIL, glm::vec3(-0.08f, 0.001f, -0.02f));
            modelMatrixSKIL = glm::scale(modelMatrixSKIL, glm::vec3(scaleXSKIs, scaleYSKIs, scaleZSKIs));
        
        RenderSimpleMesh(meshes["box"], shaders["Tema3Shader"], modelMatrixSKIL, mapTextures["romania"]);

        glm::mat4 modelMatrixSKIR = modelMatrixSkier;
        modelMatrixSKIR = glm::translate(modelMatrixSKIR, glm::vec3(0.08f, 0.001f, -0.02f));
        modelMatrixSKIR = glm::scale(modelMatrixSKIR, glm::vec3(scaleXSKIs, scaleYSKIs, scaleZSKIs));

        RenderSimpleMesh(meshes["box"], shaders["Tema3Shader"], modelMatrixSKIR, mapTextures["romania"]);
    }
    GetSceneCamera()->m_transform->Move(glm::vec3(-lastX + translateX, - lastY + translateY, - lastZ + translateZ));
    GetSceneCamera()->Update();
    lastZ = translateZ;
    lastX = translateX;
    lastY = translateY;

    
    
}


void Tema3::FrameEnd()
{
    DrawCoordinateSystem();
}


void Tema3::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // TODO(student): Set any other shader uniforms that you need
    GLint loc = glGetUniformLocation(shader->program, "quad");
    glUniform1i(loc, quad);

    loc = glGetUniformLocation(shader->program, "timeY");
    glUniform1f(loc, timeY);

    loc = glGetUniformLocation(shader->program, "timeX");
    glUniform1f(loc, timeX);

    if (texture1)
    {
        // TODO(student): Do these:
        // - activate texture location 0
        // - bind the texture1 ID
        // - send theuniform value

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

    }

   /* if (texture2)
    {
        // TODO(student): Do these:
        // - activate texture location 1
        // - bind the texture2 ID
        // - send the uniform value

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 1);

    }
    */

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


Texture2D* Tema3::CreateRandomTexture(unsigned int width, unsigned int height)
{
    GLuint textureID = 0;
    unsigned int channels = 3;
    unsigned int size = width * height * channels;
    unsigned char* data = new unsigned char[size];

    // TODO(student): Generate random texture data
    for (int i = 0; i < size; i++)
    {
        data[i] = rand() % 256;
    }

    // TODO(student): Generate and bind the new texture ID
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    if (GLEW_EXT_texture_filter_anisotropic) {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);
    }
    // TODO(student): Set the texture parameters (MIN_FILTER, MAG_FILTER and WRAPPING MODE) using glTexParameteri
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    CheckOpenGLError();

    // Use glTexImage2D to set the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    // TODO(student): Generate texture mip-maps

    glGenerateMipmap(GL_TEXTURE_2D);

    CheckOpenGLError();

    // Save the texture into a wrapper Texture2D class for using easier later during rendering phase
    Texture2D* texture = new Texture2D();
    texture->Init(textureID, width, height, channels);

    SAFE_FREE_ARRAY(data);
    return texture;
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema3::OnInputUpdate(float deltaTime, int mods)
{
    /*if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
        glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
        forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));
    }*/
    

    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        if (window->KeyHold(GLFW_KEY_W))
        {
            timeY += deltaTime;
            translateZ += deltaTime;
        }

        if (window->KeyHold(GLFW_KEY_A))
        {
            timeX -= deltaTime;
            translateX -= deltaTime;
        }

        if (window->KeyHold(GLFW_KEY_D))
        {
            timeX += deltaTime;
            translateX += deltaTime;
        }
    }
}


void Tema3::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    if ( mouseY >   resolution.y / 4)
    {
        float tg_X = -mouseX + resolution.x / 2;
        float tg_Y = -resolution.y / 4 + mouseY;
        angularStepSkier = -atan(tg_X / tg_Y);
    }
    else
    {
        angularStepSkier = 0;
    }

    if (angularStepSkier > RADIANS(60))
    {
        angularStepSkier = RADIANS(60);
    }
    else if (angularStepSkier < RADIANS(-60))
    {
        angularStepSkier = RADIANS(-60);
    }

}


void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema3::OnWindowResize(int width, int height)
{
}