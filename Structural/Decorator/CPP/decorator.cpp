/*
 * (c) 2015 Raghavendra Nayak, All Rights Reserved.
 * www.openguru.com/
 */

#include <iostream>
#include <string>

// Window is the abstract base for all concrete Window implementations
class Window {
public:
    Window() {
    }
    virtual ~Window() {
    }
    virtual void draw() = 0;
};

// MainWindow is a type of Window
class MainWindow : public Window {
    int height;
    int width;
    std::string windowName;
public:
    MainWindow(const std::string& name, int height, int width)
        : height(height), width(width), windowName(name) {
    }
    ~MainWindow() {
    }
    
    std::string name() {
        return windowName;
    }

    virtual void draw() {
        std::cout << "Rendering the MainWindow: " << name() 
            << " with height: " << height << ", width: " << width << std::endl;
    }
};

// SimpleWindow does not have any name
class SimpleWindow : public Window {
    int height;
    int width;
public:
    SimpleWindow(int height, int width)
        : height(height), width(width) {
    }
    ~SimpleWindow() {
    }

    virtual void draw() {
        std::cout << "Rendering the SimpleWindow: "
            << " with height: " << height << ", width: " << width << std::endl;
    }
};

// Below class is a decorator or wrapper
class WindowDecorator : public Window {
    // Here we store the reference
    Window& decoratedWindow;
public:
    // Constructor
    WindowDecorator(Window& window)
        : decoratedWindow(window) {
    }
    virtual ~WindowDecorator() {
    }

    // Call our wrapper object's function
    virtual void draw() {
        decoratedWindow.draw();
    }
};

class MenubarDecorator : public WindowDecorator {
    void drawMenuBar() {
        std::cout << "Drawing the Menu bar. " << std::endl;
    }
public:
    MenubarDecorator(Window& decoratedWindow)
        : WindowDecorator(decoratedWindow) {
    }
    ~MenubarDecorator() {
    }

    virtual void draw() {
        // Draw Wrapped Window first as it is in the background
        WindowDecorator::draw();
        // Now draw the actual menu bar
        drawMenuBar();
    }
};

class StatusbarDecorator : public WindowDecorator {
    void drawStatusbar() {
        std::cout << "Drawing the Status bar." << std::endl;
    }
public:
    StatusbarDecorator(Window& decoratedWindow)
        : WindowDecorator(decoratedWindow) {
    }
    ~StatusbarDecorator() {
    }

    virtual void draw() {
        // Draw Wrapped Window first as it is in the background
        WindowDecorator::draw();

        // Now draw the actual menu bar
        drawStatusbar();
    }
};

int main(int argc, char **argv)
{
    // Draw a MainWindow
    MainWindow mainWindow("simple window", 1024, 768);
    mainWindow.draw();

    // Now for the same MainWindow we can add the menubar
    // via MenubarDecorator
    MenubarDecorator windowWithMenubar(mainWindow);
    windowWithMenubar.draw();

    // Now we can add Statusbar via StatusbarDecorator
    StatusbarDecorator windowWithMenubarAndStatusBar(windowWithMenubar);
    windowWithMenubarAndStatusBar.draw();

    // Draw a simpleWindow
    SimpleWindow simpleWindow(1024, 768);
    simpleWindow.draw();

    // Now lets decorate SimpleWindow with Menubar
    MenubarDecorator simpleWindowWithMenubar(simpleWindow);
    simpleWindowWithMenubar.draw();

    return 0;
}