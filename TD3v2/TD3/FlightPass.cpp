/**********************************************************************
 * Cours : INF1010
 * Travail pratique 3
 * Nom: FlightPass.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/
#include "flightPass.h"

 /****************************************************************************
  * Fonction:	 FlightPass::FlightPass
  * Description: Constructeur par paramètre.
  * Paramètres:	 const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet
  * Retour:		 aucun
  ****************************************************************************/
FlightPass::FlightPass(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet)
	:Billet(pnr, nomPassager, prix, od, tarif, typeBillet),
	nbUtilisationsRestante_(NB_UTILISATIONS_INITIALE)
{
}

/****************************************************************************
 * Fonction:	 FlightPass::decrementeNbUtilisations
 * Description:  Decremente le nombre d'utilisations du FlightPass
 * Paramètres:	 aucun
 * Retour:		 aucun
 ****************************************************************************/
void FlightPass::decrementeNbUtilisations()
{
	nbUtilisationsRestante_--;
}

/****************************************************************************
 * Fonction:	 FlightPass::getNbUtilisationsRestante
 * Description:  Decremente le nombre d'utilisations du FlightPass
 * Paramètres:	 aucun
 * Retour:		 aucun
 ****************************************************************************/
int FlightPass::getNbUtilisationsRestante() const
{
	return nbUtilisationsRestante_;
}

/****************************************************************************
 * Fonction:	 FlightPass::afficherBillet
 * Description:  Fonction que l'on a ajoutee pour l'affichage des billets FlightPass
 * Paramètres:	 aucun
 * Retour:		 aucun
 ****************************************************************************/
void FlightPass::afficherBillet() const
{
	Billet::afficherBillet();
	cout << "\t\t\t" << setw(11) << "- Utilisations restantes" << ": " << nbUtilisationsRestante_ << endl;
}