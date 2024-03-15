#include <queue>
#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <array>
#include <stack>
#include <variant>
#include "token.hpp"
#include "wordTree.hpp"
typedef std::array<char, 50> Buffer_t; //todo move to cpp

typedef std::variant<command, int> Token_t2; // todo remove move etc

// todo move file handling to another class, handle text reading as generic stream
class Interpreter
{
public:
    Interpreter(std::string filePath_) : filePath(filePath_)
    {
        openFile();
        fillWordTree();
    };
    ~Interpreter();
    void interpret();

private:
    void openFile();
    std::optional<std::fstream> fileStream;
    static std::pair<int, int> getWordPos(Buffer_t b, int bufferSize, int startPos = 0);
    void fillWordTree();
    void sendToRenderer(std::queue<Token_t> &queue);
    //todo to be removed
    Token_t2 tokenize(std::string word);
    int getSpacesAmount(Buffer_t &buffer, int startPos, int endPos);


private:
    std::string filePath;
    WordTree wordTree;
};
