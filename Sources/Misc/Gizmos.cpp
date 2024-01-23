#include "Gizmos.h"

Gizmos::Gizmos()
{   


    int i;
    BufferLayout layout;
    // Y=0 GRID
    i = 0;
    glm::vec3 grid_color = glm::vec3(0.5);

    m_VAO[i] = std::make_shared<VertexArray>();
    m_VAO[i]->Bind();
    m_VBO[i] = std::make_shared<VertexBuffer>(0);
    m_VAO[i]->AddVertexBuffer(m_VBO[i]);

    m_shader[i] = std::make_shared<Shader>(
        "Ressources/shaders/gizmo/basegrid_vs.glsl",
        "Ressources/shaders/gizmo/basegrid_fs.glsl",
        "Ressources/shaders/gizmo/basegrid_gs.glsl");
    m_shader[i]->use();


    // AXIS GIZMO
    i = 1;
    float axis_length = 1.0f;
    float gizmo_points[] = { 0.0f , 0.0f, 0.0f , 0.0f , 0.0f, 1.0f,
                            axis_length , 0.0f , 0.0f , 0.0f, 0.0f, 1.0f,
                            0.0f , 0.0f, 0.0f  , 0.0f , 1.0f, 0.0f,
                            0.0f , axis_length , 0.0f , 0.0f, 1.0f, 0.0f,
                            0.0f , 0.0f, 0.0f  , 1.0f , 0.0f, 0.0f,
                            0.0f , 0.0f, axis_length  , 1.0f, 0.0f, 0.0f,
    };

    m_VAO[i] = std::make_shared<VertexArray>();
    m_VAO[i]->Bind();
    m_VBO[i] = std::make_shared<VertexBuffer>(gizmo_points, sizeof(float) * 6*6);

    layout = {
    {ShaderDataType::Float3, "aPos"},
    {ShaderDataType::Float3, "aColor"},
    };
    m_VBO[i]->SetLayout(layout);
    m_VAO[i]->AddVertexBuffer(m_VBO[i]);

    m_shader[i] = std::make_shared<Shader>(
        "Ressources/shaders/gizmo/gizmo_vs.glsl",
        "Ressources/shaders/gizmo/gizmo_fs.glsl");
    m_shader[i]->use();
}

Gizmos::~Gizmos()
{
}

void Gizmos::RenderAll()
{
    glLineWidth(2.0f);

    if (m_display.gizmo)
        RenderGizmo();
    if (m_display.basegrid)
        RenderGrid();

    glLineWidth(1.0f);
}

void Gizmos::RenderGrid()
{
    m_shader[0]->use();
    RendererAPI::DrawPoints(m_shader[0], m_VAO[0], 3);
}

void Gizmos::RenderGizmo()
{
    m_shader[1]->use();
    RendererAPI::DrawLines(m_shader[1], m_VAO[1], 6*6);
}

void Gizmos::RefreshGridColor()
{
    m_shader[0]->use();
    m_shader[0]->setVec3("u_Color", m_display.m_gridcolor);
}

