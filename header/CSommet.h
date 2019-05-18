#ifndef CSOMMET 
#define CSOMMET

#include "header/CArc.h"

// Codes d'exceptions
#define ERR_REALLOC		23
#define ERR_NUMARC		26

class CSommet
{
	private:
	
		unsigned int uiSOMNumero;
		CArc ** pARCSOMArrivant;
		CArc ** pARCSOMPartant;
		unsigned int uiCompteurArcArrivant;
		unsigned int uiCompteurArcPartant;
		
	public:
	
		// Constructeurs & Destructeur
		CSommet();
		CSommet(unsigned int uiNumero);
		CSommet(CSommet &SOMSommet);
		~CSommet();
		
		// Accesseurs
		unsigned int SOMLireNumero();
		void SOMModifierNumero(unsigned int uiNumero);
		
		void SOMAjouterArcArrivant(CArc * pARCArc);
		void SOMEnleverArcArrivant(unsigned int uiDestination);
		void SOMAjouterArcPartant(CArc * pARCArc);
		void SOMEnleverArcPartant(unsigned int uiDestination);
		
		CArc ** SOMLireArcArrivant();
		CArc * SOMLireArcArrivantIndice(unsigned int uiIndice);
		CArc ** SOMLireArcPartant();
		CArc * SOMLireArcPartantIndice(unsigned int uiIndice);
		void SOMModifierArcArrivant(CArc **);
		void SOMModifierArcPartant(CArc **);
		
		unsigned int SOMLireCompteurArcArrivant();
		unsigned int SOMLireCompteurArcPartant();
		
		// Methodes
		void SOMAfficherSommet();
		int SOMContientArc(unsigned int uiTo);
};

#endif