#pragma once
#include <string>

namespace IO
{
	class In 
	{
	private:
		int ReadInt();
		float ReadFloat();

		char ReadChar();
		std::string ReadString();

	public:
		inline void operator>>(int& i) { i = ReadInt(); }
		inline void operator>>(float& i) { i = ReadFloat(); }
		inline void operator>>(char& i) { i = ReadChar(); }
		inline void operator>>(std::string& i) { i = ReadString(); }
	};

	class Out
	{
	public:
		virtual Out& operator<<(const int i);
		virtual Out& operator<<(const unsigned int i);
		virtual Out& operator<<(const float i);
		virtual Out& operator<<(const char i);
		virtual Out& operator<<(const char* i);
		virtual Out& operator<<(const std::string i);

	};

	class OutDebug : public Out
	{
	public:
		virtual Out& operator<<(const int i) override;
		virtual Out& operator<<(const unsigned int i) override;
		virtual Out& operator<<(const float i) override;
		virtual Out& operator<<(const char i) override;
		virtual Out& operator<<(const char* i) override;
		virtual Out& operator<<(const std::string i) override;

	};

	extern bool g_DebugLog;
	extern std::string g_Task;
	extern In in;
	extern Out out;
	extern Out out_debug;
};

