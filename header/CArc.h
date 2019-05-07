#ifndef CARC 
#define CARC

class CArc
{
	private:
/*
 * ATTENTION : le nom "Destination" est mal choisi, l'attribut ne correspond pas au sens 
 * de l'arc mais au numéro du sommet qui se trouve "de l'autre cote"
 * Exemple : S1 ----> S2
 * Ici S1 contient un arc partant ayant pour destination 2
 * et S2 contient un arc arrivant ayant pour destination 1
 */
		unsigned int uiARCDestination;
		
	public:
	
		//Constructeurs & Destructeur
		CArc();
		CArc(unsigned int uiDestination);
		//Setter & Getter
		unsigned int ARCLireDestination();
		void ARCModifierDestination(unsigned int uiDestination);
};

#endif