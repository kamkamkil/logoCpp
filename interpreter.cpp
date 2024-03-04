#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <array>
#include <stack>
#include <variant>
#include "renderer.cpp"

typedef std::array<char, 50> Buffer_t;
enum command
{
    fd,
    bk,
    bc,
    rt,
    lt
};
typedef std::variant<command, int> Token_t;

// todo move file handling to another class, handle text reading as generic stream
class Interpreter
{
private:
    /* data */
public:
    Interpreter(std::string filePath_) : filePath(filePath_) { openFile(); };
    ~Interpreter();
    void interpret();

private:
    std::string filePath;
    void openFile();
    std::optional<std::fstream> fileStream;
    static std::pair<int, int> getWordPos(Buffer_t b, int bufferSize, int startPos = 0);
    Token_t tokenize(std::string word);
};

Interpreter::~Interpreter()
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

void Interpreter::openFile()
{
    std::fstream file;
    file.open(filePath, std::ios::in);
    if (!file)
    {
        std::cout << "file not exist or can't be open" << std::endl; // todo make error handling better
    }
    fileStream = std::move(file);
}

std::pair<int, int> Interpreter::getWordPos(Buffer_t buffer, int bufferSize, int startPos)
{
    if (startPos >= bufferSize)
    {
        return {-1, -1}; // todo better error handling
    }
    bool foundSpace;
    int pos = startPos;
    for (; pos < bufferSize; pos++)
    {
        if (buffer[pos] != ' ')
        {
            break;
        }
        startPos++;
    }
    for (; pos < bufferSize; pos++)
    {
        if (buffer[pos] == ' ')
        {
            break;
        }
    }
    return {startPos, pos};
}
// todo use more efficient way of determining if word is string
Token_t Interpreter::tokenize(std::string word)
{
    try
    {
        return std::stoi(word);
    }
    catch (const std::exception &e)
    {
        if (word == "fd")
            return command::fd;
        else if (word == "bk")
            return command::bk;
        else if (word == "bk")
            return command::bk;
        else if (word == "bc")
            return command::bc;
        else if (word == "rt")
            return command::rt;
        else if (word == "lt")
            return command::lt;
    }

    return Token_t();
}

void Interpreter::interpret()
{
    Buffer_t buffer;
    // add error handling
    std::stack<Token_t> stack;
    command c;
    bool after = false;
    while (fileStream.value().getline(&buffer[0], buffer.size()))
    {
        int pos = 0;
        while (true)
        {
            // todo extract this to func
            auto [wordStart, wordEnd] = getWordPos(buffer, fileStream.value().gcount(), pos);
            if (wordEnd == -1)
            {
                break;
            }
            std::cout << "<" << std::string(buffer.data() + wordStart, buffer.data() + wordEnd) << ">" << std::endl;
            pos = wordEnd + 1;
            //==
            auto word = std::string(buffer.data() + wordStart, buffer.data() + wordEnd);
            try
            {
                int number = std::stoi(word);
                auto renderer = Renderer::get();
                switch (c)
                {
                    case command::fd:
                        renderer->goUp(number);
                        break;
                    case command::bk:
                        renderer->goDown(number);
                        break;
                    case command::lt:
                        renderer->goLeft(number);
                        
                        Renderer::get()->main(0,nullptr);
                        break;
                    case command::rt:
                        renderer->goRight(number);
                        break;
                }
            }
            catch (const std::exception &e)
            {
                if (word == "fd")
                    c = command::fd;
                else if (word == "bk")
                    c = command::bk;
                else if (word == "bk")
                    c = command::bk;
                else if (word == "bc")
                    c = command::bc;
                else if (word == "rt")
                    c = command::rt;
                else if (word == "lt")
                    c = command::lt;
            }
        }
    }
}
