#include "SDL3/SDL.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <filesystem>
#include <iostream>

#include "GLprogram.h"
#include "errorReporting.h"
#include "fileloader.h"
#include "indexBuffer.h"
#include "shader.h"
#include "vertexArray.h"
#include "vertexBuffer.h"

#define TINYOBJLOADER_IMPLEMENTATION

int main(int argc, char **argv) {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return -1;
    }
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

    SDL_Window *window =
        SDL_CreateWindow("SDL3 + GLAD Test",                      // title
                         800, 600,                                // width, height
                         SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE // flags
        );
    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
        return -1;
    }

    SDL_GLContext ctx = SDL_GL_CreateContext(window);
    if (!ctx) {
        std::cerr << "SDL_GL_CreateContext failed: " << SDL_GetError() << "\n";
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    if (GLAD_GL_KHR_debug || GLAD_GL_ARB_debug_output) {
        enableReportGlErrors();
    } else {
        std::cerr << "No KHR_debug/ARB_debug_output support. "
                     "Falling back to glGetError wrappers.\n";
    }

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

    std::filesystem::path obj_path(RESOURCES_PATH "icosphere.obj");
    std::filesystem::path mtl_path(RESOURCES_PATH "cube.mtl");

    std::vector<fileloader::vertex> vertices;
    std::vector<unsigned int> indices;

    fileloader::loadObjMesh(vertices, indices, obj_path.string());

    for(auto vertex : vertices){
        std::cout << " position:" << vertex.p.x << ' ' << vertex.p.y << ' ' << vertex.p.z << ' ';
        std::cout << " normals:" << vertex.n.x << ' ' << vertex.n.y << ' ' << vertex.n.z << '\n';
    }

    vertexArray vao_cube;

    vertexBuffer vbo_cube =
        vertexBuffer(vertices.data(), vertices.size() * sizeof(vertices[0]));
    //indexBuffer ibo_cube = indexBuffer(indices.data(), indices.size());

    vertexLayout layout_cube;
    layout_cube.push<float>(3);
    layout_cube.push<float>(3);
    layout_cube.push<float>(2);
    vao_cube.addBuffer(vbo_cube, layout_cube);
    vao_cube.unbind();

    std::filesystem::path vertex_path(RESOURCES_PATH "shaders/DiffuseVertex.glsl");
    std::filesystem::path fragment_path(RESOURCES_PATH "shaders/ambientShaderFrag.glsl");
    std::filesystem::path light_fragment_path(RESOURCES_PATH "shaders/lightFrag.glsl");

    GLprogram program;
    GLprogram light_program;

    { // scope so the shaders delete
        shader vertex_shader(GL_VERTEX_SHADER, vertex_path.string());
        shader fragment_shader(GL_FRAGMENT_SHADER, fragment_path.string());
        shader light_fragment_shader(GL_FRAGMENT_SHADER, light_fragment_path.string());

        program.createProgram(vertex_shader.getId(), fragment_shader.getId());
        light_program.createProgram(vertex_shader.getId(), light_fragment_shader.getId());
    }

    bool running = true;
    auto t0 = SDL_GetTicks();

    glm::vec3 lightPos(0.7f, 0.5f, 0.4f);

    glm::mat4 light_proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 10.0f);
    glm::mat4 light_view =
        glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 light_model = glm::translate(glm::mat4(1.0f), lightPos);
    light_model = glm::scale(light_model, glm::vec3(0.2));


    while (running) {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                if (ev.key.key == SDLK_ESCAPE)
                    running = false;
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                glViewport(0, 0, ev.window.data1, ev.window.data2);
                break;
            default:
                break;
            }
        }

        glm::mat4 proj =
            glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 10.0f);
        // parameters: camera position, where are we looking, which way is up axis
        glm::mat4 view =
            glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        Uint32 tNow = SDL_GetTicks();
        float t = (tNow - t0) / 1000.0f;
        // parameters:model(if we already did some transformations, angle, rotation axis
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), t, glm::vec3(1, 1, 1));
        model = glm::scale(model, glm::vec3(0.5));

        //glm::mat4 MVP = proj * view * model;

        glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program.bind();
        program.setUniformMat4f("projection", proj);
        program.setUniformMat4f("view", view);
        program.setUniformMat4f("model", model);
        // white light
        program.setUniform3f("lightColor", 1.0f, 1.0f, 1.0f);
        program.setUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.z);

        vao_cube.bind();
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        //glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, nullptr);

        light_program.bind();
        light_program.setUniformMat4f("projection", light_proj);
        light_program.setUniformMat4f("view", light_view);
        light_program.setUniformMat4f("model", light_model);

        vao_cube.bind();
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        //glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, nullptr);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DestroyContext(ctx);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
