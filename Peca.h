#ifndef PECA_H_
#define PECA_H_

#include <iostream>
#include <string>
using namespace std;

class Peca
{
private:
	char simb;
	int pont;

public:
	Peca(char simbolo, int pontuacao);
	~Peca();
	char get_simb();
	int get_pont();
	void vis_simbolo();
	void set_simbolo(char simbolo);
	void set_pont(int pontuacao);
	bool operator==(const Peca & p);

};

#endif


