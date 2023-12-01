#include <fstream>
#include <string>
#include <vector>
using std::string; // std::string -> string
using std::vector; // std::vector -> vector

namespace AOC
{
	// Reads a file, returns a string with the file's content.
	string ReadFile(string Path);

	// Reads a file, returns a vector with a string for each line of the file.
	vector<string> ReadFileLines(string Path);
}

string AOC::ReadFile(string Path)
{
	std::ifstream File = std::ifstream(Path);
	string str = string((std::istreambuf_iterator<char>(File)),
		std::istreambuf_iterator<char>());
	File.close();
	return str;
}

vector<string> AOC::ReadFileLines(string Path)
{
	std::ifstream File = std::ifstream(Path);
	vector<string> Lines;
	while (!File.eof())
	{
		const uint32_t LineSize = 8092;
		char LineBuffer[LineSize];
		File.getline(LineBuffer, LineSize);
		Lines.push_back(LineBuffer);
	}
	File.close();
	return Lines;
}