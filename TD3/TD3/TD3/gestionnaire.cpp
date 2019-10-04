/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "gestionnaire.h"

Gestionnaire::Gestionnaire()
{
}

Gestionnaire::~Gestionnaire()
{
	for (int i = 0; i < membres_.size(); i++) {
		delete membres_[i];
	}

	for (int i = 0; i < coupons_.size(); i++) {
		delete coupons_[i];
	}
}

vector<Membre*> Gestionnaire::getMembres() const
{
	return membres_;
}

vector<Coupon*> Gestionnaire::getCoupons() const
{
	return coupons_;
}

void Gestionnaire::ajouterMembre(const string& nomMembre, TypeMembre typeMembre)
{
	switch (typeMembre) {
	case Membre_Occasionnel:
		membres_.push_back(new Membre(nomMembre, typeMembre));
		break;
	case Membre_Regulier:
		membres_.push_back(new MembreRegulier(nomMembre, typeMembre));
		break;
	case Membre_Premium:
		membres_.push_back(new MembrePremium(nomMembre));
		break;
	}

}

void Gestionnaire::ajouterCoupon(const string& code, double rabais, int cout)
{
	coupons_.push_back(new Coupon(code, rabais, cout));
}

Membre* Gestionnaire::trouverMembre(const string& nomMembre) const
{
	for (int i = 0; i < membres_.size(); i++) {
		if (*membres_[i] == nomMembre) {
			return membres_[i];
		}
	}
	cout << "Le membre " << nomMembre << " n'existe pas\n";

	return nullptr;
}

void Gestionnaire::assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol, bool utiliserCoupon, TypeBillet typeBillet)
{
	double prixReel;
	Membre* membre = trouverMembre(nomMembre);

	if (membre == nullptr) {
		return;
	}

	if (utiliserCoupon) {
		prixReel = prixBase - appliquerCoupon(membre, prixBase);
	}
	else {
		prixReel = prixBase;
	}
	membre->ajouterBillet(pnr, prixReel, od, tarif, typeBillet, dateVol);
}

double Gestionnaire::appliquerCoupon(Membre* membre, double prix)
{
	if (membre->getTypeMembre() != Membre_Occasionnel) {
		MembreRegulier* membre0 = static_cast<MembreRegulier*>(membre);
		if (membre0->getCoupons().size() == 0) {
			cout << "Le membre n'a pas de coupon utilisable\n";
			return 0;
		}

		else {
			Coupon* meilleurCoupon = membre0->getCoupons()[0];
			vector<Coupon*> coupons = membre0->getCoupons();
			for (int i = 1; i < coupons.size(); ++i) {
				if (*coupons[i] > *meilleurCoupon) {
					meilleurCoupon = coupons[i];
				}
			}
//si erreur revenir ICI

			*membre0 -= meilleurCoupon;
			return prix * meilleurCoupon->getRabais();
		
		}
	}

	else
		cout << "Le membre ne peut pas avoir de coupon\n";

}

void Gestionnaire::acheterCoupon(const string& nomMembre)
{
	if (coupons_.size() == 0) {
		cout << "Le gestionnaire n'a pas de coupon!" << endl;
		return;
	}

	Membre* membre = trouverMembre(nomMembre);

	if (membre == nullptr) {
		return;
	}

	Coupon* meilleurCoupon = nullptr;
	if (membre->getTypeMembre() != Membre_Occasionnel) {

		MembreRegulier* membre0 = static_cast<MembreRegulier*>(membre);
		for (unsigned int i = 0; i < coupons_.size(); i++) {
			if (membre0->getPoints() >= coupons_[i]->getCout()) {
				// Si on avait pas encore trouve de meilleur coupon, on fait la premiere assignation
				if (meilleurCoupon == nullptr) {
					meilleurCoupon = coupons_[i];
				}
				// Sinon on compare si le coupon courant a un rabais superieur au meilleur coupon
				else if (*coupons_[i] > *meilleurCoupon) {
					meilleurCoupon = coupons_[i];
				}
			}
		}

		if (membre->getTypeMembre() == Membre_Premium) {
			MembrePremium* membre1 = static_cast<MembrePremium*>(membre0);
			membre1->acheterCoupon(meilleurCoupon);
		}

		else
			membre0->acheterCoupon(meilleurCoupon);
	}

	else {
		cout << "Le membre ne peut acheter de coupon\n";
	}
}

ostream& operator<<(ostream& o, const Gestionnaire& gestionnaire)
{
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";
	for (int i = 0; i < gestionnaire.membres_.size(); i++) {
		MembreRegulier* membreReg = static_cast<MembreRegulier*>(gestionnaire.membres_[i]);
		MembrePremium* membrePrem = static_cast<MembrePremium*>(gestionnaire.membres_[i]);
		switch (gestionnaire.membres_[i]->getTypeMembre()) {
			case Membre_Occasionnel:
				o << *gestionnaire.membres_[i];
			break;

			case Membre_Regulier:
				o << *membreReg;
			break;

			case Membre_Premium:
				o << *membrePrem;
				break;
		}

	}

	return o;
}
