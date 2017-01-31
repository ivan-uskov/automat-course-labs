#include "stdafx.h"
#include "../CompilerCore/Tokenizer.h"
#include "../CompilerCore/Parser.h"
#include <algorithm>

using namespace std;
using namespace Lexer;

int main(int argc, char * argv[])
{
    Tokenizer tokenizer(cin, cerr);
    tokenizer.scan();
    auto tokens = tokenizer.getTokens();

    auto & ast = Parser().parse(tokens);


    for (auto & astRoot : ast)
    {
        
    }

    return 0;
}
