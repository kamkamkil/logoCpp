#pragma once
#include <array>
#include <memory>
#include <utility>
#include <optional>
#include <string_view>
#include "token.hpp"
struct Leaf
{
    std::array<std::shared_ptr<Leaf>, 128> letterTable;
    std::optional<Token_t> token;
};

class WordTree
{
public:
    WordTree() : root(new Leaf){};
    ~WordTree() = default;
    int addToken(Token_t token, std::string_view word);
    std::pair<Token_t,int> getToken(std::string_view word, int pos,  int end);

private:
    std::shared_ptr<Leaf> root;
    std::pair<Token_t,int>  getNumber(std::string_view word, int pos,  int end);
};