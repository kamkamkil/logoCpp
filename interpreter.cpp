#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <array>
#include "renderer.cpp"
enum command
{
    fd,
    bk,
    bc,
    rt,
    lt
};

// todo move file handling to another class, handle text reading as generic stream
class interpreter
{
private:
    /* data */
public:
    interpreter(std::string filePath_) : filePath(filePath_) { openFile(); };
    ~interpreter();

private:
    std::string filePath;
    void openFile();
    void interpret();
    std::optional<std::fstream> fileStream;
};

interpreter::~interpreter()
{
    if (fileStream)
    {
        fileStream.value().close();
    }
    else
    {
        std::cout << "failed to close file" << std::endl; // todo make error handling better
    }
}

void interpreter::openFile()
{
    std::fstream file;
    file.open(filePath, std::ios::in);
    if (!file)
    {
        std::cout << "file not exist or can't be open" << std::endl; // todo make error handling better
    }
    fileStream = std::move(file);
}

void interpreter::interpret()
{
    std::array<char, 4> a;
    //add error handling
    // while(fileStream.value().getline(&line,50))
}
