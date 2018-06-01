
#pragma once

#include "io/File.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

namespace hexifier
{
	class Hexifier
	{
	public:
		inline void setInput(const io::File & file) { m_in = file; }
		inline void setOutput(const io::File & file) { m_out = file; }

		void process();
		bool work();

	private:
		io::File m_in{ "" };
		io::File m_out{ "" };
	};
}

inline void hexifier::Hexifier::process()
{
	std::cout << "Converts the data of a file into a raw byte array" << std::endl;

	bool done = false;
	while (!done)
	{
		std::cout << "Enter an input file: ";

		std::string in;
		std::cin >> in;
		m_in = io::File{ in };

		if (m_in.exists())
		{
			std::cout << "Enter an output file: ";

			std::string out;
			std::cin >> out;
			m_out = io::File{ out };

			if (m_out.exists())
			{
				std::cout << "The file '" + m_out.getPath() + "' already exists. Overwrite it? (Y/N) ";

				std::string confirm;
				std::cin >> confirm;

				if (confirm == "Y")
					done = work();
				else
					std::cout << "Did not overwrite '" + m_out.getPath() + "'" << std::endl;
			}
			else
				done = work();
		}
		else
			std::cout << "The file '" + m_in.getPath() + "' does not exist" << std::endl;
	}
}
inline bool hexifier::Hexifier::work()
{
	std::ifstream input{ m_in.getPath(), std::ios::binary };
	std::vector<unsigned char> buffer{ std::istreambuf_iterator<char>{ input }, std::istreambuf_iterator<char>{} };

	std::ofstream output{ m_out.getPath() };
	output << "constexpr unsigned int size = " << buffer.size() << ";" << std::endl;
	output << "constexpr unsigned char data[] = {";
	for (unsigned int i = 0u; i < buffer.size(); ++i)
	{
		if (i % 20 == 0)
			output << std::endl << "\t";
		output << "0x" << std::hex << (unsigned int)buffer[i] << ", ";
	}
	output << std::endl << "};" << std::endl;
	return true;
}