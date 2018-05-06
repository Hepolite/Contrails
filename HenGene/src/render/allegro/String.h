
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
			String(const std::string & str);
			String(const String & other);
			String(String && other);
			~String();

			String & operator=(const String & other);
			String & operator=(String && other);
			String & operator=(const std::string & str);

			bool operator==(const String & other) const;
			inline bool operator!=(const String & other) const { return !(*this == other); }

			String & operator+=(const String & other);
			inline String & operator+=(const std::string & str) { return *this += String{ str }; }
			friend String operator+(String lhs, const String & rhs) { return lhs += rhs; }
			friend String operator+(String lhs, const std::string & rhs) { return lhs += rhs; }

			inline bool empty() const { return size() == 0u; }
			unsigned int size() const;
			const char * c_str() const;

			inline auto getHandle() const { return m_handle; }

		private:
			String(ALLEGRO_USTR * handle);

			ALLEGRO_USTR * m_handle = nullptr;
		};
	}
}