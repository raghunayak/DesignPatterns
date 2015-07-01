/*
 * (c) 2015 Raghavendra Nayak, All Rights Reserved.
 * www.openguru.com/
 */

#include <iostream>
#include <string>

// Widget is the abstract base for all concrete widget implementations
class Widget {
    std::string widgetName;
protected:
    std::string name() {
        return widgetName;
    }
public:
    Widget(const std::string& widgetName)
        : widgetName(widgetName) {
    }
    virtual ~Widget() {
    }
    virtual void draw() = 0;
};

// Window is a type of Widget
class Window : public Widget {
    int height;
    int width;
public:
    Window(const std::string& name, int height, int width)
        : Widget(name), height(height), width(width) {
    }
    ~Window() {
    }
    virtual void draw() {
        std::cout << "Rendering the Window: " << name() 
            << " with height: " << height << ", width: " << width << std::endl;
    }
};

// Below class is a decorator or wrapper
class WidgetDecorator : public Widget {
    // Here we store the reference
    Widget& decoratedWidget;
public:
    // Constructor
    WidgetDecorator(const std::string& widgetName, Widget& widget)
        : Widget(widgetName), decoratedWidget(widget) {
    }
    virtual ~WidgetDecorator() {
    }

    // Call our wrapper object's function
    virtual void draw() {
        decoratedWidget.draw();
    }
};

class Menubar : public WidgetDecorator {
    void drawMenuBar() {
        std::cout << "Drawing the Menu bar: " << name() << std::endl;
    }
public:
    Menubar(const std::string& menuBarName, Widget& decoratedWidget)
        : WidgetDecorator(menuBarName, decoratedWidget) {
    }
    ~Menubar() {
    }

    virtual void draw() {
        // Draw Wrapped Widget first as it is in the background
        WidgetDecorator::draw();
        // Now draw the actual menu bar
        drawMenuBar();
    }
};

class Statusbar : public WidgetDecorator {
    void drawStatusbar() {
        std::cout << "Drawing the Status bar: " << name() << std::endl;
    }
public:
    Statusbar(const std::string& statusBarName, Widget& decoratedWidget)
        : WidgetDecorator(statusBarName, decoratedWidget) {
    }
    ~Statusbar() {
    }

    virtual void draw() {
        // Draw Wrapped Widget first as it is in the background
        WidgetDecorator::draw();

        // Now draw the actual menu bar
        drawStatusbar();
    }
};

int main(int argc, char **argv)
{
    // Draw a simple Window
    Window simpleWindow("simple window", 1024, 768);
    simpleWindow.draw();

    // Now we will create another Window but this time, decorate it with
    // the Menubar
    Window windowWithMenubar("Window with Menubar", 1024, 768);
    // Now lets add menubar to the Window
    Menubar menu("Main Menu", windowWithMenubar);
    menu.draw();

    return 0;
}