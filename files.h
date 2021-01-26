/// All File IO logic is included here, as used by the editor and the game.

#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

// from https://github.com/nlohmann/json
#include <nlohmann/json.hpp>

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <exception>
#include <algorithm>

#include "bingo.h"

// for convenience
using json = nlohmann::json;

struct JSONBingoException : public std::exception
{
	const char * what () const throw ()
	{
		return "Bingo file was not a valid JSON representation of a Bingo set.";
	}
};

std::vector<bingo_task> GetTasksFromJSON(std::string filename);


#endif // FILES_H_INCLUDED
