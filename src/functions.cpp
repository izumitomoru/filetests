#include "functions.h"
#include <string>

// TODO:
// understand how console input and output streams work
// learn gap buffers (looks awesome)
// simplify and consolidate read function to be compatible with writing later on
// improve file info struct (file size, etc.)
// implement scrolling and proper file info fetching

namespace Functions {

  // default path for files
  const string defaultpath{ "./files/" };
  const string defaultcachepath{ "./cache/" };
  // const string defaultpath{ "/run/media/pebarch/pebdrive/_Code/C++/filetests/files/" };
  // const string cachepath{ "/run/media/pebarch/pebdrive/_Code/C++/filetests/cache/" };

  // making very inefficient copies at the moment, but it's workable
  fileInfo getFileInfo(string path) {
    // slightly flawed, but whatever
    string cachepath{};
    if (path[0] != '/' && path[0] != '~' && path[0] != '.') {
      cachepath = defaultcachepath + path;
      path      = defaultpath + path;
    } else if (path[0] == '/' || path[0] == '~' || path[0] == '.') {
    }

    // get total number of lines, allowing for proper padding
    string line;
    ifstream sfile(path);
    int lineSum{};
    int charSum{};
    while (getline(sfile, line)) {
      lineSum++;
      charSum += line.length();
    }
    sfile.close();

    fileInfo info{
      path,
      cachepath,
      path,
      lineSum,
      log10(lineSum),
      charSum,
    };

    return info;
  }

  void writeDummyLines(string path, int linenum) {
    // thing to write dummy lines
    ofstream sfile(path, fstream::out | fstream::trunc);
    for (int i{ 1 }; i <= linenum; ++i) {
      sfile << "line " + to_string(i) << '\n';
    }
    sfile.close();
  }

  void gotoLine(string path, int lineNum) {
    fileInfo file{ getFileInfo(path) };
    ifstream sfile(file.path);

    string line;
    if (sfile.is_open()) {
      // for (int i{}; i <= lineNum; ++i) {
      //  getline(sfile, line);
      //}
      int currentLine{};
      while (getline(sfile, line)) {
        ++currentLine;
        if (currentLine == lineNum)
          break;
      }
      cout << lineNum << ' ' << line << '\n';
    }
  }

  void readFile(const string path) {
    // get file info and open file and cache file
    fileInfo file{ getFileInfo(path) };
    ifstream sfile(file.path);
    // currently will not handle ~ and / paths
    ofstream scachefile(file.cachepath, fstream::out | fstream::trunc);

    while (sfile.is_open()) {
      // get spaces
      // double spacenum = static_cast<int>(file.lineLog10);
      int spacenum = file.lineLog10;
      string spacestr{};

      for (int i{ 0 }; i < spacenum; ++i) {
        // idk which one of these is the most efficient
        spacestr += ' ';
        // spacestr = spacestr + ' ';
        // spacestr.append(" ");
      }

      // line to read
      string line{};
      // track line number manually
      int linenum{};

      // getline() automatically moves to next line
      while (getline(sfile, line)) {
        ++linenum;

        // spaces
        if (log10(linenum) == static_cast<int>(log10(linenum))) {
          spacestr.resize(spacenum);
          --spacenum;
        }

        // print spaces, line number and line
        cout << spacestr << linenum << ' ' << line << '\n';

        // info
        // cout << file.lineLog10 << ' ' << log10(linenum) << ' ' << spacenum << ' ' << spacestr << linenum << ' ' << line << '\n';

        // write to cache file
        scachefile << line << '\n';
      }

      // cache handler
      scachefile.close();

      // enter before closing file or exiting program
      // awful solution probably
      cout << "tttttttttttest\b\b\b\b";
      string enter{};
      cin >> enter;

      remove(file.cachepath.c_str());

      sfile.close();

      // one possible (shitty) solution i found
      // while (!file.eof()) {}
    }
  }

  // awful code, really just trying to understand this library atm
  void readftxui(const string path) {
    using namespace std;
    fileInfo file{ getFileInfo(path) };
    ifstream sfile(file.path);
    ofstream scachefile(file.cachepath, fstream::out | fstream::trunc);

    while (sfile.is_open()) {
      int spacenum = file.lineLog10;
      string spacestr{};

      for (int i{ 0 }; i < spacenum; ++i) {
        spacestr += ' ';
      }

      string line{};
      int linenum{};

      using namespace ftxui;

      string testcontents{};
      tempText contents{};

      while (getline(sfile, line)) {
        ++linenum;

        contents.text.push_back(line += '\n');
        if (std::log10(linenum) == static_cast<int>(std::log10(linenum))) {
          spacestr.resize(spacenum);
          --spacenum;
        }
        // line += '\n';
        testcontents += spacestr + to_string(linenum) + ' ' + line + '\n';
        // contents.text += spacestr + to_string(linenum) + ' ' + line;

        // Element thing = text(line + '\n');
      }

      // idk
      Element thing = paragraph(testcontents);
      // Element contents = paragraph("");

      Element testframe = frame(thing);
      Element winBorder = window(text(""), testframe);
      Element testtext  = text("test thing");

      auto screen = Screen::Create(Dimension::Full());

      screen.ResetPosition(true);
      Render(screen, winBorder);

      // print screen
      // Render(screen, thing);
      // Render(screen, contents);
      screen.Print();

      string b;
      cin >> b;

      scachefile.close();
      sfile.close();
    }
  }

  void openExistingFile(string path) {
    // just wrote over my whole functions.cpp file lol thank god for undo
    // changing this shit to burger.txt ONLY
    // writeDummyLines("./files/burger.txt", 105);

    fileInfo file{ getFileInfo(path) };
    cout << "Path is " << file.path << '\n';
    cout << "Cache path is " << file.cachepath << '\n';

    readFile(file.path);

    // file >> line;

    // assuming you need a loop for all lines, i'll experiment with that

    // writing to file goes here i guess
  }

  void fileBufferTest(const string path) {
    fileInfo file{ getFileInfo(path) };

    ifstream sfile(file.path);

    while (sfile.is_open()) {
      // line to read
      string line{};
      // track line number manually
      int linenum{};

      vector<char> test{};

      while (getline(sfile, line)) {
        for (int i{}; i < line.size(); ++i) {
          test.push_back(line[i] += '\n');
        }
        // test.push_back(line += '\n');
        // GapBuffer::createTestBuffer();
      }

      sfile.close();

      for (int i; i < test.size(); ++i) {
        cout << test[i];
      }
    }
  }

} // namespace Functions
