#include <glad/glad.h>
#include "Shader.h"
#include "Skybox.h"
#include "Window.h"

int main()
{
	Window* window = new Window();

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
		window->clearBuffer();
		window->pollEvents();

		skybox.draw(window);

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
	delete window;
	return 0;
}
