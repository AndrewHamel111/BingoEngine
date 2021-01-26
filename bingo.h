#ifndef BINGO_H_
#define BINGO_H_

#include <string>
#include <vector>

struct bingo_task
{
	std::string name;
	std::string desc;

	std::vector<std::string> antirequisites; /**< vector containing the names of tasks this is mutually exclusive to. */
	double weight; /**< normalized value indicating the chance this task will appear */
};

#endif // BINGO_H_
