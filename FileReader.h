#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>  // Include this for std::invalid_argument

class FileReader {
private:
    //std::vector<std::vector<std::vector<std::vector<double>>>> _modelStats;
    std::vector<int> _sizeHeight;

public:
    FileReader();
    void readFile(std::string path);
    std::vector<std::vector<std::vector<std::vector<double>>>> getFile();
    bool isOnlyCommas(const std::string& line);
};
