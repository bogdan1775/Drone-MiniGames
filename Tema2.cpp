#include "lab_m1/Tema2/Tema2.h"

#include "lab_m1/Tema2/Tema2_object2D.h"
#include "lab_m1/Tema2/Tema2_transform3D.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    m = 120;
    n = 120;
    dim_patrat = 1.5f;

    ok = 0; // pentru a pozitiona copacii si cladirile prima data

    deplasareDrona = true;
    deplasareDrona1 = true;
	deplasareDrona2 = true;

    pachet_luat = false;
    ok_random = true;

	nr_pachete = 0;

	x_pachet = 0;
	z_pachet = 0;
	x_livrare = 0;
	z_livrare = 0;

    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);

    raza_drona = 2 * 0.1f;


    camera = new implemented::Camera_Tema2();
    camera->Set(glm::vec3(0, 1, 3.5f), glm::vec3(0, 1, 4), glm::vec3(0, 1, 0));

    // corp drona
    {
        Mesh* corpDrona = object2D::CreateDrona("corpDrona", glm::vec3(105.0 / 255, 105.0 / 255, 105.0 / 255), glm::vec3(169.0 / 255, 169.0 / 255, 169.0 / 255));
        AddMeshToList(corpDrona);
    }

    // elice
    {
        Mesh* elice = object2D::CreateElice("elice", glm::vec3(0.0 / 255, 0.0 / 255, 0.0 / 255));
        AddMeshToList(elice);
    }

    /* {
        Mesh* teren = object2D::CreateTeren("teren", 60, 60, glm::vec3(0.0 / 255, 0.0 / 255, 255.0 / 255));
        AddMeshToList(teren);
    }*/

    // pentru nori
    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* copac = object2D::CreateCopac("copac", glm::vec3(139.0 / 255, 69.0 / 255, 19.0 / 255), glm::vec3(0.0 / 255, 128.0 / 255, 0.0 / 255));
        AddMeshToList(copac);
    }
    
    {
        Mesh* cladire = object2D::CreateCladire("cladire", glm::vec3(119.0 / 255, 136.0 / 255, 153.0 / 255), glm::vec3(205.0 / 255, 133.0 / 255, 63.0 / 255));
        AddMeshToList(cladire);
	}
	{
		Mesh* pachet = object2D::CreatePachet("pachet", glm::vec3(255.0 / 255, 0.0 / 255, 0.0 / 255));
		AddMeshToList(pachet);
	}

    {
        Mesh* loclivrare = object2D::CreateLocLivrare("loclivrare", glm::vec3(255.0 / 255, 0.0 / 255, 0.0 / 255), glm::vec3(0.0 / 255, 0.0 / 255, 240.0 / 255));
        AddMeshToList(loclivrare);
    }
    {
        Mesh* loclivrare = object2D::CreateSageata("sageata", glm::vec3(0.0 / 255, 0.0 / 255, 255.0 / 255));
        AddMeshToList(loclivrare);
    }

    // creez terenul
    {
        std::vector<VertexFormat> vertices;
            for (int i = 0;i <= m;i++)
                for (int j = 0;j <= n;j++) {
                    vertices.push_back(VertexFormat(glm::vec3(j * dim_patrat, 0, i * dim_patrat), glm::vec3(255.0 / 255, 0.0 / 255, 0.0 / 255)));
                }
        std::vector<unsigned int> indices;
        for(int i = 0;i < m;i++)
            for (int j = 0;j < n;j++) {
                int st_sus, st_jos, dr_sus, dr_jos;
                st_sus = i * (n + 1) + j;
                st_jos = (i + 1) * (n + 1) + j;
                dr_sus = st_sus + 1;
                dr_jos = st_jos + 1;

                indices.push_back(st_sus);
                indices.push_back(dr_sus);
                indices.push_back(dr_jos);

                indices.push_back(st_sus);
                indices.push_back(dr_jos);
                indices.push_back(st_jos);
            }
		Mesh* teren = CreateMesh("teren", vertices, indices);
    }

    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 500.0f);
    //projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
    //projectionOrtho = false;
    //top = 30.0f;
    //bottom = -30.0f;
    //left = -50.5f;
    //right = 50.0f;
    //zNear = 30.1f;//0.3f;
    //zFar = 200.0f;//70.0f;
    //fov = RADIANS(60);//45;

    
    unghi_elice=0;
    //rotatie_drona_OY = 0;
    
}

Mesh* Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    // Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create the VBO and bind it
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Create the IBO and bind it
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);


    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    CheckOpenGLError();

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;
    return meshes[name];
}

void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::DesenareDrona(float deltaTimeSeconds) {
    float factor_scalare = 0.1f;
    
    glm::vec3 forward = camera->forward;
    glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
    glm::vec3 up = glm::normalize(glm::cross(right, forward));

    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0] = glm::vec4(right, 0);
    rotation[1] = glm::vec4(up, 0);
    rotation[2] = glm::vec4(-forward, 0);

    // corp drona
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0,-0.2f,0));
        modelMatrix *= rotation;
        modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(factor_scalare));
        RenderMesh(meshes["corpDrona"], shaders["VertexColor"], modelMatrix);
    }

    // elice x4
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.2f, 0));
        modelMatrix *= rotation;
        modelMatrix = glm::rotate(modelMatrix, RADIANS(45), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.8f * factor_scalare, 0.6* factor_scalare+0.05*0.2f, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(unghi_elice), glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
        RenderMesh(meshes["elice"], shaders["VertexColor"], modelMatrix);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.2f, 0));
        modelMatrix *= rotation;
        modelMatrix = glm::rotate(modelMatrix, RADIANS(45), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(1.8f * factor_scalare, 0.6 * factor_scalare + 0.05 * 0.2f, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(unghi_elice), glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
        RenderMesh(meshes["elice"], shaders["VertexColor"], modelMatrix);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.2f, 0));
        modelMatrix *= rotation;
        modelMatrix = glm::rotate(modelMatrix, RADIANS(45), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.6 * factor_scalare + 0.05 * 0.2f, -1.8f * factor_scalare));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(unghi_elice), glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
        RenderMesh(meshes["elice"], shaders["VertexColor"], modelMatrix);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.2f, 0));
        modelMatrix *= rotation;
        modelMatrix = glm::rotate(modelMatrix, RADIANS(45), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.6 * factor_scalare + 0.05 * 0.2f, 1.8f * factor_scalare));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(unghi_elice), glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
        RenderMesh(meshes["elice"], shaders["VertexColor"], modelMatrix);
    }

    // pentru a invarti elicele
    if (unghi_elice > 2 * M_PI) {
        unghi_elice -= 2 * M_PI;
    }
    unghi_elice += deltaTimeSeconds * 10;

}

// desenare teren
void Tema2::DesenareTeren(){
    glm::mat4 modelMatrix = glm::mat4(1);
    RenderMesh(meshes["teren"], shaders["LabShader"], modelMatrix);
}

// coliziune drona teren
void Tema2::ColiziuneDronaTeren() {
    glm::vec3 target = camera->GetTargetPosition();
    float x = target.x;
    float z = target.z;
    float y = target.y-0.2f;
    
	if (y <= 0.5f) {
		deplasareDrona = false;
	}
    else {
        deplasareDrona = true;
    }
}

// coliziune drona cladiri
void Tema2::ColiziuneDronaCladiri() {
    glm::vec3 target = camera->GetTargetPosition();
    float x_camera = target.x;
    float z_camera = target.z;
    float y_camera = target.y - 0.2f;

    int ok_cladiri = 0;
	for (int i = 0;i < obiecte.size();i++) {
		if (obiecte[i].tip == 2) {
			float x = obiecte[i].x;
			float z = obiecte[i].z;
			float y = obiecte[i].y;
			float factor = obiecte[i].factor_scalare;
			float xmin = x - 0.75f * factor;
			float xmax = x + 0.75f * factor;
			float zmin = z - 0.5f * factor;
			float zmax = z + 0.5f * factor;
			float ymin = y - 0.0f * factor;
			float ymax = y + 1.0f * factor;

			if (x_camera >= (xmin-raza_drona) && x_camera <= (xmax+raza_drona) && z_camera >= (zmin-raza_drona) && z_camera <= (zmax+raza_drona) && y_camera >= ymin && y_camera <= ymax) {
				ok_cladiri = 1;
                break;
			}
           
		}
	}
	if (ok_cladiri == 1) {
		deplasareDrona1 = false;
	}
	else {
		deplasareDrona1 = true;
	}
}

// coliziune drona copaci
void Tema2::ColiziuneDronaCopaci() {
    glm::vec3 target = camera->GetTargetPosition();
    float x_camera = target.x;
    float z_camera = target.z;
    float y_camera = target.y - 0.2f;
    int ok_copaci = 0;
    for (int i = 0;i < obiecte.size();i++) {
        if (obiecte[i].tip == 1) {
            // pentru cilindru
            float x = obiecte[i].x;
            float z = obiecte[i].z;
            float y = obiecte[i].y;
            float factor = obiecte[i].factor_scalare;
       
            float ymin = y - 0.0f * factor;
            float ymax = y + 0.5f * factor;

			float dist_cilindru = sqrt((x_camera - x) * (x_camera - x) + (z_camera - z) * (z_camera - z));
			if (y_camera >= ymin && y_camera <= ymax && dist_cilindru <= 0.1f * factor+raza_drona) {
				ok_copaci = 1;
				break;
			}

            //pt primul con
            ymin = 0.5 * factor;
            ymax = (0.5f + 0.7f) * factor;

            float inaltime1 = ymax - ymin;
			float inaltime2 = ymax - y_camera;
            float ip1, ip2, cateta1, cateta2;
            if (y_camera >= ymin && y_camera <= ymax) {
				inaltime1 = ymax - ymin;
				inaltime2 = ymax - y_camera;
                cateta1 = 0.7f * factor;
				ip1 = sqrt(inaltime1 * inaltime1 + cateta1*cateta1);
				
				ip2 = ip1 * inaltime2 / inaltime1;
				cateta2 = cateta1 * ip2 / ip1;
				float dist_con = sqrt((x_camera - x) * (x_camera - x) + (z_camera - z) * (z_camera - z));
				if (dist_con<cateta2+raza_drona) {
					ok_copaci = 1;
					break;
				}
            }

          

            // pentru al doilea con
            ymin = (0.5f + 0.55f) * factor;
            ymax = (0.5f + 0.55f + 0.5f) * factor;

            inaltime1 = ymax - ymin;
            inaltime2 = ymax - y_camera;
            ip1, ip2, cateta1, cateta2;
            if (y_camera >= ymin && y_camera <= ymax) {
                inaltime1 = ymax - ymin;
                inaltime2 = ymax - y_camera;
                cateta1 = 0.7f * factor;
                ip1 = sqrt(inaltime1 * inaltime1 + cateta1 * cateta1);

                ip2 = ip1 * inaltime2 / inaltime1;
                cateta2 = cateta1 * ip2 / ip1;
                float dist_con = sqrt((x_camera - x) * (x_camera - x) + (z_camera - z) * (z_camera - z));
                if (dist_con < cateta2 + raza_drona) {
                    ok_copaci = 1;
                    break;
                }
            }


           
        }
    }
    if (ok_copaci == 1) {
        deplasareDrona2 = false;
    }
    else {
        deplasareDrona2 = true;
    }
}

// pozitionare statica copaci
void Tema2::PozitionareStaticaCopaci() {
    float x = 10.0f;
    float z = 7.0f;
    float factor = 3.5f;
    for (int i = 0;i < 7;i++) {
        z = 7.0f + i;
        for (int j = 0;j < 8;j++) {
            if ((i + j) % 2 == 0)
                factor = 3.5f;
            else
                factor = 4.2f;

            if((i+j)%5==0)
				factor = 5;

            if (i % 3 == 0) {
                x += i;
                z += i;
                factor = 6.5f;
            }
            
            if (z > 180)
                z = 170;
            if (x > 180)
                x = 167;
            struct Obiecte copac;
            copac.x = x ;
            copac.y = 0;
            copac.z = z;
			copac.factor_scalare = factor;
			copac.tip = 1;//copac
            
			obiecte.push_back(copac);
            z += 18;
        }
		x += 20;
    }
}

// pozitionare statica cladiri
void Tema2::PozitionareStaticaCladiri() {
    struct Obiecte cladire;

    cladire.x = 20;
    cladire.y = 0;
    cladire.z = 40;
    cladire.factor_scalare = 5;
    cladire.tip = 2;
    obiecte.push_back(cladire);

    cladire.x = 20;
    cladire.y = 0;
    cladire.z = 95;
    cladire.factor_scalare = 3;
    cladire.tip = 2;
    obiecte.push_back(cladire);

    cladire.x = 42;
    cladire.y = 0;
    cladire.z = 10;
    cladire.factor_scalare = 3;
    cladire.tip = 2;
    obiecte.push_back(cladire);

    cladire.x = 125;
    cladire.y = 0;
    cladire.z = 70;
    cladire.factor_scalare = 4.2;
    cladire.tip = 2;
    obiecte.push_back(cladire);

    cladire.x = 160;
    cladire.y = 0;
    cladire.z = 90;
    cladire.factor_scalare = 4.9;
    cladire.tip = 2;
    obiecte.push_back(cladire);

    cladire.x = 135;
    cladire.y = 0;
    cladire.z = 160;
    cladire.factor_scalare = 5.5;
    cladire.tip = 2;
    obiecte.push_back(cladire);
}

// pozitionare random copaci
void Tema2::PozitionareRandomCopaci() {
    float x=0;
    float z=0;
    float factor = 2.7f;
	int ok1 = 0;
    int nr = 0;
    for (int i = 0;i < 5;i++) {
        x = rand() % 170 + 1;
        z = rand() % 170 + 1;
        
        ok1 = 0;
        for (int k = 0;k < obiecte.size();k++){
            if (obiecte[k].tip == 1) {
                float dist_x = (obiecte[k].x - x) * (obiecte[k].x - x);
                float dist_z = (obiecte[k].z - z) * (obiecte[k].z - z);
                if (sqrt(dist_x + dist_z) <= 0.7f * (obiecte[k].factor_scalare + factor)) {
                    ok1 = 1;
                    break;
                }
            }
            else {
                float dist_x = (obiecte[k].x - x) * (obiecte[k].x - x);
                float dist_z = (obiecte[k].z - z) * (obiecte[k].z - z);
                if (sqrt(dist_x + dist_z) <= 0.9f * obiecte[k].factor_scalare + factor*0.7f) {
                    ok1 = 1;
                    break;
                }
            }

        }
        if (ok1 == 0) {
            struct Obiecte copac;
            copac.x = x;
            copac.y = 0;
            copac.z = z;
            copac.factor_scalare = factor;
            copac.tip = 1;//copac
            obiecte.push_back(copac);
            nr++;
            cout << "Coordonate copac random: x=" << x << "  z=" << z << endl;
        }
        else {
            i--;
        }
    }
	cout << "S-au pozitionat random " << nr <<" copaci" << endl<<endl;

}

// pozitionez random pachetul si destinatia de livrare
void Tema2::PozitionareRandomPachetSiLivrare() {
    int ok1 = 1;
	float factor = 0.3f;

    while(ok1==1) {
        x_pachet = rand() % 170 + 1;
        z_pachet = rand() % 170 + 1;

        ok1 = 0;
        for (int k = 0;k < obiecte.size();k++) {
            if (obiecte[k].tip == 1) {
                float dist_x = (obiecte[k].x - x_pachet) * (obiecte[k].x - x_pachet);
                float dist_z = (obiecte[k].z - z_pachet) * (obiecte[k].z - z_pachet);
                if (sqrt(dist_x + dist_z) <= 0.7f * obiecte[k].factor_scalare + factor*0.3f) {
                    ok1 = 1;
                    break;
                }
            }
            else {
                float dist_x = (obiecte[k].x - x_pachet) * (obiecte[k].x - x_pachet);
                float dist_z = (obiecte[k].z - z_pachet) * (obiecte[k].z - z_pachet);
                if (sqrt(dist_x + dist_z) <= 0.9f * obiecte[k].factor_scalare + factor * 0.3f) {
                    ok1 = 1;
                    break;
                }
            }

        }
       
    }
	//cout << "x_pachet=" << x_pachet << "   z_pachet=" << z_pachet << endl;

    ok1 = 1;
    factor = 1.f;
    while (ok1 == 1) {
        x_livrare = rand() % 170 + 1;
        z_livrare = rand() % 170 + 1;

        ok1 = 0;
        for (int k = 0;k < obiecte.size();k++) {
            if (obiecte[k].tip == 1) {
                float dist_x = (obiecte[k].x - x_livrare) * (obiecte[k].x - x_livrare);
                float dist_z = (obiecte[k].z - z_livrare) * (obiecte[k].z - z_livrare);
                if (sqrt(dist_x + dist_z) <= 0.7f * obiecte[k].factor_scalare + factor * 0.3f) {
                    ok1 = 1;
                    break;
                }
            }
            else {
                float dist_x = (obiecte[k].x - x_livrare) * (obiecte[k].x - x_livrare);
                float dist_z = (obiecte[k].z - z_livrare) * (obiecte[k].z - z_livrare);
                if (sqrt(dist_x + dist_z) <= 0.9f * obiecte[k].factor_scalare + factor * 0.3f) {
                    ok1 = 1;
                    break;
                }
            }

        }

        float dist_x = (x_pachet - x_livrare) * (x_pachet - x_livrare);
        float dist_z = (z_pachet - z_livrare) * (z_pachet - z_livrare);
        // sa nu fie prea apropiate
        if (sqrt(dist_x + dist_z) <= 17) {
            ok1 = 1;
            break;
        }

    }
    //cout << "x_livrare=" << x_livrare << "   z_livrare=" << z_livrare << endl;


}

// desenez copacii
void Tema2::DesenareCopaci() {
    if (ok == 0) {
        PozitionareStaticaCopaci();
        PozitionareStaticaCladiri();
        PozitionareRandomCopaci();
        ok = 1;
    }

    for (int i = 0;i < obiecte.size();i++) {
        if (obiecte[i].tip == 1) {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(obiecte[i].x, obiecte[i].y, obiecte[i].z));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(obiecte[i].factor_scalare));
            RenderMesh(meshes["copac"], shaders["VertexColor"], modelMatrix);
        }
    }
   
}

// desenez cladirile
void Tema2::DesenareCladiri() {
    for (int i = 0;i < obiecte.size();i++) {
        if (obiecte[i].tip == 2) {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(obiecte[i].x, obiecte[i].y, obiecte[i].z));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(obiecte[i].factor_scalare));
            RenderMesh(meshes["cladire"], shaders["VertexColor"], modelMatrix);
        }
    }
}

// coliziune drona pachet
void Tema2::ColiziunePachet() {
    glm::vec3 target = camera->GetTargetPosition();
    float x_camera = target.x;
    float z_camera = target.z;
    float y_camera = target.y - 0.2f;

    float x_dist = (x_camera - x_pachet) * (x_camera - x_pachet);
    float z_dist = (z_camera - z_pachet) * (z_camera - z_pachet);
    float y_dist = (y_camera - 0.5f) * (y_camera - 0.5f);
    if (y_camera > 0.5f && sqrt(x_dist + y_dist + z_dist) < 0.5f) {
        pachet_luat = true;
    }
}

// coliziune drona loc livrare
void Tema2::ColiziuneLocLivrare() {
    glm::vec3 target = camera->GetTargetPosition();
    float x_camera = target.x;
    float z_camera = target.z;
    float y_camera = target.y - 0.2f;

    float x_dist = (x_camera - x_livrare) * (x_camera - x_livrare);
    float z_dist = (z_camera - z_livrare) * (z_camera - z_livrare);
    float y_dist = (y_camera - 0.5f) * (y_camera - 0.5f);
    if (y_camera > 0.5f && x_camera>=(x_livrare-0.3f) && x_camera<= (x_livrare +0.3f)&& z_camera >= (z_livrare - 0.3f) && z_camera <= (z_livrare + 0.3f) &&sqrt(x_dist + y_dist + z_dist) < 1.0f) {
        pachet_luat = false;
		ok_random = true;
        nr_pachete++;
		cout << "Pachetul a fost livrat cu succes!" << endl;
		cout << "Numarul de pachete livrate: " << nr_pachete << endl;
    }
}

// desenare pachet
void Tema2::DesenarePachet() {
    if(!pachet_luat){
        float x, z;
        if (ok_random) {
            PozitionareRandomPachetSiLivrare();
            ok_random = false;
        }
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x_pachet, 0.5f, z_pachet));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f));
        RenderMesh(meshes["pachet"], shaders["VertexColor"], modelMatrix);
    }
    else {
        float factor_scalare = 0.1f;
 
        glm::vec3 forward = camera->forward;
        glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
        glm::vec3 up = glm::normalize(glm::cross(right, forward));

        glm::mat4 rotation = glm::mat4(1.0f);
        rotation[0] = glm::vec4(right, 0);     
        rotation[1] = glm::vec4(up, 0);       
        rotation[2] = glm::vec4(-forward, 0); 

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.2f-factor_scalare*0.8-0.4f*0.15f, 0));
        modelMatrix *= rotation;
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f));
        RenderMesh(meshes["pachet"], shaders["VertexColor"], modelMatrix);

    }
}

// desenare loc livrare
void Tema2::DesenareLocLivrare() {
	if (pachet_luat) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(x_livrare, 0.3f, z_livrare));
		RenderMesh(meshes["loclivrare"], shaders["VertexColor"], modelMatrix);
	}
}

void Tema2::DesenareSageata() {
    glm::vec3 obiect_poz;
	if (!pachet_luat)
		obiect_poz = glm::vec3(x_pachet, 0, z_pachet);
	else
		obiect_poz = glm::vec3(x_livrare, 0, z_livrare);
  
    glm::vec3 poz = camera->position;
    poz.y += 0.05f;
    glm::vec3 sageatapoz = poz + camera->forward * 1.0f;
    glm::vec3 directie = glm::normalize(obiect_poz - sageatapoz);

    
    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::mat4 rotationMatrix = glm::lookAt(glm::vec3(0), directie, up);
    rotationMatrix = glm::transpose(rotationMatrix);

    
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, sageatapoz);
    modelMatrix *= rotationMatrix; 
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
    RenderMesh(meshes["sageata"], shaders["VertexColor"], modelMatrix);
}

void Tema2::RenderSceneViewPort() {
    DesenareCopaci();
    DesenareCladiri();
    DesenareTeren();
    DesenareDrona(17);
	DesenarePachet();
	DesenareLocLivrare();
	DesenareSageata();
}
void Tema2::Update(float deltaTimeSeconds)
{
    DesenareSageata();
    ColiziuneDronaTeren();
	ColiziuneDronaCladiri();
    ColiziuneDronaCopaci();
	DesenareCopaci();
    DesenareCladiri();

    DesenareTeren();

    DesenareDrona(deltaTimeSeconds);
    DesenarePachet();
    ColiziunePachet();
    DesenareLocLivrare();
    ColiziuneLocLivrare();
    

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);


    RenderSceneViewPort();
   

}


void Tema2::FrameEnd()
{
    //DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
  
    mesh->Render();
}



void Tema2::OnInputUpdate(float deltaTime, int mods)
{
        float cameraSpeed = 2.0f;

        // propulsie
        if (window->KeyHold(GLFW_KEY_W) && deplasareDrona1 && deplasareDrona2) {
            camera->TranslateUpward(deltaTime * cameraSpeed*5);
        }
        if (window->KeyHold(GLFW_KEY_S) && deplasareDrona && deplasareDrona1 && deplasareDrona2) {
            camera->TranslateUpward(-deltaTime * cameraSpeed * 5);
        }

        // rotatie oy
        if (window->KeyHold(GLFW_KEY_A)) {
            camera->RotateThirdPerson_OY(deltaTime * cameraSpeed);
        }
        if (window->KeyHold(GLFW_KEY_D)) {
            camera->RotateThirdPerson_OY(-deltaTime * cameraSpeed);
        }

        // rotatie ox
        if (window->KeyHold(GLFW_KEY_UP)) {
            camera->RotateThirdPerson_OX(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_DOWN)) {
            camera->RotateThirdPerson_OX(-deltaTime * cameraSpeed);
        }
    
        // rotatie oz
        if (window->KeyHold(GLFW_KEY_LEFT)) {
            camera->RotateThirdPerson_OZ(-deltaTime * cameraSpeed/10);
        }

        if (window->KeyHold(GLFW_KEY_RIGHT)) {
            camera->RotateThirdPerson_OZ(deltaTime * cameraSpeed/10);
        }


        // controale deplasare oe oX oY si oZ cum zice prima data in animatie
        if (window->KeyHold(GLFW_KEY_I) && deplasareDrona1 && deplasareDrona2) {
            camera->TranslateUpward(deltaTime * cameraSpeed *2);

        }

        if (window->KeyHold(GLFW_KEY_K) && deplasareDrona) {
            camera->TranslateUpward(-deltaTime * cameraSpeed * 2);
        }
        if (window->KeyHold(GLFW_KEY_U) && deplasareDrona && deplasareDrona1 && deplasareDrona2) {
            camera->TranslateForward(deltaTime * cameraSpeed *8 );

        }

        if (window->KeyHold(GLFW_KEY_O)) {
            camera->TranslateForward(-deltaTime * cameraSpeed*8);
        }

        if (window->KeyHold(GLFW_KEY_J)) {
            camera->TranslateRight(-deltaTime * cameraSpeed*5);
        }

        if (window->KeyHold(GLFW_KEY_L)) {
            camera->TranslateRight(deltaTime * cameraSpeed*5);
        }

}


void Tema2::OnKeyPress(int key, int mods)
{
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
