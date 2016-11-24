#include <iostream>
#include <sstream>

#include "IO.h"
#include "Task1\Task1.h"
#include "Task2\Task2.h"
#include "Task5\Task5.h"
#include "Task6\Task6.h"
#include "Task7\Task7.h"
#include "Task8\Task8.h"
#include "Task9\Task9.h"
#include "Task10\Task10.h"
#include "Task11\Task11.h"
#include "Task12\Task12.h"
#include "Task13\Task13.h"
#include "Task14\Task14.h"

void LaunchTask(const int in)
{
	if (in == 3 || in == 4)
		IO::out << "This is a pseudocode only task.\n";

	else if (in >= 1 && in <= 14)
	{
		std::stringstream ss;
		ss << "Task " << in;
		IO::g_Task = ss.str();
		IO::out << "Launching task " << in << "\n";

		switch (in)
		{
		case 1:
			TASK_1::Execute();
			break;
		case 2:
			TASK_2::Execute();
			break;
		case 5:
			TASK_5::Execute();
			break;
		case 6:
			TASK_6::Execute();
			break;
		case 7:
			TASK_7::Execute();
			break;
		case 8:
			TASK_8::Execute();
			break;
		case 9:
			TASK_9::Execute();
			break;
		case 10:
			TASK_10::Execute();
			break;
		case 11:
			TASK_11::Execute();
			break;
		case 12:
			TASK_12::Execute();
			break;
		case 13:
			TASK_13::Execute();
			break;
		case 14:
			TASK_14::Execute();
			break;
		}

		IO::g_Task = "Home";
		IO::out << "Finished task!\n";
	}
	else
		IO::out << "Input '" << in << "'" << " is outside of task range (1-14)";
}

int main(char** arg_v, int arg_c)
{
	IO::g_Task = "Home";
	IO::out << "210CT Coursework - Samuel Potter\n";

	while (true)
	{
		std::string in;
		IO::out << "Please input a command:\n";
		IO::out << "\t\t*'run %i'\t-- Launch task (-v for verbose logging)\n";
		IO::out << "\t\t*'quit'\t\t-- Quit the application\n";
		IO::in >> in;

		std::vector<std::string> param;
		std::string com_buffer;

		//Fill
		for (char c : in) 
		{
			if (c == ' ')
			{
				if (!com_buffer.empty())
					param.push_back(com_buffer);

				com_buffer = "";
			}
			else
				com_buffer += c >= 'A' && c <= 'Z' ? c + 32 : c; //Store in lower-case
		}
		if (!com_buffer.empty())
			param.push_back(com_buffer);

		const int com_count = param.size();

		if (!com_count)
		{
			IO::out << "Invalid input!\n";
			continue;
		}

		if (param[0] == "quit")
			break;

		else if (param[0] == "run")
		{
			if (com_count == 1)
			{
				IO::out << "Need to give task number\n";
				continue;
			}

			//Check second input is number
			bool is_number = true;
			for (char c : param[1])
				if (c < '0' || c > '9')
					is_number = false;

			if(!is_number)
			{
				IO::out << "'" << param[1] << "' is not a number\n";
				continue;
			}

			const int task = std::stoi(param[1]);
			IO::g_DebugLog = false;

			//Put in debug mode if -v is present
			if (com_count > 2)
			{
				for (std::string p : param)
					if (p == "-v")
					{
						IO::g_DebugLog = true;
						break;
					}
			}
			
			LaunchTask(task);
		}

		else
			IO::out << "Unknown command '" << param[0] << "'\n";
	}

	return 0;
}