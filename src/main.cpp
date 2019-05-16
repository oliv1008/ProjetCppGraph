#include "header/CGraphe.h"
#include <iostream>

using namespace std;

void test()
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
}

void testGraphe()
{
	CGraphe graph;
	
	graph.GRPAjouterSommet(1);
	graph.GRPAjouterSommet(2);
	graph.GRPAjouterSommet(3);
		
	graph.GRPAjouterArc(1, 2);
	graph.GRPAjouterArc(2, 3);
	graph.GRPAjouterArc(3, 1);
		
	graph.GRPAjouterSommet(4);
	graph.GRPAjouterArc(2, 4);
	graph.GRPAjouterArc(4, 2);
	graph.GRPAjouterArc(2, 1);
	graph.GRPAjouterArc(3, 2);
		
		
	graph.GRPAfficherGraphe();
	cout << "=======================" << endl;
	
	try {
		graph.GRPEnleverSommet(2);
	}catch(CException EXCErreur){
		switch(EXCErreur.EXCLireErreur()){
			case ERR_NUMSOM : cerr << "Erreur : ce sommet n'existe pas" << endl; break;
			case ERR_REALLOC : cerr << "Erreur realloc" << endl; exit(0);
			default : cerr << "Erreur inconnue" << endl; exit(0);
		}
	}
	
	try {
		graph.GRPEnleverArc(3, 1);
	}catch(CException EXCErreur){
		switch(EXCErreur.EXCLireErreur()){
			case ERR_NUMSOM : cerr << "Erreur : ce sommet n'existe pas" << endl; break;
			case ERR_REALLOC : cerr << "Erreur realloc" << endl; exit(0);
			default : cerr << "Erreur inconnue" << endl; exit(0);
		}
	}
	graph.GRPAfficherGraphe();
	cout << "=======================" << endl;
}

int main(int argc, char ** argv)
{
	test();
	//testGraphe();
	return 0;
}