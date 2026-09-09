#include "includeHeader.h"

double lastTime = glfwGetTime();
int frameCount = 0;
double lastFPS = 2000.0;
double currentTime;

camera MainCamera(glm::vec3(0.0f, 0.0f, -5.0f), 0.0f, 0.0f, 60.0f, 0.125f);

int main() {
    initMap();
    for (int x = 0; x < 32; x++) {
        for (int y = 0; y < 4; y++) {
            for (int z = 0; z < 32; z++) {
                addBlock(x, y, z);
            }
        }
    }

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Hello World", primaryMonitor, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    glewInit();

    loadFont("../JetBrainsMono-Bold.ttf", 24);

    Shader shaderProgram("../shader/vertex.glsl", "../shader/fragment.glsl");
    Shader shader("../shader/triVert.glsl", "../shader/triFrag.glsl");

    std::vector<quad> vertexData = meshVolume();

    GLuint TriangleVBO, texture;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &TriangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, TriangleVBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(uint32_t), vertexData.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 1, GL_INT, GL_FALSE,  sizeof(uint32_t), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    glm::mat4 projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);
    shaderProgram.use();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glm::mat4 proj = glm::perspective(glm::radians(MainCamera.FOV), 1920.0f / 1080.0f, 0.05f, 1000.0f);

    texture = loadTexture("../textures/OIP-431623837.png");

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    double xpos, ypos;

    std::cout << "Num of triangles: " << vertexData.size() / 8 << std::endl;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        glUniform1f(glGetUniformLocation(shader.ID, "time"), (float)glfwGetTime());
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(glm::lookAt(MainCamera.position, MainCamera.front + MainCamera.position, MainCamera.up)));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "proj"), 1, GL_FALSE, glm::value_ptr(proj));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertexData.size() / 8);

        renderText("FPS : " + std::to_string((int)std::round(lastFPS)), 20.0f, 1060.0f, 1.0f, glm::vec3(1.0f), shaderProgram.ID);
        renderText("DeltaTime : " + std::to_string(1.0 / lastFPS * 1000) + "ms", 20.0f, 1035.0f, 1.0f, glm::vec3(1.0f), shaderProgram.ID);
        MainCamera.print(shaderProgram);

        currentTime = glfwGetTime();
        frameCount++;
        if(currentTime - lastTime >= 1.0){
            lastFPS = frameCount / (currentTime - lastTime);
            frameCount = 0;
            lastTime = currentTime;
        }

        MainCamera.move(1.0 / lastFPS, window);
        MainCamera.rotate(window, xpos, ypos);
        MainCamera.update();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &TriangleVBO);
    glDeleteTextures(1, &texture);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}