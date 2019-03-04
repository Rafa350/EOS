


namespace eos {

    class Visual {
        public:
            virtual void render() = 0;
    }
    
    class VisualContainer: public Visual {
        public:
            void addVisual(Visual *visual);
            void removeVisual(Visual *visual);
    }
    
    class Screen: public VisualContainer {
        public:
            void setColor(const Color &color);
    }
    
    class Control: public VisualContainer {
        public:
            void setPosition(int x, int y);
            void setSize(int width, int height);
    }
    
    class Window: public Control {
        public:
            void setBackgroundColor(const Color &color);
            void setBorderColor(const Color &color);
            void setBorderThickness(int thickness);
    }
    
    class Button: public Control {
        
    }
    
    class PushButton: public Button {
        
    }
    
    class CheckButton: public Button {
        
    }
    
    class Label: public Control {
        
    }
}