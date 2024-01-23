#include "Window.h"


Window::Window(const WindowProperties windowsproperties)
{
    
    m_WindowData.Width  = windowsproperties.Width;
    m_WindowData.Height = windowsproperties.Height;
    Init();
}

Window::~Window()
{
    KGLOG("closing");
    glfwDestroyWindow(m_window);
}

void Window::OnUpdate()
{
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(m_window);
    glfwPollEvents();

}

void Window::SetEventCallback(const EventCallbackFcn& callback)
{
    m_WindowData.EventCallback = callback;
}

void Window::Init()
{

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // glfw window creation
    // --------------------
    m_window = glfwCreateWindow((int)m_WindowData.Width, 
                                (int)m_WindowData.Height, 
                                "LearnOpenGL", NULL, NULL);

    

    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        //return -1;
    }
    glfwMakeContextCurrent(m_window);

    glfwSetWindowUserPointer(m_window, &m_WindowData);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        //return -1;
    }

    glViewport(0, 0, (int)m_WindowData.Width, (int)m_WindowData.Height);


    // CALLBACKS
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    });

    SetCallbacks();

}

void Window::SetCallbacks()
{

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

            MouseMovedEvent e((float)xPos, (float)yPos);
            data.EventCallback(e);

        });

    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

            MouseScrolledEvent e((float)xOffset, (float)yOffset);
            data.EventCallback(e);
        });

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyTypedEvent e(key, 0);
                    data.EventCallback(e);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent e(key);
                    data.EventCallback(e);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent e(key, 1);
                    data.EventCallback(e);
                    break;
                }
            }
        });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });
}
