#pragma warning(disable: 4996)
#include <iostream>
#include <string>
#include <Windows.h>
#include <cwchar>
#include <clocale>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class Singletone1 {
private:
	Singletone1() { }
	Singletone1(const Singletone1&);
	Singletone1& operator= (Singletone1&);

	int _fontSize;

public:
	static Singletone1& getInstance() {
		static Singletone1 instance;
		return instance;
	}

	void setFontSize(int &fontSize) {
		_fontSize = fontSize;
	}

	void workWithConsole(int &fontSize) {

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get Console
		CONSOLE_FONT_INFOEX fontInfo;
		GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo); // Get Current Font

		// Change parameters

		wcsncpy((wchar_t*)L"Arial Cyr", fontInfo.FaceName, LF_FACESIZE); // name
		fontInfo.dwFontSize.X = fontSize; // Size

		GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo); // set new font;

	}
	
};

class Singletone2 {
private:
	Singletone2 ( Singletone1& instance ) : s1 (instance) { }
	Singletone2(const Singletone2&);
	Singletone2& operator = (Singletone2&);
	Singletone1& s1;
public:
	static Singletone2& getInstance() {
		static Singletone2 instance(Singletone1::getInstance());
		return instance;
	}
};

int main() {

	int fontSize;
	string font = "Arial Cyr";

	Singletone2& s2 = Singletone2::getInstance();
	Singletone1& s1 = Singletone1::getInstance();

	std::cout << "Please enter font size: ";
	std::cin >> fontSize;

	s1.workWithConsole(fontSize);

	return 0;
}