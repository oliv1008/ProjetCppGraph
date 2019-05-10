#include <cstdlib>
#include <iostream>
#include "header/CGraphe.h"

#define ERR_REALLOC		4
#define ERR_NUMSOM		5


using namespace std;

/********* CONSTRUCTEURS *********/
/** Constructeur par défaut **/
CGraphe::CGraphe()
{
	pSOMGRPTabSommet = nullptr;
	uiNombreSommet = 0;
}

/** Constructeur depuis un fichier **/
CGraphe::CGraphe(const char * pcChemin)
{
	unsigned int uiNbSommets;
	unsigned int uiNbArcs;
	unsigned int * puiTabSommets;
	unsigned int ** puiTabArcs;
	
	CParserGraphe::PAGParserGraphe(pcChemin, uiNbSommets, uiNbArcs, puiTabSommets, puiTabArcs);
}
/********************************/

/********** DESTRUCTEUR *********/ 
CGraphe::~CGraphe()
{
	for (unsigned int uiBoucle = 0; uiBoucle < uiNombreSommet; uiBoucle++)
	{
		delete pSOMGRPTabSommet[uiBoucle];
	}
	free(pSOMGRPTabSommet);
}
/********************************/

/********** ACCESSEURS **********/ 
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
		CException ErrRealloc(ERR_REALLOC);
		throw ErrRealloc;
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
			unsigned int uiArcsPartants = pSOMGRPTabSommet[uiBoucle]->SOMLireCompteurArcPartant();
			unsigned int uiArcsArrivants = pSOMGRPTabSommet[uiBoucle]->SOMLireCompteurArcArrivant();
			
			cout << "[GRPEnleverSommet] Sommet : " << uiNumero << endl;
			cout << "[GRPEnleverSommet] Arcs partants : " << uiArcsPartants << endl;
			cout << "[GRPEnleverSommet] Arcs arrivants : " << uiArcsArrivants << endl;
			
			// Arcs partants (from this, to other)
			for(unsigned int uiBoucleSom = 0; uiBoucleSom < uiArcsPartants; uiBoucleSom++)
			{
				GRPEnleverArc(uiNumero, pSOMGRPTabSommet[uiBoucle]->SOMLireArcPartant()[0]->ARCLireDestination());
			}
			
			// Arcs arrivant (from other, to this)
			for(unsigned int uiBoucleSom = 0; uiBoucleSom < uiArcsArrivants; uiBoucleSom++)
			{
				GRPEnleverArc(pSOMGRPTabSommet[uiBoucle]->SOMLireArcArrivant()[0]->ARCLireDestination(), uiNumero);
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
				CException ErrRealloc(ERR_REALLOC);
				throw ErrRealloc;
			}
		}
	}
}
/*******************************/ 

/*********** METHODES **********/
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
		CException ErrNumSom(ERR_NUMSOM);
		throw ErrNumSom;
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
		CException ErrNumSom(ERR_NUMSOM);
		throw ErrNumSom;
	}
	
	cout << "[GRPEnleverArc] Suppression de l'arc (from " << uiFrom << " to " << uiTo << ")" << endl;
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
/*******************************/ 