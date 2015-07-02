/*
 * (c) 2015 Raghavendra Nayak, All Rights Reserved.
 * www.openguru.com/
 */

#include <iostream>
#include <string>

// Window is the abstract base for all concrete Window implementations
class Window {
    std::string windowName;
public:
    Window(const std::string& windowName)
        : windowName(windowName) {
    }
    Window() {
    }
    virtual ~Window() {
    }
    virtual std::string name() {
        return windowName;
    }
    virtual void draw() = 0;
};

// MainWindow is a type of Window
class MainWindow : public Window {
    int height;
    int width;
public:
    MainWindow(const std::string& windowName, int height, int width)
        : Window(windowName), height(height), width(width) {
    }
    ~MainWindow() {
    }

    virtual void draw() {
        std::cout << "Rendering the MainWindow: [" << name() 
            << "] with height: " << height << ", width: " << width << std::endl;
    }
};

// SquareWindow have same height & width
class SquareWindow : public Window {
    int dimension;

public:
    SquareWindow(const std::string& windowName, int dimension)
        : Window(windowName), dimension(dimension) {
    }
    ~SquareWindow() {
    }

    virtual void draw() {
        std::cout << "Rendering the SquareWindow: [" << name()
            << "] with dimensions: " << dimension << std::endl;
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
    virtual std::string name() {
        return decoratedWindow.name();
    }

    // Call our wrapper object's function
    virtual void draw() {
        decoratedWindow.draw();
    }
};

class MenubarDecorator : public WindowDecorator {
    void drawMenuBar() {
        std::cout << "Drawing the Menu bar for [" 
            << WindowDecorator::name() << "]" << std::endl;
    }
public:
    MenubarDecorator(Window& decoratedWindow)
        : WindowDecorator(decoratedWindow) {
    }
    ~MenubarDecorator() {
    }

    virtual std::string name() {
        return WindowDecorator::name();
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
        std::cout << "Drawing the Status bar for [" 
            << WindowDecorator::name() << "]" << std::endl;
    }
public:
    StatusbarDecorator(Window& decoratedWindow)
        : WindowDecorator(decoratedWindow) {
    }
    ~StatusbarDecorator() {
    }

    virtual std::string name() {
        return WindowDecorator::name();
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
    MainWindow mainWindow("Main window", 1024, 768);
    mainWindow.draw();

    // Now for the same MainWindow we can add the menubar
    // via MenubarDecorator
    MenubarDecorator windowWithMenubar(mainWindow);
    windowWithMenubar.draw();

    // Now we can add Statusbar via StatusbarDecorator
    StatusbarDecorator windowWithMenubarAndStatusBar(windowWithMenubar);
    windowWithMenubarAndStatusBar.draw();

    // Draw a squareWindow
    SquareWindow squareWindow("Square Window", 1024);
    squareWindow.draw();

    // Now lets decorate SquareWindow with Menubar
    MenubarDecorator squareWindowWithMenubar(squareWindow);
    squareWindowWithMenubar.draw();

    return 0;
}