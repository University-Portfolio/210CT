#include "IO.h"
#include <iostream>
#include <limits>

namespace IO
{
	bool g_DebugLog = false;
	std::string g_Task;
	In in;
	Out out;
	Out out_debug;
};

using namespace IO;


float In::ReadFloat()
{
	float in;
	std::cin >> in;

	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input\n";
		std::cin >> in;
	}
	return in;
}

int In::ReadInt()
{
	float in = ReadFloat();

	while (in != int(in))
	{
		std::cout << "Invalid input\n";
		in = ReadFloat();
	}

	return int(in);
}

std::string In::ReadString()
{
	std::string in;
	std::getline(std::cin, in);
	return in;
}

char In::ReadChar()
{
	std::string in = ReadString();

	while (in.length() != 1)
	{
		std::cout << "Invalid input\n";
		in = ReadString();
	}

	return in[0];
}


Out& Out::operator<<(const int i)
{
	std::cout << i;
	return (*this);
}

Out& Out::operator<<(const unsigned int i)
{
	std::cout << i;
	return (*this);
}

Out& Out::operator<<(const float i)
{
	std::cout << i;
	return (*this);
}

Out& Out::operator<<(const char i)
{
	std::cout << i;

	if (i == '\n')
		std::cout << g_Task << ":~$ ";
	return (*this);
}

Out& Out::operator<<(const std::string i)
{
	for (const char& c : i)
	{
		std::cout << c;
		if (c == '\n')
			std::cout << g_Task << ":~$ ";
	}
	return (*this);
}

Out& Out::operator<<(const char* i)
{
	std::string a = i;
	(*this) << a;
	return (*this);
}



Out& OutDebug::operator<<(const int i)
{
	if (!IO::g_DebugLog)
		return (*this);
	Out::operator<<(i);
	return (*this);
}

Out& OutDebug::operator<<(const unsigned int i)
{
	if (!IO::g_DebugLog)
		return (*this);
	Out::operator<<(i);
	return (*this);
}

Out& OutDebug::operator<<(const float i)
{
	if (!IO::g_DebugLog)
		return (*this);
	Out::operator<<(i);
	return (*this);
}

Out& OutDebug::operator<<(const char i)
{
	if (!IO::g_DebugLog)
		return (*this);
	Out::operator<<(i);
	return (*this);
}

Out& OutDebug::operator<<(const std::string i)
{
	if (!IO::g_DebugLog)
		return (*this);
	Out::operator<<(i);
	return (*this);
}

Out& OutDebug::operator<<(const char* i)
{
	if (!IO::g_DebugLog)
		return (*this);
	Out::operator<<(i);
	return (*this);
}
