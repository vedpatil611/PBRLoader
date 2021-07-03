#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <Camera.h>
#include <Mesh.h>
#include <Shader.h>
#include <Skybox.h>
#include <TextureArray.h>
#include <Texture.h>
#include <Window.h>
#include <ImGui/imgui.h>
#include <imgui-filebrowser/imfilebrowser.h>
#include <UI/DockableWindow.h>

Camera* camera;
Window* window;
Shader* skyboxShader;
Shader* basicShader;

float deltaTime = 0.0f;
float lastTime = 0.0f;

void propertyPage();

static char meshName[256] = "null";
static bool selectMeshBox = false;

static char diffuseTexName[256] = "null";
static bool selectdiffuseTexBox = false;

int main()
{
	window = new Window();
	camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 20.0f, 5.0f);
	TextureArray texArray;

	DockableWindow::init(window);

	const char* faces[] = {
		"assets/skybox/right.jpg",
		"assets/skybox/left.jpg",
		"assets/skybox/top.jpg",
		"assets/skybox/bottom.jpg",
		"assets/skybox/front.jpg",
		"assets/skybox/back.jpg"
	};

	basicShader = new Shader("shaders/basic.vert.glsl", "shaders/basic.frag.glsl");
	skyboxShader = new Shader("shaders/skybox.vert.glsl", "shaders/skybox.frag.glsl");

	Skybox skybox(faces, skyboxShader);

	float floorVertices[] = {
		-50.0f, 0.0f, -50.0f,	0.0f, 0.0f,		//0
		 50.0f, 0.0f, -50.0f,	1.0f, 0.0f,		//1
		 50.0f, 0.0f,  50.0f,	1.0f, 1.0f,		//2
		-50.0f, 0.0f,  50.0f,	0.0f, 1.0f,		//3
	};
	unsigned short floorIndicies[] = {
		0, 1, 2,
		2, 3, 0
	};
	Mesh floor(floorVertices, 4 * 5, floorIndicies, 2 * 3, basicShader);
	floor.setTranslation(glm::vec3(0.0f, -50.0f, 0.0f));
	

	floor.setTexture(texArray["brick"]);

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
		
		DockableWindow::begin();
		propertyPage();
		DockableWindow::end();

		window->swapBuffer();

#ifdef DEBUG
		while (GLenum err = glGetError())
		{
			printf("open gl error code: %d\n", err);
		}
#endif // DEBUG
	}

	DockableWindow::destroy();
	delete skyboxShader;
	delete basicShader;
	delete camera;
	delete window;
	return 0;
}

void propertyPage()
{
	ImGui::Begin("Properties");

	ImGui::Text("Mesh");

	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
	ImGui::BeginChild("Mesh Box", ImVec2(0, ImGui::GetFrameHeightWithSpacing() + 10.0f), true);
	ImGui::Text("%s", meshName);
	ImGui::EndChild();
	ImGui::PopStyleVar(2);

	ImGui::Button("Select Mesh");
	
	ImGui::NewLine();

	////////////////////////////////////////////

	ImGui::Text("Diffuse Texture");

	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
	ImGui::BeginChild("Diffuse Tex Box", ImVec2(0, ImGui::GetFrameHeightWithSpacing() + 10.0f), true);
	ImGui::Text("%s", meshName);
	ImGui::EndChild();
	ImGui::PopStyleVar(2);

	ImGui::Button("Select Texture");

	ImGui::End();
}
