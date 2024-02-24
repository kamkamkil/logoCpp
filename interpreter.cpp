#include <iostream>
#include <string>
#include <optional>
#include<fstream>

class interpreter
{
private:
    /* data */
public:
    interpreter(std::string filePath_) : filePath(filePath_) {};
    ~interpreter();

private:
    std::string filePath;
    void openFile();
    std::optional<std::fstream> fileStream;
};

interpreter::~interpreter()
{
}

void interpreter::openFile()
{
    std::fstream file;
    file.open(filePath, std::iso::in);

}
