#include "header/CGraphe.h"
#include <iostream>

using namespace std;

void test(char ** argv)
{
	try {
		CGraphe GRPGraphe(argv[1]);
		GRPGraphe.GRPAfficherGraphe();
		cout << "Copie de GRPGraphe" << endl;
		CGraphe GRPGrapheCopie = GRPGraphe;
		cout << "Inversion de GRPGrapheCopie" << endl;
		GRPGrapheCopie.GRInverserGraphe();
		cout << "Supression du somet 63 dans GRPGrapheCopie" << endl;
		GRPGrapheCopie.GRPEnleverSommet(63);
		cout << "Affichage GRPGrapheCopie" << endl;
		GRPGrapheCopie.GRPAfficherGraphe();
		
		CGraphe GRPGraphe2(argv[1]);
		GRPGraphe2.GRPAfficherGraphe();
	} catch(CException EXCErreur){
		switch(EXCErreur.EXCLireErreur()){
			case ERR_FORMAT : cerr << "Erreur format" << endl; break;
			case ERR_NUMERIQUE : cerr << "Erreur numérique" << endl; break;
			case ERR_FICHIER : cerr << "Erreur fichier" << endl; break;
			default : cerr << "Erreur inconnue" << endl; break;
		}
	}
}

int main(int argc, char ** argv)
{
	test(argv);
	/*if (argc != 2)
	{
		cout << "Nombre d'argument incorrect" << endl;
		cout << "Utilisation : ./ProjetCppGraphe [Chemin vers un fichier valide]" << endl;
		return -1;
	}
	
	try {
		CGraphe GRPGraphe(argv[1]);
		GRPGraphe.GRPAfficherGraphe();
		CGraphe GRPGrapheCopie;
		GRPGrapheCopie = GRPGraphe;
		GRPGrapheCopie.GRInverserGraphe();
		cout << "======================" << endl;
		GRPGrapheCopie.GRPAfficherGraphe();
	} catch(CException EXCErreur){
		switch(EXCErreur.EXCLireErreur()){
			case ERR_FORMAT : cerr << "Erreur format" << endl; break;
			case ERR_NUMERIQUE : cerr << "Erreur numérique" << endl; break;
			case ERR_FICHIER : cerr << "Erreur fichier" << endl; break;
			default : cerr << "Erreur inconnue" << endl; break;
		}
		return -1;
	}
	*/
	return 0;
}