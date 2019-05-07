#ifndef CPARSERGRAPHE
#define CPARSERGRAPHE

#include <header/CParser.h>
#include <header/CException.h>
#include <fstream>
#include <iostream>

using namespace std;

#define ERR_FORMAT    1
#define ERR_NUMERIQUE 2

class CParserGraphe : private CParser {

	private :


	public :
	
		static void PAGParserGraphe(const char * pcChemin, unsigned int &uiNbSommets, unsigned int &uiNbArcs, unsigned int * &puiNumeroSommets, \
									unsigned int ** &puiTabArc)
		{
			ifstream fichier(pcChemin, ios::in);  // on ouvre le fichier en lecture
 
			if(fichier)  // si l'ouverture a réussi
			{       
				// instructions
				char ligne[256];
				char resultat[256];
				
				//On récupère le nombre de sommets
				fichier >> ligne;
				cout << ligne << endl;
				CParser::PARSeparateString('=', ligne, resultat);
				
				if (!CParser::PARIsStringEqual(ligne, "NBSommets"))
				{
					/*CException ErrFormat(ERR_FORMAT);
					throw ErrFormat;*/
				}
				else if (!CParser::PARIsStringANumericalValue(resultat))
				{
					/*CException ErrFormat(ERR_NUMERIQUE);
					throw ErrFormat;*/
				}
				
				uiNbSommets = atoi(resultat);
				
				//On récupère le nombre d'arcs
				fichier >> ligne;
				cout << ligne << endl;
				CParser::PARSeparateString('=', ligne, resultat);
				
				if (!CParser::PARIsStringEqual(ligne, "NBArcs"))
				{
					/*CException ErrFormat(ERR_FORMAT);
					throw ErrFormat;*/
				}
				else if (!CParser::PARIsStringANumericalValue(resultat))
				{
					/*CException ErrNumerique(ERR_NUMERIQUE);
					throw ErrNumerique;*/
				}

				uiNbArcs = atoi(resultat);
				
				//On récupère la ligne "Sommets=["
				fichier >> ligne;
				cout << ligne << endl;
				if (!CParser::PARIsStringEqual(ligne, "Sommets=["))
				{
					/*CException ErrFormat(ERR_FORMAT);
					throw ErrFormat;*/
				}
				
				//On remplit le tableau
				puiNumeroSommets = (unsigned int *)malloc(uiNbSommets * sizeof(unsigned int));
				for (unsigned int uiBoucle = 0; uiBoucle < uiNbSommets; uiBoucle++)
				{
					//On récupère l'élement
					fichier >> ligne;
					cout << ligne << endl;
					if (CParser::PARIsStringEqual(ligne, "]"))
					{
						/*CException ErrDimension(ERR_FORMAT);
						throw ErrDimension;*/
					}
					else if (!CParser::PARIsStringANumericalValue(ligne))
					{
						/*CException ErrNumerique(ERR_NUMERIQUE);
						throw ErrNumerique;*/
					}
					
					puiNumeroSommets[uiBoucle] = atoi(ligne);
				}
				
				fichier >> ligne;
				cout << ligne << endl;
				if (!CParser::PARIsStringEqual(ligne, "]"))
				{
					/*CException ErrDimension(ERR_FORMAT);
					throw ErrDimension;*/
				}
				
				//On récupère la ligne "Arcs=["
				fichier >> ligne;
				cout << ligne << endl;
				if (!CParser::PARIsStringEqual(ligne, "Arcs=["))
				{
					/*CException ErrFormat(ERR_FORMAT);
					throw ErrFormat;*/
				}
				
				//On remplit le tableau
				puiTabArc = (unsigned int **)malloc(uiNbSommets * sizeof(unsigned int *));
				for (unsigned int uiBoucle = 0; uiBoucle < uiNbArcs; uiBoucle++)
				{
					puiTabArc[uiBoucle] = (unsigned int *)malloc(2 * sizeof(unsigned int));
				}
				
				for (unsigned int uiBoucle = 0; uiBoucle < uiNbSommets; uiBoucle++)
				{
					//On récupère l'élement
					fichier >> ligne;
					cout << ligne << endl;
					if (CParser::PARIsStringEqual(ligne, "]"))
					{
						/*CException ErrDimension(ERR_FORMAT);
						throw ErrDimension;*/
					}
					CParser::PARSeparateString('=', ligne, resultat);
					puiTabArc[uiBoucle][0] = atoi(resultat);
					
					fichier >> ligne;
					cout << ligne << endl;
					if (CParser::PARIsStringEqual(ligne, "]"))
					{
						/*CException ErrDimension(ERR_FORMAT);
						throw ErrDimension;*/
					}
					CParser::PARSeparateString('=', ligne, resultat);
					puiTabArc[uiBoucle][1] = atoi(resultat);
				}
				
				fichier >> ligne;
				cout << ligne << endl;
				if (!CParser::PARIsStringEqual(ligne, "]"))
				{
					/*CException ErrDimension(ERR_FORMAT);
					throw ErrDimension;*/
				}

				fichier.close();  // on ferme le fichier
			}
			else  // sinon
			{
				cerr << "Impossible d'ouvrir le fichier !" << endl;
			}
		}

};

#endif