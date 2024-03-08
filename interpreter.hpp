#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <array>
#include <stack>
#include <variant>

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
