#pragma once
#include "Core/Timestep.h"

#include "Events/Event.h"

namespace Heirloom
{
	class HL_API Layer
	{
	public:
		explicit Layer(const std::string& debugName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate(Timestep ts) = 0;
		virtual void OnImGuiRender() = 0;
		virtual void OnEvent(Event& event) = 0;

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}
