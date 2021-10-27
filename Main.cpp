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
ImGuiIO& imGuiSetup();

class Screen {
private:
    bool* screen = new bool[SIZE * SIZE];
    bool* screenCopy = new bool[SIZE * SIZE];
    enum drawType {STANDARD, GLIDER};
    drawType drawCursor;

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
                screen[i * SIZE + j] = 0;
                screenCopy[i * SIZE + j] = 0;
            }
        }
    }

    ~Screen() {
        delete[] screen;
        delete[] screenCopy;
    }

    bool get(int row, int col) {
        return screen[row * SIZE + col];
    }

    void set(int row, int col, bool state) {
        screen[row * SIZE + col] = state;
    }

    void swap(int row, int col) {
        screen[row * SIZE + col] = !(screen[row * SIZE + col]);
    }

    void update() {
        int neighbors;
        copy(&screen[0], &screen[0] + SIZE * SIZE, &screenCopy[0]);
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                neighbors = findNeighbors(row, col);
                if (neighbors < 2) {
                    screenCopy[row * SIZE + col] = false;
                }
                else if (neighbors == 3) {
                    screenCopy[row * SIZE + col] = true;
                }
                else if (neighbors > 3) {
                    screenCopy[row * SIZE + col] = false;
                }
            }
        }
        copy(&screenCopy[0], &screenCopy[0] + SIZE * SIZE, &screen[0]);
    }

    void setDrawing(int type) {
        drawCursor = (drawType) type;
    }


    void draw(int row, int col) {
        switch (drawCursor) {
        case STANDARD: {
            set(row, col, true);
            break;
        }
        case GLIDER: {
            set(row - 1, col, true);
            set(row, col + 1, true);
            set(row + 1, col + 1, true);
            set(row + 1, col, true);
            set(row + 1, col - 1, true);
            break;
        }
        }
    }

    void fillRandom() {
        srand(time(0));
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if ((float) rand() / INT16_MAX > 0.8)
                    screen[i * SIZE + j] = 1;
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

ImGuiIO& io = imGuiSetup();

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

    //IMGUI
    // Setup Dear ImGui context
    // 
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);




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
            screen.draw((int)(xpos / (512 / SIZE)), (int)(ypos / (512 / SIZE)));
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

        ImGui::Begin("Drawing");
        if (ImGui::Button("Standard")) {
            screen.setDrawing(0);
        }
        if (ImGui::Button("Glider")) {
            screen.setDrawing(1);
        }
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

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (!io.WantCaptureMouse) {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            leftButtonDown = true;
        else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
            leftButtonDown = false;
    }

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

ImGuiIO& imGuiSetup() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    return ImGui::GetIO();
}