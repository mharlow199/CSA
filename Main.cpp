#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

class Screen {
private:
    bool screen[128][128];
public:
    Screen() {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                screen[i][j] = 0;
            }
        }
    }

    bool get(int row, int col) {
        return screen[row][col];
    }

    void set(int row, int col, bool state) {
        screen[row][col] = state;
    }

    void swap(int row, int col) {
        screen[row][col] = !(screen[row][col]);
    }

};

Screen screen;
double xpos, ypos;
bool leftButtonDown;

int main(void)
{
    GLFWwindow* window;
    

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(512, 512, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glOrtho(0, 128, 128, 0, 1, -1);

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    //screen.swap(0, 0);
    //screen.swap(54, 87);
    //screen.swap(127, 127);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwGetCursorPos(window, &xpos, &ypos);
        if (leftButtonDown) {
            screen.set((int)(xpos / 4), (int)(ypos / 4), true);
        }

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_QUADS);
        for (int row = 0; row < 128; row++) {
            for (int col = 0; col < 128; col++) {
                if (screen.get(row, col)) {
                    glVertex2f(row, col);
                    glVertex2f(row + 1, col);
                    glVertex2f(row + 1, col + 1);
                    glVertex2f(row, col + 1);
                }
            }
        }
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        leftButtonDown = true;
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        leftButtonDown = false;

        //screen.swap((int) (xpos / 4), (int) (ypos / 4));
        //divide by 4 to match orthographic with grid
}