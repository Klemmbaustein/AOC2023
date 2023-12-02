#include "../Shared/Shared.hpp"
#include <print>
#include <sstream>
#include <map>

#define INPUT_TEST 0
#define ADVANCED 1

// Seperates a string into a vector of strings, seperated by "Seperator"
vector<string> Seperate(string String, char Seperator)
{
	vector<string> Sets;

	size_t Last = 0;
	do
	{
		size_t PrevLast = Last == 0 ? Last : Last + 1;
		Last = String.find_first_of(string({ Seperator }), PrevLast);
		string Set = String.substr(PrevLast, Last - PrevLast);
		if (Set[0] == ' ')
		{
			Set = Set.substr(1);
		}
		Sets.push_back(Set);
	} while (Last != std::string::npos);
	return Sets;
}

#if ADVANCED
std::map<string, int32_t> Colors =
{
	{"red", 0},
	{"green", 0},
	{"blue", 0}
};
#else
std::map<string, int32_t> Colors =
{
	{"red", 12},
	{"green", 13},
	{"blue", 14}
};
#endif
int main()
{
#if INPUT_TEST
	auto Lines = AOC::ReadFileLines("test_input.txt");
#else
	auto Lines = AOC::ReadFileLines("input.txt");
#endif

	uint32_t Total = 0;

	for (string i : Lines)
	{
		if (i.empty())
		{
			continue;
		}
		string GameName = i.substr(0, i.find_first_of(":"));

		string GameString = i.substr(i.find_first_of(":") + 2);

		// "4 red, 3 blue; 2 green, 5 red" -> {"4 red, 3 blue", "2 green, 5 red"}
		vector<string> Sets = Seperate(GameString, ';');

		vector<vector<string>> SetEntries;
		for (string s : Sets)
		{
			// "4 red, 3 blue" -> {"4 red", "3 blue"}
			SetEntries.push_back(Seperate(s, ','));
		}

#if !ADVANCED
		bool Possible = true;
#endif
		std::map ColorCount = Colors;

		for (vector Set : SetEntries)
		{

			for (string Entry : Set)
			{
				// "12 blue" -> {"12", "blue"}
				vector EntryVector = Seperate(Entry, ' ');
				int Amount = std::stoi(EntryVector[0]);

#if ADVANCED
				ColorCount[EntryVector[1]] = std::max(Amount, ColorCount[EntryVector[1]]);
#else
				ColorCount[EntryVector[1]] -= Amount;
#endif
			}
#if !ADVANCED
			for (auto& Color : ColorCount)
			{
				if (Color.second < 0)
				{
					Possible = false;
				}
			}
#endif
		}

		uint32_t Power = 1;
		for (auto& Color : ColorCount)
		{
			Power *= Color.second;
		}
		Total += Power;

		uint32_t GameID = std::stoul(GameName.substr(GameName.find_first_of(" ")));

#if !ADVANCED
		if (Possible)
		{
			Total += GameID;
		}
#endif
		// std::println("Game {}: Possible - {}!", GameID, Possible ? "yes" : "no");
	}

	std::println("Result is {}", Total);
}