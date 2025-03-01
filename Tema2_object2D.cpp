#include "Tema2_object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


// creez drona
Mesh* object2D::CreateDrona(
    const std::string& name,
    glm::vec3 color1,
    glm::vec3 color2)
{

    std::vector<VertexFormat> vertices
    {
        // primul paralelipiped
        // capul apropiat pe Oz
        VertexFormat(glm::vec3(-0.2f, -0.2f,  2), color1),
        VertexFormat(glm::vec3(0.2f, -0.2f, 2), color1),
        VertexFormat(glm::vec3(0.2f, 0.2f,  2), color1),
        VertexFormat(glm::vec3(-0.2f, 0.2f,  2), color1),
        // capul departat pe Oz
        VertexFormat(glm::vec3(-0.2f, -0.2f,  -2), color1),
        VertexFormat(glm::vec3(0.2f, -0.2f, -2), color1),
        VertexFormat(glm::vec3(0.2f, 0.2f,  -2), color1),
        VertexFormat(glm::vec3(-0.2f, 0.2f,  -2), color1),


        // al doilea paralelipiped
        VertexFormat(glm::vec3(-2, -0.2f,  -0.2f), color1),
        VertexFormat(glm::vec3(-2, -0.2f,  0.2f), color1),
        VertexFormat(glm::vec3(-2, 0.2f,  0.2f), color1),
        VertexFormat(glm::vec3(-2, 0.2f, - 0.2f), color1),

        VertexFormat(glm::vec3(2, -0.2f,  -0.2f), color1),
        VertexFormat(glm::vec3(2, -0.2f,  0.2f), color1),
        VertexFormat(glm::vec3(2, 0.2f,  0.2f), color1),
        VertexFormat(glm::vec3(2, 0.2f,  -0.2f), color1),


        // cub pt primul paralelipiped
        VertexFormat(glm::vec3(-0.2f, 0.2f,  2), color2),
        VertexFormat(glm::vec3(0.2f, 0.2f, 2), color2),
        VertexFormat(glm::vec3(0.2f, 0.6f,  2), color2),
        VertexFormat(glm::vec3(-0.2f, 0.6f,  2), color2),
        
        VertexFormat(glm::vec3(-0.2f, 0.2f,  1.6f), color2),
        VertexFormat(glm::vec3(0.2f, 0.2f, 1.6f), color2),
        VertexFormat(glm::vec3(0.2f, 0.6f,  1.6f), color2),
        VertexFormat(glm::vec3(-0.2f, 0.6f,  1.6f), color2),

        //al 2-lea cub
        VertexFormat(glm::vec3(-0.2f, 0.2f,  -2), color2),
        VertexFormat(glm::vec3(0.2f, 0.2f, -2), color2),
        VertexFormat(glm::vec3(0.2f, 0.6f,  -2), color2),
        VertexFormat(glm::vec3(-0.2f, 0.6f,  -2), color2),

        VertexFormat(glm::vec3(-0.2f, 0.2f,  -1.6f), color2),
        VertexFormat(glm::vec3(0.2f, 0.2f, -1.6f), color2),
        VertexFormat(glm::vec3(0.2f, 0.6f,  -1.6f), color2),
        VertexFormat(glm::vec3(-0.2f, 0.6f,  -1.6f), color2),


        //cub pt al doilea paralelipiped
        VertexFormat(glm::vec3(-2, 0.2f,  -0.2f), color2),
        VertexFormat(glm::vec3(-2, 0.2f,  0.2f), color2),
        VertexFormat(glm::vec3(-2, 0.6f,  0.2f), color2),
        VertexFormat(glm::vec3(-2, 0.6f, -0.2f), color2),

        VertexFormat(glm::vec3(-1.6f, 0.2f,  -0.2f), color2),
        VertexFormat(glm::vec3(-1.6f, 0.2f,  0.2f), color2),
        VertexFormat(glm::vec3(-1.6f, 0.6f,  0.2f), color2),
        VertexFormat(glm::vec3(-1.6f, 0.6f, -0.2f), color2),


        // al 2-lea cub
        VertexFormat(glm::vec3(1.6f, 0.2f,  -0.2f), color2),
        VertexFormat(glm::vec3(1.6f, 0.2f,  0.2f), color2),
        VertexFormat(glm::vec3(1.6f, 0.6f,  0.2f), color2),
        VertexFormat(glm::vec3(1.6f, 0.6f,  -0.2f), color2),

        VertexFormat(glm::vec3(2, 0.2f,  -0.2f), color2),
        VertexFormat(glm::vec3(2, 0.2f,  0.2f), color2),
        VertexFormat(glm::vec3(2, 0.6f,  0.2f), color2),
        VertexFormat(glm::vec3(2, 0.6f,  -0.2f), color2),


    };

    Mesh* corpDrona = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        //capacele
        0,1,2,
        0,2,3,
        4,5,6,
        4,6,7,
        //corpul
        0,1,5,//jos
        0,5,4,
        3,2,6,//sus
        3,6,7,
        2,1,5,//drepata
        2,5,6,
        4,0,3,//stanga
        4,3,7,

        // capacele
        8,9,10,
        8,10,11,
        14,13,12,
        14,12,15,

        // corpul
        8,9,13,//jos
        8,13,12,
        11,10,14,//sus
        11,14,15,
        10,9,13,//dreapta
        10,13,14,
        11,12,8,//stanga
        11,15,12,


        // cub1 primul paralelipiped
        16,17,18,
        16,18,19,
        20,21,22,
        20,22,23,
        16,17,21,
        16,21,20,
        19,18,22,
        19,22,23,
        18,17,21,
        18,21,22,
        19,16,20,
        19,20,23,

        // cub2
        24,25,26,
        24,26,27,
        28,29,30,
        28,30,31,

        28,29,25,
        28,25,24,
        31,30,26,
        31,26,27,
        30,29,25,
        30,25,26,
        31,28,24,
        31,24,27,


        // cub3 pt al 2-lea paralelipiped
        32,33,34,
        32,34,35,
        36,37,38,
        36,38,39,

        32,33,37,
        32,37,36,
        35,34,38,
        35,38,39,
        34,33,37,
        34,37,38,
        35,32,36,
        35,36,39,

        // cub4
        40,41,42,
        40,42,43,
        44,45,46,
        44,46,47,

        40,41,45,
        40,45,44,
        43,42,46,
        43,46,47,
        42,41,45,
        42,45,46,
        43,40,44,
        43,44,47,

    };

    corpDrona->InitFromData(vertices, indices);
    return corpDrona;
}

// creez elicea pt drona
Mesh* object2D::CreateElice(
    const std::string& name,
    glm::vec3 color)
{

    std::vector<VertexFormat> vertices
    {
        
        VertexFormat(glm::vec3(-0.3f, -0.05f,  -0.05f), color),
        VertexFormat(glm::vec3(-0.3f, -0.05f, 0.05f), color),
        VertexFormat(glm::vec3(-0.3f, 0.05f,  0.05f), color),
        VertexFormat(glm::vec3(-0.3f, 0.05f,  -0.05f), color),

        VertexFormat(glm::vec3(0.3f, -0.05f,  -0.05f), color),
        VertexFormat(glm::vec3(0.3f, -0.05f, 0.05f), color),
        VertexFormat(glm::vec3(0.3f, 0.05f,  0.05f), color),
        VertexFormat(glm::vec3(0.3f, 0.05f,  -0.05f), color),

    };

    Mesh* elice = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0,1,2,
        0,2,3,
        4,5,6,
        4,6,7,

        0,1,5,
        0,5,4,
        3,2,6,
        3,6,7,
        2,1,5,
        2,5,6,
        3,0,4,
        3,4,7,
    };

    elice->InitFromData(vertices, indices);
    return elice;
}

Mesh* object2D::CreateTeren(const std::string& name, int m, int n, glm::vec3 color) {
    
    float dim_patrat = 0.2f;
    std::vector<VertexFormat> vertices;
    for(int i=0;i<=m;i++)
        for (int j = 0;j <= n;j++) {
            vertices.push_back(VertexFormat(glm::vec3(j * dim_patrat, 0, i * dim_patrat), color));
        }

    Mesh* teren = new Mesh(name);
    std::vector<unsigned int> indices;

    for (int i = 0;i < m;i++)
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

    teren->InitFromData(vertices, indices);
    return teren;

}

Mesh* object2D::CreateCopac(
    const std::string& name,
    glm::vec3 color1,
    glm::vec3 color2)
{

    std::vector<VertexFormat> vertices;
    
    // creare cilindru
	float raza = 0.1f;
	float inaltime = 0.5f;
    for (int i = 0;i <= 30;i++) {
		float unghi = 2 * M_PI / 30 * i;
		float x = raza * cos(unghi);
		float z = raza * sin(unghi);
		vertices.push_back(VertexFormat(glm::vec3(x, 0, z), color1));
		vertices.push_back(VertexFormat(glm::vec3(x, inaltime, z), color1));
    }

    Mesh* copac = new Mesh(name);
    std::vector<unsigned int> indices;
    for (int i = 0;i < 30;i++) {
        indices.push_back(2 * i);
        indices.push_back(2 * (i + 1));
        indices.push_back(2 * i + 1);

        indices.push_back(2 * i + 1);
        indices.push_back(2 * (i + 1));
        indices.push_back(2 * (i + 1) + 1);
    }

    // creare con

    int nr_punte = 2 * (30 + 1);
    raza = 0.7f;
    vertices.push_back(VertexFormat(glm::vec3(0, inaltime + 0.7f, 0), color2));//varful conului
    vertices.push_back(VertexFormat(glm::vec3(0, inaltime, 0), color2));// certrului bazei conului
    nr_punte += 2;
    for (int i = 0;i <= 50;i++) {
        float unghi = 2 * M_PI / 50 * i;
        float x = raza * cos(unghi);
        float z = raza * sin(unghi);
        vertices.push_back(VertexFormat(glm::vec3(x, inaltime, z), color2));
    }
    for (int i = 0;i < 50;i++) {
        indices.push_back(nr_punte - 1);
        indices.push_back(nr_punte+i);
        indices.push_back(nr_punte + i+1);
    }

    for (int i = 0;i < 50;i++) {
        indices.push_back(nr_punte - 2);
        indices.push_back(nr_punte + i);
        indices.push_back(nr_punte + i + 1);
    }

    // al doilea con
    nr_punte+=51;
    raza = 0.55f;
    vertices.push_back(VertexFormat(glm::vec3(0, inaltime + 0.55f+0.5f, 0), color2));//varful conului
    vertices.push_back(VertexFormat(glm::vec3(0, inaltime+0.55f, 0), color2));// certrului bazei conului
    nr_punte += 2;
    for (int i = 0;i <= 50;i++) {
        float unghi = 2 * M_PI / 50 * i;
        float x = raza * cos(unghi);
        float z = raza * sin(unghi);
        vertices.push_back(VertexFormat(glm::vec3(x, inaltime+0.55f, z), color2));
    }
    for (int i = 0;i < 50;i++) {
        indices.push_back(nr_punte - 1);
        indices.push_back(nr_punte + i);
        indices.push_back(nr_punte + i + 1);
    }

    for (int i = 0;i < 50;i++) {
        indices.push_back(nr_punte - 2);
        indices.push_back(nr_punte + i);
        indices.push_back(nr_punte + i + 1);
    }
    
    copac->InitFromData(vertices, indices);
    return copac;
}


// creez cladirea
Mesh* object2D::CreateCladire(
    const std::string& name,
    glm::vec3 color1,
    glm::vec3 color2)
{

    std::vector<VertexFormat> vertices;

	// creare paralelipiped
	vertices.push_back(VertexFormat(glm::vec3(-0.75f, 0, 0.5f), color1));
	vertices.push_back(VertexFormat(glm::vec3(0.75f, 0, 0.5f), color1));
	vertices.push_back(VertexFormat(glm::vec3(0.75f, 0, -0.5f), color1));
	vertices.push_back(VertexFormat(glm::vec3(-0.75f, 0, -0.5f), color1));

    vertices.push_back(VertexFormat(glm::vec3(-0.75f, 1, 0.5f), color1));
    vertices.push_back(VertexFormat(glm::vec3(0.75f, 1, 0.5f), color1));
    vertices.push_back(VertexFormat(glm::vec3(0.75f, 1, -0.5f), color1));
    vertices.push_back(VertexFormat(glm::vec3(-0.75f, 1, -0.5f), color1));


    // creare acoperis
    /*vertices.push_back(VertexFormat(glm::vec3(0, 1.4f, 0), color2));
    vertices.push_back(VertexFormat(glm::vec3(-0.75f, 1, 0.5f), color2));
    vertices.push_back(VertexFormat(glm::vec3(0.75f, 1, 0.5f), color2));
    vertices.push_back(VertexFormat(glm::vec3(0.75f, 1, -0.5f), color2));
    vertices.push_back(VertexFormat(glm::vec3(-0.75f, 1, -0.5f), color2));*/

    Mesh* cladire = new Mesh(name);
    std::vector<unsigned int> indices{
        0,1,2,
        0,2,3,
        4,5,6,
        4,6,7,

        0,1,5,
        0,5,4,
        3,2,6,
        3,6,7,

        5,1,2,
        5,2,6,
        4,0,3,
        4,3,7,

        // acoperisi
		/*8,9,10,
		8,10,11,
		8,11,12,
		8,12,9,*/
    };


	

    cladire->InitFromData(vertices, indices);
    return cladire;
}


// creez pachetul
Mesh* object2D::CreatePachet(
    const std::string& name,
    glm::vec3 color)
{

    std::vector<VertexFormat> vertices;

    // creare paralelipiped
    vertices.push_back(VertexFormat(glm::vec3(-0.3f, 0, 0.2f), color));
    vertices.push_back(VertexFormat(glm::vec3(0.3f, 0, 0.2f), color));
    vertices.push_back(VertexFormat(glm::vec3(0.3f, 0, -0.2f), color));
    vertices.push_back(VertexFormat(glm::vec3(-0.3f, 0, -0.2f), color));

    vertices.push_back(VertexFormat(glm::vec3(-0.3f, 0.4f, 0.2f), color));
    vertices.push_back(VertexFormat(glm::vec3(0.3f, 0.4f, 0.2f), color));
    vertices.push_back(VertexFormat(glm::vec3(0.3f, 0.4f, -0.2f), color));
    vertices.push_back(VertexFormat(glm::vec3(-0.3f, 0.4f, -0.2f), color));


  

    Mesh* pachet = new Mesh(name);
    std::vector<unsigned int> indices{
        0,1,2,
        0,2,3,
        4,5,6,
        4,6,7,

        0,1,5,
        0,5,4,
        3,2,6,
        3,6,7,

        5,1,2,
        5,2,6,
        4,0,3,
        4,3,7,

    };




    pachet->InitFromData(vertices, indices);
    return pachet;
}


// creez locul de livrare
Mesh* object2D::CreateLocLivrare(
    const std::string& name,
    glm::vec3 color1,
    glm::vec3 color2)
{

    std::vector<VertexFormat> vertices;

    // creare cilindru
    float raza = 0.3f;
    float inaltime = 0.3f;
    for (int i = 0;i <= 30;i++) {
        float unghi = 2 * M_PI / 30 * i;
        float x = raza * cos(unghi);
        float z = raza * sin(unghi);
        vertices.push_back(VertexFormat(glm::vec3(x, 0, z), color1));
        vertices.push_back(VertexFormat(glm::vec3(x, inaltime, z), color1));
    }

    Mesh* loclivrare = new Mesh(name);
    std::vector<unsigned int> indices;
    for (int i = 0;i < 30;i++) {
        indices.push_back(2 * i);
        indices.push_back(2 * (i + 1));
        indices.push_back(2 * i + 1);

        indices.push_back(2 * i + 1);
        indices.push_back(2 * (i + 1));
        indices.push_back(2 * (i + 1) + 1);
    }

    //cerc
	raza = 0.28f;
	vertices.push_back(VertexFormat(glm::vec3(0, 0.3f, 0), color2));
	for (int i = 0;i <= 30;i++) {
		float unghi = 2 * M_PI / 30 * i;
		float x = raza * cos(unghi);
		float z = raza * sin(unghi);
		vertices.push_back(VertexFormat(glm::vec3(x, 0.3f, z), color2));
	}
	for (int i = 0;i < 30;i++) {
		indices.push_back(62);
		indices.push_back(63 + i);
		indices.push_back(63 + i + 1);
	}

    loclivrare->InitFromData(vertices, indices);
    return loclivrare;
}

Mesh* object2D::CreateSageata(
    const std::string& name,
    glm::vec3 color)
{

    std::vector<VertexFormat> vertices{
        VertexFormat(glm::vec3(-0.1f,0,0),color),
        VertexFormat(glm::vec3(0.1f,0,0),color),
        VertexFormat(glm::vec3(-0.1f,0,-0.3f),color),
        VertexFormat(glm::vec3(0.1f,0,-0.3f),color),
        VertexFormat(glm::vec3(-0.3f,0,-0.3f),color),
        VertexFormat(glm::vec3(0.3f,0,-0.3f),color),
        VertexFormat(glm::vec3(0.0f,0,-0.45f),color),
    };

    Mesh* sageata = new Mesh(name);
    std::vector<unsigned int> indices{
        0,1,3,
        0,3,2,
        4,5,6,
    };

   

    sageata->InitFromData(vertices, indices);
    return sageata;
}