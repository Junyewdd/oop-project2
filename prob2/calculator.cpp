#include "inf_int.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	while (1) {
		string input;
		cout << "Input: ";
		getline(cin, input);
		if (input == "0")break;

		//������ �������� split�ؼ� ����
		stringstream ss(input);


		string inputA, inputB, oper;
		ss >> inputA >> oper >> inputB;

		inf_int a(inputA.c_str()); //c_str�� string�� const char*�� ��ȯ
		inf_int b(inputB.c_str());

		//����
		inf_int result;
		if (oper == "+") {
			result = a + b;
		}
		else if (oper == "-") {
			result = a - b;
		}
		else if (oper == "*") {
			result = a * b;
		}
		cout << "Output: " << result << "\n";
	}



	return 0;
}