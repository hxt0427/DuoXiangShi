// 多项式四则运算---链表.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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
		header = new Monomial();
		header->next = NULL;
		header->prior = NULL;

	}
	void Insert(double c, int e)
	{
		if (c == 0)
			return;
		Monomial * p = header->next;
		if (!p || e > p->exp)					//	链表为空  或 添加的指数>第一个节点指数
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
				if (p->coef == 0)
				{
					length--;
					p->prior->next = p->next;
					if (p->next)
					{
						p->next->prior = p->prior;
					}

				}
				return;
			}
			p = p->next;
		}
		p = header;
		while (p->next)
		{
			p = p->next;
			if (p->next == NULL || (p->exp > e && e > p->next->exp))
				break;
		}
		length++;
		Monomial * q = new Monomial();
		q->coef = c;
		q->exp = e;
		q->next = p->next;
		q->prior = p;
		p->next = q;
		if (p->next)
			p->next->prior = q;
		return;
	}
	void DeleteExp(int e)		//	删除指数为e的节点
	{
		Monomial* p = header->next;
		while (p)
		{
			if (p->exp == e)
			{
				p->prior->next = p->next;
				if (p->next)
					p->next->prior = p->prior;
				delete p;
				length--;
				return;
			}
			p = p->next;
		}
	}
	void DeleteCoef(double c)		//	删除第一个系数为c的节点
	{
		Monomial* p = header->next;
		while (p)
		{
			if (p->coef == c)
			{
				p->prior->next = p->next;
				if (p->next)
					p->next->prior = p->prior;
				delete p;
				length--;
				return;
			}
			p = p->next;
		}
	}
	void Append(double c, int e)		//修改指数为e的系数为 c
	{
		Monomial* p = header->next;
		while (p)
		{
			if (p->exp == e)
			{
				p->coef = c;
				return;
			}
			p = p->next;
		}
		Insert(c, e);
	}
	Monomial* FindExp(int e)
	{
		Monomial* p = header->next;
		while (p)
		{
			if (p->exp == e)
			{
				return p;
			}
			p = p->next;
		}
	}
	Monomial* FindCoef(double c)
	{
		Monomial* p = header->next;
		while (p)
		{
			if (p->coef == c)
			{
				return p;
			}
			p = p->next;
		}
	}
	int FindCoef1(double c)
	{
		Monomial* p = header->next;
		while (p)
		{
			if (p->coef == c)
			{
				return p->exp;
			}
			p = p->next;
		}
	}
	double FindExp1(int e)
	{
		Monomial* p = header->next;
		while (p)
		{
			if (p->exp == e)
			{
				return p->coef;
			}
			p = p->next;
		}
	}
	void Output()
	{
		Monomial* p = header->next;
		if (!p)
			cout << "空";
		while (p)
		{
			if (p->coef > 0 && p->prior != header)
				cout << " +";
			if(p->coef != 0)
				cout << p->coef << "X^(" << p->exp << ")";
			p = p->next;
		}
		cout << endl;
	}
	void Clear()
	{
		Monomial*p;
		while (header->next)
		{
			p = header->next;
			header->next = p->next;
			delete p;
		}
	}
	void Copy(Polynomial polynomial)
	{
		Clear();
		Monomial *p = polynomial.header->next;
		while (p)
		{
			Insert(p->coef, p->exp);
			p = p->next;
		}
	}
	void AddPolynomial(Polynomial polynomial1, Polynomial polynomial2)
	{
		Clear();
		Monomial *p;
		p = polynomial1.header->next;
		while (p)
		{
			Insert(p->coef, p->exp);
			p = p->next;
		}
		p = polynomial2.header->next;
		while (p)
		{
			Insert(p->coef, p->exp);
			p = p->next;
		}
	}
	void SubPolynomial(Polynomial polynomial1, Polynomial polynomial2)
	{
		Clear();
		Monomial *p;
		p = polynomial1.header->next;
		while (p)
		{
			Insert(p->coef, p->exp);
			p = p->next;
		}
		p = polynomial2.header->next;
		while (p)
		{
			Insert(-p->coef, p->exp);
			p = p->next;
		}
	}
	void MulPolynomial(Polynomial polynomial1, Polynomial polynomial2)
	{
		Clear();
		Monomial *p,*q;
		p = polynomial1.header->next;
		while (p)
		{
			q = polynomial2.header->next;
			while (q)
			{
				Insert(p->coef * q->coef , p->exp + q->exp);
				q = q->next;
			}
			p = p->next;
		}
	}
	void DivQuoPolynomial(Polynomial polynomial1, Polynomial polynomial2)		//商
	{				//当前存放当前商   polynomial存放当前余数   polynomial3存放部分积
		Clear();
		Polynomial polynomial = Polynomial();
		Polynomial polynomial3 = Polynomial();
		Polynomial polynomial4 = Polynomial();
		polynomial.Copy(polynomial1);				//polynomial1 -->polynomial
		Monomial *p, *q,*s;
		p = polynomial2.header->next;
		q = polynomial.header->next;

		while ( q && q->exp >= p->exp ) //被除数最高次比除数的最高次高
		{
			Insert(q->coef / p->coef, q->exp - p->exp);
			polynomial3.Clear();
			s = p;
			while (s)
			{
				polynomial3.Insert(s->coef * (q->coef / p->coef), s->exp + (q->exp - p->exp));//polynomial3 = polynomial2 * 部分商
				s = s->next;
			}
			polynomial4.Clear();
			polynomial4.SubPolynomial(polynomial, polynomial3);
			polynomial.Copy(polynomial4);
			q = polynomial.header->next;
		}
	}
	void DivRemPolynomial(Polynomial polynomial1, Polynomial polynomial2)		//余数
	{				
		Clear();
		Polynomial polynomial3 = Polynomial();			//polynomial3 = polynomial1/polynomial2
		Polynomial polynomial4 = Polynomial();			//polynomial4 = (polynomial1/polynomial2)   *polynomial2
	
		polynomial3.DivQuoPolynomial(polynomial1, polynomial2);
		polynomial4.MulPolynomial(polynomial3, polynomial2);
		SubPolynomial(polynomial1, polynomial4);
	}
};

int main()
{
	Polynomial polynomial1 = Polynomial();		//多项式1
	Polynomial polynomial2 = Polynomial();		//多项式2
	Polynomial polynomial3 = Polynomial();		//多项式3		多项式1与多项式1运算的结果
	Polynomial polynomial4 = Polynomial();
	Polynomial polynomial5 = Polynomial();
	polynomial1.Insert(6, 6);
	polynomial1.Insert(10, 4);
	polynomial1.Insert(3, 2);
	polynomial1.Insert(2,3);
	polynomial1.Insert(5, 1);
	polynomial1.Insert(1,0);
	cout << "polynomial1 ：" << endl;
	polynomial1.Output();
	polynomial2.Insert(1,0);
	polynomial2.Insert(2, 3);
	cout << "polynomial2 ：" << endl;
	polynomial2.Output();
	cout << endl << "polynomial1 + polynomial2 ：" << endl;
	polynomial3.AddPolynomial(polynomial1, polynomial2);
	polynomial3.Output();
	cout << endl << "polynomial1 - polynomial2 ：" << endl;
	polynomial3.SubPolynomial(polynomial1, polynomial2);
	polynomial3.Output();
	cout << endl << "polynomial1 * polynomial2 ：" << endl;
	polynomial3.MulPolynomial(polynomial1, polynomial2);
	polynomial3.Output();
	cout << endl << "polynomial1 / polynomial2 ：" << endl;
	polynomial3.DivQuoPolynomial(polynomial1, polynomial2);
	polynomial3.Output();
	cout << endl << "polynomial1 % polynomial2 ：" << endl;
	polynomial4.DivRemPolynomial(polynomial1, polynomial2);
	polynomial4.Output();
	cout << endl << "商*除数 ：" << endl;
	polynomial5.MulPolynomial(polynomial3, polynomial2);
	polynomial5.Output();
	cout << endl << "商*除数 + 余数 ：" << endl;
	polynomial3.AddPolynomial(polynomial4, polynomial5);
	polynomial3.Output();
	cout <<endl<<endl<< "polynomial1 ：" << endl;
	polynomial1.Output();
	polynomial1.Append(4, 4);			//修改系数
	cout << "修改指数为4的系数为4：" << endl;
	polynomial1.Output();   
	polynomial1.Append(4, 36);			//修改系数   当前指数不在链表
	cout << "修改指数为36(原链表中无）的系数为4：" << endl;
	polynomial1.Output();
	polynomial1.DeleteCoef(4);			//根据系数删除第一个节点
	cout << "删除指数为系数为4的第一个节点：" << endl;
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
