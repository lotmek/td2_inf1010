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
	case TypeMembre::Membre_Occasionnel:
		membres_.push_back(new Membre(nomMembre, typeMembre));
		break;
	case TypeMembre::Membre_Regulier:
		membres_.push_back(new MembreRegulier(nomMembre, typeMembre));
		break;
	case TypeMembre::Membre_Premium:
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
	if (typeBillet == Flight_Pass)
		prixBase *= 10;

	if (utiliserCoupon) {
		prixReel = prixBase - appliquerCoupon(membre, prixBase);
	}
	else {
		prixReel = prixBase;
	}

	if (membre->getTypeMembre() == Membre_Premium) {
		MembrePremium * membrePrem = static_cast<MembrePremium*>(membre);
		double rabais = membrePrem->getpointsCumulee() * 5 / 1000 / 100.0 >= 0.1 ? 0.1 : membrePrem->getpointsCumulee() / 1000 / 100.0;
		prixReel -= prixReel * rabais;
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
				if (coupons[i]->getCout() >= meilleurCoupon->getCout()) {
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
				else if (coupons_[i]->getRabais() > meilleurCoupon->getRabais()) {
					meilleurCoupon = coupons_[i];
				}
			}
		}

		if (membre->getTypeMembre() == Membre_Premium && meilleurCoupon != nullptr) {		//Même explication que ligne 149 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			MembrePremium* membre1 = static_cast<MembrePremium*>(membre0);
			membre1->acheterCoupon(meilleurCoupon);
		}

		else if (meilleurCoupon != nullptr)		//Ici, il y a la possibilité que le pointeur soit null, voir ligne 134 et 127 pour comprendre !!!!!!!!!!!!!!!!!!!!!!!!
			membre0->acheterCoupon(meilleurCoupon);
	}

	else {
		cout << "Le membre ne peut acheter de coupon\n";
	}
}

ostream& operator<<(ostream& o, const Gestionnaire& gestionnaire)
{
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";
	MembreRegulier* membreReg = nullptr;// = static_cast<MembreRegulier*>(gestionnaire.membres_[i]);
	MembrePremium* membrePrem = nullptr;// = static_cast<MembrePremium*>(gestionnaire.membres_[i]);
	for (int i = 0; i < gestionnaire.membres_.size(); i++) {
		//if (gestionnaire.membres_[i]->getTypeMembre()==Membre_Premium)
		switch (gestionnaire.membres_[i]->getTypeMembre()) {
			case Membre_Occasionnel:
				o << *gestionnaire.membres_[i];	// !!!!!!!!!!!!!!!! ICI ON DOIT PASSSER UN POINTEUR ET NON UN SIMPLE MEMBRE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			break;

			case Membre_Regulier:
				membreReg = static_cast<MembreRegulier*>(gestionnaire.membres_[i]);
				o << membreReg;				// !!!!!!!!!!!!!!!! ICI ON DOIT PASSSER UN POINTEUR ET NON UN SIMPLE MEMBRE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			break;

			case Membre_Premium:
				membrePrem = static_cast<MembrePremium*>(gestionnaire.membres_[i]);
				o << membrePrem;			// !!!!!!!!!!!!!!!! ICI ON DOIT PASSSER UN POINTEUR ET NON UN SIMPLE MEMBRE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				break;
		}

	}

	return o;
}
