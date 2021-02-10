#pragma once
#include "Heirloom/Layer.h"
#include "Heirloom/Events/ApplicationEvent.h"

namespace Heirloom
{
	class HL_API ImGuiLayer final : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override { }
		void OnImGuiRender() override;
		void OnEvent(Event& event) override { }
		
		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}
