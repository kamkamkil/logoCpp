#include "interpreter.cpp"

int main(int argc, char const *argv[])
{
    Interpreter in("../../testFile.txt");
    in.interpret();
    return 0;
}
