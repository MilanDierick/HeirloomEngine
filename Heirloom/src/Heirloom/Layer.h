#pragma once
#include "Events/Event.h"

namespace Heirloom
{
	class HL_API Layer
	{
	public:
		explicit Layer(const std::string& debugName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() { }
		virtual void OnDetach() { }
		virtual void OnUpdate() { }
		virtual void OnEvent(Event& event) { }

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}
