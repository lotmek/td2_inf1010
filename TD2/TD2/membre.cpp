/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "membre.h"

Membre::Membre() :
	nom_(""),
	points_(0)
{
}

Membre::Membre(const string& nom) :
	nom_(nom),
	points_(0),
	billets_(),
	coupons_()
{
}

Membre::Membre(const Membre& copieMembre)
	: nom_(copieMembre.nom_), points_(copieMembre.points_) {
	for (unsigned i = 0; i < copieMembre.billets_.size(); i++) {
		billets_.push_back(new Billet(*(copieMembre.billets_[i])));
	}

	for (unsigned i = 0; i < copieMembre.coupons_.size(); i++) {
		coupons_.push_back(copieMembre.coupons_[i]);
	}

}

Membre::~Membre()
{
	for (unsigned i = 0; i < billets_.size(); i++) {
		delete billets_[i];
	}
}

string Membre::getNom() const
{
	return nom_;
}

int Membre::getPoints() const
{
	return points_;
}

vector<Billet*> Membre::getBillets() const
{
	return billets_;
}

vector<Coupon*> Membre::getCoupons() const
{
	return coupons_;
}

int Membre::getNbBillets() const
{
	return billets_.size();
}

int Membre::getNbCoupons() const
{
	return coupons_.size();
}


void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

void Membre::modifierPoints(int points)
{
	points_ += points;
}

void Membre::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol)
{
	Billet* billet = new Billet(pnr, nom_, prix, od, tarif, dateVol);
	billets_.push_back(billet);
	modifierPoints(calculerPoints(billet));
}

void Membre::acheterCoupon(Coupon* coupon)
{
	if (points_ > coupon->getCout()) {
		// TODO: Utiliser la surcharge de l'operateur += de la classe Membre plutot qu'utiliser la methode ajouterCoupon
		*this += coupon;
		modifierPoints(-coupon->getCout());
	}
}

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

// TODO: Remplacer cette methode par l'operateur +=
Membre& Membre::operator+=(Coupon* coupon)
{
	coupons_.push_back(coupon);
	return *this;
}

// TODO: Remplacer cette methode par l'operateur -=
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

// TODO: Surcharger l'operateur == (operande de gauche est un membre et droite est un string)
bool Membre::operator==(const string& nom) const
{
	return (nom_ == nom);
}


// TODO: Surcharger l'operateur == (operande de gauche est un string et droite est un membre)
bool operator==(const string& nom, const Membre& membre)
{
	return (membre.nom_ == nom);
}

// TODO: Surcharger l'operateur =
Membre& Membre::operator=(const Membre& membre) // ????????????????
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


// TODO: Remplacer cette methode par la surcharge de l'operateur <<
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


