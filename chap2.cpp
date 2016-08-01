#include<iostream>
#include<fstream>
#include <ctype.h>
using namespace std;

enum kind{ IF, ID };

struct token{
	enum kind k;
	char *lexeme;
};

struct token* new_Token(char* lexeme, enum kind k){
	struct token* p = (struct token*)malloc(sizeof(*p));
	p->k = k;
	p->lexeme = lexeme;
	return p;
}

void printToken(ofstream& fout, struct token* t, int row, int col){
	if (t->k == IF) fout << "IF";
	else fout << "ID " << t->lexeme;
	fout << " (" << row << "," << col << ")" << '\n';
}

int main(){
	ifstream srcFile("code.txt", ios::in);
	if (!srcFile){
		cout << "error in open inut file" << endl;
	}
	ofstream destFile("tokens.txt", ios::out);
	if (!destFile){
		cout << "error in open output file" << endl;
	}
	// do not ignore ' ' and '\n'
	srcFile >> noskipws;
	char c;
	int row = 1, col = 0;
	while (!srcFile.eof()){
		srcFile >> c;
		char lexeme[10];
		int index = 0;
		if (isalpha(c) && c != 'i')
		{
			enum kind k = ID;
			int column = ++col;
			lexeme[index++] = c;
			srcFile >> c;
			++col;
			while (isalnum(c)){
				lexeme[index++] = c;
				srcFile >> c;
				++col;
			}
			lexeme[index++] = '\0';
			printToken(destFile, new_Token(lexeme, k), row, column);
			if (c == '\n'){
				row++;
				col = 0;
			}
		}
		if (c == 'i'){
			int column = ++col;
			lexeme[index++] = c;
			srcFile >> c;
			++col;
			if (c == 'f'){
				lexeme[index++] = c;
				srcFile >> c;
				++col;
				if (!isalnum(c)){
					enum kind k = IF;
					lexeme[index++] = '\0';
					printToken(destFile, new_Token(lexeme, k), row, column);
					if (c == '\n') {
						row++;
						col = 0;
					}
				}
				else{
					enum kind k = ID;
					lexeme[index++] = c;
					srcFile >> c;
					++col;
					while (isalnum(c)){
						lexeme[index++] = c;
						srcFile >> c;
						++col;
					}
					lexeme[index++] = '\0';
					printToken(destFile, new_Token(lexeme, k), row, column);
					if (c == '\n') {
						row++;
						col = 0;
					}
				}
			}
			else{
				enum kind k = ID;
				lexeme[index++] = c;
				srcFile >> c;
				++col;
				while (isalnum(c)){
					lexeme[index++] = c;
					srcFile >> c;
					++col;
				}
				lexeme[index++] = '\0';
				printToken(destFile, new_Token(lexeme, k), row, column);
				if (c == '\n'){
					row++;
					col = 0;
				}
			}
		}
		else if (c == '\n'){
			row++;
			col = 0;
		}
		else continue;
	}
	srcFile.close();
	destFile.close();
}

