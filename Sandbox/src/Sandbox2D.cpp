#include "Sandbox2D.h"

#include "Heirloom/Audio/SoundService.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"),
	  m_CameraController(1280.0f / 960.0f, false),
	  m_BackgroundMusic(Heirloom::CreateRef<Heirloom::Sound>("assets/sounds/breakout.mp3", 1.0f, false))
{
}

void Sandbox2D::OnAttach()
{
	HL_PROFILE_FUNCTION()

	Heirloom::SoundService::Provide(new Heirloom::SimpleSoundEngine());

	Heirloom::SoundService::GetSoundEngine()->Play("assets/sounds/breakout.mp3");

	m_BackgroundTexture = Heirloom::Texture2D::Create("assets/textures/Checkerboard.png");
	m_Logo              = Heirloom::Texture2D::Create("assets/textures/logo.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(const Heirloom::Timestep)
{
	HL_PROFILE_FUNCTION()

	if (Heirloom::Input::IsKeyPressed(HL_KEY_SPACE))
	{
		Heirloom::SoundService::GetSoundEngine()->Stop(m_BackgroundMusic);
	}

	m_CameraController.Update(Heirloom::Timestep{0.016f});
}

void Sandbox2D::OnRender()
{
	Heirloom::Renderer2D::ResetStats();

	Heirloom::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	Heirloom::RenderCommand::Clear();

	Heirloom::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Heirloom::Renderer2D::DrawRotatedQuad({1.0f, 0.0f}, {0.8f, 0.8f}, -45.0f, {0.8f, 0.2f, 0.3f, 1.0f});
	Heirloom::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
	Heirloom::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});
	Heirloom::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {20.0f, 20.0f}, m_BackgroundTexture, 10.0f);
	Heirloom::Renderer2D::DrawRotatedQuad({-2.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, 45.0f, m_BackgroundTexture, 20.0f);

	Heirloom::Renderer2D::EndScene();

	Heirloom::Renderer2D::BeginScene(m_CameraController.GetCamera());
	for (float y = -5.0f; y < 5.0f; y += 0.5f)
	{
		for (float x = -5.0f; x < 5.0f; x += 0.5f)
		{
			glm::vec4 color = {(x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f};
			Heirloom::Renderer2D::DrawQuad({x, y}, {0.45f, 0.45f}, color);
		}
	}
	Heirloom::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	HL_PROFILE_FUNCTION()

	// Note: Switch this to true to enable dockspace
	static bool dockingEnabled = true;
	if (dockingEnabled)
	{
		static bool dockspaceOpen                 = true;
		static bool optFullscreenPersistant       = true;
		const bool optFullscreen                 = optFullscreenPersistant;
		static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (optFullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
				ImGuiWindowFlags_NoMove;
			windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
		{
			windowFlags |= ImGuiWindowFlags_NoBackground;
		}

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, windowFlags);
		ImGui::PopStyleVar();

		if (optFullscreen)
		{
			ImGui::PopStyleVar(2);
		}

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			const ImGuiID dockspaceID = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit"))
				{
					Heirloom::Application::Get().Close();
				}
				
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		const auto stats = Heirloom::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

		const uint32_t textureID = m_BackgroundTexture->GetRendererID();
		#pragma warning (disable : 4312)
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{256.0f, 256.0f});
		ImGui::End();

		ImGui::End();
	}
	else
	{
		ImGui::SetNextWindowPos(ImVec2(10, 10));
		ImGui::Begin("main",
					 nullptr,
					 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::SetWindowFontScale(2.0);
		ImGui::Text("%.0f FPS", ImGui::GetIO().Framerate);
		ImGui::End();

		ImGui::Begin("Settings");

		auto stats = Heirloom::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

		const uint32_t textureID = m_BackgroundTexture->GetRendererID();
		#pragma warning (disable : 4312)
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{256.0f, 256.0f});
		ImGui::End();
	}
}
