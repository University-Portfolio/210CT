#pragma once

#define VERBOSE_LOG 1

#if VERBOSE_LOG
#define LOG(str) std::cout << "[Debug] " << str << '\n'
#else
#define LOG(str)
#endif