#include"All_headers.h"
#include"scaner.h"

int main()
{
	system("chcp 1251");
	//Scaner A;

	//
	//A.to_scan();
	//A.print_stream_of_lex();
	//A.print_another_table();
	Parser a;
	a.finde_syntaxTree();
	//system("pause");

	return 0;
}