#ifndef PONTUACAO_H_
#define PONTUACAO_H_

#include <iostream>
#include <string>
#include <vector>
#include "Jogador.h"
using std::string;
using std::vector;

class Pontuacao
{
private:
	string name;
	int  score;


public:
	Pontuacao(string nome, int pontuacao);
	string get_name();
	int get_score();
	void set_score(int pontuacao);

};
#endif
