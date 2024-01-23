#include "SpaceshipBlueprint.h"

SpaceshipBlueprint::SpaceshipBlueprint()
{

    g_vertex = new int[grid.x * grid.y] {
        0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 0, 0,
        0, 1, 1, 1, 1, 0, 0,
        0, 0, 1, 1, 1, 0, 0,
        0, 1, 1, 1, 1, 0, 0,
        0, 0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0,
    };

    c_vertex = new int[grid.x * grid.y];

    m_count = grid.x * grid.y;

    PropagateMarchingSquare();
    Init();
}

SpaceshipBlueprint::~SpaceshipBlueprint()
{
    /*delete g_vertex, c_vertex;*/
}

void SpaceshipBlueprint::Init()
{
    float r = 0.2f;


	m_VAO = std::make_shared<VertexArray>();
	m_VAO->Bind();
    m_VBO = std::make_shared<VertexBuffer>(c_vertex,  8 * m_count);

    BufferLayout layout = {
    {ShaderDataType::Int, "aPos"},
    };
    m_VBO->SetLayout(layout);
	m_VAO->AddVertexBuffer(m_VBO);
    
    KGLOG(m_count);
    // --- Shaders ----
    m_shader = std::make_shared<Shader>(
        "Ressources/shaders/shaders_SpaceshipBlueprint/blueprint_vs.glsl",
        "Ressources/shaders/shaders_SpaceshipBlueprint/blueprint_fs.glsl",
        "Ressources/shaders/shaders_SpaceshipBlueprint/blueprint_gs.glsl");
    m_shader->use();
}

void SpaceshipBlueprint::PropagateMarchingSquare()
{
    
    
    for (int i = 0; i < grid.y - 1; i++)
    {
        for (int j = 0; j < grid.x - 1; j++)
        {
            int idx  = (i    ) * grid.x + j;
            int idx2 = (i    ) * grid.x + j + 1;
            int idx3 = (i + 1) * grid.x + j + 1;
            int idx4 = (i + 1) * grid.x + j;

            int val = 8 * g_vertex[idx] + 4 * g_vertex[idx2] + 2 * g_vertex[idx3] + g_vertex[idx4];

            c_vertex[i * grid.x + j] = val;

            std::cout << val << " = " << std::bitset<8>(val) << std::endl;

        }
    }

}

void SpaceshipBlueprint::Render()
{
    m_shader->use();
    m_shader->setiVec2("u_grid", grid);
    //RendererAPI::DrawPoints(m_shader, m_VAO, m_count); //TO DO: cast mcount to int
    RendererAPI::DrawPoints(m_shader, m_VAO, m_count); //TO DO: cast mcount to int
}
