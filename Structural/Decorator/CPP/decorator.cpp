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
    virtual void draw() {
        std::cout << "Rendering the Window: " << name() 
            << " with height: " << height << ", width: " << width << std::endl;
    }
};

// Below class is a decorator or wrapper
class WidgetWrapper : public Widget {
    // Here we store the reference
    Widget& widget;
public:
    // Constructor
    WidgetWrapper(Widget& widget)
        : Widget("Widget Wrapper"), widget(widget) {
    }

    // Call our wrapper object's function
    virtual void draw() {
        widget.draw();
    }

};

class Menubar : public Widget {
    Widget& wrappedWidget;

    void drawMenuBar() {
        std::cout << "Drawing the Menu bar: " << name() << std::endl;
    }
public:
    Menubar(const std::string& name, Widget& wrappedWidget)
        : Widget(name), wrappedWidget(wrappedWidget) {

    }
    virtual void draw() {
        // Draw Wrapped Widget first as it is in the background
        wrappedWidget.draw();
        // Now draw the actual menu bar
        drawMenuBar();
    }
};

class Statusbar : public Widget {
    Widget& wrappedWidget;

    void drawStatusbar() {
        std::cout << "Drawing the Status bar: " << name() << std::endl;
    }
public:
    Statusbar(const std::string& name, Widget& wrappedWidget)
        : Widget(name), wrappedWidget(wrappedWidget) {

    }
    virtual void draw() {
        // Draw Wrapped Widget first as it is in the background
        wrappedWidget.draw();

        // Now draw the actual menu bar
        drawStatusbar();
    }
};

int main(int argc, char **argv)
{
    // Draw a simple Window
    Window window("simple window", 1024, 768);
    window.draw();

    // Draw a Window with Menubar
    Menubar menu("Main Menu", Window("Main Window", 1024, 768));
    menu.draw();



    return 0;
}