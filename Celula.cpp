#include "Celula.h"

Celula::Celula(char simbolo)
{
	this->simb = simbolo;
	this->peca = NULL;
}

Celula::~Celula()
{

}

void Celula::set_simb(char c)
{
	this->simb = c;
}
void Celula::add_peca(Peca * peca)
{
	this->peca = peca;
}

char Celula::get_letra()
{
	return simb;
}

/*ostream & operator << (ostream & os, const Celula& c)
{
	if(c.get_peca() == NULL)
	{
		os << c.get_letra();
	}
	else
	{
		os << c.get_peca();
	}
	return os;

}*/

