#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// #include "cli/cli.h"
// doesn't work i guess
// #include "cpp-terminal/terminal.hpp" // will be trying to use this if ftxui sucks (unlikely)

#include "gap_buffer.h"
#include <cmath>
#include <fstream>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <streambuf>
#include <string>

namespace Functions {
  using namespace std;
  struct fileInfo {
    string path{};
    string filename{};
    string cachepath;
    int lineSum{};
    double lineLog10{};
    int charSum{};
  };
  fileInfo getFileInfo(const string);
  void readFile(const string);
  void readftxui(const string);
  void writeDummyLines(string, int);
  void openExistingFile(string);
  void mainLoop();
  string getLine(const string path, int lineNum);
} // namespace Functions
#endif
