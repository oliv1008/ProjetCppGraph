#include "header/CGraphe.h"
#include "header/CParser.h"
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
	char pcBalise[256];
	char pcResultat[256];
	CParser PARParserGraphe(pcChemin);
	
	PARParserGraphe.PARLireLigne(pcBalise, pcResultat);
	if (!CParser::PARIsStringEqual(pcBalise, "NBSommets"))
	{
		/*CException ErrFormat(ERR_FORMAT);
		throw ErrFormat;*/
	}
	else if (!CParser::PARIsStringANumericalValue(pcResultat))
	{
		/*CException ErrFormat(ERR_NUMERIQUE);
		throw ErrFormat;*/
	}
	uiNbSommets = atoi(pcResultat);
	
	PARParserGraphe.PARLireLigne(pcBalise, pcResultat);
	if (!CParser::PARIsStringEqual(pcBalise, "NBArcs"))
	{
		/*CException ErrFormat(ERR_FORMAT);
		throw ErrFormat;*/
	}
	else if (!CParser::PARIsStringANumericalValue(pcResultat))
	{
		/*CException ErrNumerique(ERR_NUMERIQUE);
		throw ErrNumerique;*/
	}
	uiNbArcs = atoi(pcResultat);
	
	PARParserGraphe.PARLireLigne(pcBalise, pcResultat);
	if (!CParser::PARIsStringEqual(pcBalise, "Sommets=["))
	{
		/*CException ErrFormat(ERR_FORMAT);
		throw ErrFormat;*/
	}
	
	//On remplit le tableau
	puiTabSommets = (unsigned int *)malloc(uiNbSommets * sizeof(unsigned int));
	for (unsigned int uiBoucle = 0; uiBoucle < uiNbSommets; uiBoucle++)
	{
		//On récupère l'élement
		PARParserGraphe.PARLireLigne(pcBalise, pcResultat);
		if (CParser::PARIsStringEqual(pcBalise, "]"))
		{
			/*CException ErrDimension(ERR_FORMAT);
			throw ErrDimension;*/
		}
		else if (!CParser::PARIsStringANumericalValue(pcBalise))
		{
			/*CException ErrNumerique(ERR_NUMERIQUE);
			throw ErrNumerique;*/
		}
					
		puiTabSommets[uiBoucle] = atoi(pcResultat);
	}
				
	PARParserGraphe.PARLireLigne(pcBalise, pcResultat);
	if (!CParser::PARIsStringEqual(pcBalise, "]"))
	{
		/*CException ErrDimension(ERR_FORMAT);
		throw ErrDimension;*/
	}
	
	//On récupère la ligne "Arcs=["
	PARParserGraphe.PARLireLigne(pcBalise, pcResultat);
	if (!CParser::PARIsStringEqual(pcBalise, "Arcs=["))
	{
		/*CException ErrFormat(ERR_FORMAT);
		throw ErrFormat;*/
	}
	//On remplit le tableau
	puiTabArcs = (unsigned int **)malloc(uiNbSommets * sizeof(unsigned int *));
	for (unsigned int uiBoucle = 0; uiBoucle < uiNbArcs; uiBoucle++)
	{
		puiTabArcs[uiBoucle] = (unsigned int *)malloc(2 * sizeof(unsigned int));
	}
	for (unsigned int uiBoucle = 0; uiBoucle < uiNbSommets; uiBoucle++)
	{
		//On récupère l'élement
		PARParserGraphe.PARLireLigne(pcBalise, pcResultat);
		if (CParser::PARIsStringEqual(pcBalise, "]"))
		{
			/*CException ErrDimension(ERR_FORMAT);
			throw ErrDimension;*/
		}
		puiTabArcs[uiBoucle][0] = atoi(pcResultat);
			
		PARParserGraphe.PARLireLigne(pcBalise, pcResultat);
		if (CParser::PARIsStringEqual(pcBalise, "]"))
		{
			/*CException ErrDimension(ERR_FORMAT);
			throw ErrDimension;*/
		}
		puiTabArcs[uiBoucle][1] = atoi(pcResultat);
	}
	
	PARParserGraphe.PARLireLigne(pcBalise, pcResultat);
	if (!CParser::PARIsStringEqual(pcBalise, "]"))
	{
		/*CException ErrDimension(ERR_FORMAT);
		throw ErrDimension;*/
	}
	
	//Les données du fichiers ont été récupérées sans problèmes, on créer le graphe
	
	pSOMGRPTabSommet = nullptr;
	uiNombreSommet = 0;
	
	for (unsigned int uiBoucle = 0; uiBoucle < uiNbSommets; uiBoucle++)
	{
		GRPAjouterSommet(new CSommet(puiTabSommets[uiBoucle]));
	}
	for (unsigned int uiBoucle = 0; uiBoucle < uiNbSommets; uiBoucle++)
	{
		GRPAjouterArc(puiTabArcs[uiBoucle][0], puiTabArcs[uiBoucle][1]);
	}
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