#pragma once
#include "inf_int.h"
#pragma warning (disable : 4996)

//constructor
inf_int::inf_int() {// assign 0 as a default value
	this->digits = new char[2]; //동적 할당

	this->digits[0] = '0';
	this->digits[1] = '\0';
	this->length = 1;
	this->thesign = true;
}

inf_int::inf_int(int n) {
	char buf[100];

	if (n < 0) { //음수 처리
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

	if (i == 0) { // 숫자의 절댓값이 0일 경우
		new (this) inf_int(); //생성자 재호출
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
	// 부호 처리
	// "100"이 들어왔다면 내부 표현에 맞게 "001"로 변환
	// ex) "-1053" -> thesign=false, digits="3501", len=4
	int i = 0;
	int len_str = strlen(str);

	if (str[0] == '-') { // 음수인지 확인
		this->thesign = false;
		i++;
	}
	else {
		this->thesign = true;
	}

	// 메모리 할당
	this->digits = new char[len_str - i + 1];

	// 역순으로 저장
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
	delete digits;		// 메모리 할당 해제
}

//operator
inf_int& inf_int::operator=(const inf_int& a) {
	if (this->digits) {
		delete this->digits;		// 이미 문자열이 있을 경우 제거.
	}
	this->digits = new char[a.length + 1];

	strcpy(this->digits, a.digits);
	this->length = a.length;
	this->thesign = a.thesign;

	return *this;
}

bool operator==(const inf_int& a, const inf_int& b) {
	// we assume 0 is always positive.
	if ((strcmp(a.digits, b.digits) == 0) && a.thesign == b.thesign)	// 부호가 같고, 절댓값이 일치해야함.
		return true;
	return false;
}
bool operator!=(const inf_int& a, const inf_int& b) {
	return !operator==(a, b);
}
bool operator>(const inf_int& a, const inf_int& b) {
	// to be filled
	// 절대값 비교
	// 둘 다 양수일 경우 절댓값 비교한 것을 그대로 return
	// 둘 다 음수일 경우 절댓값 비교의 것을 반전하여 return
	// 부호가 다를 경우, a가 양수일 경우 b는 음수, a가 음수일 경우 b는 양수이기에 a의 부호진리값을 반환하면 됨

	//부호가 다른 경우
	if (a.thesign != b.thesign) {
		if (a.thesign == true)return true;
		else return false;
	}

	//부호가 같은 경우
	if (a.length != b.length) { //길이 다를 때
		if (a.thesign == true) {//둘 다 양수일 때
			if (a.length > b.length)return true;
			else return false;
		}
		else { //둘 다 음수일 때
			if (a.length > b.length)return false;
			else return true;
		}
	}
	else { //길이 같을 때
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

	if (a.thesign == b.thesign) {	// 이항의 부호가 같을 경우 + 연산자로 연산
		for (i = 0; i < a.length; i++) {
			c.Add(a.digits[i], i + 1);
		}
		for (i = 0; i < b.length; i++) {
			c.Add(b.digits[i], i + 1);
		}

		c.thesign = a.thesign;

		return c;
	}
	else {	// 이항의 부호가 다를 경우 - 연산자로 연산
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

		temp -= borrow; //이전에 빌린 것 빼기
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

void inf_int::Add(const char num, const unsigned int index)	// a의 index 자리수에 n을 더한다. 0<=n<=9, ex) a가 391일때, Add(a, 2, 2)의 결과는 411
{
	if (this->length < index) {
		this->digits = (char*)realloc(this->digits, index + 1);

		if (this->digits == NULL) {		// 할당 실패 예외처리
			cout << "Memory reallocation failed, the program will terminate." << endl;

			exit(0);
		}

		this->length = index;					// 길이 지정
		this->digits[this->length] = '\0';	// 널문자 삽입
	}

	if (this->digits[index - 1] < '0') {	// 연산 전에 '0'보다 작은 아스키값인 경우 0으로 채움. 쓰여지지 않았던 새로운 자리수일 경우 발생
		this->digits[index - 1] = '0';
	}

	this->digits[index - 1] += num - '0';	// 값 연산


	if (this->digits[index - 1] > '9') {	// 자리올림이 발생할 경우
		this->digits[index - 1] -= 10;	// 현재 자릿수에서 (아스키값) 10을 빼고
		Add('1', index + 1);			// 윗자리에 1을 더한다
	}
}
