#include "stdafx.h"

#include "Tokenizer.h"
#include "Parser.h"
#include "CodeGenerator.h"

using namespace std;
using namespace Lexer;

int main()
{
	try
	{
		Tokenizer tokenizer(cin, cerr);
		tokenizer.scan();
		auto tokens = tokenizer.getTokens();

		auto parser = Parser();
		parser.parse(tokens);
		auto const& ast = parser.getAST();
		CodeGenerator cg;
		cg.generate(*ast[0]);
	}
	catch (exception const& e)
	{
		cout << e.what() << endl;
	}

    return 0;
}

