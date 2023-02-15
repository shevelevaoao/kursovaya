#include <string>
#include <iostream>
#include <queue>
#include <stack>
#include <Windows.h>//handle
#include <conio.h>//_getch

using namespace std;

char is_operation(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

string infix_to_postfix(string str)
{
	string res = "";
	stack<char> stck;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
		{
			stck.push(str[i]);
		}
		if (str[i] == ')')
		{
			while (!stck.empty() && stck.top() != '(')
			{
				res.push_back(stck.top());
				res.push_back(' ');
				stck.pop();
			}
			stck.pop();
		}
		if (str[i] == '^')
		{
			while (!stck.empty() && stck.top() == '^')
			{
				res.push_back(stck.top());
				res.push_back(' ');
				stck.pop();
			}
			stck.push(str[i]);
		}
		if (str[i] == '*' || str[i] == '/')
		{
			while (!stck.empty() && (stck.top() == '^' || stck.top() == '*' || stck.top() == '/'))
			{
				res.push_back(stck.top());
				res.push_back(' ');
				stck.pop();
			}
			stck.push(str[i]);
		}
		if (str[i] == '+' || str[i] == '-')
		{
			stck.push(str[i]);
		}
		if (isdigit(str[i]) || str[i] == ',')
		{
			while (isdigit(str[i]) || str[i] == ',')
			{
				res.push_back(str[i]);
				i++;
			}
			res.push_back(' ');
			i--;
		}
	}
	while (!stck.empty())
	{
		res.push_back(stck.top());
		res.push_back(' ');
		stck.pop();
	}
	return res;
}

string prefix_to_postfix(string str)
{
	stack<string> s;
	stack<char> digit;
	int length = str.length();
	string temp1;

	for (int i = length - 1; i >= 0; i--)
	{
		if (is_operation(str[i]))
		{
			string op1 = s.top();
			s.pop();
			string op2 = s.top();
			s.pop();

			string temp = op1 + ' ' + op2 + ' ' + str[i];

			s.push(temp);
		}

		else if (isdigit(str[i]) || str[i] == ',')
		{
			while (isdigit(str[i]) || str[i] == ',')
			{
				digit.push(str[i]);
				i--;
			}
			while (!digit.empty())
			{
				temp1 += digit.top();
				digit.pop();
			}
			i++;
			s.push(temp1);
			temp1 = "";
		}
	}
	return s.top();
}

string postfix_to_postfix(string str)
{
	return str;
}

float calculation(float op1, float op2, char oper)
{
	switch (oper)
	{
	case '*':
		return op1 * op2;
	case '/':
		return op1 / op2;
	case '+':
		return op1 + op2;
	case '-':
		return op1 - op2;
	case '^':
		return pow(op1, op2);
	}
}

void count_post(string str)
{
	stack<float> stck;
	string temp;
	for (int i = 0; i < str.length(); i++)
	{
		if (isdigit(str[i]) || str[i] == ',')
		{
			while (isdigit(str[i]) || str[i] == ',')
			{
				temp.push_back(str[i]);
				i++;
			}
			i--;
			stck.push(stof(temp));
		}
		if (is_operation(str[i]))
		{
			float op2 = stck.top();
			stck.pop();
			float op1 = stck.top();
			stck.pop();
			float res = calculation(op1, op2, str[i]);
			stck.push(res);
		}
		temp = "";
	}
	cout << "Result = " << stck.top() << endl;
}

int main()
{
	//post 10,5 3,2 / 7 * 7 6,3 7,8 - ^ /
	//inf (((10,5/3,2)*7)/(7^(6,3-7,8)))
	//pre  / * / 10,5 3,2 7 ^ 7 - 6,3 7,8
	setlocale(0, "");
	string str;

	HANDLE descriptor = GetStdHandle(STD_OUTPUT_HANDLE);
	short key = 0, code = 0;
	do
	{
		do
		{
			system("cls");
			key = (key + 3) % 3;
			code = 0;
			if (key == 0)
			{
				cout << "Выберите тип вводимой записи:\n";
				SetConsoleTextAttribute(descriptor, 2);
				cout << "Префиксная" << endl;
				SetConsoleTextAttribute(descriptor, 7);
				cout << "Инфиксная" << endl;
				cout << "Постфиксная" << endl;
			}
			if (key == 1)
			{
				cout << "Выберите тип вводимой записи:\n";
				cout << "Префиксная" << endl;
				SetConsoleTextAttribute(descriptor, 2);
				cout << "Инфиксная" << endl;
				SetConsoleTextAttribute(descriptor, 7);
				cout << "Постфиксная" << endl;
			}
			if (key == 2)
			{
				cout << "Выберите тип вводимой записи:\n";
				cout << "Префиксная" << endl;
				cout << "Инфиксная" << endl;
				SetConsoleTextAttribute(descriptor, 2);
				cout << "Постфиксная" << endl;
				SetConsoleTextAttribute(descriptor, 7);
			}
			if (code != 13)
			{
				code = _getch();
				if (code == 80 || code == 115)
					++key;
				if (code == 72 || code == 119)
					--key;
			}
		} while (code != 13);

		cout << "Введите запись: ";
		getline(cin, str);
		switch (key)
		{
		case 0:
			str = prefix_to_postfix(str);
			break;
		case 1:
			str = infix_to_postfix(str);
			break;
		case 2:
			str = postfix_to_postfix(str);
			break;
		default:
			cout << "ошибка, сюда не попасть, как вы это сделали?\n";
			break;
		}
		count_post(str);
		system("pause");
	} while (true);
}