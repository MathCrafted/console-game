#include "renderer.h"

class ScreenBuffer {

    public:

        //Constructors//

        ScreenBuffer() {

            this->layerCount = 5;

            for (int i = 0; i < this->layerCount; i++) {

                screenBuffer[i] = new Layer();

            }

        }

        //Destructors//

        ~ScreenBuffer() {

            //

        }

        //Accessors//

    private:

        //Properties//
        
        unsigned int height;
        unsigned int width;
        char transparentChar;
        unsigned int layerCount;

        //Screen Buffer
    
        Layer ** screenBuffer;

};

class Layer {

    public:

        //Constructors//
        Layer() {

            //Init in 16:9
            this->height = 9;
            this->width = 16;

            //Alloc and init array
            this->layer = new char*[this->height];
            for (int i = 0; i < this->height; i++) {

                this->layer[i] = new char[this->width];
                for (int j = 0; j < this->width; j++) {

                    this->layer[i][j] = transparentChar;

                }

            }

        }

        //Destructors//

        ~Layer() {

            for (int i = 0; i < this->height; i++) {

                delete(this->layer[height]);

            }
            delete(this->layer);

        }

        //Accessors//

        //Height

        unsigned int getHeight() {return this->height;}

        void setHeight(unsigned int height) {

            //Resize the array
            char ** oldLayer = this->layer;

            layer = new char*[height];
            for (int i = 0; i < height; i++) {

                layer[height] = new char[this->width];
                for (int j = 0; j < this->width; j++) {
                    
                    if (i < this->height) {

                        layer[i][j] = oldLayer[i][j];

                    } else {

                        layer[i][j] = transparentChar;

                    }

                }

            }

            //Release the old layer
            for (int i = 0; i < this->height; i++) {

                delete(layer[i]);

            }
            delete(layer);

            //Set height
            this->height = height;

        }

        //Width

        unsigned int getWidth() {return this->width;}

        void setWidth(unsigned int width) {

            //Resize the array
            char ** oldLayer = this->layer;

            layer = new char*[this->height];
            for (int i = 0; i < this->height; i++) {

                layer[height] = new char[width];
                for (int j = 0; j < width; j++) {
                    
                    if (j < this->width) {

                        layer[i][j] = oldLayer[i][j];

                    } else {

                        layer[i][j] = transparentChar;
                        
                    }

                }

            }

            //Release the old layer
            for (int i = 0; i < this->height; i++) {

                delete(layer[i]);

            }
            delete(layer);

            //Set height
            this->width = width;

        }

        //Visibility

        bool getVisible() {return this->visible;}
        void setVisible(bool visible) {this->visible = visible;}

        //Transparent Character

        char getTransparentChar() {return this->transparentChar;}
        void setTransparentChar(char transparentChar) {this->transparentChar = transparentChar;}
    
    private:

        //Properties//

        unsigned int height;
        unsigned int width;
        bool visible;
        char transparentChar;

        //Layer

        char ** layer;

};