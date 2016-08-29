#include "LoadCSV.h"
#include <iostream>
#include <fstream>


string LoadCSV(const char* filepath, string variableName);
string getDataFromCSV(const char* filepath, string variableName)
{
	std::ifstream is(filepath);
	std::string tempString;
	std::string stringToReturn = "100";

	if (is.is_open())
	{
		while (is.good())
		{
			std::getline(is, tempString, ',');
			if (tempString == variableName)
			{
				tempString.clear();
				std::getline(is, tempString);
				stringToReturn = tempString;
				tempString.clear();
				break;
			}
			else
			{
				tempString.clear();
				std::getline(is, tempString);
				tempString.clear();
			}
		}
		is.close();
		return stringToReturn;
	}
	else
	{
		std::cout << "error, cannot open file" << std::endl;
		return "1";
	}
}