#include "Peca.h"

Peca::Peca(char simbolo, int pontuacao)
{
	this->pont = pontuacao;
	this->simb = simbolo;
}

Peca::~Peca()
{
}

char Peca::get_simb()
{
	return simb;
}

void Peca::vis_simbolo()
{
	cout << simb;
}
int Peca::get_pont()
{
	return pont;
}

void Peca::set_simbolo(char simbolo)
{
	this->simb = simbolo;
}

void Peca::set_pont(int pontuacao)
{
	this->pont = pontuacao;
}

bool Peca::operator==(const Peca & p)
{
	return simb == p.simb;
}
