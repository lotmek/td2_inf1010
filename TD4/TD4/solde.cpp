/**********************************************************************
 * Cours : INF1010
 * Travail pratique 4
 * Nom: solde.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussi�res    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#include "solde.h"

 /****************************************************************************
  * Fonction:		Solde:solde
  * Description:	Constructeur par parametre
  * Param�tres:		(double pourcentageSolde)
  * Retour:			aucun
  ****************************************************************************/
Solde::Solde(double pourcentageSolde)
{
	pourcentageSolde_ = pourcentageSolde;
}

/****************************************************************************
 * Fonction:		Solde:~solde
 * Description:		Destructeur de Solde
 * Param�tres:		aucun
 * Retour:			aucun
 ****************************************************************************/
Solde::~Solde()
{
}

/****************************************************************************
 * Fonction:		Solde:getPourcentageSolde
 * Description:		Fournit le pourcentageSolde
 * Param�tres:		aucun
 * Retour:			double pourcentageSolde
 ****************************************************************************/
double Solde::getPourcentageSolde() const
{
	return pourcentageSolde_;
}

/****************************************************************************
 * Fonction:		Solde:setPourcentageSolde
 * Description:		Modifie le pourcentageSolde
 * Param�tres:		(double pourcentageSolde)
 * Retour:			aucun
 ****************************************************************************/
void Solde::setPourcentageSolde(double pourcentageSolde)
{
	pourcentageSolde_ = pourcentageSolde;
}
