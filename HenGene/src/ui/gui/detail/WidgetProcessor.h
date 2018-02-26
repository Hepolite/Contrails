
#pragma once

#include "ui/gui/detail/Widget.h"
#include "ui/gui/detail/Widgets.h"
#include "logic/script/Script.h"

#include <glm/vec2.hpp>

namespace ui
{
	namespace gui
	{
		class Processor
		{
		public:
			Processor() = delete;
			Processor(Widgets & widgets, Widget & widget);
			Processor(const Processor &) = default;
			Processor(Processor &&) = default;
			virtual ~Processor() = default;

			Processor & operator=(const Processor &) = default;
			Processor & operator=(Processor &&) = default;
			inline void operator()(const glm::vec2 & pos) { onProcess(pos); }
			inline void operator()(const logic::script::Script & script) { onAction(script); }

			virtual void onProcess(const glm::vec2 & pos);
			virtual void onAction(const logic::script::Script & script);

			const Widget & getParent() const;
			const Widget & getChild(const std::string & name) const;

			glm::vec2 calculatePosition() const;
			glm::vec2 calculateSize() const;

		protected:
			Widgets * m_widgets = nullptr;
			Widget * m_widget = nullptr;
		};

		class ProcessorButtonCheckbox : public Processor
		{
		public:
			ProcessorButtonCheckbox(Widgets & widgets, Widget & widget) : Processor(widgets, widget) {}

			virtual void onAction(const logic::script::Script & script) override final;
		};
		class ProcessorButtonRadio : public Processor
		{
		public:
			ProcessorButtonRadio(Widgets & widgets, Widget & widget) : Processor(widgets, widget) {}

			virtual void onAction(const logic::script::Script & script) override final;
		};
	}
}