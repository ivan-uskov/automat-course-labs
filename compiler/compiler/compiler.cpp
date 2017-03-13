#include "stdafx.h"

#include "Tokenizer.h"
#include "Parser.h"
#include "Evaluator.h"

using namespace std;
using namespace Lexer;

int main()
{
	Tokenizer tokenizer(cin, cerr);
	tokenizer.scan();
	auto tokens = tokenizer.getTokens();

	auto parser = Parser();
	parser.parse(tokens);
	auto const& ast = parser.getAST();

	auto evaluator = Evaluator();

	for (auto const& astRoot : ast)
	{
		std::cout << evaluator.eval(*astRoot) << endl;
	}

    return 0;
}

