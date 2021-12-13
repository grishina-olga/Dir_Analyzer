#include <string>
#include <iostream>
#include <dirent.h>
#include <vector>


class DirAnalyzer {
public:
    void compare(std::string firstPath, std::string secondPath);
    static std::vector<std::string> getDirFiles(std::string path);
};


int main()
{
    DirAnalyzer* dirAnalyzer = new DirAnalyzer();
    std::cout<<"Search for identical files in two directories."<<std::endl;

    std::cout<<"Input the first dir: ";
    std::string firstDir;
    std::cin>>firstDir;

    std::cout<<"Input the second dir: ";
    std::string secondDir;
    std::cin>>secondDir;

    dirAnalyzer->compare(firstDir, secondDir);
    return 0;
}

std::vector<std::string> DirAnalyzer::getDirFiles(std::string path) {
    std::vector<std::string> dirFiles = {};
    DIR* dir = opendir(path.c_str());
    if (!dir) {
        closedir(dir);
        return dirFiles;
    }

    struct dirent* firstEntry;
    while ((firstEntry = readdir(dir)) != NULL) {
        dirFiles.push_back(path +  "/" + firstEntry->d_name);
    }
    closedir(dir);
    dir = nullptr;
    return dirFiles;
}

void DirAnalyzer::compare(std::string firstPath, std::string secondPath) {
    std::vector<std::string> firstDirFiles = getDirFiles(firstPath);
    std::vector<std::string> secondDirFiles = getDirFiles(secondPath);

    std::vector<std::string> dublicatedFiles;
    FILE* ptrFile1;
    FILE* ptrFile2;
    for (auto firstFile : firstDirFiles) {
        for (auto secondFile : secondDirFiles) {
            ptrFile1 = fopen(firstFile.c_str(), "r");
            ptrFile2 = fopen(secondFile.c_str(), "r");
            unsigned long pos;
            int c1, c2;
            for (pos = 0;; pos++) {
                c1 = getc(ptrFile1);
                c2 = getc(ptrFile2);
                if (c1 != c2 || c1 == EOF)
                    break;
            }
            if (c1 == c2) {
                dublicatedFiles.push_back(firstFile);
                dublicatedFiles.push_back(secondFile);
            }
            fclose(ptrFile1);
            fclose(ptrFile2);
        }
    }
    ptrFile1 = nullptr;
    ptrFile2 = nullptr;

    std::cout<<"Identical files: "<<std::endl;
    for (auto file : dublicatedFiles) {
        std::cout<<file<<std::endl;
    }
}