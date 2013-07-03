#include "Pontuacao.h"

Pontuacao::Pontuacao(string nome, int pontuacao)
{
	this->name = nome;
	this->score = pontuacao;
}

string Pontuacao::get_name()
{
	return name;
}

int Pontuacao::get_score()
{
	return score;
}

void Pontuacao::set_score(int pontuacao)
{
	this->score = pontuacao + score;
}
