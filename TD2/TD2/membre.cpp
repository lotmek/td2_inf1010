/**********************************************************************
 * Cours : INF1010
 * Travail pratique 2
 * Nom: membre.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#include "membre.h"

 /****************************************************************************
  * Fonction:	Membre::Membre
  * Description: Constructeur par défaut.
  * Paramètres:	aucun
  * Retour:		aucun
  ****************************************************************************/
Membre::Membre() :
	nom_(""),
	points_(0)
{
}

/****************************************************************************
 * Fonction:	Membre::Membre
 * Description: Constructeur par paramètres.
 * Paramètres:	(const string&) nom
 * Retour:		aucun
 ****************************************************************************/
Membre::Membre(const string& nom) :
	nom_(nom),
	points_(0),
	billets_(),
	coupons_()
{
}

/****************************************************************************
 * Fonction:	Membre::Membre(
 * Description: Constructeur par copie.
 * Paramètres:	(const Membre&) copieMembre
 * Retour:		aucun
 ****************************************************************************/
Membre::Membre(const Membre& copieMembre)
	: nom_(copieMembre.nom_), points_(copieMembre.points_) {
	for (unsigned i = 0; i < copieMembre.billets_.size(); i++) {
		billets_.push_back(new Billet(*(copieMembre.billets_[i])));
	}

	for (unsigned i = 0; i < copieMembre.coupons_.size(); i++) {
		coupons_.push_back(copieMembre.coupons_[i]);
	}

}

/****************************************************************************
 * Fonction:	Membre::~Membre
 * Description: Destructeur, détruit le membre du système.
 * Paramètres:	aucun
 * Retour:		aucun
 ****************************************************************************/
Membre::~Membre()
{
	for (unsigned i = 0; i < billets_.size(); i++) {
		delete billets_[i];
	}
}

/****************************************************************************
 * Fonction:	Membre::getNom
 * Description: Fournit le nom.
 * Paramètres:	aucun
 * Retour:		(string) Nom du membre
 ****************************************************************************/
string Membre::getNom() const
{
	return nom_;
}

/****************************************************************************
 * Fonction:	Membre::getPoints
 * Description: Fournit les points.
 * Paramètres:	aucun
 * Retour:		(int) Les points du membre
 ****************************************************************************/
int Membre::getPoints() const
{
	return points_;
}

/****************************************************************************
 * Fonction:	Membre::getBillets
 * Description: Fournit les billets.
 * Paramètres:	aucun
 * Retour:		vector<Billet*> vecteur de billets
 ****************************************************************************/
vector<Billet*> Membre::getBillets() const
{
	return billets_;
}

/****************************************************************************
 * Fonction:	Membre::getCoupons
 * Description: Fournit le tableau de coupons.
 * Paramètres:	aucun
 * Retour:		vector<Coupon*> vecteur de coupons
 ****************************************************************************/
vector<Coupon*> Membre::getCoupons() const
{
	return coupons_;
}

/****************************************************************************
 * Fonction:	Membre::setNom
 * Description: Modificateur de nom.
 * Paramètres:	(const string& nom)
 * Retour:		aucun
 ****************************************************************************/
void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

/****************************************************************************
 * Fonction:	Membre::modifierPoints
 * Description: Modificateur de points.
 * Paramètres:	(int) points
 * Retour:		aucun
 ****************************************************************************/
void Membre::modifierPoints(int points)
{
	points_ += points;
}

/****************************************************************************
 * Fonction:	Membre::ajouterBillet
 * Description:	Ajoute un pointeur billet dans le vecteur.
 * Paramètres:	(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol)
 * Retour:		aucun
 ****************************************************************************/
void Membre::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol)
{
	Billet* billet = new Billet(pnr, nom_, prix, od, tarif, dateVol);
	billets_.push_back(billet);
	modifierPoints(calculerPoints(billet));
}

/****************************************************************************
 * Fonction:	Membre::acheterCoupon
 * Description:	Ajoute le coupon(achète) si le membre possède assez de points.
 * Paramètres:	(Coupon* coupon)
 * Retour:		aucun
 ****************************************************************************/
void Membre::acheterCoupon(Coupon* coupon)
{
	if (points_ > coupon->getCout()) {
		// TODO: Utiliser la surcharge de l'operateur += de la classe Membre plutot qu'utiliser la methode ajouterCoupon
		*this += coupon;
		modifierPoints(-coupon->getCout());
	}
}

/****************************************************************************
 * Fonction:	Membre::calculerPoints
 * Description:	Calcule le nombre de points incluant les points bonus selon la classe du billet.
 * Paramètres:	(Billet* billet)
 * Retour:		(double) nombre de points
 ****************************************************************************/
double  Membre::calculerPoints(Billet * billet) const
{
	double bonus = 0;
	switch (billet->getTarif()) {
	case TarifBillet::PremiumEconomie:
		bonus = 50;
		break;
	case TarifBillet::Affaire:
		bonus = 150;
		break;
	case TarifBillet::Premiere:
		bonus = 300;
		break;
	default:
		break;
	}

	return billet->getPrix()* 0.10 + bonus;
}


/****************************************************************************
 * Fonction:	Membre::operator+=
 * Description:	Surcharge l'opérateur += pour ajouter un pointeur coupon dans le vecteur cpouns_
 * Paramètres:	(Coupon* coupon)
 * Retour:		Membre& membre
 ****************************************************************************/
Membre& Membre::operator+=(Coupon* coupon)
{
	coupons_.push_back(coupon);
	return *this;
}

/****************************************************************************
 * Fonction:	Membre::operator-=
 * Description:	Surcharge l'opérateur -= pour retirer un pointeur coupon du vecteur coupons_
 * Paramètres:	(Coupon* coupon)
 * Retour:		Membre& membre
 ****************************************************************************/
Membre& Membre::operator-=(Coupon* coupon)
{
	for (unsigned i = 0; i < coupons_.size(); i++) {
		if (coupons_[i] == coupon) {
			coupons_[i] = coupons_[coupons_.size() - 1];
			coupons_.pop_back();
		}
	}
	return *this;
}

/****************************************************************************
 * Fonction:	Membre::operator==
 * Description:	Surcharge l'operateur == (operande de gauche est un membre et droite est un string)
 *				Compare les noms.
 * Paramètres:	const string& nom
 * Retour:		bool vrai ou faux
 ****************************************************************************/
bool Membre::operator==(const string& nom) const
{
	return (nom_ == nom);
}


/****************************************************************************
 * Fonction:	friend operator==
 * Description:	Surcharge l'operateur == (operande de gauche est un string et droite est un membre)
 *				Compare les noms.
 * Paramètres:	(const string& nom, const Membre& membre)
 * Retour:		bool vrai ou faux
 ****************************************************************************/
bool operator==(const string& nom, const Membre& membre)
{
	return (membre.nom_ == nom);
}

/****************************************************************************
 * Fonction:	Membre::operator==
 * Description:	Surcharge l'operateur =
 *				Ecrase les attributs d'un membre et les remplace par ceux de l'autre
 * Paramètres:	(const Membre& membre)
 * Retour:		Membre& membre final avec les attributs du membre passé en paramètre
 ****************************************************************************/
Membre& Membre::operator=(const Membre& membre)
{
	if (nom_ != membre.nom_) {

		nom_ = membre.nom_;
		points_ = membre.points_;
		for (unsigned i = 0; i < billets_.size(); i++)
			delete billets_[i];

		billets_.clear();
		coupons_.clear();
		for (unsigned i = 0; i < membre.billets_.size(); i++) {
			Billet* billet = new Billet(*membre.billets_[i]);
			billets_.push_back(billet);
		}

		for (unsigned i = 0; i < membre.coupons_.size(); i++) {
			coupons_.push_back(membre.coupons_[i]);
		}



	}


	return *this;
}

/****************************************************************************
 * Fonction:	friend operator<<
 * Description:	Surcharge l'operateur <<
 *				Affiche les informations du membre
 * Paramètres:	(ostream& o, const Membre& membre)
 * Retour:		ostream& affichage
 ****************************************************************************/
ostream& operator<<(ostream& o, const Membre& membre)
{
	o << setfill(' ');
	o << "- Membre " << membre.nom_ << ":" << endl;
	o << "\t" << left << setw(10) << "- Points" << ": " << membre.points_ << endl;
	o << "\t" << "- Billets :" << endl;
	for (unsigned i = 0; i < membre.billets_.size(); i++) {
		o << *membre.billets_[i];
	}
	o << "\t" << "- Coupons :" << endl;
	for (unsigned i = 0; i < membre.coupons_.size(); i++) {
		o << *membre.coupons_[i];
	}
	o << endl;

	return o;
}


