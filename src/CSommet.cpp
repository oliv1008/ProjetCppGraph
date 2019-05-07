#include <header/CSommet.h>
#include <cstdlib>
#include <iostream>

using namespace std;

CSommet::CSommet()
{
	uiSOMNumero = 0;
	pARCSOMArrivant = nullptr;
	pARCSOMPartant = nullptr;
	uiCompteurArcArrivant = 0;
	uiCompteurArcPartant = 0;
}

CSommet::CSommet(unsigned int uiNumero)
{
	uiSOMNumero = uiNumero;
	pARCSOMArrivant = nullptr;
	pARCSOMPartant = nullptr;
	uiCompteurArcArrivant = 0;
	uiCompteurArcPartant = 0;
}

CSommet::~CSommet()
{
	for (unsigned int uiBoucle = 0; uiBoucle < uiCompteurArcArrivant; uiBoucle++)
	{
		delete pARCSOMArrivant[uiBoucle];
	}
	free(pARCSOMArrivant);
	
	for (unsigned int uiBoucle = 0; uiBoucle < uiCompteurArcPartant; uiBoucle++)
	{
		delete pARCSOMPartant[uiBoucle];
	}
	free(pARCSOMPartant);
}

unsigned int CSommet::SOMLireNumero()
{
	return uiSOMNumero;
}

void CSommet::SOMModifierNumero(unsigned int uiNumero)
{
	uiSOMNumero = uiNumero;
}

void CSommet::SOMAjouterArcArrivant(CArc * pARCArc)
{
	CArc ** pARCTemp;
	
	pARCTemp = (CArc**)realloc(pARCSOMArrivant, sizeof(CArc*) * (uiCompteurArcArrivant + 1));
	
	if (pARCTemp != nullptr)
	{
		pARCSOMArrivant = pARCTemp;
		pARCSOMArrivant[uiCompteurArcArrivant] = pARCArc;
		uiCompteurArcArrivant++;
	}
	else
	{
		cout << "erreur reallocation lors de l'ajout d'un arc partant" << endl;
	}
}

void CSommet::SOMEnleverArcArrivant(unsigned int uiDestination)
{
	CArc ** pARCTemp;
	bool bArcDel = true;
	
	for (unsigned int uiBoucle = 0; uiBoucle < uiCompteurArcArrivant && bArcDel; uiBoucle++)
	{
		if (pARCSOMArrivant[uiBoucle]->ARCLireDestination() == uiDestination)
		{
			//On supprime l'arc et on réarrange le tableau
			delete pARCSOMArrivant[uiBoucle];
			for (unsigned int uiBoucleDel = uiBoucle; uiBoucleDel < uiCompteurArcArrivant - 1; uiBoucleDel++)
			{
				pARCSOMArrivant[uiBoucleDel] = pARCSOMArrivant[uiBoucleDel + 1];
			}
			//On réalloue le tableau
			pARCTemp = (CArc**)realloc(pARCSOMArrivant, sizeof(CArc*) * (uiCompteurArcArrivant - 1));
			
			if (pARCTemp != nullptr || uiCompteurArcArrivant == 1)
			{
				pARCSOMArrivant = pARCTemp;
				uiCompteurArcArrivant--;
				bArcDel = false;
			}
			else
			{
				cout << "erreur reallocation lors de la suppression d'un arc arrivant" << endl;
			}
		}
	}
}

void CSommet::SOMAjouterArcPartant(CArc * pARCArc)
{
	CArc ** pARCTemp;
	
	pARCTemp = (CArc**)realloc(pARCSOMPartant, sizeof(CArc*) * (uiCompteurArcPartant + 1));
	
	if (pARCTemp != nullptr)
	{
		pARCSOMPartant = pARCTemp;
		pARCSOMPartant[uiCompteurArcPartant] = pARCArc;
		uiCompteurArcPartant++;
	}
	else
	{
		cout << "erreur reallocation lors de l'ajout d'un arc partant" << endl;
	}
}

void CSommet::SOMEnleverArcPartant(unsigned int uiDestination)
{
	CArc ** pARCTemp;
	bool bArcDel = true;
	
	for (unsigned int uiBoucle = 0; uiBoucle < uiCompteurArcPartant && bArcDel; uiBoucle++)
	{
		if (pARCSOMPartant[uiBoucle]->ARCLireDestination() == uiDestination)
		{
			//On supprime l'arc et on réarrange le tableau
			delete pARCSOMPartant[uiBoucle];
			for (unsigned int uiBoucleDel = uiBoucle; uiBoucleDel < uiCompteurArcPartant - 1; uiBoucleDel++)
			{
				pARCSOMPartant[uiBoucleDel] = pARCSOMPartant[uiBoucleDel + 1];
			}
			//On réalloue le tableau
			pARCTemp = (CArc**)realloc(pARCSOMPartant, sizeof(CArc*) * (uiCompteurArcPartant - 1));
			
			if (pARCTemp != nullptr || uiCompteurArcPartant == 1)
			{
				pARCSOMPartant = pARCTemp;
				uiCompteurArcPartant--;
				bArcDel = false;
			}
			else
			{
				cout << "erreur reallocation lors de la suppression d'un arc partant" << endl;
			}
		}
	}
}

void CSommet::SOMAfficherSommet()
{
	cout << "S" << uiSOMNumero << endl;
	cout << "Arc arrivant :" << endl;
	for (unsigned int uiBoucleA = 0; uiBoucleA < uiCompteurArcArrivant; uiBoucleA++)
	{
		cout << "\tArc à destination de " << pARCSOMArrivant[uiBoucleA]->ARCLireDestination() << endl;
	}
	cout << "Arc partant :" << endl;
	for (unsigned int uiBoucleP = 0; uiBoucleP < uiCompteurArcPartant; uiBoucleP++)
	{
		cout << "\tArc à destination de " << pARCSOMPartant[uiBoucleP]->ARCLireDestination() << endl;
	}
}