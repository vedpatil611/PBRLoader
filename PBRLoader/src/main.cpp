#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "Shader.h"
#include "Skybox.h"
#include "Window.h"

Camera* camera;
Window* window;
Shader* skyboxShader;

float deltaTime = 0.0f;
float lastTime = 0.0f;

int main()
{
	Window* window = new Window();

	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 1.0f);

	const char* faces[] = {
		"assets/skybox/right.jpg",
		"assets/skybox/left.jpg",
		"assets/skybox/top.jpg",
		"assets/skybox/bottom.jpg",
		"assets/skybox/front.jpg",
		"assets/skybox/back.jpg"
	};

	Shader* skyboxShader = new Shader("shaders/skybox.vert.glsl", "shaders/skybox.frag.glsl");

	Skybox skybox(faces, skyboxShader);

	while (!window->shouldClose())
	{
		float now = static_cast<float>(glfwGetTime());
		deltaTime = now - lastTime;
		lastTime = now;

		window->clearBuffer();
		window->pollEvents();

		camera->handleInputs(window->getKey(), window->getXChange(), window->getYChange(), deltaTime);
		skybox.draw(window, camera);

		window->swapBuffer();

#ifdef DEBUG
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			printf("open gl error code: %d\n", err);
		}
#endif // DEBUG
	}

	delete skyboxShader;
	delete camera;
	delete window;
	return 0;
}
