/*
PROJECTO: 3


DESCRIÇÃO: Jogo do Scrabble


TURMA / GRUPO: Turma 9 ; Grupo 3

AUTORES:
Joaquim José Silva Faria Oliveira
José Carlos Portela Pereira

DECLARAÇÃO:
Declaramos sob compromisso de honra que este trabalho nas suas partes constituintes de código (e
relatório, se aplicável) é original e da nossa autoria, não correspondendo, portanto, a cópia ou tradução
de outros trabalhos já realizados, na FEUP ou fora dela.
Mais declaramos que todos os documentos ou código que serviram de base ao desenvolvimento do
trabalho descrito no relatório e seus anexos são adequadamente citados e explicitados na respectiva
secção de referências bibliográficas e que todas as eventuais partes transcritas ou utilizadas de outras
fontes estão devidamente assinaladas, identificadas e evidenciadas.
Subscrevemos a declaração acima:
Joaquim Oliveira
José Pereira

REFERÊNCIAS E FONTES DE INFORMAÇÃO UTILIZADAS:
Apresentações em Powerpoint das aulas teóricas

SISTEMA OPERATIVO:
Windows 7

AMBIENTE DE DESENVOLVIMENTO:
Eclipse


DATA DE CONCLUSÃO: 29/05/2010
 */
#include "Celula.h"
#include "Jogador.h"
#include "Jogo.h"
#include "Peca.h"
#include "Pontuacao.h"
#include "Tabuleiro.h"
#include <cctype>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

string to_uppers(string in)   //converte a palavra em maiusculas
{
	int tamanho = in.size();
	for (int r = 0; r < tamanho; ++r)
	{char letra = in[r];
		in[r] = toupper(letra);
	}
	return in;
	}



int opcoes(string num, int min, int max) //verifica a validade das opcoes tomadas pelo jogador
{
	unsigned int h;
	bool opcao_bool = false;
	while(opcao_bool == false)
	{
		for (unsigned int q=0; q < num.size(); q++)
		{
			if (isdigit(num[q]) == 0)
			{
				h=0;
				break;
			}
			else
			{
				h=1;
			}
		}
		if (h==1)
		{
			if (atoi(num.c_str()) < max || atoi(num.c_str()) == max )
			{
				opcao_bool = true;
			}
			else
			{
				cout << endl <<"Numero tem que estar compreendido entre (inclusive) " << min << " e " << max <<"."<< endl << "Tente novamente." << endl<< "Opçâo: ";
				getline(cin, num);
			}
		}
		else
		{
			cout << endl << "Numero de opcao invalido, tente novamente." << endl;
			cout << endl <<"Numero tem que estar compreendido entre (inclusive) " << min << " e " << max <<"."<< endl << "Tente novamente." << endl<< "Opçâo: ";
			cin >> num;
		}
	}
	int numero = atoi(num.c_str());
	return numero;
}

int pos_vert(string v)
{
	string letras = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int r =0;
	bool cont = true;
	while(cont)
	{
		r = 0;
		v = to_uppers(v);
		char s = v[0];
	while(letras[r] != s)
		++r;

		if(r > 14)
		{
			cout << "Valor da posiçao vertical invalido!" << endl << "Tente de novo (< A - P >): ";
			cin >> v;
		}
		else
			cont = false;

	}
	return r;
}


char orient(string v)
{
	bool verificar = true;
	string a = v;
	while(verificar)
	{
		char c;
		c = a[0];
		c = toupper(c);
		if(c == 'V' || c == 'H')
		{
			return c;
		}
		else
		{
					cout << "Orientação inválida!" << endl << "Por favor tente de novo (<H, V>): ";
					cin >> a;
				}
	}
	return 'V';
}


int main()
{
	Jogo jogo;
	jogo.criar_ranking("rank.txt");
	jogo.carrega_vec_jogo("vec_jogo.txt");
	int passagens = 0;
	cout << "BEM-VINDO AO SCRABLLE!" <<endl <<endl;
	cout << "1. Novo jogo " <<endl;
	cout << "2. Carregar jogo " <<endl;
	cout << "3. Ver melhores pontuações " <<endl <<endl;
	cout << "Escolha uma opção: ";
	string opcao_menu;
	getline(cin, opcao_menu);
	unsigned int opcao_menu1; 
	opcao_menu1 = opcoes(opcao_menu, 0, 3);
	if(opcao_menu1 == 1)
	{
		jogo.cria_baralho("baralho.txt");
		jogo.cria_dicionario("dicionario.txt");
		cout << "Nome do jogador numero 1:";
		string nome_jogador1;
		cin >> nome_jogador1;
		cout << "Nome do jogador numero 2:";
		string nome_jogador2;
		cin >> nome_jogador2;
		vector<Peca> mao_jogador1 = jogo.cria_mao();
		vector<Peca> mao_jogador2 = jogo.cria_mao();
		jogo.add_jogador(Jogador(nome_jogador1, mao_jogador1, 0));
		jogo.add_jogador(Jogador(nome_jogador2, mao_jogador2, 0));
		bool jogar = true;
		int i = 0;
		while (jogar)
		{
			int terminar = jogo.terminar();
			if(terminar != 2) // termina por acabar as peças
			{
				cout << "O jogo terminou porque as peças esgotaram!" << endl;
				int pont_mao_0 = jogo.pontos_mao(0);
				int pont_mao_1 = jogo.pontos_mao(1);
				if(terminar == 0) //acabou as peças ao jogador 1
				{
					jogo.actualiza_pontuacao(pont_mao_1, 0);
					jogo.actualiza_pontuacao((-pont_mao_1), 1);
				}else
				{
					jogo.actualiza_pontuacao(pont_mao_0, 1);
					jogo.actualiza_pontuacao((-pont_mao_0), 0);
				}
				if(jogo.acesso_jogador(0).get_score() == jogo.acesso_jogador(1).get_score())
								{
									cout << "Os jogadores empataram!!" << endl;
									jogo.update_best_scores(Pontuacao(jogo.acesso_jogador(0).get_nome() + ", " + jogo.acesso_jogador(1).get_nome() , jogo.acesso_jogador(0).get_score()));
														jogo.guarda_ranking("rank.txt", 10);
								}
								else
				if(jogo.acesso_jogador(0).get_score() > jogo.acesso_jogador(1).get_score())
				{
					cout << "O vencedor é " << jogo.acesso_jogador(0).get_nome() << " . PARABENS!" << endl;
					jogo.update_best_scores(Pontuacao(jogo.acesso_jogador(0).get_nome(), jogo.acesso_jogador(0).get_score()));
					jogo.guarda_ranking("rank.txt", 10);
				}
				else
				{
					cout << "O vencedor é " << jogo.acesso_jogador(1).get_nome() << " . PARABENS!" << endl;
					jogo.update_best_scores(Pontuacao(jogo.acesso_jogador(1).get_nome(), jogo.acesso_jogador(1).get_score()));
					jogo.guarda_ranking("rank.txt", 10);
				}
				jogar = false;
			}
			else {
				if(passagens == 4) // termina por passar a vez
				{
					if(jogo.acesso_jogador(0).get_score() == jogo.acesso_jogador(1).get_score())
									{
										cout << "Os jogadores empataram!!" << endl;
										jogo.update_best_scores(Pontuacao(jogo.acesso_jogador(0).get_nome() + ", " + jogo.acesso_jogador(1).get_nome() , jogo.acesso_jogador(0).get_score()));
															jogo.guarda_ranking("rank.txt", 10);
									}
									else
					if(jogo.acesso_jogador(0).get_score() > jogo.acesso_jogador(1).get_score())
					{
						cout << "O vencedor é " << jogo.acesso_jogador(0).get_nome() << " . PARABENS!" << endl;
						jogo.update_best_scores(Pontuacao(jogo.acesso_jogador(0).get_nome(), jogo.acesso_jogador(0).get_score()));
						jogo.guarda_ranking("rank.txt", 10);
					}
					else
					{
						cout << "O vencedor é " << jogo.acesso_jogador(1).get_nome() << " . PARABENS!" << endl;
						jogo.update_best_scores(Pontuacao(jogo.acesso_jogador(1).get_nome(), jogo.acesso_jogador(1).get_score()));
						jogo.guarda_ranking("rank.txt", 10);
					}
					jogar = false;
				}
				else {

			i = (i + 1) % 2;
			jogo.show_tabuleiro();
			cout << "Vez do " << jogo.acesso_jogador(i).get_nome()<< endl;
			cout << "Letras na mao: " << jogo.mostra_mao(i)<<endl;
			cout << "Pontuacao actual: "  << jogo.acesso_jogador(i).get_score() <<endl <<endl;
			cout << "1) Jogar" <<endl;
			cout << "2) Trocar letras do saco" <<endl;
			cout << "3) Passar a vez" <<endl;
			cout << "4) Gravar o jogo" <<endl;
			cout << "5) Sair" << endl <<endl;
			cout << "O que deseja fazer? ";
			string opcao_submenu;
			cin >> opcao_submenu;
			int opcao_submenuf = opcoes(opcao_submenu, 1, 5);
			if(opcao_submenuf == 1)
			{
				bool palavra_certa = false;
				while(palavra_certa == false)
				{
					cout << "Palavra a formar: ";
					string pal, palavra;
					cin >> pal;
					palavra = to_uppers(pal);
					if(jogo.verifica_inicio())
					{
						if(jogo.verifica_palavra(palavra) && jogo.verif_pal_tabuleiro(palavra, 7 - palavra.size() / 2, 7, 'h', i))
						{
							cout << "Como o tabuleiro ainda se encontrava vazio, a peça foi colocada automaticamente" << endl;
							jogo.coloca_palavra(palavra, 7 - palavra.size() / 2, 7, 'h', jogo.acesso_jogador(i).get_mao());
							jogo.completa_mao(i);
							int pontuacao = jogo.pont_palavra(palavra, 7 - palavra.size() / 2, 7, 'h');
							jogo.actualiza_pontuacao(pontuacao, i);
							cout << "Pontuação total: " << jogo.acesso_jogador(i).get_score() <<endl <<endl;
							palavra_certa = true; 
							passagens = 0;
						}else
						{
							cout << "Jogada invalida!" << endl;
							cout << "O que pertende fazer?" << endl << "Precione 1 para continuar, o 2 para passar a vez!";
							string n_tente;
							int n_tent;
							cin >> n_tente;
							n_tent= opcoes(n_tente, 1, 2);
							if(n_tent == 2)
							{
								++passagens;
								palavra_certa = true;
							}
						}
					}else
					{
						cout << "Coordenadas vertical da primeira letra da palavra (<A – P>): ";
						string pos_v;
						cin >> pos_v;
						cout << "Coordenadas horizontal da primeira letra da palavra (<1 – 15>): ";
						string pos_h;
						cin >> pos_h;
						cout << "Orientação da palavra (<H , V>): ";
						string ori;
						cin >> ori;
						int horizontal = opcoes(pos_h, 1, 15) - 1;
						int vertical = pos_vert(pos_v);
						char orien = orient(ori);
						if(jogo.verif_pal_tabuleiro(palavra, horizontal, vertical, orien, i) && jogo.ver_tabuleiro(vertical, horizontal, orien) && jogo.verifica_tamanho(palavra, horizontal, vertical, orien) && jogo.verifica_posiblidade(palavra, horizontal, vertical, orien) && jogo.verifica_palavra(palavra))
						{
							cout << endl << "Palavra válida!" << endl;
							jogo.coloca_palavra(palavra, horizontal, vertical, orien, jogo.acesso_jogador(i).get_mao());
							int pontuacao = jogo.pont_palavra(palavra, horizontal, vertical, orien);
							cout << "Pontuação da palavra a formar " << pontuacao << endl;
							jogo.actualiza_pontuacao(pontuacao, i);
							jogo.completa_mao(i);
							cout << "Pontuação total: " << jogo.acesso_jogador(i).get_score() <<endl <<endl;
							palavra_certa = true;
							passagens = 0;
						}else
						{
							cout << "Jogada invalida!" << endl;
							cout << "O que pertende fazer?" << endl << "Precione 1 para continuar, o 2 para passar a vez!";
							string n_tente;
							unsigned n_tent;
							cin >> n_tente;
							n_tent= opcoes(n_tente, 1, 2);
							if(n_tent == 2)
							{
								palavra_certa = true;
								++passagens;
							}

						}

					}}
			}
			else
			if(opcao_submenuf == 2) //trocar letras da mao
			{
				passagens = 0;
				bool continuar = false;
				while(continuar == false)
				{
				cout << "Quantas letras pretende trocar? ";
				string n_letras_troca;
				cin >> n_letras_troca;
				int n_letras;
				n_letras = opcoes(n_letras_troca, 0, 7);
				cout << "Indique as letras que pretende trocar (sem espacos): ";
				string letras_troca;
				cin >> letras_troca;
				cout << "Por favor volte a repetir as letras que pertende trocar (sem espaços): ";
				string letras_trocar2;
				cin >> letras_trocar2;
				if(letras_troca == letras_trocar2)
				{
					letras_troca = to_uppers(letras_troca);
					jogo.troca_mao(letras_troca, i);
					continuar = true;
				}
				else
					cout << "Letras erradas. Volte a tentar!" << endl << endl;
				}
			}
			else
				if(opcao_submenuf == 3) //passar a vez
			{
				++passagens;
			}
				else
					if(opcao_submenuf ==4)
			{

						cout << "Indique o nome para guardar o jogo: ";
						string nome;
						cin >> nome;
						jogo.nome_jogo(nome);
						nome = nome + ".txt";
						jogo.guardar_jogo(nome);
						jogo.update_jogos("vec_jogo.txt");
						jogar = false;

			}
					else
						if(opcao_submenuf == 5) // termina jogo
			{
				cout << "Tem a certeza que pertende sair? " << endl << "Se sim pressione 1, caso contrario pressione 2! ";
				string dec;
				cin >> dec;
				unsigned int decis = opcoes(dec, 1, 2);
				if(decis == 1)
				{
				jogar = false;
				if(jogo.acesso_jogador(0).get_score() == jogo.acesso_jogador(1).get_score())
								{
									cout << "Os jogadores empataram!!" << endl;
									jogo.update_best_scores(Pontuacao(jogo.acesso_jogador(0).get_nome() + ", " + jogo.acesso_jogador(1).get_nome() , jogo.acesso_jogador(0).get_score()));
														jogo.guarda_ranking("rank.txt", 10);
								}
								else
				if(jogo.acesso_jogador(0).get_score() > jogo.acesso_jogador(1).get_score())
				{
					cout << "O vencedor é " << jogo.acesso_jogador(0).get_nome() << " . PARABENS!" << endl;
					jogo.update_best_scores(Pontuacao(jogo.acesso_jogador(0).get_nome(), jogo.acesso_jogador(0).get_score()));
					jogo.guarda_ranking("rank.txt", 10);
				}
				else
				{
					cout << "O vencedor é " << jogo.acesso_jogador(1).get_nome() << " . PARABENS!" << endl;
					jogo.update_best_scores(Pontuacao(jogo.acesso_jogador(1).get_nome(), jogo.acesso_jogador(1).get_score()));
					jogo.guarda_ranking("rank.txt", 10);
				}
			}else {
				if(i==1)
					i = 0;
				else
					i = 1;
			}

			}

		}

	}
		}
	}

	else
		if(opcao_menu1 == 2) // carrega jogo
	{
		jogo.mostrar_nome_jogo();
		cout << "Escolha numero do jogo que pertende carregar: ";
		string escol;
		int esc;
		cin >> escol;
		esc = opcoes(escol, 0, 20);
		jogo.carregar_jogo(jogo.devolve_no_jogo(esc - 1));
		bool jogar = true;
		jogo.cria_dicionario("dicionario.txt");
		int i = 0;
		while (jogar)
		{
			int terminar = jogo.terminar();
			if(terminar != 2) // termina por a mao ser zero
			{
				cout << "O jogo terminou porque as peças esgotaram!" << endl;
				int pont_mao_0 = jogo.pontos_mao(0);
				int pont_mao_1 = jogo.pontos_mao(1);
				if(terminar == 0)
				{
					jogo.actualiza_pontuacao(pont_mao_1, 0);
					jogo.actualiza_pontuacao((-pont_mao_1), 1);
				}else
				{
					jogo.actualiza_pontuacao(pont_mao_0, 1);
					jogo.actualiza_pontuacao((-pont_mao_0), 0);
				}
				if(jogo.acesso_jogador(0).get_score() == jogo.acesso_jogador(1).get_score())
				{
					cout << "Os jogadores empataram!!" << endl;
					jogo.update_best_scores(Pontuacao(jogo.acesso_jogador(0).get_nome() + ", " + jogo.acesso_jogador(1).get_nome() , jogo.acesso_jogador(0).get_score()));
										jogo.guarda_ranking("rank.txt", 10);
				}
				else
				if(jogo.acesso_jogador(0).get_score() > jogo.acesso_jogador(1).get_score())
				{
					cout << "O vencedor é " << jogo.acesso_jogador(0).get_nome() << " . PARABENS!" << endl;
					jogo.update_best_scores(Pontuacao(jogo.acesso_jogador(0).get_nome(), jogo.acesso_jogador(0).get_score()));
					jogo.guarda_ranking("rank.txt", 10);
				}
				else
				{
					cout << "O vencedor é " << jogo.acesso_jogador(1).get_nome() << " . PARABENS!" << endl;
					jogo.update_best_scores(Pontuacao(jogo.acesso_jogador(1).get_nome(), jogo.acesso_jogador(1).get_score()));
					jogo.guarda_ranking("rank.txt", 10);
				}
				jogar = false;
			}
			else {
				if(passagens == 4) // termina por passar a vez
				{
					if(jogo.acesso_jogador(0).get_score() == jogo.acesso_jogador(1).get_score())
									{
										cout << "Os jogadores empataram!!" << endl;
										jogo.update_best_scores(Pontuacao(jogo.acesso_jogador(0).get_nome() + ", " + jogo.acesso_jogador(1).get_nome() , jogo.acesso_jogador(0).get_score()));
															jogo.guarda_ranking("rank.txt", 10);
									}
									else
					if(jogo.acesso_jogador(0).get_score() > jogo.acesso_jogador(1).get_score())
					{
						cout << "O vencedor é " << jogo.acesso_jogador(0).get_nome() << " . PARABENS!" << endl;
						jogo.update_best_scores(Pontuacao(jogo.acesso_jogador(0).get_nome(), jogo.acesso_jogador(0).get_score()));
						jogo.guarda_ranking("rank.txt", 10);
					}
					else
					{
						cout << "O vencedor é " << jogo.acesso_jogador(1).get_nome() << " . PARABENS!" << endl;
						jogo.update_best_scores(Pontuacao(jogo.acesso_jogador(1).get_nome(), jogo.acesso_jogador(1).get_score()));
						jogo.guarda_ranking("rank.txt", 10);
					}
					jogar = false;
				}
				else {

			i = (i + 1) % 2;
			jogo.show_tabuleiro();
			cout << "Vez do " << jogo.acesso_jogador(i).get_nome()<< endl;
			cout << "Letras na mao: " << jogo.mostra_mao(i)<<endl;
			cout << "Pontuacao actual: "  << jogo.acesso_jogador(i).get_score() <<endl <<endl;
			cout << "1) Jogar" <<endl;
			cout << "2) Trocar letras do saco" <<endl;
			cout << "3) Passar a vez" <<endl;
			cout << "4) Gravar o jogo" <<endl;
			cout << "5) Sair" << endl <<endl;
			cout << "O que deseja fazer? ";
			string opcao_submenu;
			cin >> opcao_submenu;
			int opcao_submenuf = opcoes(opcao_submenu, 1, 5);
			if(opcao_submenuf == 1)
			{
				bool palavra_certa = false;
				while(palavra_certa == false)
				{
					cout << "Palavra a formar: ";
					string pal, palavra;
					cin >> pal;
					palavra = to_uppers(pal);
					if(jogo.verifica_inicio())
					{
						if(jogo.verifica_palavra(palavra) && jogo.verif_pal_tabuleiro(palavra, 7 - palavra.size() / 2, 7, 'h', i))
						{
							cout << "Como o tabuleiro ainda se encontrava vazio," << endl << "a peça foi colocada automaticamente" << endl;
							jogo.coloca_palavra(palavra, 7 - palavra.size() / 2, 7, 'h', jogo.acesso_jogador(i).get_mao());
							jogo.completa_mao(i);
							int pontuacao = jogo.pont_palavra(palavra, 7 - palavra.size() / 2, 7, 'h');
							jogo.actualiza_pontuacao(pontuacao, i);
							cout << "Pontuação total: " << jogo.acesso_jogador(i).get_score() <<endl <<endl;
							palavra_certa = true;
							passagens = 0;
						}else
						{
							cout << "Jogada invalida!" << endl;
							cout << "O que pertende fazer?" << endl << "Precione 1 para continuar, o 2 para passar a vez!";
							string n_tente;
							int n_tent;
							cin >> n_tente;
							n_tent= opcoes(n_tente, 1, 2);
							if(n_tent == 2)
							{
								++passagens;
								palavra_certa = true;
							}
						}
					}else
					{
						cout << "Coordenadas vertical da primeira letra da palavra (<A – P>): ";
						string pos_v;
						cin >> pos_v;
						cout << "Coordenadas horizontal da primeira letra da palavra (<1 – 15>): ";
						string pos_h;
						cin >> pos_h;
						cout << "Orientação da palavra (<H , V>): ";
						string ori;
						cin >> ori;
						int horizontal = opcoes(pos_h, 1, 15) - 1;
						int vertical = pos_vert(pos_v);
						char orien = orient(ori);
						if(jogo.verif_pal_tabuleiro(palavra, horizontal, vertical, orien, i) && jogo.ver_tabuleiro(vertical, horizontal, orien) && jogo.verifica_tamanho(palavra, horizontal, vertical, orien) && jogo.verifica_posiblidade(palavra, horizontal, vertical, orien) && jogo.verifica_palavra(palavra))
						{
							cout << endl << "Palavra válida!" << endl;
							jogo.coloca_palavra(palavra, horizontal, vertical, orien, jogo.acesso_jogador(i).get_mao());
							int pontuacao = jogo.pont_palavra(palavra, horizontal, vertical, orien);
							jogo.completa_mao(i);
							cout << "Pontuação da palavra a formar " << pontuacao << endl;
							jogo.actualiza_pontuacao(pontuacao, i);
							cout << "Pontuação total: " << jogo.acesso_jogador(i).get_score() <<endl <<endl;
							palavra_certa = true;
							passagens = 0;
						}else
						{
							cout << "Jogada invalida!" << endl;
							cout << "O que pertende fazer?" << endl << "Precione 1 para continuar, o 2 para passar a vez!";
							string n_tente;
							unsigned n_tent;
							cin >> n_tente;
							n_tent= opcoes(n_tente, 1, 2);
							if(n_tent == 2)
							{
								palavra_certa = true;
								++passagens;
							}

						}

					}}
			}
			else
			if(opcao_submenuf == 2)
			{
				passagens = 0;
				bool continuar = false;
				while(continuar == false)
				{
				cout << "Quantas letras pretende trocar? ";
				string n_letras_troca;
				cin >> n_letras_troca;
				int n_letras;
				n_letras = opcoes(n_letras_troca, 0, 7);
				cout << "Indique as letras que pretende trocar (sem espacos): ";
				string letras_troca;
				cin >> letras_troca;
				cout << "Por favor volte a repetir as letras que pertende trocar (sem espaços): ";
				string letras_trocar2;
				cin >> letras_trocar2;
				if(letras_troca == letras_trocar2)
				{
					letras_troca = to_uppers(letras_troca);
					jogo.troca_mao(letras_troca, i);
					continuar = true;
				}
				else
					cout << "Letras erradas. Volte a tentar!" << endl << endl;
				}
			}
			else
				if(opcao_submenuf == 3)
			{
				++passagens;
			}
				else
					if(opcao_submenuf ==4)
			{

						cout << "Indique o nome para guardar o jogo: ";
						string nome;
						cin >> nome;
						jogo.nome_jogo(nome);
						nome = nome + ".txt";
						jogo.guardar_jogo(nome);
						jogo.update_jogos("vec_jogo.txt");
						jogar = false;
			}
					else
						if(opcao_submenuf == 5)
			{
				cout << "Tem a certeza que pertende sair? " << endl << "Se sim pressione 1, caso contrario pressione 2! ";
				string dec;
				cin >> dec;
				unsigned int decis = opcoes(dec, 1, 2);
				if(decis == 1)
				{
				jogar = false;
				if(jogo.acesso_jogador(0).get_score() == jogo.acesso_jogador(1).get_score())
								{
									cout << "Os jogadores empataram!!" << endl;
									jogo.update_best_scores(Pontuacao(jogo.acesso_jogador(0).get_nome() + ", " + jogo.acesso_jogador(1).get_nome() , jogo.acesso_jogador(0).get_score()));
														jogo.guarda_ranking("rank.txt", 10);
								}
								else
				if(jogo.acesso_jogador(0).get_score() > jogo.acesso_jogador(1).get_score())
				{
					cout << "O vencedor é " << jogo.acesso_jogador(0).get_nome() << ". PARABENS!" << endl;
					jogo.update_best_scores(Pontuacao(jogo.acesso_jogador(0).get_nome(), jogo.acesso_jogador(0).get_score()));
					jogo.guarda_ranking("rank.txt", 10);
				}
				else
				{
					cout << "O vencedor é " << jogo.acesso_jogador(1).get_nome() << ". PARABENS!" << endl;
					jogo.update_best_scores(Pontuacao(jogo.acesso_jogador(1).get_nome(), jogo.acesso_jogador(1).get_score()));
					jogo.guarda_ranking("rank.txt", 10);
				}
			}else {
				if(i==1)
					i = 0;
				else
					i = 1;
			}

			}

		}

	}
		}
	}
		else
			if(opcao_menu1 == 3)
	{
		jogo.mostrar_ranking();

	}

	return 0;
}






