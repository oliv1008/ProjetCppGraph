#include "header/CGraphe.h"
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
	try {
		CGraphe pGRPGraphe("fichier.txt");
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
		exit(0);
	}

	return 0;
}