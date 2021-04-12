#include "SandboxScene2D.h"

SandboxScene2D::SandboxScene2D(const std::string& sceneName)
	: Scene(sceneName), m_CameraController(1280.0f / 960.0f, false)
{
}

void SandboxScene2D::OnLoad()
{
	HL_PROFILE_FUNCTION()

	Heirloom::SoundService::Provide(new Heirloom::SimpleSoundEngine());

	Heirloom::SoundService::GetSoundEngine()->Play("assets/sounds/breakout.mp3");

	m_BackgroundTexture = Heirloom::Texture2D::Create("assets/textures/Checkerboard.png");
	m_Logo              = Heirloom::Texture2D::Create("assets/textures/logo.png");
	
	m_BackgroundSprite = Heirloom::Sprite({0.0f, 0.0f, -0.1f},
										  {5.0f, 5.0f},
										  glm::radians(45.0f),
										  m_BackgroundTexture,
										  10.0f,
										  {1.0f, 0.9f, 0.9f, 1.0f});
}

void SandboxScene2D::OnUnload()
{
}

void SandboxScene2D::OnUpdate()
{
	HL_PROFILE_FUNCTION()

	m_CameraController.Update(Heirloom::Timestep{0.016f});
}

void SandboxScene2D::OnRender()
{
	HL_PROFILE_FUNCTION()

	Heirloom::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	Heirloom::RenderCommand::Clear();

	Heirloom::Renderer2D::BeginScene(m_CameraController.GetCamera());

	// Heirloom::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, m_SquareColor);
	// Heirloom::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, m_SquareColor);
	Heirloom::Renderer2D::DrawRotatedQuad(m_BackgroundSprite);
	Heirloom::Renderer2D::DrawQuad({0.0f, 0.8f}, {1.0f, 1.0f}, m_Logo);

	Heirloom::Renderer2D::EndScene();
}

void SandboxScene2D::OnImGuiRender()
{
	HL_PROFILE_FUNCTION()

	ImGui::SetNextWindowPos(ImVec2(10, 10));
	ImGui::Begin("main",
				 nullptr,
				 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SetWindowFontScale(2.0);
	ImGui::Text("%.0f FPS", ImGui::GetIO().Framerate);
	ImGui::End();
}
