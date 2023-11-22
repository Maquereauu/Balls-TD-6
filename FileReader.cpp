#include "fileReader.h"
#include "GameManager.h"


FileReader::FileReader() {};


void FileReader::readFile(std::string path) {
    bool isList;
    std::fstream newfile;
    newfile.open(path, std::ios::in);
    int counter = 0;
    if (newfile.is_open()) {
        std::string tp;
        _sizeHeight.push_back(0);
        GameManager::Get()->_modelStats.resize(GameManager::Get()->_modelStats.size() + 1);
        while (getline(newfile, tp)) {
            if (isOnlyCommas(tp)) {
                _sizeHeight.push_back(0);
                GameManager::Get()->_modelStats.resize(GameManager::Get()->_modelStats.size() + 1);
                //counter++;
            }
            else {
                counter = 0;
                isList = false;
                std::stringstream ss(tp);
                std::string value;
                _sizeHeight.back()++; // Increment the size for the current row

                // Resize GameManager::Get()->_modelStats before accessing its elements
                GameManager::Get()->_modelStats.back().resize(_sizeHeight.back());
                size_t pos = tp.find(',');
                if (pos != std::string::npos && pos + 1 < tp.length() && tp[pos + 1] == '"') {
                    isList = true;
                    std::cout << "Double quote found after the first comma in line " << counter << std::endl;
                }

                while (getline(ss, value, ',')) {
                    try {
                        // Convert the string value to a double and add to GameManager::Get()->_modelStats
                        if (isList) {
                            GameManager::Get()->_modelStats.back()[_sizeHeight.back() - 1].resize(GameManager::Get()->_modelStats.back()[_sizeHeight.back() - 1].size() + 1);
                            /*GameManager::Get()->_modelStats.back()[_sizeHeight.back() - 1][GameManager::Get()->_modelStats.back()[_sizeHeight.back() - 1].size() - 1].resize(GameManager::Get()->_modelStats.back()[_sizeHeight.back() - 1].size() + 1); */
                            GameManager::Get()->_modelStats.back()[_sizeHeight.back() - 1][counter / 5].push_back(std::stod(value));
                        }
                        else {
                            GameManager::Get()->_modelStats.back()[_sizeHeight.back() - 1].resize(GameManager::Get()->_modelStats.back()[_sizeHeight.back() - 1].size() + 1);
                            //GameManager::Get()->_modelStats.back()[_sizeHeight.back() - 1][GameManager::Get()->_modelStats.back()[_sizeHeight.back() - 1].size() - 1].push_back(std::stod(value));
                            GameManager::Get()->_modelStats.back()[_sizeHeight.back() - 1][counter % 3].push_back(std::stod(value));
                        }
                        counter++;
                    }
                    catch (const std::invalid_argument& e) {
                        std::cerr << "Error converting string to double: " << e.what() << std::endl;
                        // Handle the error (e.g., set a default value or skip the entry)
                    }
                }
            }
        }

        newfile.close();
        //for (size_t i = 0; i < GameManager::Get()->_modelStats.size(); ++i) {
        //    for (size_t j = 0; j < GameManager::Get()->_modelStats[i].size(); ++j) {
        //        for (size_t k = 0; k < GameManager::Get()->_modelStats[i][j].size(); ++k) {
        //            for (size_t l = 0; l < GameManager::Get()->_modelStats[i][j][k].size(); ++l) {
        //                std::cout << "GameManager::Get()->_modelStats[" << i << "][" << j << "][" << k << "][" << l << "] = "
        //                    << GameManager::Get()->_modelStats[i][j][k][l] << std::endl;
        //            }
        //        }
        //    }
        //}
    }
    else {
        std::cerr << "Error opening file: " << path << std::endl;
    }
}

std::vector<std::vector<std::vector<std::vector<double>>>> FileReader::getFile() {
    return GameManager::Get()->_modelStats;
}

bool FileReader::isOnlyCommas(const std::string& line) {
    // Check if all characters in the line are commas
    return line.find_first_not_of(',') == std::string::npos;
}