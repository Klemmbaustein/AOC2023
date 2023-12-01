#include "../Shared/Shared.hpp"
#include <print>
#include <unordered_map>

#define INPUT_TEST 0
#define ADVANCED 1

#if ADVANCED
std::unordered_map<string, string> DigitStrings =
{
	{"one", "1"},
	{"two", "2"},
	{"three", "3"},
	{"four", "4"},
	{"five", "5"},
	{"six", "6"},
	{"seven", "7"},
	{"eight", "8"},
	{"nine", "9"},
};
#endif

// https://stackoverflow.com/questions/2896600/how-to-replace-all-occurrences-of-a-character-in-string
void ReplaceAll(string& str, const string& from, const string& to) 
{
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos) 
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
}

int main()
{
#if INPUT_TEST
	auto Lines = AOC::ReadFileLines("test_input.txt");
#else
	auto Lines = AOC::ReadFileLines("input.txt");
#endif

	uint64_t Sum = 0;

	for (string Line : Lines)
	{
		if (Line.empty())
		{
			continue;
		}

		char FirstNumber = 0, LastNumber = 0;

#if ADVANCED
		// Add the literal digit into any digit string. So onetwothree -> on1etw2othr3ee
		// This should *probably* not cause any issues where two numbers are connected
		// Like: twone -> 2, 1 -> tw2o, on1e -> tw2on1e
		for (const auto& digit : DigitStrings)
		{
			size_t StringPos = 0;
			while (true)
			{
				bool Found = false;
				StringPos = Line.find(digit.first, StringPos);
				if (StringPos != std::string::npos)
				{
					Line.insert(StringPos + digit.first.size() / 2 + 1, digit.second);
					StringPos += digit.first.size();
					Found = true;
				}
				if (!Found)
				{
					break;
				}
			}
		}
#endif
		for (char c : Line)
		{
			if (!std::isdigit(c))
			{
				continue;
			}
			if (!FirstNumber)
			{
				FirstNumber = c;
			}
			LastNumber = c;
		}
		Sum += std::stoi(string({ FirstNumber, LastNumber }));
	}

	std::println("Result is {}", Sum);
}