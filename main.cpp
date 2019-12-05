#include"AllStruct.h"
#include"scaner.h"
#include<iostream>
int main()
{
	system("chcp 1251");
	Scaner A;
	string str = "afaf";
	/*Table <Token> A;
	string str = "HALLOW? BITch";
	Token B(str, 1);
	A += B;
	cout<<A[0].get_name()<<endl;
	cout << A[0].get_type()<<endl;
	system("pause");*/
	while (!str.empty())
	{
		str = A.get_lex();
		cout<<str<<endl;
	}
	//A.get_lex();
	system("pause");
	return 0;
}