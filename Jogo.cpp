#include "Jogo.h"
#include <cctype>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include <ctype.h>
#include <iostream>
#include <windows.h>
#include <sstream>
#include <algorithm>

Jogo::Jogo() 
{
	vector<int> vec;
	for(int r = 0; r < 27; ++r)
		vec.push_back(0);
	this->tabuleiro = Tabuleiro("tabuleiro.txt", vec);
}

Jogo::~Jogo()
{

}

/* void Jogo::cria_tabuleiro(string filename)
{
	Tabuleiro coiso(filename);
	tabuleiro = coiso;
}*/

Tabuleiro Jogo::GetTabuleiro()
{
	return tabuleiro;
}

void Jogo::SetTabuleiro(Tabuleiro tb)
{
	this->tabuleiro = tb;
}

bool Jogo::ver_tabuleiro(int ver, int hor, char ori)
{
	if(ori == 'H' || ori == 'h')
	{
		hor = hor - 1;
	}
	else
	{
		ver = ver - 1;
	}
	if(tabuleiro.get_celula(hor, ver).get_peca() == NULL)
		return true;
	else
	{
		cout << "Forma palavra invalida";
		return false;
}}

void Jogo::show_tabuleiro()
	{
		string letras = "ABCDEFGHIJLMNOP";
		string espacos = string(21, ' ');
		cout << endl << espacos << "1 1 1 1 1 1" << endl;
		cout << "   1 2 3 4 5 6 7 8 9 0 1 2 3 4 5" << endl;
		cout << "  +-----------------------------+" << endl;
		for(int  unsigned r = 0; r < 15; ++r)
		{
			cout << letras[r] << " |";

			for(int unsigned i = 0; i < 15; ++i)
			{
				if(tabuleiro.get_celula(i, r).get_peca() == NULL)
					cout << tabuleiro.get_celula(i, r).get_letra();
				else
					tabuleiro.get_celula(i, r).get_peca()->vis_simbolo();
				if(i+1 != 15)
					cout << " ";
			}
			cout << "|" << endl;
		}
		cout << "  " << "+-----------------------------+" << endl;

	}


void Jogo::add_jogador(Jogador player)
{
	jogadores.push_back(player);
}



string to_upper(string in)   //converte a palavra em maiusculas
{
	int tamanho = in.size();
	for (int r = 0; r < tamanho; ++r)
	{char letra = in[r];
		in[r] = toupper(letra);
	}
	return in;
	}


void Jogo::cria_dicionario(string filename)
{
	ifstream file;
		file.open(filename.c_str());
		if (file.is_open()) {
			int nWords;
			string word;
			file >> nWords;
			for (int i = 0; i < nWords; i++) {
				file >> word;
				word = to_upper(word);
				dicionario.push_back(word);
			}
			file.close();
		}
}



void Jogo::cria_baralho(string filename)
{
		ifstream file;
		vector<Peca> bar;
		file.open(filename.c_str());
		if (file.is_open()) {
			char letra;
			int pont;
			int num_carc;
			for (int r = 0; r < 27; r++) {
				file >> letra >> num_carc >> pont;
				for(int i = 0; i < num_carc; ++i)
				bar.push_back(Peca(letra, pont));
				vec_ponto.push_back(pont);
			}
			file.close();
			srand((unsigned int)time (0));
				while (bar.size() != 0)
					{
						int aleat = rand() % bar.size();
						baralho.push_back(bar[aleat]);
						bar.erase(bar.begin() + aleat);
					}
}}

bool Jogo::verifica_palavra(string palavra) //verifica palavra no dicionario
{
		vector<string>::iterator it = find(dicionario.begin(), dicionario.end(), palavra);
		if(it == dicionario.end())
		{
			cout << "Palavra nao se encontra no dicionario!!" << endl;
			return false;

		}
		else
			return true;

}


bool Jogo::verifica_tamanho(string palavra, int pos_horizontal, int pos_vertical, char direccao) // verifica se a palavra cabe no tabuleiro
{
	int unsigned numero;
	if(direccao == 'V' || direccao == 'v')
	{
		numero = pos_vertical + palavra.size();
		if(numero < 15)
			return true;
		else
		{
			cout << "A palavra nao cabe no tabulerio!!";
			return false;
		}
	}

	else
	{
		numero = pos_horizontal + palavra.size();
		if(numero < 15)
				return true;
			else
			{
						cout << "A palavra nao cabe no tabulerio!!";
						return false;
					}

	}
}


bool Jogo::verifica_inicio() // verifica se é a primeira jogada
{
	if(jogadores[0].get_score() == 0 && jogadores[1].get_score() == 0)
		return true;
	else
		return false;

}

void Jogo::completa_mao(int i)
{
	vector<Peca> vec = jogadores[i].get_mao();
	while(vec.size() < 7)
	{
		if(baralho.size() == 0)
		break;
		else
		{
		vec.push_back(baralho[baralho.size() - 1]);
		baralho.erase(baralho.end() - 1);
	}}

	jogadores[i].set_mao(vec);
}

void Jogo::troca_mao(string letras_trocar, int i)
{
	vector<Peca> vec = jogadores[i].get_mao();
	for(int unsigned r = 0; r < letras_trocar.size(); ++r)
	{
		if(baralho.size() == 0)
			break;
			else
			{
		int p = 0;
		while(letras_trocar[r] != vec[p].get_simb())
		{
			++p;
		}
		vec[p] = baralho[baralho.size() - 1];
		baralho.erase(baralho.end() - 1);
	}
	}
	jogadores[i].set_mao(vec);
}

void Jogo::actualiza_pontuacao(int actualizacao, int i)
{
	jogadores[i].set_score(actualizacao + jogadores[i].get_score());
}


bool Jogo::verifica_posiblidade(string palavra, int pos_horiz, int pos_vert, char direc) //verifica se a palavra é formada a partir de peças ja no tabuleiro
{
	for(int unsigned i=0; i < palavra.size(); ++i)
	{
		if(direc == 'h' || direc == 'H')
		{
			if(tabuleiro.acesso_tabuleiro()[pos_vert][pos_horiz + i].get_peca() != NULL)
				return true;
				else
					if(i+1 == palavra.size())
					{
						cout << "Palavra tem de ser formada utilizando letras do tabuleiro!" << endl;
						return false;
					}
		}
		else {
			if(direc == 'V' || direc == 'v')
			{
				if(tabuleiro.acesso_tabuleiro()[pos_vert + i][pos_horiz].get_peca() != NULL)
								return true;
								else
									if(i+1 == palavra.size())
									{
										cout << "Palavra tem de ser formada utilizando letras do tabuleiro!" << endl;
										return false;
									}
			}

		}
	}
	return false;
}

bool Jogo::verif_pal_tabuleiro(string palavra, int pos_horiz, int  pos_vert, char direc, int i) //verifica se com  a mao e as letras do tabuleiro e possivel formar a palavra
{
	vector<Peca> mao = jogadores[i].get_mao();
	for(int unsigned r = 0; r < palavra.size(); ++r)
	{
		if(direc == 'h' || direc == 'H')
				{
					if(tabuleiro.acesso_tabuleiro()[pos_vert][pos_horiz + r].get_peca() == NULL)
					{
						cout << "vkv" << endl;
						for(int  unsigned p = 0;p < mao.size(); ++p)
						{
							if(palavra[r] == mao[p].get_simb()) //se encontar a letra da palavra na mao
							{
								mao.erase(mao.begin() + p);
										break;
							}

								if(p+1 == mao.size())
								{
									vector<Peca>::iterator it = find(mao.begin(), mao.end(), Peca('_', 0));
									if(it != mao.end()){
										mao.erase(it);
										break;
									}
									else
									{
									cout << "Não é possivel formar a palavra com as letras que tem na mao." << endl;
									return false;
								}
							}
						}
					}
					else
					{
						if(palavra[r] != tabuleiro.acesso_tabuleiro()[pos_vert][pos_horiz + r].get_peca()->get_simb())
						{
							cout << "Não é possivel formar a palavra com as letras do tabuleiro." << endl;
							return false;
						}

					}
					if(r+1 == palavra.size())
							return true;
				}
		else
		{
							if(tabuleiro.acesso_tabuleiro()[pos_vert + r][pos_horiz].get_peca() == NULL)
							{
								for(int  unsigned p = 0;p < mao.size(); ++p)
								{
									if(palavra[r] == mao[p].get_simb())
									{
										mao.erase(mao.begin() + p);
												break;
									}

									if(p+1 == mao.size())
									{
										vector<Peca>::iterator it = find(mao.begin(), mao.end(), Peca('_', 0));
										if(it != mao.end()){
											mao.erase(it);
											break;
										}
										else
										{
											cout << "Não é possivel formar a palavra com as letras que tem na mao." << endl;
											return false;
										}
									}
								}
							}
							else
							{
								if(palavra[r] != tabuleiro.acesso_tabuleiro()[pos_vert + r][pos_horiz].get_peca()->get_simb())
								{
									cout << "Não é possivel formar a palavra com as letras do tabuleiro." << endl;
									return false;
								}

							}
							if(r+1 == palavra.size())
									return true;
						}



	}
	return false;


}

int Jogo::pont_palavra(string palavra, int pos_horizontal, int pos_vertical, char orientacao) //devolve a pontuaçao da palavra
{
	bool duplica = false;
	bool duplica1 = false;
	bool triplica = false;
	int pont = 0;

	for(int unsigned r = 0; r < palavra.size(); ++r)
	{
		int horizontal, vertical;
		if(orientacao == 'v' || orientacao == 'V')
			{
			vertical = pos_vertical + r;
			horizontal = pos_horizontal;
			}
		else
		{
			vertical = pos_vertical;
			horizontal = pos_horizontal + r;
		}
		if(tabuleiro.get_celula(horizontal, vertical).get_letra() == '.')
			{
			pont = pont + tabuleiro.acesso_tabuleiro()[vertical][horizontal].get_peca()->get_pont();
			tabuleiro.get_celula(horizontal, vertical).set_simb('.');
			}
		else
			if(tabuleiro.get_celula(horizontal, vertical).get_letra() == '*')
				{
				pont = pont + 2 * tabuleiro.get_celula(horizontal, vertical).get_peca()->get_pont();
				tabuleiro.get_celula(horizontal, vertical).set_simb('.');
				}
			else
				if(tabuleiro.get_celula(horizontal, vertical).get_letra() == '#')
					{
					pont = pont + 3 * tabuleiro.get_celula(horizontal, vertical).get_peca()->get_pont();
					tabuleiro.get_celula(horizontal, vertical).set_simb('.');
					}
				else
					if(tabuleiro.get_celula(horizontal, vertical).get_letra() == '$')
					{
						pont = pont + tabuleiro.get_celula(horizontal, vertical).get_peca()->get_pont();
						tabuleiro.get_celula(horizontal, vertical).set_simb('.');
						if(duplica)
							duplica1 = true;
						else
							duplica = true;
					}
					else
						if(tabuleiro.get_celula(horizontal, vertical).get_letra() == '%')
						{
							pont = pont + tabuleiro.get_celula(horizontal, vertical).get_peca()->get_pont();
							tabuleiro.get_celula(horizontal, vertical).set_simb('.');
							triplica = true;
						}

		}
	if(duplica)
		pont = 2 * pont;
	if(duplica1)
		pont = 2 * pont;
	if(triplica)
		pont = 3 * pont;
	return pont;

}

vector<Peca> Jogo::cria_mao()
{
	cout << baralho.size();
	vector<Peca> mao;
	for(int unsigned r = 0; r < 7; ++r)
	{
		mao.push_back(baralho[0]);
		baralho.erase(baralho.begin());
	}

return mao;
}


void Jogo::coloca_palavra(string palavra, int pos_horiz, int pos_vert, char direc, vector<Peca> & mao) //coloca palavra no tabuleiro
{

		for(int unsigned r = 0; r < palavra.size(); ++r)
		{
			if(direc == 'h' || direc == 'H')
					{
						if(tabuleiro.acesso_tabuleiro()[pos_vert][pos_horiz + r].get_peca() == NULL)
						{
							for(int  unsigned p = 0;p < mao.size(); ++p)
							{
								if(palavra[r] == mao[p].get_simb())
								{
									Peca * peca = new Peca(palavra[r], mao[p].get_pont());
									tabuleiro.add_p(peca,pos_horiz + r, pos_vert);
									mao.erase(mao.begin() + p);
											p = 20;
								}

								if(p + 1 == mao.size())
								{
									vector<Peca>::iterator it = find(mao.begin(), mao.end(), Peca('_', 0));
									Peca * peca = new Peca(palavra[r], 0);
									tabuleiro.add_p(peca,pos_horiz + r, pos_vert);
										mao.erase(it);
								}
						}}}
						else
							if(direc == 'v' || direc == 'V')
												{
													if(tabuleiro.acesso_tabuleiro()[pos_vert + r][pos_horiz].get_peca() == NULL)
													{
														for(int  unsigned p = 0;p < mao.size(); ++p)
														{
															if(palavra[r] == mao[p].get_simb())
															{
																Peca * peca = new Peca(palavra[r], mao[p].get_pont());
																tabuleiro.add_p(peca,pos_horiz, pos_vert + r);
																mao.erase(mao.begin() + p);
																		p=20;
															}

															if(p + 1 == mao.size())
															{
																vector<Peca>::iterator it = find(mao.begin(), mao.end(), Peca('_', 0));
																Peca * peca = new Peca(palavra[r], 0);
																tabuleiro.add_p(peca,pos_horiz, pos_vert + r);
																	mao.erase(it);

														}
													}}}
						}}

string Jogo::mostra_mao(int i)
{

	int tamanho = jogadores[i].get_mao().size();
		string nova(tamanho, '*');
		for(int r = 0; r < tamanho; ++r)
		{
			nova[r] = jogadores[i].get_mao()[r].get_simb();
		}

		return nova;
}

void Jogo::mostrar_ranking()
{
	cout << "Melhores jogadores:" << endl;
for(int unsigned r = 0; r < rank.size(); ++r)
{
	cout << rank[r].get_name() << ": " << rank[r].get_score() << endl;
}
}

void Jogo::criar_ranking(string filename)
{
	ifstream file;
		file.open(filename.c_str());
		if (file.is_open())
		{
			int valor;
			string nome;
			while (file >> valor && getline(file, nome))
			{
				rank.push_back(Pontuacao(nome.substr(1), valor));
			}
			file.close();
		}
}

Jogador & Jogo::acesso_jogador(int i)
{
	return jogadores[i];
}

void ranking(vector<Pontuacao> rank)
{
	cout << "Melhores jogadores:" << endl;
for(int unsigned r = 0; r < rank.size(); ++r)
{
	cout << rank[r].get_name() << ": " << rank[r].get_score() << endl;
}
}

void Jogo::update_best_scores(Pontuacao s) //actualiza o ranking
{
	if (rank.size() == 0)
	{
		rank.push_back(s);
		cout << "Parabens acabou de entrar no ranking!" << endl;
		ranking(rank);
	}
	else {
	for (int unsigned i = 0 ; i < rank.size(); ++i)
	{
		if (rank[i].get_score() > s.get_score())
		{
			rank.insert(rank.begin()+i, s);
			if (rank.size() > 10)
				rank.erase(rank.begin() + 10);
			if(i < 10)
			cout << "Parabens acabou de entrar no ranking!" << endl;
			ranking(rank);
			break;

		}
	}
}

}


void Jogo::guarda_ranking(string filename, unsigned int n_best )
{

	vector<Pontuacao> vec;
	if (rank.size() < n_best)
	{
		vec= rank;
	}
	else
	{
		for (unsigned int i = 0; i < n_best; ++i)
		{
			vec.push_back(rank[i]);
		}
	}
	ofstream file;
	file.open(filename.c_str());
	if (file.is_open())
	{
		for (unsigned int k = 0; k < vec.size(); ++k)
		{
			file << vec[k].get_score() << " " << vec[k].get_name() << endl;
		}
		file.close();
	}
}



vector<int> conta_baralho(vector<Peca> & baralho) // conta as letras do baralho
		{
	vector<int> vec;
	for(int unsigned p = 0; p < 27; ++p)
		vec.push_back(0);
	string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	int i;
	for(int unsigned r = 0; r < baralho.size(); ++r)
	{
		i = 0;
		while(baralho[r].get_simb() != alf[i])
			++i;
		vec[i] = vec[i] + 1;
	}
	return vec;
}

void Jogo::nome_jogo(string n)
{
	nome_j.push_back(n);
}

void guarda_tab(string filename, Tabuleiro tabuleiro)
{
	ofstream file;
	file.open(filename.c_str());
	if (file.is_open())
	{
		for(int unsigned v = 0; v < 15; ++v)
			{
				for(int unsigned h = 0; h < 15; ++h)
				{
					char letra;
					if(tabuleiro.get_celula(h,v).get_peca() == NULL)
					{
						letra = tabuleiro.get_celula(h,v).get_letra();
					}
					else
					{
						if(tabuleiro.get_celula(h,v).get_peca()->get_pont() == 0)
							letra = tabuleiro.get_celula(h,v).get_peca()->get_simb() + 32;
						else
							letra = tabuleiro.get_celula(h,v).get_peca()->get_simb();

					}
					file << letra << " ";
				}
				file << endl;
			}
			file.close();
	}
}

void Jogo::guardar_jogo(string filename)
{

	ofstream file;
	file.open(filename.c_str());
	if (file.is_open())
	{
	for(int r = 0; r < 2; ++r) //guarda jogadores
	{
		file << jogadores[r].get_nome() << endl << jogadores[r].get_score() << endl << jogadores[r].get_mao().size() << endl;
		for(int unsigned i = 0; i < jogadores[r].get_mao().size(); ++i)
		{
			file << jogadores[r].get_mao()[i].get_simb() << " " << jogadores[r].get_mao()[i].get_pont() << endl;
		}
	}
	vector<int> vec = conta_baralho(baralho);
	string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	for(int r = 0; r < 27; ++r) //guarda baralho
	{
		file << alf[r] << " " << vec[r] << " " << vec_ponto[r] << endl;
	}
	for(int unsigned v = 0; v < 15; ++v)
	{

	file.close();
}}
	string name = filename.erase(filename.size() - 5);
	name = name + "_tab.txt";
	guarda_tab(name, tabuleiro); //guarda tabuleiro
}
void Jogo::carrega_vec_jogo(string filename)
{
	ifstream file;
	file.open(filename.c_str());
	if (file.is_open()) {
		int r;
		string jogo;
		file >> r;
		while(r > nome_j.size())
		{
			file >> jogo;
			nome_j.push_back(jogo);
		}
	file.close();
	}

}

string Jogo::devolve_no_jogo(int i) //devolve nome de jogo guardado
{
	string nome = nome_j[i];
	string name = nome + ".txt";
	return name;
}

void Jogo::mostrar_nome_jogo()
{
	for(int unsigned r = 0; r < nome_j.size(); ++ r)
	{
		cout << r + 1 << ") " << nome_j[r] << endl;
	}
}

void Jogo::update_jogos(string filename) //guarda num ficheiro de texto o nome dos jogos guardados
{

	ofstream file;
	file.open(filename.c_str());
	if (file.is_open()) {
		string nome;
		file << nome_j.size() << endl;
		for(int unsigned r = 0; r < nome_j.size(); ++r)
		{
			file << nome_j[r] << endl;
		}
		file.close();
	}
}

void Jogo::carregar_jogo(string filename)
{

	ifstream file;
	file.open(filename.c_str());
	if (file.is_open()) {
		for(int r = 0; r < 2; ++r)
			{
			string nome;
			int score, f;
			char letra;
			int pont;
			file >> nome;
			file >> score;
			file >> f;
			vector<Peca> vec;

				for(int i = 0; i < f; ++i)
				{
					file >> letra >> pont;
					vec.push_back(Peca(letra, pont));
				}
				jogadores.push_back(Jogador(nome, vec, score));
			}
		vector<Peca> bar;
		for(int r = 0; r < 27; ++r)
		{
			char letra;
			int pont;
			int num_carc;
				file >> letra >> num_carc >> pont;
				for(int i = 0; i < num_carc; ++i)
					bar.push_back(Peca(letra, pont));
				vec_ponto.push_back(pont);
		}
		srand((unsigned int)time (0));
						while (bar.size() != 0)
							{
								int aleat = rand() % bar.size();
								baralho.push_back(bar[aleat]);
								bar.erase(bar.begin() + aleat);
							}
						string name = filename.erase(filename.size() - 5);
							name = name + "_tab.txt";

							this->tabuleiro = Tabuleiro(name, vec_ponto);


				file.close();
			}

}

int Jogo::terminar(){
	if(baralho.size() == 0 && (jogadores[0].get_mao().size() == 0 || jogadores[1].get_mao().size() == 0))
	{
		if(jogadores[0].get_mao().size() == 0)
			return 0;
		else
			return 1;
	}
		else
		return 2;
}

int Jogo::pontos_mao(int i)
{
	vector<Peca> mao = jogadores[i].get_mao();
	int pontos = 0;
	for(int unsigned r = 0; r < mao.size(); ++ r)
	{
		pontos = pontos + mao[r].get_pont();
	}
	vector<Peca>::iterator it = find(mao.begin(), mao.end(), Peca('_', 0));
	if(it != mao.end())
		pontos = pontos + 30;
	return pontos;
}



