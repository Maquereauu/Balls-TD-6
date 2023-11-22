#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class FileReader
{
private:
	std::vector<std::vector<std::vector<int>>> _modelStats;
	std::vector<int> _sizeHeight;
	int _sizeWidth;


public:
	FileReader();

	void readFile(std::string path);
	//bool compareFileRead(std::vector<std::vector<int>> startFile);
	std::vector<std::vector<int>> getFile();
	int getFileHeight();
	int getFileWidth();
	bool isOnlyCommas(const std::string& line);
};

