#include "GameLayer.h"


std::unique_ptr<GameLayer::GameData> GameLayer::m_GameData = std::make_unique<GameData>();

GameLayer::GameLayer()
{
    m_ViewportWidth = Application::Get().GetWindowWidth();
    m_ViewportHeight = Application::Get().GetWindowHeight();

    /*m_GameData = std::make_unique<GameData>();*/
}

GameLayer::~GameLayer()
{
    delete(camera);
    delete(tex);
}

void GameLayer::OnCreate()
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //m_terrain = new Terrain(512.0f, 512.0f);
    // TERRAIN
    float verticesT[] = {
        // positions          // colors           
         -1000.0f,  -0.5f, -1000.0f,   0.0f, 0.5f, 0.25f, 0.0f, 0.0f,   // top right
          1000.0f,  -0.5f, -1000.0f,   0.0f, 0.5f, 0.25f, 1000.0f, 0.0f,    // bottom right
          1000.0f,  -0.5f,  1000.0f,   0.0f, 0.5f, 0.25f, 1000.0f, 1000.0f,    // bottom left
         -1000.0f,  -0.5f,  1000.0f,   0.0f, 0.5f, 0.25f, 0.0f, 1000.0f,    // top left 
    };

    uint32_t indicesT[6] = {  // note that we start from 0!
    0, 1, 2,   // first triangle
    0, 2, 3,    // second triangle
    };


    // Create Camera
    camera = new CameraController(m_ViewportWidth, m_ViewportHeight, 40.0f, 1.0f, 5000.0f);

    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // top left 

        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // top left 

        // positions          // colors           // texture coords
         0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right 0
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
         0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top left 

        -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // top left 

         0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top 
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,

         0.5f,  -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // bottom
         0.5f,  -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        -0.5f,  -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f,
        -0.5f,  -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
    };
    uint32_t indices[36] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3,    // second triangle

        4, 5, 7,
        5, 6, 7,

        8, 9, 11,
        9, 10,11,

        12, 13, 15,
        13, 14, 15,

        16, 17, 19,
        17, 18, 19,

        20, 21, 23,
        21, 22, 23
    };
    m_indices = &indices[0];

    float range = 10.0f;
    int rangei = (int)range;

    //glm::vec3 cubepos[N];
    // 
    // 
    // 
    // INITIALIZE ENTITIES
    cubepos = new glm::vec3[N];
    cubepos_ini = new glm::vec3[N];
    vel = new float[N];
    for (int i = 0; i < N; i++)
    {
        auto entity = m_Registry.create();
        auto& trans = m_Registry.emplace<TransformComponent>(entity);
        trans.Value = GetGridPosFromIndex(i, 1000);
        trans.Value.y = m_terrain->getheight(trans.Value.x, trans.Value.z);
        trans.idx = i;
        trans.offset = GetGridPosFromIndex(i, 1000);;
        auto& velocity = m_Registry.emplace<VelocityComponent>(entity);
        velocity.norm = glm::gaussRand(3.0f, 0.2f);
        velocity.idx = i;

        cubepos_ini[i] = GetGridPosFromIndex(i, 1000);
        cubepos[i] = GetGridPosFromIndex(i, 1000);
        vel[i] = velocity.norm;
    }
    
    
    m_VAO = std::make_shared<VertexArray>();
    m_VAO->Bind();
    m_VBO = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
    BufferLayout layout = {
        {ShaderDataType::Float3, "aPos"},
        {ShaderDataType::Float3, "aColor" },
        {ShaderDataType::Float2, "aTexCoord"}
    };
    m_VBO->SetLayout(layout);
    
    m_IBO = std::make_shared<IndexBuffer>(indices, sizeof(indices)/sizeof(uint32_t));
    m_VAO->AddVertexBuffer(m_VBO);
    m_VAO->SetIndexBuffer(m_IBO);


    KGLOG(sizeof(cubepos))
    instancedVBO = std::make_shared<VertexBuffer>(cubepos, N * sizeof(glm::vec3));
    BufferLayout layout2 = {
        {ShaderDataType::Float3, "instanced_Pos"}
    };
    instancedVBO->SetLayout(layout2);
    glVertexAttribDivisor(3, 1);


    m_VAO->AddVertexBuffer(instancedVBO, true);


    //- terrain
    m_VAOT = std::make_shared<VertexArray>();
    m_VAOT->Bind();
    m_VBOT = std::make_shared<VertexBuffer>(verticesT, sizeof(verticesT));
    BufferLayout layoutT = {
        {ShaderDataType::Float3, "aPos"},
        {ShaderDataType::Float3, "aColor" },
        {ShaderDataType::Float2, "aTexCoord"}
    };
    m_VBOT->SetLayout(layoutT);

    m_IBOT = std::make_shared<IndexBuffer>(indicesT, sizeof(indicesT) / sizeof(uint32_t));
    m_VAOT->AddVertexBuffer(m_VBOT);
    m_VAOT->SetIndexBuffer(m_IBOT);
    // --- Shaders ----
    //Shader myshader("Ressources/shaders/vertexshader.vs", "Ressources/shaders/fragshader.fs");
    myshader = std::make_shared<Shader>("Ressources/shaders/vertexshader.vs", "Ressources/shaders/fragshader.fs");
    myshader->use();

    //Texture tex("Ressources/textures/container.jpg");
    tex = new Texture("Ressources/textures/container.jpg");
    tex->BindTexture();
    myshader->setInt("texture1", 0);


    myshaderT = std::make_shared<Shader>("Ressources/shaders/terrainshader.vs", "Ressources/shaders/terrainshader.fs");
    myshaderT->use();

    texT = new Texture("Ressources/textures/ground.jpg");
    texT->BindTexture();
    myshaderT->setInt("texture1", 0);
    KGLOG("GameLayer Created")


}

void GameLayer::OnUpdate(const float& dT)
{
    
    camera->OnUpdate(dT);
    RendererAPI::BeginScene(camera->GetCamera());


    OnImGui();
    //update
    
    //m_Registry.view<TransformComponent, VelocityComponent>().each(
    //    [&](TransformComponent& trans, VelocityComponent& v) {

    //        if (glm::l2Norm((target + trans.offset) - trans.Value) > 0.1f ) 
    //        {
    //            trans.Value += glm::normalize((target + trans.offset)-trans.Value) * v.norm * dT;
    //            trans.Value.y = m_terrain->getheight2(trans.Value.x, trans.Value.z);

    //            cubepos[trans.idx] = trans.Value;

    //        }

    //    });

    //for (int i = 0; i < N; i++)
    //{
    //    cubepos[i] += glm::normalize(target - cubepos[i]) * vel[i] * dT;
    //}


    //-----------
    //m_VAO->Bind();
    //instancedVBO->Bind();
    myshader->use();
    tex->BindTexture();
    instancedVBO->SetData(cubepos, N * sizeof(glm::vec3));

    //glDrawElementsInstanced(GL_TRIANGLES, m_VAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0, N);
    RendererAPI::Submit(myshader, m_VAO);


    // NEW TERRAIN
    m_terrain->GetTerrainShader()->use();
    RendererAPI::SubmitElements(m_terrain->GetTerrainShader(), m_terrain->GetTerrainVAO(), m_terrain->GetTerrainVAO()->GetIndexBuffer()->GetCount());
}

void GameLayer::OnEvent(Event& e)
{
    camera->OnEvent(e);
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&GameLayer::OnMouseClicked, this, std::placeholders::_1));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&GameLayer::OnMouseReleased, this, std::placeholders::_1));
    dispatcher.Dispatch<KeyTypedEvent>(std::bind(&GameLayer::OnKeyTyped, this, std::placeholders::_1));

    //KGLOG(e.GetName())

}

bool GameLayer::OnMouseClicked(MouseButtonPressedEvent& e)
{
    if (Inputs::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
        target = Raycast::ShootRay(camera);

    if (!DragStart && Inputs::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {
        DragStart = true;
        DragFirst = glm::vec2(Inputs::GetMouseX(), Inputs::GetMouseY());
    }




    
    return false;
}

bool GameLayer::OnMouseReleased(MouseButtonReleasedEvent& e)
{

    if (DragStart) {
        DragStart = false;
        DragLast = glm::vec2(Inputs::GetMouseX(), Inputs::GetMouseY());
    }

    return false;
}

bool GameLayer::OnKeyTyped(KeyTypedEvent& e)
{
    KGLOG("Polygon mode activated/desactivated")
    if (e.GetKeyCode() == GLFW_KEY_F1 && !m_POLYGON_MODE) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        m_POLYGON_MODE = true;
        return false;
    }
        

    if (e.GetKeyCode() == GLFW_KEY_F1 && m_POLYGON_MODE)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        m_POLYGON_MODE = false;
        return false;
    }

    
    return false;
}

void GameLayer::OnImGui()
{
    {
        glm::vec3 campos = camera->GetCamera().GetPosition();
        ImGuiIO& io = ImGui::GetIO();
        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::Text("Game Data");
        ImGui::Text("Number of VBO : %u", m_VAO->GetInstancedCount());
        ImGui::Separator();
        ImGui::Text("cubepos[20] : %f,%f,%f", cubepos[1].x, cubepos[1].y, cubepos[1].z);
        ImGui::Text("Intersection : %f,%f,%f", target.x, target.y, target.z);
        ImGui::Separator();
        ImGui::Text("DragFirst : %f,%f", DragFirst.x, DragFirst.y);
        ImGui::Text("DragLast : %f,%f", DragLast.x, DragLast.y);
        ImGui::Separator();
       

        ImGui::Text("az %f", m_terrain->GetVBOCount());
        ImGui::End();
        
    }

}

// ---------------------
void GameLayer::ImGui_vec3(const char* label, glm::vec3& v)
{
    ImGui::Text("%s : %f,%f,%f",label, v.x, v.y, v.z);
}

void GameLayer::UpdateSystems()
{
}

void GameLayer::RenderSystems()
{
}


//--------------
glm::vec3 GameLayer::GetGridPosFromIndex(const unsigned int& index, const unsigned int& N)
{
    unsigned int width = N;
    unsigned int x = index % width;
    unsigned int y = (index - x) / width;

    return glm::vec3((float)x * 2.0f, 0.0f, (float)y * 2.0f);
}

void GameLayer::CreateTerrain() {

    terrain = new glm::vec3[N];
    for (int i = -N/2; i < N/2; i++)
    {
        terrain[i] = GetGridPosFromIndex(i, 100);
    }
}