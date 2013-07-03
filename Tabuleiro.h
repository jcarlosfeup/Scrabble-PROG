#ifndef TABULEIRO_H_
#define TABULEIRO_H_

#include <iostream>
#include <string>
#include <vector>
#include "Peca.h"
#include "Celula.h"
using std::string;
using std::vector;

class Tabuleiro
{
private:
	vector<vector<Celula> > tabuleiro;


public:
	Tabuleiro(string filename, vector<int> vec_ponto);
	Tabuleiro() {}
	~Tabuleiro();
	void set_tab(vector<vector<Celula> > vec);
	vector<vector<Celula> > acesso_tabuleiro();
	void add_p(Peca * peca, int pos_horizontal, int pos_vertical);
	Celula get_celula(int pos_horizontal, int pos_vertical);

};
#endif
