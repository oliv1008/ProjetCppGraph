#ifndef CGRAPHE 
#define CGRAPHE

#include "header/CSommet.h"

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
		
		// Setter & Getter
		CSommet * GRPLireSommet(unsigned int uiNumero);
		void GRPAjouterSommet(CSommet *pSOMSommet);
		void GRPEnleverSommet(unsigned int uiNumero);
		
		// Methodes
		void GRPAjouterArc(unsigned int uiFrom, unsigned int uiTo);
		void GRPEnleverArc(unsigned int uiFrom, unsigned int uiTo);
		void GRPAfficherGraphe();
};

#endif