/**********************************************************************
 * Cours : INF1010
 * Travail pratique 3
 * Nom: billetRegulier.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#include "billetRegulier.h"

/****************************************************************************
 * Fonction:	 BilletRegulier::BilletRegulier
 * Description:  Constructeur par defaut
 * Paramètres:	 const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, const string& dateVol, TypeBillet typeBillet
 * Retour:		 aucun
 ****************************************************************************/
BilletRegulier::BilletRegulier(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, const string& dateVol, TypeBillet typeBillet)
	:Billet(pnr, nomPassager, prix, od,  tarif, typeBillet),
	dateVol_(dateVol)
{	
}

/****************************************************************************
 * Fonction:	BilletRegulier::getDateVol
 * Description: Fournit la date de vol
 * Paramètres:	aucun
 * Retour:		(string) dateVol
 ****************************************************************************/
string BilletRegulier::getDateVol() const
{
	return dateVol_;
}

/****************************************************************************
 * Fonction:	BilletRegulier::setDateVol
 * Description: Modifie la date de vol
 * Paramètres:	const string& dateVol
 * Retour:		aucun
 ****************************************************************************/
void BilletRegulier::setDateVol(const string& dateVol)
{
	dateVol_ = dateVol;
}

/****************************************************************************
 * Fonction:	 BilletRegulier::afficherBillet
 * Description:  Fonction que l'on a ajoutee pour l'affichage des billets
 * Paramètres:	 ostream& o
 * Retour:		 aucun
 ****************************************************************************/
void BilletRegulier::afficherBillet(ostream& o) const
{
	Billet::afficherBillet(o);
	o << "\t\t\t" << setw(11) << "- Vol le : " << dateVol_ << endl;
}