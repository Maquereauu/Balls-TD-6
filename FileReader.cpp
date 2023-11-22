#include "fileReader.h"


FileReader::FileReader() {};

void FileReader::readFile(std::string path)
{
    int i = 0;
    int j = 0;
    int c = 0;
    std::fstream newfile;
    std::string result = "";


    newfile.open(path, std::ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()) { //checking whether the file is open
        std::string tp;
        _sizeHeight.push_back(0);
        while (getline(newfile, tp)) { //read data from file object and put it into string.
            if (isOnlyCommas(tp))
            {
                c += 1;
                _sizeHeight.push_back(0);
            }
            else {
                result += tp; // incrémentation d'une string à partir du fichier txt
                _sizeHeight[c]++;
            }
        }
    }
    newfile.close(); //close the file object.
    _modelStats.resize(_sizeHeight.size());
    for (int k = 0; k < _sizeHeight.size(); k++)
    {
        _modelStats[k].resize(_sizeHeight[k]);
    }
    _tabFile.resize(_sizeHeight);

    /* incrémentation du tableau à parti des valeurs présentes dans le fichier txt */
    while (i < _sizeHeight)
    {
        if (result[j] == *" ")
        {
            _tabFile[i].push_back(-1);
        }
        else if (result[j] == 0)
        {
            _tabFile[i].push_back(0);
        }
        else if (result[j] == *"&")
        {
            i++;
        }
        else
        {
            _tabFile[i].push_back(result[j] - 48);
        }
        j++;
    }
}


//bool FileReader::compareFileRead(std::vector<std::vector<int>> startFile)
//{
//    /* Comparaison entre deux tableaux des valeurs enregistrer depuis un fichier txt */
//    for (int i = 0; i < _sizeHeight; i++)
//    {
//        for (int j = 0; j < _sizeWidth; j++)
//        {
//            if (_tabFile[i][j] != startFile[i][j])
//            {
//                return false;
//            }
//        }
//    }
//    return true;
//}

std::vector<std::vector<int>> FileReader::getFile()
{
    return _tabFile;
}

int FileReader::getFileHeight()
{
    return _sizeHeight;
}
int FileReader::getFileWidth()
{
    return _sizeWidth;
}

bool FileReader::isOnlyCommas(const std::string& line) {
    // Check if all characters in the line are commas
    return line.find_first_not_of(',') == std::string::npos;
}