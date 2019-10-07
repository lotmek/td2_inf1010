/**********************************************************************
 * Cours : INF1010
 * Travail pratique 3
 * Nom: billet.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussi�res    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#include "billet.h"

 /****************************************************************************
  * Fonction:	 Billet::Billet
  * Description: Constructeur par defaut
  * Param�tres:	 aucun
  * Retour:		 aucun
  ****************************************************************************/
Billet::Billet() :
	pnr_(""),
	nomPassager_(""),
	prix_(0),
	od_(""),
	tarif_(TarifBillet::Economie),
	typeBillet_(TypeBillet::Billet_Base)
{
}

/****************************************************************************
 * Fonction:	 Billet::Billet
 * Description:  Constructeur par defaut
 * Param�tres:	 const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet
 * Retour:		 aucun
 ****************************************************************************/
Billet::Billet(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet) :
	pnr_(pnr),
	nomPassager_(nomPassager),
	prix_(prix),
	od_(od),
	tarif_(tarif),
	typeBillet_(typeBillet)
{
}

/****************************************************************************
 * Fonction:	Billet::Billet
 * Description: Destructeur de Billet.
 * Param�tres:	aucun
 * Retour:		aucun
 ****************************************************************************/
Billet::~Billet()
{
}

/****************************************************************************
 * Fonction:	Billet::getPnr
 * Description: Fournit le Pnr: numero de reservation du billet (ID).
 * Param�tres:	aucun
 * Retour:		(string) pnr
 ****************************************************************************/
string Billet::getPnr() const
{
	return pnr_;
}

/****************************************************************************
 * Fonction:	Billet::getNomPassager
 * Description: Fournit le nom du passager.
 * Param�tres:	aucun
 * Retour:		(string) nom du passager
 ****************************************************************************/
string Billet::getNomPassager() const
{
	return nomPassager_;
}

/****************************************************************************
 * Fonction:	Billet::getPrix
 * Description: Fournit le prix du billet.
 * Param�tres:	aucun
 * Retour:		(double) prix du billet
 ****************************************************************************/
double Billet::getPrix() const
{
	return prix_;
}

/****************************************************************************
 * Fonction:	Billet::getOd
 * Description: Fournit l'origine et la destination du billet.
 * Param�tres:	aucun
 * Retour:		(string) od
 ****************************************************************************/
string Billet::getOd() const
{
	return od_;
}

/****************************************************************************
 * Fonction:	Billet::getTarif
 * Description: Fournit le tarif du billet.
 * Param�tres:	aucun
 * Retour:		(TarifBillet) le tarif
 ****************************************************************************/
TarifBillet Billet::getTarif() const
{
	return tarif_;
}

/****************************************************************************
 * Fonction:	Billet::getTypeBillet
 * Description: Fournit le type billet de l'enum TypeBillet
 * Param�tres:	aucun
 * Retour:		(string) typeBillet
 ****************************************************************************/
TypeBillet Billet::getTypeBillet() const
{
	return typeBillet_;
}
		//Setters

/****************************************************************************
 * Fonction:	Billet::setPnr
 * Description: Modifie le pnr: numero de reservation du billet (ID).
 * Param�tres:	(const string& pnr)
 * Retour:		aucun
 ****************************************************************************/
void Billet::setPnr(const string& pnr)
{
	pnr_ = pnr;
}

/****************************************************************************
 * Fonction:	Billet::setNomPassager
 * Description: Modifie le nom du passager.
 * Param�tres:	(const string& nomPassager)
 * Retour:		aucun
 ****************************************************************************/
void Billet::setNomPassager(const string& nomPassager)
{
	nomPassager_ = nomPassager;
}

/****************************************************************************
 * Fonction:	Billet::setPrix
 * Description: Modifie le prix.
 * Param�tres:	(double prix)
 * Retour:		aucun
 ****************************************************************************/
void Billet::setPrix(double prix)
{
	prix_ = prix;
}

/****************************************************************************
 * Fonction:	Billet::setOd
 * Description: Modifie l'origine et la destination du billet.
 * Param�tres:	(const string& od)
 * Retour:		aucun
 ****************************************************************************/
void Billet::setOd(const string& od)
{
	od_ = od;
}

/****************************************************************************
 * Fonction:	Billet::setTarif
 * Description: Modifie le tarif du billet.
 * Param�tres:	(TarifBillet tarif)
 * Retour:		aucun
 ****************************************************************************/
void Billet::setTarif(TarifBillet tarif)
{
	tarif_ = tarif;
}

/****************************************************************************
 * Fonction:	Billet::setTypeBillet
 * Description: Modifie le type du billet dans l'enum TypeBillet
 * Param�tres:	(TarifBillet tarif)
 * Retour:		aucun
 ****************************************************************************/
void Billet::setTypeBillet(TypeBillet typeBillet)
{
	typeBillet_ = typeBillet;
}

/****************************************************************************
 * Fonction:	Billet::formatTarif
 * Description: Fournit la string correspondante a la classe de l'Enum TarifBillet.
 * Param�tres:	(TarifBillet tarif) const
 * Retour:		(string) classe du billet
 ****************************************************************************/
string Billet::formatTarif(TarifBillet tarif) const
{
	switch (tarif)
	{
		case TarifBillet::Economie:
			return "Economie";
		case TarifBillet::PremiumEconomie:
			return "Premium economie";
		case TarifBillet::Affaire:
			return "Affaire";
		case TarifBillet::Premiere:
			return "Premiere";
		default:
			return "";
	}
}

/****************************************************************************
 * Fonction:	 Billet::afficherBillet
 * Description:  Fonction que l'on a ajoutee pour l'affichage des billets
 * Param�tres:	 ostream& o
 * Retour:		 aucun
 ****************************************************************************/
void Billet::afficherBillet(ostream& o) const {

	o << "\t\t- Billet " << pnr_ << " (Classe : " << formatTarif(tarif_) << ")" << endl;
	o << left << "\t\t\t" << setw(11) << "- Passager : " << nomPassager_ << endl;
	o << "\t\t\t" << setw(11) << "- Prix : " << prix_ << "$" << endl;
	o << "\t\t\t" << setw(11) << "- Trajet : " << od_ << endl;

}

/****************************************************************************
 * Fonction:	 operator<< pour Billet
 * Description:  Fonction qui affiche les billet
 * Param�tres:	 ostream& o, const Billet& billet
 * Retour:		 ostream& o
 ****************************************************************************/
ostream& operator<<(ostream& o, const Billet& billet)
{
	billet.afficherBillet(o);

	return o;
}
