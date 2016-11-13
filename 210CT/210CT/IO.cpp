#include "IO.h"
#include <iostream>
#include <limits>
#include <stdio.h>

namespace IO
{
	bool g_DebugLog = false;
	std::string g_Task;
	In in;
	Out out;
	Out out_debug;
};

using namespace IO;

inline void PrintStartLine() { std::cout << g_Task << ":~$ "; }

float In::ReadFloat()
{
	float in;
	std::cin >> in;
	PrintStartLine();

	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		IO::out << "Invalid input\n";
		std::cin >> in;
		PrintStartLine();
	}
	return in;
}

int In::ReadInt()
{
	float in = ReadFloat();

	while (in != int(in))
	{
		IO::out << "Invalid input\n";
		in = ReadFloat();
	}

	return int(in);
}

std::string In::ReadString()
{
	std::string in = "";

	while (!in.length()) //To deal with the left overs from last time
		std::getline(std::cin, in);

	PrintStartLine();
	return in;
}

char In::ReadChar()
{
	std::string in = ReadString();

	while (in.length() != 1)
	{
		IO::out << "Invalid input\n";
		in = ReadString();
	}

	return in[0];
}


Out& Out::operator<<(const int i)
{
	if(!g_DebugLog && this == &IO::out_debug)
		return (*this);

	std::cout << i;
	return (*this);
}

Out& Out::operator<<(const unsigned int i)
{
	if (!g_DebugLog && this == &IO::out_debug)
		return (*this);

	std::cout << i;
	return (*this);
}

Out& Out::operator<<(const float i)
{
	if (!g_DebugLog && this == &IO::out_debug)
		return (*this);

	std::cout << i;
	return (*this);
}

Out& Out::operator<<(const char i)
{
	if (!g_DebugLog && this == &IO::out_debug)
		return (*this);

	std::cout << i;

	if (i == '\n')
		PrintStartLine();
	return (*this);
}

Out& Out::operator<<(const std::string i)
{
	if (!g_DebugLog && this == &IO::out_debug)
		return (*this);

	for (const char& c : i)
	{
		std::cout << c;
		if (c == '\n')
			PrintStartLine();
	}
	return (*this);
}

Out& Out::operator<<(const char* i)
{
	if (!g_DebugLog && this == &IO::out_debug)
		return (*this);

	std::string a = i;
	(*this) << a;
	return (*this);
}