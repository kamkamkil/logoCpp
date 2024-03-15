#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <array>
#include <stack>
#include <variant>
#include "renderer.cpp"
#include "interpreter.hpp"
#include "wordTree.hpp"
#include "token.hpp"
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

std::pair<int, int> Interpreter::getWordPos(Buffer_t buffer, int bufferSize, int startPos) // todo to remove
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
Token_t2 Interpreter::tokenize(std::string word)
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

    return Token_t2();
}

int Interpreter::getSpacesAmount(Buffer_t &buffer, int startPos, int endPos) // todo add proper tab recognicion now only works with spaces
{
    for (int pos = startPos; pos < endPos; pos++)
    {
        if (buffer[pos] != ' ')
        {
            return pos;
        }
    }
    return endPos;
}

void Interpreter::fillWordTree()
{
    wordTree.addToken(command::bc, "bc");
    wordTree.addToken(command::bk, "bk");
    wordTree.addToken(command::fd, "fd");
    wordTree.addToken(command::lt, "lt");
    wordTree.addToken(command::rt, "tr");
}

void Interpreter::sendToRenderer(std::queue<Token_t> &queue)
{
    auto renderer = Renderer::get();
    while (!queue.empty())
    {
        Token_t token = queue.front();
        queue.pop();
        switch (token.index())
        {
        case 0: // modify this case so it works with multi params proc and float
            if (!queue.empty() and queue.front().index() == 1)
            {
                int val = std::get<int>(queue.front());
                queue.pop();
                switch (std::get<command>(token))
                {
                case command::bk:
                    renderer->goDown(val);
                    break;
                case command::fd:
                    renderer->goUp(val);
                    break;
                case command::lt:
                    renderer->goLeft(val);
                    break;
                case command::rt:
                    renderer->goRight(val);
                    break;

                default:
                    break;
                }
            }
            break;
        default:
            std::cout << "wrong token at wrong time" << std::endl;
            break;
        }
    }
}

void Interpreter::interpret()
{
    Buffer_t buffer;
    std::queue<Token_t> queue;
    bool after = false;
    while (fileStream.value().getline(&buffer[0], buffer.size()))
    {
        int lineSize = fileStream.value().gcount();
        auto tab = getSpacesAmount(buffer, 0, lineSize);
        // todo refactoring
        while (true)
        {
            auto [token, pos] = wordTree.getToken(std::string_view(buffer.data()), tab, lineSize);
            queue.push(token);
            if (pos == lineSize)
            {
                break;
            }
            tab = getSpacesAmount(buffer, pos, lineSize);
        }
    }
    sendToRenderer(queue);
}
