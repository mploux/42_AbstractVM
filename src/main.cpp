//
// Created by Marc-andre PLOUX on 4/24/18.
//

#include <iostream>
#include <deque>
#include <fstream>
#include <regex>
#include <map>
#include <vector>

#include "exceptions/AvmException.hpp"
#include "exceptions/AvmSeverException.hpp"
#include "Action.hpp"

static bool parseLine(const std::string &raw_line, std::vector<Action *> &actions, Factory *factory)
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
		return true;

	std::regex validLine("^[A-Za-z0-9\\(\\)\\-\\.\\ \t]*$");
	if (!std::regex_match(line, validLine))
		return false;

	std::regex validCommands("^([a-z]+)$");
	std::regex validParamCommands("^([a-z]+) ([a-z0-9]+)\\((.+)\\)$");
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
		throw AvmException("Invalid syntax !", raw_line);
	return true;
}

static void readStream(std::istream &in, std::ifstream &fin, std::vector<Action *> &actions, Factory &factory)
{
	std::string line;
	int line_count = 1;

	bool hasExit = false;
	while (std::getline(in, line))
	{
		try
		{
			if (line_count + 1 >= std::numeric_limits<int>::max() - 1)
				throw AvmSeverException("The file is to big !");
			if (line == "exit")
				hasExit = true;
			if ((fin.is_open() && line == "exit") || (!fin.is_open() && line == ";;"))
				break;
			if (!parseLine(line, actions, &factory))
				throw AvmSeverException("Invalid input file !");
		}
		catch (AvmSeverException &e)
		{ Error::getInstance().sever(e.getMessage()); }
		catch (AvmException &e)
		{ Error::getInstance().error(e.getMessage(), e.getLine()); }
		catch (std::exception &e)
		{ Error::getInstance().sever("Unknown exception: " + std::string(e.what())); }

		Error::getInstance().setLine(++line_count);
	}
	if (fin.is_open())
		fin.close();
	Error::getInstance().setLine(++line_count);
	try
	{
		if (!hasExit)
			throw AvmException("exit is missing !");
	}
	catch (AvmSeverException &e)
	{ Error::getInstance().sever(e.getMessage()); }
	catch (AvmException &e)
	{ Error::getInstance().error(e.getMessage(), e.getLine()); }
	catch (std::exception &e)
	{ Error::getInstance().sever("Unknown exception: " + std::string(e.what())); }
}

int main(int ac, char **av)
{
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

	readStream(in, fin, actions, factory);

	if (Error::getInstance().hasErrors())
		Error::getInstance().show();
	
	bool running = true;
	for (Action *a : actions)
	{
		if (!Error::getInstance().hasErrors() && running)
		{
			if (a->getAction() == "exit")
				running = false;
			a->execute();
		}
		delete a;
	}
	actions.clear();
	Stack::getInstance().clean();

	return EXIT_SUCCESS;
}
