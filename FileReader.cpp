#include "fileReader.h"


void FileReader::readFile(std::string path) {
    std::fstream newfile;
    newfile.open(path, std::ios::in);
    int counter = 0;
    if (newfile.is_open()) {
        std::string tp;
        _sizeHeight.push_back(0);
        _modelStats.resize(_modelStats.size() + 1);
        while (getline(newfile, tp)) {
            if (isOnlyCommas(tp)) {
                _sizeHeight.push_back(0);
                _modelStats.resize(_modelStats.size() + 1);
                counter++;
            }
            else {
                std::stringstream ss(tp);
                std::string value;
                _sizeHeight.back()++; // Increment the size for the current row

                // Resize _modelStats before accessing its elements
                _modelStats.back().resize(_sizeHeight.back());

                while (getline(ss, value, ',')) {
                    try {
                        // Convert the string value to a double and add to _modelStats
                        _modelStats.back()[_sizeHeight.back() - 1].push_back(std::stod(value)); // Correct the indexing
                    }
                    catch (const std::invalid_argument& e) {
                        std::cerr << "Error converting string to double: " << e.what() << std::endl;
                        // Handle the error (e.g., set a default value or skip the entry)
                    }
                }
            }
        }

        newfile.close();

        // Output the read values (for testing purposes)
        //for (size_t i = 0; i < _modelStats.size(); ++i) {
        //    for (size_t j = 0; j < _modelStats[i].size(); ++j) {
        //        for (size_t k = 0; k < _modelStats[i][j].size(); ++k) {
        //            std::cout << "_modelStats[" << i << "][" << j << "][" << k << "] = "
        //                << _modelStats[i][j][k] << std::endl;
        //        }
        //    }
        //}
    }
    else {
        std::cerr << "Error opening file: " << path << std::endl;
    }
}

std::vector<std::vector<std::vector<double>>> FileReader::getFile() {
    return _modelStats;
}

bool FileReader::isOnlyCommas(const std::string& line) {
    // Check if all characters in the line are commas
    return line.find_first_not_of(',') == std::string::npos;
}