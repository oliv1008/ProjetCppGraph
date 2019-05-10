#include "header/CGraphe.h"
#include <iostream>

using namespace std;

void test()
{
	/*CSommet * pSOMSommet1 = new CSommet(1);
	CArc * pARCArc1 = new CArc(2);
	CSommet * pSOMSommet2 = new CSommet(2);
	CArc * pARCArc2 = new CArc(1);
	CSommet * pSOMSommet3 = new CSommet(3);
	CArc * pARCArc3 = new CArc(3);
	CArc * pARCArc4 = new CArc(1);
	
	cout << "Ajout des arcs" << endl << endl;
	pSOMSommet1->SOMAjouterArcPartant(pARCArc1);
	pSOMSommet2->SOMAjouterArcArrivant(pARCArc2);
	pSOMSommet1->SOMAjouterArcPartant(pARCArc3);
	pSOMSommet3->SOMAjouterArcArrivant(pARCArc4);
	
	cout << "Affichage des sommets" << endl;
	pSOMSommet1->SOMAfficherSommet();
	pSOMSommet2->SOMAfficherSommet();
	pSOMSommet3->SOMAfficherSommet();
	
	
	cout << "On supprime l'arc de S1 vers S2" << endl << endl;
	pSOMSommet1->SOMEnleverArcPartant(2);
	pSOMSommet2->SOMEnleverArcArrivant(1);
	
	cout << "Affichage des sommets" << endl;
	pSOMSommet1->SOMAfficherSommet();
	pSOMSommet2->SOMAfficherSommet();
	pSOMSommet3->SOMAfficherSommet();
	
	delete pSOMSommet1;
	delete pSOMSommet2;
	delete pARCArc1;
	delete pARCArc2;*/
	
	CGraphe * pGRPGraphe = new CGraphe("fichier.txt");
	delete pGRPGraphe;
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
	//test();
	testGraphe();
	return 0;
}