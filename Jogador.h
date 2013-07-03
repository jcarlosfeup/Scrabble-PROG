#ifndef JOGADOR_H_
#define JOGADOR_H_

#include <iostream>
#include <string>
#include <vector>
#include "Peca.h"
using std::string;
using std::vector;

class Jogador
{
private:
	string name;
	vector<Peca> mao;
	int score;



public:
	Jogador(string nome, vector<Peca> p_mao, int pontos);
	~Jogador();
	void show_tabuleiro();
	string get_nome();
	void set_nome(string nome);
	vector<Peca> & get_mao();
	void set_mao(vector<Peca> p_mao);
	int get_score();
	void set_score(int pontos);

};
#endif

