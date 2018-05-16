
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
			String();
			String(const std::string & string);
			String(const String & other);
			String(String && other);
			~String();

			String & operator=(const String & other);
			String & operator=(String && other);

			void setString(const std::string & string);

			unsigned int getLength() const;
			unsigned int getCodepoint(int & index) const;

		private:
			ALLEGRO_USTR * m_handle;
		};
	}
}