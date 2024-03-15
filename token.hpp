#pragma once
#include <variant>
enum command
{
    fd,
    bk,
    bc,
    rt,
    lt
};

enum bad_token
{
    bad
};

typedef std::variant<command, int, float, bad_token> Token_t;
// typedef std::variant<command, int, float, err, proc> Token_t;
