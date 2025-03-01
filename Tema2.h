#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/Tema2_camera.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
         struct ViewportArea
         {
             ViewportArea() : x(0), y(0), width(1), height(1) {}
             ViewportArea(int x, int y, int width, int height)
                 : x(x), y(y), width(width), height(height) {}
             int x;
             int y;
             int width;
             int height;
         };
         Tema2();
        ~Tema2();

        void Init() override;
        Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DesenareDrona(float deltaTimeSeconds);
        void DesenareTeren();
        void DesenareCopaci();
		void PozitionareStaticaCopaci();
        void PozitionareStaticaCladiri();
        void PozitionareRandomCopaci();
        void PozitionareRandomPachetSiLivrare();
        void DesenareCladiri();
        void DesenarePachet();
        void DesenareLocLivrare();
        void DesenareSageata();

		void ColiziunePachet();
		void ColiziuneLocLivrare();
        void RenderSceneViewPort();

		void ColiziuneDronaTeren();
        void ColiziuneDronaCladiri();
        void ColiziuneDronaCopaci();

        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;


     protected:
        implemented::Camera_Tema2 *camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        // TODO(student): If you need any other class variables, define them here.
        bool  projectionOrtho;
        float left, right, bottom, top, zNear, zFar, fov;

        
        // adaug tema2
        float unghi_elice;
        float rotatie_drona_OY;

        int m, n;
        float dim_patrat;
        //int poz_obiecte[300][300];
        int ok;

        struct Obiecte {
            int x, y, z;
            int tip;
			float factor_scalare;
        };
		std::vector<Obiecte> obiecte;

        bool deplasareDrona;
        bool deplasareDrona1;
        bool deplasareDrona2;

        int nr_pachete;

        bool pachet_luat;
        bool ok_random;
        float x_pachet, z_pachet;
		float x_livrare, z_livrare;

        float raza_drona;

        ViewportArea miniViewportArea;
    };
}   // namespace m1
