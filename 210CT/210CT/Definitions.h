#pragma once

#define VERBOSE_LOG 0

#if VERBOSE_LOG
#define LOG(str) std::cout << str << '\n'
#else
#define LOG(str)
#endif