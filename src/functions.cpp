#include "functions.h"

// TODO:
// make slightly less bad structs
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
    while (getline(sfile, line)) {
      lineSum++;
    }
    sfile.close();

    fileInfo info{
      path,
      cachepath,
      path,
      lineSum,
      0,
    };

    return info;
  }

  // uses line sum to calculate spaces (highly inefficient right now)
  void getSpaces(int& linenum, int& spacenum, string& spacestr) {
    spacestr = "";
    // if whole number, decrement the number of spaces, this means each time it becomes a power of 10 it can recognize the change without needing a shitton of if statements
    if (log10(linenum) == static_cast<int>(log10(linenum))) {
      --spacenum;
    }
    for (int i{}; i <= spacenum; ++i) {
      // idk which one of these is the most efficient
      // spacestr = spacestr + ' ';
      spacestr += ' ';
      // spacestr.append(" ");
    }
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
    // open file and get line number
    fileInfo file{ getFileInfo(path) };
    ifstream sfile(file.path);
    // const int linesum{ getLineSum(path) };

    sfile.close();

    // reopen file (required)
    sfile.open(path);

    // create and open cache file
    // currently will not handle ~ and / paths
    ofstream cachefile(file.cachepath, fstream::out | fstream::trunc);

    // space counter
    int spacenum = log10(file.lineSum);
    // string for the spaces
    string spacestr;
    // line to read
    string line;

    /// reading file

    // good solution i found
    // don't use file.eof() as it only returns true after reading the end of the stream, it doesn't indicate that the next read will be end
    if (sfile.is_open()) {
      // track line number manually
      int linenum{};

      // getline() automatically moves to next line
      while (getline(sfile, line)) {
        // print lines
        ++linenum;

        // calculate number of spaces (super inefficiently)
        getSpaces(linenum, spacenum, spacestr);

        // print spaces, line number and line
        cout << spacestr << linenum << ' ' << line << '\n';

        // write to cache file
        cachefile << line << '\n';
      }

      // i wanna be able to get a line number and print just that line
      // void getspecificline(vector<ifstream*> file) {
      //  getline(*file[45], line);

      //  cout << "line 30 " << line;
      //}

      // cache handler
      cachefile.close();

      // enter before closing file or exiting program
      // awful solution probably
      string enter{};
      cin >> enter;

      remove(file.cachepath.c_str());

      sfile.close();

      // one possible (shitty) solution i found
      // while (!file.eof()) {}
    }
  }

  void openExistingFile(string path) {
    // just wrote over my whole functions.cpp file lol thank god for undo
    // changing this shit to burger.txt ONLY
    // writeDummyLines("./files/burger.txt", 200);

    fileInfo file{ getFileInfo(path) };
    cout << "Path is " << file.path << '\n';

    readFile(file.path);

    // file >> line;

    // assuming you need a loop for all lines, i'll experiment with that

    // writing to file goes here i guess
  }
} // namespace Functions
