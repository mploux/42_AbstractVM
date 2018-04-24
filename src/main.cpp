//
// Created by Marc-andre PLOUX on 4/24/18.
//

#include <iostream>
#include <deque>
#include <fstream>
#include <regex>
#include <map>
#include <vector>
#include "Action.hpp"

void parseLine(const std::string &raw_line, std::vector<Action *> &actions, const int &line_num, std::map<int, std::string> &errors)
{
	std::string line;

	line = raw_line;

	size_t commentIndex = line.find(";");
	if (commentIndex != std::string::npos)
		line.erase(line.begin() + commentIndex, line.end());

	size_t trimSpaces = line.find_last_not_of(" \t");
	if (trimSpaces != std::string::npos)
		line.erase(line.begin() + trimSpaces + 1, line.end());
	if (trimSpaces == std::string::npos && !line.empty())
		line.erase(line.begin(), line.end());

	if (line.empty())
		return;

	std::regex validCommands("^(add|dump|pop|mul|exit)$");
	std::regex validParamCommands("^(push|assert) (int8|int16|int32|float|double)\\((.+)\\)$");
	std::smatch command;

	if (std::regex_match(line, command, validCommands))
	{
		std::string cmd = command.str();
		actions.push_back(new Action(cmd));
	}
	else if (std::regex_match(line, command, validParamCommands))
	{
		std::string cmd = command[1].str();
		std::string type = command[2].str();
		std::string value = command[3].str();
		actions.push_back(new Action(cmd, type, value));
	}
	else
		errors[line_num] = "Syntax error !";
}

int main(int ac, char **av)
{
	std::deque<float> stack;
	std::vector<Action *> actions;
	std::map<int, std::string> errors;

	std::ifstream in(av[1]);
	if (in.is_open())
	{
		std::string line;
		int line_count = 1;
		while (std::getline(in, line))
		{
			if (line == "exit")
				break;
			parseLine(line, actions, line_count, errors);
			line_count++;
		}
		if (line != "exit")
			errors[line_count] = "Missing exit !";
		in.close();
		if (!errors.empty())
		{
			for (std::pair<int, std::string> s : errors)
				std::cout << "error:" << s.first << "  " << s.second << "\n";
			return 0;
		}
		for (Action *a : actions)
		{
			a->execute(stack);
			delete a;
		}
		actions.clear();
	}
	else
		std::cout << "Invalid file !" << std::endl;
	return 0;
}
