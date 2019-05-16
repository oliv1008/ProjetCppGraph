#include "header/CGraphe.h"
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
	if (argc != 2)
	{
		cout << "Nombre d'argument incorrect" << endl;
		cout << "Utilisation : ./ProjetCppGraphe [Chemin vers un fichier valide]" << endl;
		return -1;
	}
	
	try {
		CGraphe pGRPGraphe(argv[1]);
		pGRPGraphe.GRPAfficherGraphe();
		pGRPGraphe.GRInverserGraphe();
		cout << "======================" << endl;
		pGRPGraphe.GRPAfficherGraphe();
	} catch(CException EXCErreur){
		switch(EXCErreur.EXCLireErreur()){
			case ERR_FORMAT : cerr << "Erreur format" << endl; break;
			case ERR_NUMERIQUE : cerr << "Erreur numérique" << endl; break;
			case ERR_FICHIER : cerr << "Erreur fichier" << endl; break;
		}
		
		return -1;
	}

	return 0;
}