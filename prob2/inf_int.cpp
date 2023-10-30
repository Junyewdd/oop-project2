#pragma once
#include "inf_int.h"
#pragma warning (disable : 4996)

//constructor
inf_int::inf_int() {// assign 0 as a default value
	this->digits = new char[2]; //���� �Ҵ�

	this->digits[0] = '0';
	this->digits[1] = '\0';
	this->length = 1;
	this->thesign = true;
}

inf_int::inf_int(int n) {
	char buf[100];

	if (n < 0) { //���� ó��
		this->thesign = false;
		n = -n;
	}
	else {
		this->thesign = true;
	}
	int i = 0;
	while (n > 0) {
		buf[i] = n % 10 + '0';

		n /= 10;
		i++;
	}

	if (i == 0) { // ������ ������ 0�� ���
		new (this) inf_int(); //������ ��ȣ��
	}
	else {
		buf[i] = '\0';

		this->digits = new char[i + 1];
		this->length = i;
		strcpy(this->digits, buf);
	}
}

inf_int::inf_int(const char* str) {// you may modify this to "inf_int(const string);"
	// to be filled
	// ��ȣ ó��
	// "100"�� ���Դٸ� ���� ǥ���� �°� "001"�� ��ȯ
	// ex) "-1053" -> thesign=false, digits="3501", len=4
	int i = 0;
	int len_str = strlen(str);

	if (str[0] == '-') { // �������� Ȯ��
		this->thesign = false;
		i++;
	}
	else {
		this->thesign = true;
	}

	// �޸� �Ҵ�
	this->digits = new char[len_str - i + 1];

	// �������� ����
	for (int j = len_str - 1, k = 0; j >= i; --j, ++k) {
		this->digits[k] = str[j];
	}

	this->digits[len_str - i] = '\0';
	this->length = len_str - i;
}

inf_int::inf_int(const inf_int& a) {// copy constructor
	this->digits = new char[a.length + 1];

	strcpy(this->digits, a.digits);
	this->length = a.length;
	this->thesign = a.thesign;
}
inf_int::~inf_int() {// destructor
	delete digits;		// �޸� �Ҵ� ����
}

//operator
inf_int& inf_int::operator=(const inf_int& a) {
	if (this->digits) {
		delete this->digits;		// �̹� ���ڿ��� ���� ��� ����.
	}
	this->digits = new char[a.length + 1];

	strcpy(this->digits, a.digits);
	this->length = a.length;
	this->thesign = a.thesign;

	return *this;
}

bool operator==(const inf_int& a, const inf_int& b) {
	// we assume 0 is always positive.
	if ((strcmp(a.digits, b.digits) == 0) && a.thesign == b.thesign)	// ��ȣ�� ����, ������ ��ġ�ؾ���.
		return true;
	return false;
}
bool operator!=(const inf_int& a, const inf_int& b) {
	return !operator==(a, b);
}
bool operator>(const inf_int& a, const inf_int& b) {
	// to be filled
	// ���밪 ��
	// �� �� ����� ��� ���� ���� ���� �״�� return
	// �� �� ������ ��� ���� ���� ���� �����Ͽ� return
	// ��ȣ�� �ٸ� ���, a�� ����� ��� b�� ����, a�� ������ ��� b�� ����̱⿡ a�� ��ȣ�������� ��ȯ�ϸ� ��

	//��ȣ�� �ٸ� ���
	if (a.thesign != b.thesign) {
		if (a.thesign == true)return true;
		else return false;
	}

	//��ȣ�� ���� ���
	if (a.length != b.length) { //���� �ٸ� ��
		if (a.thesign == true) {//�� �� ����� ��
			if (a.length > b.length)return true;
			else return false;
		}
		else { //�� �� ������ ��
			if (a.length > b.length)return false;
			else return true;
		}
	}
	else { //���� ���� ��
		for (int i = a.length - 1; i >= 0; i--) {
			if (a.digits[i] != b.digits[i]) {
				return (a.digits[i] > b.digits[i]) == a.thesign;
			}
		}
	}
	return false;
}
bool operator<(const inf_int& a, const inf_int& b) {
	if (operator>(a, b) || operator==(a, b)) {
		return false;
	}
	else {
		return true;
	}
}

inf_int operator+(const inf_int& a, const inf_int& b) {
	inf_int c;
	unsigned int i;

	if (a.thesign == b.thesign) {	// ������ ��ȣ�� ���� ��� + �����ڷ� ����
		for (i = 0; i < a.length; i++) {
			c.Add(a.digits[i], i + 1);
		}
		for (i = 0; i < b.length; i++) {
			c.Add(b.digits[i], i + 1);
		}

		c.thesign = a.thesign;

		return c;
	}
	else {	// ������ ��ȣ�� �ٸ� ��� - �����ڷ� ����
		c = b;
		c.thesign = a.thesign;

		return a - c;
	}
}
inf_int operator-(const inf_int& a, const inf_int& b) {
	//to be filled
	inf_int c;
	unsigned int i;

	if (a > b) {
		c.thesign = true;
	}
	else if (a < b) {
		c.thesign = false;
	}
	else { // a == b -> a - b == 0
		c.thesign = true;
	}
	unsigned int max_length = (a.length > b.length) ? a.length : b.length;
	int borrow = 0;
	for (i = 0; i < max_length; i++) {
		int temp = 0;
		if (i < a.length)temp += a.digits[i] - '0';
		if (i < b.length)temp -= b.digits[i] - '0';

		temp -= borrow; //������ ���� �� ����
		if (temp < 0) {
			temp += 10;
			borrow = 1;
		}
		else {
			borrow = 0;
		}

		c.Add(temp + '0', i + 1);
	}

	return c;
}
inf_int operator*(const inf_int& a, const inf_int& b) {
	// Initialize result as zero.
	inf_int c("0");

	for (unsigned int i = 0; i < a.length; ++i) {
		int carry = 0;
		for (unsigned int j = 0; j < b.length || carry > 0; ++j) {
			int temp = carry;
			if (j < b.length) {
				temp += (a.digits[i] - '0') * (b.digits[j] - '0');
			}

			if (i + j < c.length) { // If the position exists in the result.
				temp += c.digits[i + j] - '0';
				c.digits[i + j] = temp % 10 + '0';
			}
			else { // If the position does not exist in the result.
				char* new_digits = new char[c.length + 2];
				std::copy(c.digits, c.digits + c.length, new_digits);
				new_digits[c.length] = temp % 10 + '0';
				new_digits[c.length + 1] = '\0';

				delete[] c.digits;

				c.digits = new_digits;
				++c.length;
			}

			carry = temp / 10;
		}
	}

	// Determine sign of the result.
	if ((a.thesign && b.thesign) || (!a.thesign && !b.thesign)) {
		c.thesign = true;
	}
	else {
		c.thesign = false;
	}

	return c;
}

// friend inf_int operator/(const inf_int& , const inf_int&); // not required

ostream& operator<<(ostream& out, const inf_int& a) {
	int i;

	if (a.thesign == false) {
		out << '-';
	}
	for (i = a.length - 1; i >= 0; i--) {
		out << a.digits[i];
	}
	return out;
}
// friend istream& operator>>(istream& , inf_int&);    // not required

void inf_int::Add(const char num, const unsigned int index)	// a�� index �ڸ����� n�� ���Ѵ�. 0<=n<=9, ex) a�� 391�϶�, Add(a, 2, 2)�� ����� 411
{
	if (this->length < index) {
		this->digits = (char*)realloc(this->digits, index + 1);

		if (this->digits == NULL) {		// �Ҵ� ���� ����ó��
			cout << "Memory reallocation failed, the program will terminate." << endl;

			exit(0);
		}

		this->length = index;					// ���� ����
		this->digits[this->length] = '\0';	// �ι��� ����
	}

	if (this->digits[index - 1] < '0') {	// ���� ���� '0'���� ���� �ƽ�Ű���� ��� 0���� ä��. �������� �ʾҴ� ���ο� �ڸ����� ��� �߻�
		this->digits[index - 1] = '0';
	}

	this->digits[index - 1] += num - '0';	// �� ����


	if (this->digits[index - 1] > '9') {	// �ڸ��ø��� �߻��� ���
		this->digits[index - 1] -= 10;	// ���� �ڸ������� (�ƽ�Ű��) 10�� ����
		Add('1', index + 1);			// ���ڸ��� 1�� ���Ѵ�
	}
}