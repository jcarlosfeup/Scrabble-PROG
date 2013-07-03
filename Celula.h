#ifndef CELULA_H_
#define CELULA_H_

#include <iostream>
#include <string>
#include <vector>
#include "Peca.h"
using std::string;
using std::vector;

class Celula
{
private:
char simb;
Peca * peca;


public:
	Celula(char simbolo);
	~Celula();
	char get_letra();
	void set_simb(char c);
	Peca * get_peca()
	{
		return peca;
	}
	void add_peca(Peca * peca);

};
ostream & operator << (ostream & os, const Celula& c);
#endif

