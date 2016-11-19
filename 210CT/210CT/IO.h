#pragma once
#include <string>

namespace IO
{
	class In 
	{
	private:
		int ReadInt();
		int ReadUnsignedInt();
		float ReadFloat();

		char ReadChar();
		std::string ReadString();

	public:
		inline void operator>>(int& i) { i = ReadInt(); }
		inline void operator>>(unsigned int& i) { i = ReadUnsignedInt(); }
		inline void operator>>(float& i) { i = ReadFloat(); }
		inline void operator>>(char& i) { i = ReadChar(); }
		inline void operator>>(std::string& i) { i = ReadString(); }
	};

	class Out
	{
	public:
		Out& operator<<(const int i);
		Out& operator<<(const unsigned int i);
		Out& operator<<(const float i);
		Out& operator<<(const char i);
		Out& operator<<(const char* i);
		Out& operator<<(const std::string i);

	};

	extern bool g_DebugLog;
	extern std::string g_Task;
	extern In in;
	extern Out out;
	extern Out out_debug;
};

