#include "FileReader.hh"

#include <cstdio>
#include <stdexcept>
#include <string>
#include <array>

using std::string;
#define BUFF_SIZE 1024
#define CPP_ERR "Preprocessor failed"

string processCmdFile(string filename)
{
  std::array<char, BUFF_SIZE> buff;
  string command = "cpp -P " + filename;
  string result;

  FILE *pipe = popen(command.c_str(), "r");

  if (!pipe)
    throw std::runtime_error(CPP_ERR);

  while (!feof(pipe))
  {
    if (fgets(buff.data(), BUFF_SIZE, pipe) != nullptr)
      result += buff.data();
  }

  if (pclose(pipe) == EXIT_SUCCESS)
    return result;
  else
    throw std::runtime_error(CPP_ERR);
}