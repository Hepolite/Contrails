
#pragma once

namespace render
{
	namespace allegro
	{
		class Allegro
		{
		public:
			Allegro();
			~Allegro();

			inline auto isInitialized() const { return m_isInitialized; }
			inline auto hasErrors() const { return m_hasErrors; }

		private:
			bool m_isInitialized = false;
			bool m_hasErrors = false;
		};
	}
}