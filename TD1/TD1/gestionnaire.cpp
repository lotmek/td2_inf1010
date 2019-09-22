
#include "gestionnaire.h"


// TODO: Implementer toutes les methodes
Gestionnaire::Gestionnaire() 
{
	capaciteMembres_ = capaciteCoupons_ = CAPACITE_INITIALE;
	membres_ = new Membre * [capaciteMembres_];
	nbMembres_ = 0;
	coupons_ = new Coupon * [capaciteCoupons_];
	nbCoupons_ = 0;

}

Gestionnaire::~Gestionnaire() {}

// Getters
Membre** Gestionnaire::getMembres() 
{
	return membres_;
}

int Gestionnaire::getNbMembres()
{
	return nbMembres_;
}

int Gestionnaire::getCapaciteMembres()
{
	return capaciteMembres_;
}

Coupon** Gestionnaire::getCoupons()
{
	return coupons_;
}

int Gestionnaire::getNbCoupons()
{
	return nbCoupons_;
}

int Gestionnaire::getCapaciteCoupons()
{
	return capaciteCoupons_;
}


void Gestionnaire::ajouterMembre(const string& nomMembre)
{
	
	if (capaciteMembres_ <= nbMembres_) {
		capaciteMembres_ *= 2;
		Membre** nouveauTableau = new Membre * [capaciteMembres_];
		for (int i = 0; i < nbMembres_; i++) {
			nouveauTableau[i] = membres_[i];
		}
		delete[] membres_;
		membres_ = nouveauTableau;
	}

	Membre* nouveauMembrePtr = new Membre(nomMembre);
	membres_[nbMembres_++] = nouveauMembrePtr;

}

void Gestionnaire::ajouterCoupon(const string& code, double rabais, int cout)
{
	if (capaciteCoupons_ <= nbCoupons_) {
		capaciteCoupons_ *= 2;
		Coupon** nouveauCoupon = new Coupon * [capaciteCoupons_];
		for (int i = 0; i < nbCoupons_; i++) {
			nouveauCoupon[i] = coupons_[i];
		}
		delete[] coupons_;
		coupons_ = nouveauCoupon;
	}

	Coupon* nouveauCouponPtr = new Coupon(code, rabais, cout);
	coupons_[nbCoupons_++] = nouveauCouponPtr;

}

Membre* Gestionnaire::trouverMembre(const string& nomMembre)
{
	for (int i = 0; i < nbMembres_; i++) {
		if (membres_[i]->getNom() == nomMembre)
			return membres_[i];
	}
	return nullptr;
}
void Gestionnaire::assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol, bool utiliserCoupon)
{
	Membre* membreAssigne = trouverMembre(nomMembre);
	if(utiliserCoupon==true)
	{
		prixBase = prixBase - appliquerCoupon(membreAssigne, prixBase);
	}

	membreAssigne->ajouterBillet(pnr, prixBase, od, tarif, dateVol);
	

}
double Gestionnaire::appliquerCoupon(Membre* membre, double prix)
{
	double rabais = 0.0;
	int indiceCoupon;
	Coupon** tableauCouponsMembre = membre->getCoupons();
	for (int i = 0; i < membre->getNbCoupons(); i++) {
		if (rabais < tableauCouponsMembre[i]->getRabais()) {
			rabais = tableauCouponsMembre[i]->getRabais();
			indiceCoupon = i;
		}
	}



	if (rabais == 0.0) {
		cout << "erreur\n";

	}
	
	else membre->retirerCoupon(tableauCouponsMembre[indiceCoupon]);

	return rabais * prix;
}
void Gestionnaire::acheterCoupon(const string& nomMembre)
{

	Membre* membreAcheteur = trouverMembre(nomMembre);
	int nbPointsClient = membreAcheteur->getPoints();
	Coupon* meilleurCoupon = new Coupon;
	bool findCoupon = false;
	for (int i = 0; i < nbCoupons_; i++)
	{
		if ((coupons_[i]->getCout() >= meilleurCoupon->getCout()) && (nbPointsClient >= coupons_[i]->getCout())) {
			meilleurCoupon = coupons_[i];
			findCoupon = true;
		}
			
	}
	if (findCoupon == true)
		membreAcheteur->acheterCoupon(meilleurCoupon);
	else cout << "erreur\n";
}

void Gestionnaire::afficherInfos()
{


}