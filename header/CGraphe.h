#ifndef CGRAPHE 
#define CGRAPHE

#include "header/CSommet.h"
#include "header/CParser.h"

// Codes d'exceptions
#define ERR_FORMAT    	1
#define ERR_NUMERIQUE 	2
#define ERR_REALLOC		4
#define ERR_NUMSOM		5
#define ERR_DOUBLON		6

class CGraphe
{
	private:

		CSommet ** pSOMGRPTabSommet;
		unsigned int uiNombreSommet;
		
	public:
	
		// Constructeurs & Destructeur
		CGraphe();
		CGraphe(const char * pcChemin);
		~CGraphe();
		
		// Accesseurs
		CSommet * GRPLireSommet(unsigned int uiNumero);
		
		// Methodes
		bool GRPContientSommet(unsigned int uiNumero);
		void GRPAjouterSommet(unsigned int uiNumero);
		void GRPEnleverSommet(unsigned int uiNumero);
		bool GRPContientArc(unsigned int uiFrom, unsigned int uiTo);
		void GRPAjouterArc(unsigned int uiFrom, unsigned int uiTo);
		void GRPEnleverArc(unsigned int uiFrom, unsigned int uiTo);
		void GRInverserGraphe();
		void GRPAfficherGraphe();
};

#endif