
#pragma once

#include <allegro5/utf8.h>
#include <string>

namespace render
{
	namespace allegro
	{
		class String
		{
		public:
			static constexpr unsigned int END = 0xFFFFFFFFu;

			String();
			String(const std::string & string);
			String(const String & other);
			String(String && other);
			~String();

			String & operator=(const String & other);
			String & operator=(String && other);

			void setString(const std::string & string);
			std::string getString() const;

			unsigned int length() const;
			unsigned int at(unsigned int index) const;
			unsigned int next(unsigned int & index) const;

			unsigned int find(unsigned int codepoint, unsigned int index = 0u) const;
			String substr(unsigned int begin = 0u, unsigned int end = END) const;

		private:
			String(ALLEGRO_USTR * handle) : m_handle(handle) {}

			ALLEGRO_USTR * m_handle = nullptr;
		};
	}
}