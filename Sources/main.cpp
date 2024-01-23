#include "Application.h"

int main()
{
    //Application

    std::unique_ptr<Application> app = std::make_unique<Application>();
    app->Run();

    return 0;
}
