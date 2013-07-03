#include "Tabuleiro.h"
#include <sstream>
#include <fstream>

Tabuleiro::Tabuleiro(string filename, vector<int> vec_ponto)
{
	ifstream file;
	file.open(filename.c_str());
	if (file.is_open()) {
	char caracter;
	string linha;
	vector<vector<Celula> > tab;
	vector<Celula> vec;
	while(getline(file, linha))
	{
		istringstream ss(linha);
		vector<Celula> vec;
		while (ss >> caracter)
		{ if(caracter != '.' && caracter != '*' && caracter!= '#' && caracter != '%' && caracter != '$')
		{
			Celula cel = Celula('.');
			if(islower(caracter))
			{
				Peca * peca = new Peca(toupper(caracter), 0);
				cel.add_peca(peca);
				vec.push_back(cel);
			}
			else
			{
				string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_";
				int b = 0;
				while(alf[b] == caracter)
					++b;
				Peca * peca = new Peca(caracter, vec_ponto[b]);
				cel.add_peca(peca);
				vec.push_back(cel);

			}
		}
		else
		{
			vec.push_back(Celula(caracter));
		}
		}

		tab.push_back(vec);
	}
		this->tabuleiro = tab;
		file.close();
	}

}
Tabuleiro::~Tabuleiro()
{

}

vector<vector<Celula> > Tabuleiro::acesso_tabuleiro()
{
	return tabuleiro;
}
void Tabuleiro::set_tab(vector<vector<Celula> > vec)
{
	this->tabuleiro = vec;
}



void Tabuleiro::add_p(Peca * peca, int pos_horizontal, int pos_vertical)
{
	tabuleiro[pos_vertical][pos_horizontal].add_peca(peca);
}
Celula Tabuleiro::get_celula(int pos_horizontal, int pos_vertical)
{
	return tabuleiro[pos_vertical][pos_horizontal];
}

