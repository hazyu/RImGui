#pragma once

#include <iostream>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

template<typename ...Args>
void l(Args&&...args) {
  (std::cout << ... << args);
}

template<typename ...Args>
inline void LogError(std::string name, Args && ...args) {
  std::cout << RED << name << RESET << ": ";
  l(args...);
  std::cout << std::endl;
}

template<typename ...Args>
inline void Log(std::string name, Args && ...args) {
  std::cout << CYAN << name << RESET << ": ";
  l(args...);
  std::cout << std::endl;
}
