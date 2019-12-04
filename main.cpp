#include"AllStruct.h"

int main()
{
	Table <Token> A;
	string str = "HALLOW? BITch";
	Token B(str, 1);
	A += B;
	cout<<A[0].get_name()<<endl;
	cout << A[0].get_type()<<endl;
	system("pause");
	return 0;
}