#include "GameLayer0.h"


std::unique_ptr<GameLayer0::GameData> GameLayer0::m_GameData = std::make_unique<GameData>();

GameLayer0::GameLayer0()
{
    m_ViewportWidth = Application::Get().GetWindowWidth();
    m_ViewportHeight = Application::Get().GetWindowHeight();
    OnCreate();
    /*m_GameData = std::make_unique<GameData>();*/
}

GameLayer0::~GameLayer0()
{
    delete(camera);
    delete(texT);
}

void GameLayer0::OnCreate()
{
    // Create Camera && Gizmos
    camera = new CameraController((float)m_ViewportWidth, (float)m_ViewportHeight, 40.0f, 1.0f, 5000.0f);
    m_gizmos = std::make_shared<Gizmos>();
    Raycast::Init(camera);
    // Create Terrain & Ground
    m_Terrain = new TerrainGenerator();

    // Create Spaceship with MarchingCubes
    m_mc = new MarchingCubes();

    KGLOG("GameLayer Created")
}

void GameLayer0::OnUpdate(const float& dT)
{
    camera->OnUpdate(dT);
    RendererAPI::BeginScene(camera->GetCamera());
    OnImGui();

    //update
    if(m_display.terrain)
        m_Terrain->Render();


    m_mc->Render();
    //ship_bp->Render();

    // ---- RENDER GIZMOS ----
    m_gizmos->RenderAll();
    // -----------------------
}

void GameLayer0::OnEvent(Event& e)
{
    camera->OnEvent(e);
    m_mc->OnEvent(e);
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&GameLayer0::OnMouseClicked, this, std::placeholders::_1));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&GameLayer0::OnMouseReleased, this, std::placeholders::_1));
    dispatcher.Dispatch<KeyTypedEvent>(std::bind(&GameLayer0::OnKeyTyped, this, std::placeholders::_1));
}

bool GameLayer0::OnMouseClicked(MouseButtonPressedEvent& e)
{
    if (Inputs::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
        target = Raycast::ShootRay(camera);

    if (!DragStart && Inputs::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {
        DragStart = true;
        DragFirst = glm::vec2(Inputs::GetMouseX(), Inputs::GetMouseY());
    }
    
    return false;
}

bool GameLayer0::OnMouseReleased(MouseButtonReleasedEvent& e)
{
    if (DragStart) {
        DragStart = false;
        DragLast = glm::vec2(Inputs::GetMouseX(), Inputs::GetMouseY());
    }

    return false;
}

bool GameLayer0::OnKeyTyped(KeyTypedEvent& e)
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

void GameLayer0::OnImGui()
{
    { 
        ImGui::ShowDemoWindow();
        
        glm::vec3 campos = camera->GetCamera().GetPosition();
        ImGuiIO& io = ImGui::GetIO();
        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::Text("campos : %f,%f,%f", campos.x, campos.y, campos.z);

        ImGui::Text("Yaw : %f, Pitch : %f", camera->GetCamera().GetYawPitch().x, camera->GetCamera().GetYawPitch().y);
        ImGui::Separator();
        ImGui::Text("DragFirst : %f,%f", DragFirst.x, DragFirst.y);
        ImGui::Text("DragLast : %f,%f", DragLast.x, DragLast.y);
        ImGui::Text("target : %f,%f,%f", target.x, target.y, target.z);
        ImGui::Separator();

        m_gizmos->RefreshGridColor();
        if (ImGui::CollapsingHeader("Gizmos & Grid"))
        {
            ImGui::Checkbox("Show Gizmo"    , &m_gizmos->m_display.gizmo);
            ImGui::Checkbox("Show Base Grid", &m_gizmos->m_display.basegrid);
            if (ImGui::ColorEdit3("Grid Color##1", (float*)&m_gizmos->m_display.m_gridcolor))
                m_gizmos->RefreshGridColor();
        }

        if (ImGui::CollapsingHeader("Marching Cubes"))
        {


            int cube_idx = m_mc->Index(m_mc->mc_display_opts.select_cube);
            //ImGui::Text("DX,DZ : %i,%i", m_mc->mc_select_opts.dX, m_mc->mc_select_opts.dZ);
            if (ImGui::Button("Add"))
                m_mc->SetGridPointValue(cube_idx, 1.0f); // value of 1.0 by default
            if(ImGui::Button("Del"))
                m_mc->SetGridPointValue(cube_idx, 1.0f); // value of 1.0 by default

            ImGui::VSliderInt("X", ImVec2(18, 160), &m_mc->mc_display_opts.select_cube.x, 0, m_mc->getGridDimension().x);
            ImGui::SameLine();
            ImGui::VSliderInt("Z", ImVec2(18, 160), &m_mc->mc_display_opts.select_cube.z, 0, m_mc->getGridDimension().z);
            ImGui::SameLine();
            ImGui::VSliderInt("Y", ImVec2(18, 160), &m_mc->mc_display_opts.select_cube.y, 0, m_mc->getGridDimension().y);

            ImGui::Text("# triangles / Max triangles: %i / %i",m_mc->getCountTriangles(), m_mc->getMaxTriangles());
            ImGui::Separator();

            ImGui::DragFloat("aaa", &m_mc->mc_edit_points_opts.value, 0.1f, 0.0f, 1.0f);
            if (ImGui::InputFloat("Point value", &m_mc->mc_edit_points_opts.value,0.1f,0.1f,"%.1f"))
                m_mc->SetGridPointValue(m_mc->mc_edit_points_opts.selected_point, m_mc->mc_edit_points_opts.value);// value of 1.0 by default
        }

        if (ImGui::CollapsingHeader("Terrain"))
        {
            ImGui::Checkbox("Display Ground Terrain", &m_display.terrain);
            ImGui::SliderFloat("Height Factor", &m_Terrain->m_HeightFactor, 0.0f, 32.0f);
        }
        ImGui::End();
    }

}

// ---------------------
void GameLayer0::ImGui_vec3(const char* label, glm::vec3& v)
{
    ImGui::Text("%s : %f,%f,%f",label, v.x, v.y, v.z);
}

void GameLayer0::UpdateSystems()
{
}

void GameLayer0::RenderSystems()
{
}
