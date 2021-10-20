#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdio.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


constexpr auto SIZE = 64;

using namespace std;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

class Screen {
private:
    bool screen[SIZE][SIZE];
    bool screenCopy[SIZE][SIZE];

    int findNeighbors(int row, int col) {
        int n = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (get((row + i + SIZE) % SIZE, (col + j + SIZE) % SIZE)) {
                    n++;
                }
            }
        }
        if (get(row, col))
            n--;
        return n;
    }
public:
    Screen() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
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

    void update() {
        int neighbors;
        copy(&screen[0][0], &screen[0][0] + SIZE * SIZE, &screenCopy[0][0]);
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                neighbors = findNeighbors(row, col);
                if (neighbors < 2) {
                    screenCopy[row][col] = false;
                }
                else if (neighbors == 3) {
                    screenCopy[row][col] = true;
                }
                else if (neighbors > 3) {
                    screenCopy[row][col] = false;
                }
            }
        }
        copy(&screenCopy[0][0], &screenCopy[0][0] + SIZE * SIZE, &screen[0][0]);
    }

    void fillRandom() {
        srand(time(0));
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if ((float) rand() / INT16_MAX > 0.8)
                    screen[i][j] = 1;
            }
        }
    }

};

struct Timer {
    double time = 0.0;

    void update(double dt) {
        time += 1.0 * dt;
    }

    void reset() {
        time = 0.0;
    }
};

Screen screen;
double xpos, ypos;
bool leftButtonDown, paused = true;

int main(void)
{
    GLFWwindow* window;


    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(512, 512, "Conway's Game of Life", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glOrtho(0, SIZE, SIZE, 0, 1, -1);
    glfwSwapInterval(0);

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);


    //IMGUI
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();


    double end, begin;
    double dt = -1.0f;
    Timer timer;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        
        begin = glfwGetTime();

        if (dt != -1.0) {
            timer.update(dt);
        }

        glfwGetCursorPos(window, &xpos, &ypos);
        if (leftButtonDown) {
            screen.set((int)(xpos / (512 / SIZE)), (int)(ypos / (512 / SIZE)), true);
        }
        if (!paused && timer.time > 0.1) {
            screen.update();
            timer.reset();
        }

        //IMGUI
        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_QUADS);
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (screen.get(row, col)) {
                    glColor3f(row/ (float) SIZE, col/ (float) SIZE, 0.5f);
                    glVertex2f(row, col);
                    glVertex2f(row + 1, col);
                    glVertex2f(row + 1, col + 1);
                    glVertex2f(row, col + 1);
                }
            }
        }
        glEnd();

        ImGui::Begin("Demo window");
        ImGui::Button("Hello!");
        ImGui::End();

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        end = glfwGetTime();
        dt = end - begin;
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

    //ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

    //screen.swap((int) (xpos / 4), (int) (ypos / 4));
    //divide by 4 to match orthographic with grid
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        paused = !paused;
    else if (key == GLFW_KEY_R && action == GLFW_PRESS)
        screen.fillRandom();
}