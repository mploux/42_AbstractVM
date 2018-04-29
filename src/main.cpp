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

void parseLine(const std::string &raw_line, std::vector<Action *> &actions, Factory *factory)
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

	std::regex validCommands("^(add|sub|div|mul|dump|pop|exit)$");
	std::regex validParamCommands("^(push|assert) (int8|int16|int32|float|double)\\((.+)\\)$");
	std::smatch command;

	if (std::regex_match(line, command, validCommands))
	{
		std::string cmd = command.str();
		actions.push_back(new Action(cmd, factory));
	}
	else if (std::regex_match(line, command, validParamCommands))
	{
		std::string cmd = command[1].str();
		std::string type = command[2].str();
		std::string value = command[3].str();
		actions.push_back(new Action(cmd, type, value, factory));
	}
	else
		Error::getInstance().error("Invalid syntax !", raw_line);
}

int main(int ac, char **av)
{
	std::deque<const IOperand *> stack;
	std::vector<Action *> actions;
	Factory	factory;
	std::ifstream fin;
	std::istream in(std::cin.rdbuf());

	Error::getInstance().setLine(0);

	if (ac == 2)
	{
		fin.open(av[1]);
		if (fin.is_open())
			in.rdbuf(fin.rdbuf());
		else
			std::cout << "Invalid file, continuing in command line mode...\n"; 
	}

	std::string line;
	int line_count = 1;
	while (std::getline(in, line))
	{
		if ((fin.is_open() && line == "exit") || (!fin.is_open() && line == ";;"))
			break;
		parseLine(line, actions, &factory);
		Error::getInstance().setLine(++line_count);
	}
	if (fin.is_open())
		fin.close();
	Error::getInstance().setLine(++line_count);
	if (fin.is_open() && line != "exit")
		Error::getInstance().error("exit is missing !");
	if (Error::getInstance().hasErrors())
		Error::getInstance().show();
	else
	{
		for (Action *a : actions)
		{
			a->execute(stack);
			delete a;
		}
		actions.clear();
	}

	return 0;
}
