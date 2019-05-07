#include "header/CGraphe.h"
#include <cstdlib>
#include <iostream>

using namespace std;

CGraphe::CGraphe()
{
	pSOMGRPTabSommet = nullptr;
	uiNombreSommet = 0;
}

CGraphe::~CGraphe()
{
	for (unsigned int uiBoucle = 0; uiBoucle < uiNombreSommet; uiBoucle++)
	{
		delete pSOMGRPTabSommet[uiBoucle];
	}
	free(pSOMGRPTabSommet);
}

CSommet * CGraphe::GRPLireSommet(unsigned int uiNumero)
{
	return pSOMGRPTabSommet[uiNumero];
}

void CGraphe::GRPAjouterSommet(CSommet *pSOMSommet)
{
	CSommet **pSOMTemp;
	
	pSOMTemp = (CSommet **)realloc(pSOMGRPTabSommet, (uiNombreSommet + 1) * sizeof(CSommet *));
	
	if (pSOMTemp != nullptr)
	{
		pSOMGRPTabSommet = pSOMTemp;
		pSOMGRPTabSommet[uiNombreSommet] = pSOMSommet;
		uiNombreSommet++;
	}
	else
	{
		// EXCEPTION
		cout << "erreur reallocation lors de l'ajout d'un arc partant" << endl;
	}
}

void CGraphe::GRPEnleverSommet(unsigned int uiNumero)
{
	CSommet ** pSOMTemp;
	bool bSommetDel = true;
	
	for (unsigned int uiBoucle = 0; uiBoucle < uiNombreSommet && bSommetDel; uiBoucle++)
	{
		if (pSOMGRPTabSommet[uiBoucle]->SOMLireNumero() == uiNumero)
		{
			// On supprime le sommet et on réarrange le tableau
			delete pSOMGRPTabSommet[uiBoucle];
			for (unsigned int uiBoucleDel = uiBoucle; uiBoucleDel < uiNombreSommet - 1; uiBoucleDel++)
			{
				pSOMGRPTabSommet[uiBoucleDel] = pSOMGRPTabSommet[uiBoucleDel + 1];
			}
			// On réalloue le tableau
			pSOMTemp = (CSommet **)realloc(pSOMGRPTabSommet, (uiNombreSommet - 1) * sizeof(CSommet *));
			
			if (pSOMTemp != nullptr)
			{
				pSOMGRPTabSommet = pSOMTemp;
				uiNombreSommet--;
				bSommetDel = false;
			}
			else
			{
				// EXCEPTION
				cout << "erreur reallocation lors de la suppression d'un arc arrivant" << endl;
			}
		}
	}
}

void CGraphe::GRPAjouterArc(unsigned int uiFrom, unsigned int uiTo)
{
	bool bTrouveFrom = false, bTrouveTo = false;
	unsigned int uiIndiceFrom = 0, uiIndiceTo = 0;
	
	for (unsigned int uiBoucle = 0; uiBoucle < uiNombreSommet; uiBoucle++)
	{
		if (pSOMGRPTabSommet[uiBoucle]->SOMLireNumero() == uiFrom)
		{
			uiIndiceFrom = uiBoucle;
			bTrouveFrom = true;
		}
		
		if (pSOMGRPTabSommet[uiBoucle]->SOMLireNumero() == uiTo)
		{
			uiIndiceTo = uiBoucle;
			bTrouveTo = true;
		}
	}
	
	if(!(bTrouveFrom && bTrouveTo)){
		// EXCEPTION
		cerr << "Erreur : calisse tu t'es planté dans les numéros de sommets" << endl;
	}
	
	pSOMGRPTabSommet[uiIndiceFrom]->SOMAjouterArcPartant(new CArc(uiTo));

	pSOMGRPTabSommet[uiIndiceTo]->SOMAjouterArcArrivant(new CArc(uiFrom));
}