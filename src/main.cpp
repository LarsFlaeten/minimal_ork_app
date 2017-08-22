#include <iostream>
#include <sstream>

#include "ork/core/FileLogger.h"
#include "ork/render/FrameBuffer.h"
#include "ork/ui/GlfwWindow.h"


using namespace std;
using namespace ork;

class AppWindow : public GlfwWindow
{
public:
    AppWindow() : GlfwWindow(Window::Parameters().size(1024,768))
    {
        frames = 0;
    }

    virtual ~AppWindow()
    {

    }

    virtual void redisplay(double t, double dt)
    {
        ++frames;

        // Update
        // ...

        // Draw
        // ...


        GlfwWindow::redisplay(t, dt);
    }

    virtual void reshape(int x, int y)
    {
        ptr<FrameBuffer> fb = FrameBuffer::getDefault();
        fb->setDepthTest(true, LESS);
        fb->setViewport(vec4<GLint>(0, 0, x, y));
    
        // Call redisplay on any event handlers here...
        // ...
    
        GlfwWindow::reshape(x, y);
        idle(false);
    }

    virtual void idle(bool damaged)
    {
        GlfwWindow::idle(damaged);
        if(damaged) {
            updateResources();
        }

        // Call idle on any event handlers here
        // ...
    }

    virtual bool mouseClick(button b, state s, modifier m, int x, int y)
    {
        return false;
    }

    virtual bool mouseMotion(int x, int y)
    {
        return false;
    }

    virtual bool mousePassiveMotion(int x, int y)
    {
        return false;
    }

    virtual bool mouseWheel(wheel b, modifier m, int x, int y)
    {
        return false;
    }

    virtual bool keyTyped(unsigned char c, modifier m, int x, int y)
    {
        // Call any event handlers here
        // ...
        if (c == 27) {
            :: exit(0); // Example, exit with ESC
        }
        return false;
    }

    virtual bool keyReleased(unsigned char c, modifier m, int x, int y)
    {
        return false;
    }

    virtual bool specialKey(key k, modifier m, int x, int y)
    {
        // Call any event handlers here
        // ...

        switch (k) {
            //case KEY_F1:
            //    ShowLogTask::enabled = !ShowLogTask::enabled;
            //    return true;
            case KEY_F5:
                updateResources();
                return true;
            default:
                break;
        }
        
        return false;
    }

    virtual bool specialKeyReleased(key k, modifier m, int x, int y)
    {
        return false;
    }

    void updateResources()
    {

    }

protected:
    void swap(ptr<AppWindow> o)
    {
        std::swap(frames, o->frames);
    }

    int frames;

};

int main(int argc, char** argv) {
    FileLogger::File *out = new FileLogger::File("log.html");
    Logger::INFO_LOGGER = new FileLogger("INFO", out, Logger::INFO_LOGGER);
    Logger::WARNING_LOGGER = new FileLogger("WARNING", out, Logger::WARNING_LOGGER);
    Logger::ERROR_LOGGER = new FileLogger("ERROR", out, Logger::ERROR_LOGGER);
    //Logger::DEBUG_LOGGER = new VerboseFileLogger(verbose, "DEBUG", out,       Logger::DEBUG_LOGGER);

    ptr<Window> app = new AppWindow();
    
    app->start();
    return 0;
}
