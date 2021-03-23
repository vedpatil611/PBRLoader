#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Skybox.h"
#include "Window.h"

Camera* camera;
Window* window;
Shader* skyboxShader;
Shader* basicShader;

float deltaTime = 0.0f;
float lastTime = 0.0f;

int main()
{
	window = new Window();
	camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 5.0f);

	const char* faces[] = {
		"assets/skybox/right.jpg",
		"assets/skybox/left.jpg",
		"assets/skybox/top.jpg",
		"assets/skybox/bottom.jpg",
		"assets/skybox/front.jpg",
		"assets/skybox/back.jpg"
	};

	skyboxShader = new Shader("shaders/skybox.vert.glsl", "shaders/skybox.frag.glsl");
	basicShader = new Shader("shaders/basic.vert.glsl", "shaders/basic.frag.glsl");

	Skybox skybox(faces, skyboxShader);

	float floorVertices[] = {
		-50.0f, 0.0f, -50.0f,
		 50.0f, 0.0f, -50.0f,
		 50.0f, 0.0f,  50.0f,
		-50.0f, 0.0f,  50.0f,
	};
	unsigned short floorIndicies[] = {
		0, 1, 2,
		2, 3, 0
	};
	Mesh floor(floorVertices, 4 * 3, floorIndicies, 2 * 3, basicShader);
	floor.setTranslation(glm::vec3(0.0f, -50.0f, 0.0f));
	floor.setScaling(glm::vec3(3.0f, 3.0f, 3.0f));

	while (!window->shouldClose())
	{
		float now = static_cast<float>(glfwGetTime());
		deltaTime = now - lastTime;
		lastTime = now;

		window->clearBuffer();
		window->pollEvents();

		camera->handleInputs(window->getKey(), window->getXChange(), window->getYChange(), deltaTime);
		skybox.draw(window, camera);
		floor.draw(window, camera);

		window->swapBuffer();
#ifdef DEBUG
		while (GLenum err = glGetError())
		{
			printf("open gl error code: %d\n", err);
		}
#endif // DEBUG
	}

	delete skyboxShader;
	delete basicShader;
	delete camera;
	delete window;
	return 0;
}
