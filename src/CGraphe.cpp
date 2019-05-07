#include "header/CGraphe.h"
#include "header/CParserGraphe.h"
#include <cstdlib>
#include <iostream>

using namespace std;

CGraphe::CGraphe()
{
	pSOMGRPTabSommet = nullptr;
	uiNombreSommet = 0;
}

CGraphe::CGraphe(const char * pcChemin)
{
	unsigned int uiNbSommets;
	unsigned int uiNbArcs;
	unsigned int * puiTabSommets;
	unsigned int ** puiTabArcs;
	
	CParserGraphe::PAGParserGraphe(pcChemin, uiNbSommets, uiNbArcs, puiTabSommets, puiTabArcs);
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

void CGraphe::GRPAjouterSommet(unsigned int uiNumero)
{
	CSommet **pSOMTemp;
	
	pSOMTemp = (CSommet **)realloc(pSOMGRPTabSommet, (uiNombreSommet + 1) * sizeof(CSommet *));
	
	if (pSOMTemp != nullptr)
	{
		pSOMGRPTabSommet = pSOMTemp;
		pSOMGRPTabSommet[uiNombreSommet] = new CSommet(uiNumero);
		uiNombreSommet++;
	}
	else
	{
		// EXCEPTION
		cout << "erreur reallocation lors de l'ajout d'un sommet" << endl;
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
			// On supprime tous les arcs liés à ce sommet
			// from CE SOMMET to LES AUTRES
			for(unsigned int uiBoucleSom = 0; uiBoucleSom < pSOMGRPTabSommet[uiBoucle]->SOMLireCompteurArcPartant(); uiBoucleSom++)
			{
				cout << "Suppression de l'arc (from " << uiNumero << " to " << pSOMGRPTabSommet[uiBoucle]->SOMLireArcPartant()[uiBoucleSom]->ARCLireDestination() << ")\n";
				GRPEnleverArc(uiNumero, pSOMGRPTabSommet[uiBoucle]->SOMLireArcPartant()[uiBoucleSom]->ARCLireDestination());
			}
			// from LES AUTRES to CE SOMMET
			for(unsigned int uiBoucleSom = 0; uiBoucleSom < pSOMGRPTabSommet[uiBoucle]->SOMLireCompteurArcArrivant(); uiBoucleSom++)
			{
				cout << "Suppression de l'arc (from " << pSOMGRPTabSommet[uiBoucle]->SOMLireArcArrivant()[uiBoucleSom]->ARCLireDestination() << " to " << uiNumero << ")\n";
				GRPEnleverArc(pSOMGRPTabSommet[uiBoucle]->SOMLireArcArrivant()[uiBoucleSom]->ARCLireDestination(), uiNumero);
			}
			
			// On supprime le sommet et on réarrange le tableau
			delete pSOMGRPTabSommet[uiBoucle];
			
			for (unsigned int uiBoucleDel = uiBoucle; uiBoucleDel < uiNombreSommet - 1; uiBoucleDel++)
			{
				pSOMGRPTabSommet[uiBoucleDel] = pSOMGRPTabSommet[uiBoucleDel + 1];
			}
			
			// On réalloue le tableau
			pSOMTemp = (CSommet **)realloc(pSOMGRPTabSommet, (uiNombreSommet - 1) * sizeof(CSommet *));
			
			if (pSOMTemp != nullptr || uiNombreSommet == 1)
			{
				pSOMGRPTabSommet = pSOMTemp;
				uiNombreSommet--;
				bSommetDel = false;
			}
			else
			{
				// EXCEPTION
				cout << "erreur reallocation lors de la suppression d'un sommet" << endl;
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

void CGraphe::GRPEnleverArc(unsigned int uiFrom, unsigned int uiTo)
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
	
	pSOMGRPTabSommet[uiIndiceFrom]->SOMEnleverArcPartant(uiTo);

	pSOMGRPTabSommet[uiIndiceTo]->SOMEnleverArcArrivant(uiFrom);
}

void CGraphe::GRPAfficherGraphe()
{
	for(unsigned int uiBoucle = 0; uiBoucle < uiNombreSommet; uiBoucle++)
	{
		pSOMGRPTabSommet[uiBoucle]->SOMAfficherSommet();
	}
}