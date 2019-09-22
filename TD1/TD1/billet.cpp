/**********************************************************************
 * Cours : INF1010
 * Travail pratique 1
 * Nom: billet.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#include "billet.h"

 /****************************************************************************
  * Fonction:	Billet::Billet
  * Description: Constructeur par défaut.
  * Paramètres:	aucun
  * Retour:		aucun
  ****************************************************************************/
Billet::Billet()
{
	pnr_ = "000000000";
	nomPassager_ = "aucun nom";
	prix_ = 0.0;
	od_ = "terre - lune";
	tarif_ = TarifBillet::Economie;
	dateVol_ = "21 decembre 2012";
}

/****************************************************************************
 * Fonction:	Billet::Billet
 * Description: Constructeur par paramètres.
 * Paramètres:	(const) string& pnr, (const string&) nomPassager, (double) prix, (const string&) od, (TarifBillet) tarif, const string& dateVol)
 * Retour:		aucun
 ****************************************************************************/
Billet::Billet(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, const string& dateVol)
{
	pnr_ = pnr;
	nomPassager_ = nomPassager;
	prix_ = prix;
	od_ = od;
	tarif_ = tarif;
	dateVol_ = dateVol;
}

/****************************************************************************
 * Fonction:	Billet::Billet
 * Description: Destructeur de Billet.
 * Paramètres:	aucun
 * Retour:		aucun
 ****************************************************************************/
Billet::~Billet() {}

		// Getters

/****************************************************************************
 * Fonction:	Billet::getPnr
 * Description: Fournit le Pnr: numero de reservation du billet (ID).
 * Paramètres:	aucun
 * Retour:		(string) pnr
 ****************************************************************************/
string Billet::getPnr() const
{
	return pnr_;
}

/****************************************************************************
 * Fonction:	Billet::getNomPassager
 * Description: Fournit le nom du passager.
 * Paramètres:	aucun
 * Retour:		(string) nom du passager
 ****************************************************************************/
string Billet::getNomPassager() const
{
	return nomPassager_;
}

/****************************************************************************
 * Fonction:	Billet::getPrix
 * Description: Fournit le prix du billet.
 * Paramètres:	aucun
 * Retour:		(double) prix du billet
 ****************************************************************************/
double Billet::getPrix() const
{
	return prix_;
}

/****************************************************************************
 * Fonction:	Billet::getOd
 * Description: Fournit l'origine et la destination du billet.
 * Paramètres:	aucun
 * Retour:		(string) od
 ****************************************************************************/
string Billet::getOd() const
{
	return od_;
}

/****************************************************************************
 * Fonction:	Billet::getTarif
 * Description: Fournit le tarif du billet.
 * Paramètres:	aucun
 * Retour:		(TarifBillet) le tarif
 ****************************************************************************/
TarifBillet Billet::getTarif() const
{
	return tarif_;
}

/****************************************************************************
 * Fonction:	Billet::getDateVol
 * Description: Fournit la date de vol.
 * Paramètres:	aucun
 * Retour:		(string) date de vol
 ****************************************************************************/
string Billet::getDateVol() const
{
	return dateVol_;
}

		// Setters

/****************************************************************************
 * Fonction:	Billet::setPnr
 * Description: Modifie le pnr: numero de reservation du billet (ID).
 * Paramètres:	(const string& pnr)
 * Retour:		aucun
 ****************************************************************************/
void Billet::setPnr(const string& pnr)
{
	pnr_ = pnr;
}

/****************************************************************************
 * Fonction:	Billet::setNomPassager
 * Description: Modifie le nom du passager.
 * Paramètres:	(const string& nomPassager)
 * Retour:		aucun
 ****************************************************************************/
void Billet::setNomPassager(const string& nomPassager)
{
	nomPassager_ = nomPassager;
}

/****************************************************************************
 * Fonction:	Billet::setPrix
 * Description: Modifie le prix.
 * Paramètres:	(double prix)
 * Retour:		aucun
 ****************************************************************************/
void Billet::setPrix(double prix)
{
	prix_ = prix;
}

/****************************************************************************
 * Fonction:	Billet::setOd
 * Description: Modifie l'origine et la destination du billet.
 * Paramètres:	(const string& od)
 * Retour:		aucun
 ****************************************************************************/
void Billet::setOd(const string& od)
{
	od_ = od;
}

/****************************************************************************
 * Fonction:	Billet::setTarif
 * Description: Modifie le tarif du billet.
 * Paramètres:	(const TarifBillet& tarif)
 * Retour:		aucun
 ****************************************************************************/
void Billet::setTarif(const TarifBillet& tarif)	
{
	tarif_ = tarif;
}

/****************************************************************************
 * Fonction:	Billet::setDateVol
 * Description: Modifie la date de vol du billet.
 * Paramètres:	(const string& dateVol)
 * Retour:		aucun
 ****************************************************************************/
void Billet::setDateVol(const string& dateVol)
{
	dateVol_ = dateVol;
}

/****************************************************************************
 * Fonction:	Billet::formatTarif
 * Description: Fournit la string correspondante a la classe de l'Enum TarifBillet.
 * Paramètres:	(TarifBillet tarif) const
 * Retour:		(string) classe du billet
 ****************************************************************************/
string Billet::formatTarif(TarifBillet tarif) const
{
	switch (tarif) {
	case TarifBillet::Economie: return "Economie"; break;
	case TarifBillet::PremiumEconomie: return "Premium economie"; break;
	case TarifBillet::Affaire: return "Affaire"; break;
	case TarifBillet::Premiere: return "Premiere"; break;
	}
}

		//Méthode d'affichage

/****************************************************************************
 * Fonction:	Billet::afficherBillet
 * Description: Affiche les informations du billet, c-à-d la classe du billet, nom du passager, prix, trajet et date de vol.
 * Paramètres:	aucun
 * Retour:		aucun
 ****************************************************************************/
void Billet::afficherBillet() const		
{
	cout << "\t\t- Billet " << pnr_ << " (Classe : " << formatTarif(tarif_) << ")\n"
		<< "\t\t\t- Passager : " << nomPassager_ << "\n"
		<< "\t\t\t- Prix     : " << prix_ << "$\n"
		<< "\t\t\t- Trajet   : " << od_ << "\n"
		<< "\t\t\t- Vol le   : " << dateVol_ << "\n"; 
}