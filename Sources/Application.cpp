#include "Application.h"


Application* Application::s_Instance = nullptr;

Application::Application()
{
    // Create window
    //m_window = new Window(WindowProperties());
    m_window = std::make_unique<Window>(WindowProperties());

    // make the callback in WindowData from Window class the Application::OnEvent function.
    // In the glfw callback (Window Class), we access this WindowData callback thanks to 
    // the glfwWindowUserPointer that we binded to the WindowData pointer
    m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

    m_GLFWwindow = m_window->GetGLFWWindow();
    s_Instance = this;

    
    ImGui = new ImGuiLayer();
   
}

Application::~Application()
{

}

//void Application::MainLoop()
//{
//    camera = new Camera(glm::vec3(-50.0f, 30.0f, 50.0f));
//    //--------------
//    const char* glsl_version = "#version 130";
//
//
//    float vertices[] = {
//        // positions          // colors           // texture coords
//         0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//         0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // top left 
//
//        // positions          // colors           // texture coords
//         0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//         0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//        -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//        -0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // top left 
//
//        // positions          // colors           // texture coords
//         0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right 0
//         0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//         0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//         0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top left 
//
//        -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//        -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // top left 
//
//         0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top 
//         0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
//
//         0.5f,  -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // bottom
//         0.5f,  -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
//        -0.5f,  -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f,
//        -0.5f,  -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
//    };
//    unsigned int indices[] = {  // note that we start from 0!
//        0, 1, 3,   // first triangle
//        1, 2, 3,    // second triangle
//
//        4, 5, 7,
//        5, 6, 7,
//
//        8, 9, 11,
//        9, 10,11,
//
//        12, 13, 15,
//        13, 14, 15,
//
//        16, 17, 19,
//        17, 18, 19,
//
//        20, 21, 23,
//        21, 22, 23
//    };
//
//
//    float range = 10.0f;
//    int rangei = (int)range;
//    const int N = 100000;
//    //glm::vec3 cubepos[N];
//
//    glm::vec3* cubepos = new glm::vec3[N];
//    for (int i = 1; i < N; i++)
//    {
//        cubepos[i] = GetGridPosFromIndex(i, 1000);
//    }
//
//
//    // generate VAO, VBO, IBO buffer
//    GLuint VAO[2], VBO[2], IBO[2];
//    glGenVertexArrays(2, VAO);
//    glGenBuffers(2, VBO);
//    glGenBuffers(2, IBO);
//
//    // --------------------
//    // Bind the VAO first
//    glBindVertexArray(VAO[0]);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    // Vertex Attributes
//    // position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    // color attribute
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//    // texture coord attribute
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//    // Element (Index) Buffer Object
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[0]);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//    // --------------------
//
//    GLuint instancedVBO;
//    glGenBuffers(1, &instancedVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, instancedVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * N, cubepos, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(3);
//    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glVertexAttribDivisor(3, 1);
//    // --- Shaders ----
//    Shader myshader("Ressources/shaders/vertexshader.vs", "Ressources/shaders/fragshader.fs");
//    myshader.use();
//
//    Texture tex("Ressources/textures/container.jpg");
//    tex.BindTexture();
//    myshader.setInt("texture1", 0);
//
//
//    // Wireframe mode
//    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_FRONT);
//
//
//    // --- IMGUI
//    //     // Setup Dear ImGui context
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO(); (void)io;
//    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
//    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
//    // Setup Dear ImGui style
//    ImGui::StyleColorsDark();
//    // Setup Platform/Renderer backends
//
//    ImGui_ImplGlfw_InitForOpenGL(m_GLFWwindow, true);
//    ImGui_ImplOpenGL3_Init(glsl_version);
//
//    // Main loop
//    // ----------------
//    double lastTime = glfwGetTime();
//
//    int nbFrames = 0;
//    glm::vec3* cubepos_update = new glm::vec3[N];
//    while (!glfwWindowShouldClose(m_GLFWwindow))
//    {
//        
//       
//        // -------------------------------------------------------------------------------
//        // per-frame time logic
//        // Color clear the screen
//        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        ImGui_ImplOpenGL3_NewFrame();
//        ImGui_ImplGlfw_NewFrame();
//        ImGui::NewFrame();
//
//        //float currentFrame = static_cast<float>(glfwGetTime());
//        //deltaTime = currentFrame - lastFrame;
//        //lastFrame = currentFrame;
//
//        //processInput(m_GLFWwindow);
//
//        // -------------------------------------------------------------------------------
//        // RENDERING
//        // Matrix
//        // pass projection matrix to shader (note that in this case it could change every frame)
//        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)GetWindowWidth() / (float)GetWindowHeight(), 0.1f, 1000.0f);
//        myshader.setMat4("u_projection", projection);
//
//        // camera/view transformation
//        glm::mat4 view = camera->GetViewMatrix();
//        myshader.setMat4("u_view", view);
//        // create transformations
//
//        // calculate the model matrix and pass it to shader before drawing
//        glm::mat4 model = glm::mat4(1.0f);
//        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
//        myshader.setMat4("u_model", model);
//
//        //update
//
//        for (int i = 1; i < N; i++)
//        {
//            cubepos[i] += 0.01f * glm::vec3((float)glfwGetTime(),
//                0.0f,
//                (float)glfwGetTime());
//        }
//        //-----------
//
//        glBindBuffer(GL_ARRAY_BUFFER, instancedVBO);
//        //glGetBufferSubData(GL_ARRAY_BUFFER, 0, N * sizeof(glm::vec3), cubepos_update);
//
//        glBufferSubData(GL_ARRAY_BUFFER, 0, N * sizeof(glm::vec3), cubepos);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//        glBindVertexArray(VAO[0]);
//        glDrawElementsInstanced(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0, N);
//
//
//
//        // -------------------------------------------------------------------------------
//        // Start the Dear ImGui frame
//        {
//            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
//            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//
//            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
//            ImGui::End();
//        }
//
//        // -------------------------------------------------------------------------------
//        // END FRAME LOGIC
//
//
//        ImGui::Render();
//        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        glfwSwapBuffers(m_GLFWwindow);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    glDeleteVertexArrays(2, VAO);
//    glDeleteBuffers(2, VBO);
//    glDeleteBuffers(2, IBO);
//    glDeleteProgram(myshader.ID);
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    // Cleanup
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
//    glfwTerminate();
//    //--------------
//}

void Application::Run()
{

    RendererAPI::s_Instance->Init();

    //m_GameLayer = new GameLayer();
    //m_GameLayer->OnCreate();

    m_GameLayer0 = new GameLayer0();

    ImGui->OnAttach();

    while (!glfwWindowShouldClose(m_GLFWwindow))
    {

        ImGui->Begin();

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        RendererAPI::s_Instance->Clear();
        RendererAPI::s_Instance->SetClearColor();
        m_GameLayer0->OnUpdate(deltaTime);

        
        ImGui->End();

        m_window->OnUpdate();
    }
}

void Application::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseMovedEvent>(std::bind(&Application::OnMouseMoveEvent, this, std::placeholders::_1));
    
    //m_GameLayer->OnEvent(e);
    m_GameLayer0->OnEvent(e);
}

unsigned int Application::GetWindowWidth() const
{
	return m_window->GetWidth();
}

unsigned int Application::GetWindowHeight() const
{
	return m_window->GetHeight();
}

bool Application::OnMouseMoveEvent(MouseMovedEvent& e)
{
    return 1;
}
