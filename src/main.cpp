#include "config.h"


int main(){
    GLFWwindow* window;

    if(!glfwInit()){
        std::cout << "GLFW didn't start" <<std::endl;
        return -1;
    }

    window = glfwCreateWindow(640, 480, "My window haha", NULL, NULL); //The monitor(4th parameter) tells us which monitor to show this up on
    return 0;
}