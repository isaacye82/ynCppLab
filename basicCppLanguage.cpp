#include "basicCppLanguage.h"
#include <memory>
#include <iostream>
#include <vector>
using namespace std;

struct destination
{
	int position;
};

struct connection
{
	bool isConnected;
	connection(destination* d) { 
		isConnected = true;
		std::cout << "Connected..." << std::endl;
	}
};

void disconnect(connection* c)
{
	c->isConnected = false;
	std::cout << "Disconnect." << std::endl;
}

void deleter(connection* c)
{
	disconnect(c);
}

void foo(destination& des)
{
	connection cnet(&des);
	shared_ptr<connection> p(&cnet, deleter); //cnet����new�����ģ�������Ҫ�Զ���ɾ����
	                                          //������shared_ptrĬ�ϵ��õ�delete
}

void revim::Test_DynamicMemorryAllocation()
{
//	shared_ptr<int> p1 = new int(1024); // error: class��std::shared_ptr<int>���Ĺ��캯������Ϊ��explicit��
//	shared_ptr<int> p1(new int(1024));

	destination des;
	foo(des);
}

//C++ primer 5e, practice 6.54-6.56
void revim::Test_fncPointer()
{
	using F = int(int, int);
	std::vector<F*> vFuncPointers;

	vFuncPointers.push_back(revim::add);
	vFuncPointers.push_back(revim::minus);
	vFuncPointers.push_back(revim::multiple);
	vFuncPointers.push_back(revim::divided);

	std::cout << "�ӷ���" << vFuncPointers[0](30, 10) << std::endl;
	std::cout << "������" << vFuncPointers[1](30, 10) << std::endl;
	std::cout << "�˷���" << vFuncPointers[2](30, 10) << std::endl;
	std::cout << "������" << vFuncPointers[3](30, 0) << std::endl;
}

int revim::add(int a, int b)
{
	return a + b;
}
int revim::minus(int a, int b)
{
	return a - b;
}
int revim::multiple(int a, int b)
{
	return a * b;
}

int revim::divided(int a, int b)
{
	if (b>1.0e-15 || b<-1.0e-15) {
		return a / b;
	}
	else {
		std::cerr << "����Ϊ0"<<std::endl;
		return 0;
	}
	
}