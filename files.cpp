#include "files.h"

std::vector<bingo_task> GetTasksFromJSON(std::string filename)
{
	json j;

	std::ifstream is(filename);
	is >> j;
	is.close();

	json tasks = j["tasks"];
	std::vector<bingo_task> v;

	auto i = tasks.begin();
	auto iEnd = tasks.end();
	for(; i != iEnd; i++)
	{
		bingo_task t;
		t.weight = 1;
		t.name = i->at("name");
		t.desc = i->at("desc");

		v.push_back(t);
	}

	return v;
}
