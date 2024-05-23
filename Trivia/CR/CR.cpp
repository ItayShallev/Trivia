#include <iostream>
class A
{
public:
	int x;
};
A* foo()
{
	A a;
	return &a;
}
int main()
{
	int* a = new int;
	return 0;
}