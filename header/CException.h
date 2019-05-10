#ifndef CEXCEPTION
#define CEXCEPTION

class CException 
{
	private :
	
		unsigned int uiEXCErreur;
		
	public :
	
		// Constructeur
		CException(unsigned int uiErreur);
		
		// Accesseurs
		unsigned int EXCLireErreur();
		void EXCModifierErreur(unsigned int uiErreur);
};

#endif