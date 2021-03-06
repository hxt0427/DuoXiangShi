// 多项式--链表.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//



#include "pch.h"
#include<stdlib.h>
#include<iostream>
using namespace std;

struct Monomial
{
	double coef;
	int exp;
	Monomial * next;
	Monomial * prior;
};

struct Polynomial
{
	Monomial* header;
	int length = 0;
	Polynomial()
	{
		header->next = NULL;
		header->prior = NULL;

	}
	void Insert(double c, int e)
	{
		Monomial * p = header->next;
		if (!p)					//	链表为空  或 添加的指数>第一个节点指数
		{
			length++;
			Monomial * q = new Monomial();
			q->coef = c;
			q->exp = e;
			q->next = p;
			q->prior = header;
			header->next = q;
			if (p)
				p->prior = q;
			return;
		}
		while (p) {
			if (p->exp == e)
			{
				p->coef += c;
				return;
			}
			p = p->next;
		}
		p = header;
		while (p->next)
		{
			p = p->next;
			if (p->exp > e && e > p->next->coef)
				break;	
		}
		length++;
		Monomial * q = new Monomial();
		q->coef = c;
		q->exp = e;
		q->next = p->next;
		q->prior = p;
		p->next = q;
		if(p->next)
			p->next->prior = q;
		return;
	}
	void Output()
	{
		cout << "Polynomial: ";
		Monomial* p = header->next;
		while (p)
		{
			if (p->coef > 0 && p->prior != header)
				cout << " +";
			cout << p->coef << "X^(" << p->exp << ")";
			p = p->next;
		}
		cout << endl;
	}
};



int main()
{
	Polynomial polynomial1;
	polynomial1.Insert(32.4, 5);
//	polynomial1.Insert(3, 7);
//	polynomial1.Insert(5, 9);
//	polynomial1.Insert(2, 5);

	polynomial1.Output();

	return 0;

}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
