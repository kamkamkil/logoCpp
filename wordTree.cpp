#include <charconv>
#include <iostream>
#include "wordTree.hpp"
#include "token.hpp"

int WordTree::addToken(Token_t token, std::string_view word)
{
    auto leaf = root;
    for (auto &&letter : word)
    {
        if (leaf->letterTable[letter] == nullptr) // todo protect this against bad access
        {
            leaf->letterTable[letter] = std::make_unique<Leaf>();
        }
        leaf = leaf->letterTable[letter];
    }
    if (leaf->token)
    {
        return -1; // todo think how this should work
    }
    leaf->token = token;

    return 0;
}

std::pair<Token_t, int> WordTree::getToken(std::string_view word, int StartPos, int end)
{
    auto leaf = root;
    bool canBeNumber = true;
    int pos = StartPos;
    for (; pos < word.size(); pos++)
    {
        if (pos == end or word[pos] == ' ')
        {
            break;
        }
        if (word[pos] < '0' or word[pos] > '9')
        {
            canBeNumber = false;
        }
        if (leaf->letterTable[word[pos]] == nullptr) // todo protect this against bad access
        {
            if (canBeNumber)
            {
                return getNumber(word, StartPos, end);
            }

            return {bad_token::bad, pos}; //todo find a end of the
        }
        leaf = leaf->letterTable[word[pos]];
    }

    if (canBeNumber)
    {
        return getNumber(word, StartPos, end);
    }
    if (leaf->token)
    {
        return {leaf->token.value(), pos}; // todo think how this should work
    }
    return {bad_token::bad, pos};
}

std::pair<Token_t, int> WordTree::getNumber(std::string_view word, int pos, int end)
{
    int result;
    auto [ptr, ec] = std::from_chars(word.data() + pos,word.data() + end,result);
    int newEnd = ptr - word.data();
    if(ec != std::errc())
    {
        return {bad_token::bad, end};
    }
    //todo add option to recognize bad token starting with number
    return {result,newEnd};
}
