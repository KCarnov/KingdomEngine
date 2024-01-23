#include "MarchingCubes.h"

grid LinearInterp(grid p2, grid p1, float value, int plane)
{
    grid p;
    p.val = ((value - p1.val) / (p2.val - p1.val));

    if (p1.val != p2.val) {
        p.pos = p1.pos +  ((value - p1.val) / (p2.val - p1.val)) * (p2.pos - p1.pos);
        p.level = p1.level + (p2.level - p1.level) / 2.0;
    }
    else {
        p.pos = p1.pos;
        p.level = p1.level;
    }
    return p;
}

MarchingCubes::MarchingCubes() :
    nX(10), nY(4), nZ(10)
{
    
    MAX_TRIANGLES = 4 * nX * nY * nZ;
    m_count_points = (nX + 1) * (nY + 1) * (nZ + 1);
    m_vertices_per_level = (nX + 1) * (nZ + 1);
    m_grid = new grid[m_count_points];


    m_stepSize = glm::vec3((MAXX - MINX) / nX, (MAXY - MINY) / nY, (MAXZ - MINZ) / nZ);
    for (int y = 0; y < nY + 1; y++)          // y axis
        for (int z = 0; z < nZ + 1; z++)      // z axis 
            for (int x = 0; x < nX + 1; x++)  // x axis
            {
                glm::vec3 pos = { MINX + x * m_stepSize.x ,  MINY + y * m_stepSize.y , MINZ + z * m_stepSize.z };
                grid vert;
                vert.pos = pos;
                vert.val = 100.0;
                vert.level = (float)y;
                vert.g_cubeIndexType = 0;
                m_grid[y * (nX + 1) * (nZ + 1) + z * (nX + 1) + x] = vert;
            }


    m_triangles = PropagateMarchingSquare(nX, nY, nZ, gridthresold, m_grid);

    InitBuffers();
    m_shader->use();
    m_shader->setInt("u_vertices_per_level", m_vertices_per_level);

    m_shaderg->use();
    m_shaderg->setVec3("u_stepsize", m_stepSize);
    m_shaderg->setInt("u_vertices_per_level", m_vertices_per_level);

    m_shadersc->use();
    m_shadersc->setVec3("u_stepsize", m_stepSize);

}

MarchingCubes::~MarchingCubes()
{
}



void MarchingCubes::Render()
{
    OnImGui();
    if (mc_display_opts.marching_cubes)
        if(!m_stoprender)
            RenderShip();

    if(mc_display_opts.blueprint_grid)
        RenderGrid();

    

    GetIndexFromRaycast(); // update selected cell from mouse position every frame (without click)
    if (mc_select_opts.DragStart)
        UpdateRectangleSelection();
    else {
        mc_select_opts.dX = 1;
        mc_select_opts.dZ = 1;
    }
    mc_display_opts.select_cube = mc_select_opts.selected_cell;

    RenderSelectCube();
}

void MarchingCubes::InitBuffers()
{
    // ----- PREPARE SHIP TRIANGLES --------
    m_VAO = std::make_shared<VertexArray>();
    m_VAO->Bind();
    KGLOG(MAX_TRIANGLES)
    m_VBO = std::make_shared<VertexBuffer>(m_triangles, MAX_TRIANGLES * sizeof(TRIANGLE));

    BufferLayout layout = {
    {ShaderDataType::Float3, "aPos"},
    {ShaderDataType::Float3, "aNormal"},
    {ShaderDataType::Float, "aLevel"},
    };
    m_VBO->SetLayout(layout);
    m_VAO->AddVertexBuffer(m_VBO);

    m_textures[0] = std::make_shared<Texture>("Ressources/textures/texture_spaceship.jpg");

    KGLOG("Vertices count : " << m_count_points);
    // --- Shaders ----
    m_shader = std::make_shared<Shader>(
        "Ressources/shaders/shaders_SpaceshipBlueprint/blueprint_vs.glsl",
        "Ressources/shaders/shaders_SpaceshipBlueprint/blueprint_fs.glsl",
        "Ressources/shaders/shaders_SpaceshipBlueprint/blueprint_gs.glsl");
    m_shader->use();
    m_shader->setInt("u_Texture_spaceship", 0);
    // ----- PREPARE GRID --------
    m_VAOg = std::make_shared<VertexArray>();
    m_VAOg->Bind();
    m_VBOg = std::make_shared<VertexBuffer>(m_grid, m_count_points * sizeof(grid));

    layout = {
    {ShaderDataType::Float3, "aPos"},
    {ShaderDataType::Float, "aVal"},
    {ShaderDataType::Float, "aLevel"},
    {ShaderDataType::Int, "aCubeIndex"},
    };
    m_VBOg->SetLayout(layout);
    m_VAOg->AddVertexBuffer(m_VBOg);

    // --- Shaders ----
    m_shaderg = std::make_shared<Shader>(
        "Ressources/shaders/shaders_SpaceshipBlueprint/blueprint_grid_vs.glsl",
        "Ressources/shaders/shaders_SpaceshipBlueprint/blueprint_grid_fs.glsl",
        "Ressources/shaders/shaders_SpaceshipBlueprint/blueprint_grid_gs.glsl");
    m_shaderg->use();

    // ----- PREPARE SELECTABLE GRID --------
    m_VAOsc = std::make_shared<VertexArray>();
    m_VAOsc->Bind();
    m_VBOsc = std::make_shared<VertexBuffer>(0);
    m_VAOsc->AddVertexBuffer(m_VBOsc);

    // --- Shaders ----
    m_shadersc = std::make_shared<Shader>(
        "Ressources/shaders/shaders_SpaceshipBlueprint/select_cube_vs.glsl",
        "Ressources/shaders/shaders_SpaceshipBlueprint/select_cube_fs.glsl",
        "Ressources/shaders/shaders_SpaceshipBlueprint/select_cube_gs.glsl");
    //"Ressources/shaders/shaders_SpaceshipBlueprint/select_cube_gs.glsl"
    m_shadersc->use();
    

}



TRIANGLE* MarchingCubes::PropagateMarchingSquare(int ncellsX, int ncellsY, int ncellsZ, float thresold, grid* points)
{

    m_count_triangles = 0;
    int numTriangles = int(0);
    TRIANGLE* tmptriangles = new TRIANGLE[MAX_TRIANGLES];

    int XtimeZ = (ncellsX + 1) * (ncellsZ + 1);
    //go through all the points
    for (int y = 0; y < ncellsY; y++)			//y axis
        for (int z = 0; z < ncellsZ; z++)		//z axis
            for (int x = 0; x < ncellsX; x++)	//x axis
            {
                //initialize vertices
                grid cube_verts[8];

                int ind = y * XtimeZ + z * (ncellsX + 1) + x;
                int delta = 0;

                //cube_verts[0] = points[ind]; // 0
                //cube_verts[1] = points[ind + 1 + delta]; // 1
                //cube_verts[2] = points[ind + (ncellsX + 1) + 1 + delta]; // 3
                //cube_verts[3] = points[ind + (ncellsX + 1)]; // 2
                //cube_verts[4] = points[ind + XtimeZ]; //4
                //cube_verts[5] = points[ind + XtimeZ + 1 + delta]; // 5
                //cube_verts[6] = points[ind + XtimeZ + (ncellsX + 1) + 1 + delta]; // 7
                //cube_verts[7] = points[ind + XtimeZ + (ncellsX + 1)]; // 6
                /*(step 3)*/ 
                cube_verts[0] = points[ind];
                cube_verts[1] = points[ind + XtimeZ];
                cube_verts[2] = points[ind + XtimeZ + 1];
                cube_verts[3] = points[ind + 1];
                cube_verts[4] = points[ind + (ncellsZ + 1)];
                cube_verts[5] = points[ind + XtimeZ + (ncellsZ + 1)];
                cube_verts[6] = points[ind + XtimeZ + (ncellsZ + 1) + 1];
                cube_verts[7] = points[ind + (ncellsZ + 1) + 1];

                //get the index
                int cubeIndex = int(0);
                for (int n = 0; n < 8; n++) {            
                    if (cube_verts[n].val > 0.0f) {
                        cubeIndex |= (1 << n);
                    }
                }
                m_grid[ind].g_cubeIndexType = cubeIndex;

                //check if its completely inside or outside
                if (!edgeTable[cubeIndex]) continue;

                //get intersection vertices on edges and save into the array
                grid edgeVerts[12];
                float minValue = thresold;
                if (edgeTable[cubeIndex] & 1) edgeVerts[0] = LinearInterp(cube_verts[0], cube_verts[1], minValue, HORIZONTAL);
                if (edgeTable[cubeIndex] & 2) edgeVerts[1] = LinearInterp(cube_verts[1], cube_verts[2], minValue, HORIZONTAL);
                if (edgeTable[cubeIndex] & 4) edgeVerts[2] = LinearInterp(cube_verts[2], cube_verts[3], minValue, HORIZONTAL);
                if (edgeTable[cubeIndex] & 8) edgeVerts[3] = LinearInterp(cube_verts[3], cube_verts[0], minValue, HORIZONTAL);
                if (edgeTable[cubeIndex] & 16) edgeVerts[4] = LinearInterp(cube_verts[4], cube_verts[5], minValue, HORIZONTAL);
                if (edgeTable[cubeIndex] & 32) edgeVerts[5] = LinearInterp(cube_verts[5], cube_verts[6], minValue, HORIZONTAL);
                if (edgeTable[cubeIndex] & 64) edgeVerts[6] = LinearInterp(cube_verts[6], cube_verts[7], minValue, HORIZONTAL);
                if (edgeTable[cubeIndex] & 128) edgeVerts[7] = LinearInterp(cube_verts[7], cube_verts[4], minValue, HORIZONTAL);
                if (edgeTable[cubeIndex] & 256) edgeVerts[8] = LinearInterp(cube_verts[0], cube_verts[4], minValue, VERTICAL);
                if (edgeTable[cubeIndex] & 512) edgeVerts[9] = LinearInterp(cube_verts[1], cube_verts[5], minValue, VERTICAL);
                if (edgeTable[cubeIndex] & 1024) edgeVerts[10] = LinearInterp(cube_verts[2], cube_verts[6], minValue, VERTICAL);
                if (edgeTable[cubeIndex] & 2048) edgeVerts[11] = LinearInterp(cube_verts[3], cube_verts[7], minValue, VERTICAL);

                //float res = 0.0f;
                //for (std::size_t n = 0; n < 12; n++) {
                //    res += edgeVerts[n].val;
                //}
                //KGLOG(res)


                //now build the triangles using triTable
                for (int n = 0; triTable[cubeIndex][n] != -1; n += 3) {

                    tmptriangles[numTriangles].tpoint[0].p = edgeVerts[triTable[cubeIndex][n]].pos;
                    tmptriangles[numTriangles].tpoint[1].p = edgeVerts[triTable[cubeIndex][n + 1]].pos;
                    tmptriangles[numTriangles].tpoint[2].p = edgeVerts[triTable[cubeIndex][n + 2]].pos;
                    
                    glm::vec3 nor = glm::normalize(glm::cross(tmptriangles[numTriangles].tpoint[1].p - tmptriangles[numTriangles].tpoint[0].p,
                                    tmptriangles[numTriangles].tpoint[2].p - tmptriangles[numTriangles].tpoint[0].p));
                    
                    tmptriangles[numTriangles].tpoint[0].normal = nor;
                    tmptriangles[numTriangles].tpoint[1].normal = nor;
                    tmptriangles[numTriangles].tpoint[2].normal = nor;

                    float level_mean = (edgeVerts[triTable[cubeIndex][n + 2]].level + 
                                        edgeVerts[triTable[cubeIndex][n + 1]].level + 
                                        edgeVerts[triTable[cubeIndex][n + 0]].level) / 3.0;

                    tmptriangles[numTriangles].tpoint[0].level = level_mean;
                    tmptriangles[numTriangles].tpoint[1].level = level_mean;
                    tmptriangles[numTriangles].tpoint[2].level = level_mean;

                    numTriangles++;
                }
                
            }
    
    m_count_triangles = numTriangles;
    return tmptriangles;
}

// ///////////////////////////////////////////////////////
// ADD / REMOVE WITH 3D GRID
// ///////////////////////////////////////////////////////
void MarchingCubes::SetGridPointValue(const int& idx, float val)
{
   
    glm::ivec3 a = GridCoords_FromIndex(idx);
    int sym_X = ((nZ) - (2*a.z))*(nX+1);
    shippoint myship;
    myship.pos = a;
    myship.size = slidersize;
    if (slidershape == 0)
        myship.shapefcn = &SDF::square_fcn;
    else if (slidershape == 1)
        myship.shapefcn = &SDF::circle_fcn;
    else if (slidershape == 2)
        myship.shapefcn = &SDF::trap_fcn;
    else if (slidershape == 3)
        myship.shapefcn = &SDF::rhombus_fcn;


    m_ship.push_back(myship);

    //KGLOG(m_ship.size())
    //KGLOG("--------------------------------------")

    for (int y = 0; y < nY + 1; y++)    //int y = a.y;          // y axis
        for (int z = 0; z < nZ + 1; z++)      // z axis 
            for (int x = 0; x < nX + 1; x++)  // x axis
            {

                float minvalue2 = myship.shapefcn(myship.size, glm::ivec3(x, y, z), myship.pos);
                float minvalue = m_grid[y * (nX + 1) * (nZ + 1) + z * (nX + 1) + x].val;
                m_grid[y * (nX + 1) * (nZ + 1) + z * (nX + 1) + x].val = (minvalue < minvalue2 ) ? minvalue : minvalue2;
            }

    myship.pos.y += 1;
    for (int y = 0; y < nY + 1; y++)    //int y = a.y;          // y axis
        for (int z = 0; z < nZ + 1; z++)      // z axis 
            for (int x = 0; x < nX + 1; x++)  // x axis
            {

                float minvalue2 = myship.shapefcn(myship.size, glm::ivec3(x, y, z), myship.pos);
                float minvalue = m_grid[y * (nX + 1) * (nZ + 1) + z * (nX + 1) + x].val;
                m_grid[y * (nX + 1) * (nZ + 1) + z * (nX + 1) + x].val = (minvalue < minvalue2) ? minvalue : minvalue2;
            }


    m_triangles = PropagateMarchingSquare(nX, nY, nZ, gridthresold, m_grid);
    m_VBO->SetData(m_triangles, MAX_TRIANGLES * sizeof(TRIANGLE));
    m_VBOg->SetData(m_grid, m_count_points * sizeof(grid));

}

void MarchingCubes::SetGridAreaPointValue(const int& idx0, const int& idx1, float val = 1.0f)
{
    glm::ivec3 a = GridCoords_FromIndex(idx0);
    glm::ivec3 b = GridCoords_FromIndex(idx1);

    int dX = glm::abs(a.x - b.x);
    int dZ = glm::abs(a.z - b.z);

    int minx = glm::min(a.x, b.x);
    int minz = glm::min(a.z, b.z);

    int start = Index(minx, a.y , minz);

    for (int z = 0; z < dZ+1; z++) {
        for (int x = 0; x < dX+1; x++) {
            int temp_idx = start + ((nX+1) * z) + x;
            SetGridPointValue(temp_idx, val);
        }
    }

}
// ///////////////////////////////////////////////////////
// MOUSE INTERACTION
// ///////////////////////////////////////////////////////

void MarchingCubes::OnEvent(Event& e)
{
    if(!ImGui::GetIO().WantCaptureMouse){
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&MarchingCubes::OnMouseClicked, this, std::placeholders::_1));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&MarchingCubes::OnMouseReleased, this, std::placeholders::_1));
    }
}
bool MarchingCubes::OnMouseClicked(MouseButtonPressedEvent& e)
{
    if (Inputs::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2)) {

        if (!mc_select_opts.DragStart) {
            mc_select_opts.DragStart = true;
            mc_select_opts.DragFirstIndex = GetIndexFromRaycast();
            m_shadersc->use();
            m_shadersc->setVec3("u_pos0", m_grid[Index(mc_select_opts.selected_cell)].pos);
            m_shadersc->setBool("u_rectangle_selector", true);

        }

    }

    if (Inputs::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {
        mc_edit_points_opts.selected_point = Index(mc_display_opts.select_cube);
        mc_edit_points_opts.value = m_grid[mc_edit_points_opts.selected_point].val;

        if (mc_select_opts.DragStart) {
            mc_select_opts.DragStart = false;
           
        }

    }

    if (Inputs::IsKeyPressed(GLFW_KEY_DELETE)) {
        m_VAOsc->Bind();
        m_VBOsc->SetData(NULL, m_count_points * sizeof(grid));
    }

    return false;
}

bool MarchingCubes::OnMouseReleased(MouseButtonReleasedEvent& e)
{
    if (mc_select_opts.DragStart) {
        mc_select_opts.DragStart = false;
        m_shadersc->use();
        m_shadersc->setBool("u_rectangle_selector", false);
        int cubeIndex = GetIndexFromRaycast();
        mc_select_opts.DragLastIndex = GetIndexFromRaycast();

        SetGridAreaPointValue(mc_select_opts.DragFirstIndex, cubeIndex, 1.0f);

    }

    return false;
}


int MarchingCubes::GetIndexFromRaycast()
{
    // get pos of level
    glm::vec3 level_plane = m_MAIN_POSITION + glm::vec3(0.0, mc_display_opts.floor_level * m_stepSize.y, 0.0);
    glm::vec3 target = Raycast::RayCast_XZplane(level_plane) - m_MAIN_POSITION;

    mc_select_opts.selected_cell.x = glm::clamp((int)glm::floor(target.x / m_stepSize.x) - (int)m_MAIN_POSITION.x, 0, nX);
    mc_select_opts.selected_cell.y = mc_display_opts.floor_level;// glm::clamp((int)glm::floor(target.y), 0, nY);
    mc_select_opts.selected_cell.z = glm::clamp((int)glm::floor(target.z / m_stepSize.z) - (int)m_MAIN_POSITION.z, 0, nZ);
    //glm::floatBitsToInt(glm::floor(mc_select_opts.target.z))

    return Index(mc_select_opts.selected_cell);
}

// Update DX and DZ to use in cube rendering 
void MarchingCubes::UpdateRectangleSelection()
{
    int cubeIndex = GetIndexFromRaycast();
    glm::ivec3 a = GridCoords_FromIndex(mc_select_opts.DragFirstIndex);
    glm::ivec3 b = GridCoords_FromIndex(cubeIndex);

    mc_select_opts.dX = b.x - a.x;
    mc_select_opts.dZ = b.z - a.z;
}

void MarchingCubes::OnImGui()
{
    ImGui::Begin("Hello, marching cubes");

    ImGui::Checkbox("Show Blueprint Grid", &mc_display_opts.blueprint_grid);
    ImGui::Checkbox("Show Marching Cubes", &mc_display_opts.marching_cubes);

    ImGui::Text("DX,DZ : %i,%i", mc_select_opts.dX, mc_select_opts.dZ);
    ImGui::SeparatorText("Level");
    ImGui::SliderInt("Level", &mc_display_opts.floor_level, 1, getMax_NumberOfLevel());
    ImGui::SeparatorText("Slider Selection");
    ImGui::SliderInt("Shape", &slidershape, 0, 3);
    ImGui::InputFloat("Slider Size", &slidersize, 0.25f, 0.25f);
    ImGui::Separator();
    ImGui::Text("Index : %i", mc_edit_points_opts.selected_point);
    ImGui::Text("Value : %f", mc_edit_points_opts.value);
    ImGui::Text("Value : %i", m_grid[mc_edit_points_opts.selected_point].g_cubeIndexType);
    ImGui::End();
}
// ///////////////////////////////////////////////////////
// RENDER AND INDEX
// ///////////////////////////////////////////////////////

void MarchingCubes::RenderShip()
{
    m_shader->use();
    m_shader->setFloat("u_show_level", (float)mc_display_opts.floor_level);
    m_textures[0]->BindTexture(0);
    m_VBO->Bind();
    RendererAPI::DrawTriangles(m_shader, m_VAO, 3 * m_count_triangles); //TO DO: cast mcount to int
}


void MarchingCubes::RenderGrid()
{
    m_shaderg->use();
    // 1 level of padding + floor level (in shader we add roof level (for 1 story ship, vaisseau 1 etage))
    m_shaderg->setInt("u_show_level", mc_display_opts.floor_level);
    RendererAPI::DrawPoints(m_shaderg, m_VAOg, m_count_points); //TO DO: cast mcount to int
}

void MarchingCubes::RenderSelectCube()
{
    glLineWidth(4.0f);
    glPointSize(4.0f);

    m_shadersc->use();
    m_shadersc->setVec3("u_pos", m_grid[Index(mc_display_opts.select_cube)].pos);
    RendererAPI::DrawPoints(m_shadersc, m_VAOsc, 1); //TO DO: cast mcount to int
    glLineWidth(1.0f);
}

int MarchingCubes::Index(const int& x, const int& y, const int& z)
{
    return (y * (nX + 1) * (nZ + 1) + z * (nX + 1) + x);
}

int MarchingCubes::Index(const glm::ivec3& v)
{
    return (v.y * (nX + 1) * (nZ + 1) + v.z * (nX + 1) + v.x);
}

glm::ivec3 MarchingCubes::GridCoords_FromIndex(const int& index)
{

    int XZ = (int)glm::mod((float)index, (float)m_vertices_per_level);
    int Y  = (int)glm::floor(index / m_vertices_per_level);
    int X  = (int)glm::mod((float)XZ, (float)(nX+1));
    int Z  = (int)glm::floor(XZ / (nX+1));
    glm::ivec3 coords = glm::ivec3(X,Y,Z);
    return coords;
}
