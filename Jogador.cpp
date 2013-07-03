#include "Jogador.h"

Jogador::Jogador(string nome, vector<Peca> p_mao, int pontos)
{
	this->name = nome;
	this->mao = p_mao;
	this->score = pontos;
}

Jogador::~Jogador()
{
}

string Jogador::get_nome()
{
	return name;
}

void Jogador::set_nome(string nome)
{
	this->name = nome;

}


vector<Peca> & Jogador::get_mao()
{
	return mao;
}

void Jogador::set_mao(vector<Peca> p_mao)
{
	this->mao = p_mao;

}

int Jogador::get_score()
{
	return score;
}


void Jogador::set_score(int pontos)
{
	this->score = pontos;

}
