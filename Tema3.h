#pragma once

#include <string>
#include <unordered_map>

#include "components/simple_scene.h"
#include "components/transform.h"


namespace m1
{
    class Tema3 : public gfxc::SimpleScene
    {
     public:
        Tema3();
        ~Tema3();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, Texture2D *texture1 = NULL);
        Texture2D *CreateRandomTexture(unsigned int width, unsigned int height);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        std::unordered_map<std::string, Texture2D *> mapTextures;

        int quad = 0;

        float timeY, timeX;

        float scaleXBody, scaleYBody, scaleZBody;
        float scaleXSKIs, scaleYSKIs, scaleZSKIs;

        float translateX, translateZ, translateY;
        float angleSlope;
        float lastZ, lastX, lastY;
        float tg_X;
        glm::ivec2 resolution;
        float angleGoDown, angleRotateDown;
        float angularStepSkier;
        bool autoCamera;

        glm::vector<glm::vec3> pos_trees;
        glm::vector<glm::vec3> pos_gifts;
        glm::vector<glm::vec3> pos_lighting_poles;
        glm::vector<glm::vec3> pos_rocks;
        float time;
        float last_time_object;

        float scaleCone;
        float scaleGift;
        int timerNewObjects;
        bool blocat;
        float scaleTrunk;
        float material_kd, material_ks;
        int material_shininess;
        int N;
        glm::vector<glm::vec3> positions_objects;
        glm::vector<glm::vec3> color_light_objects;
        glm::vec3 spotPos;
        bool blocat2;
    };

}   // namespace m1
