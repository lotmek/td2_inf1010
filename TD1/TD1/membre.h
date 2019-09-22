/**********************************************************************
 * Cours : INF1010
 * Travail pratique 1
 * Nom: membre.h
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#ifndef MEMBRE_H
#define MEMBRE_H

#include <string>
#include "billet.h"			//ENLEVER LE ; 
#include "coupon.h"			//ENLEVER LE ; 

using namespace std;

class Membre {
public:
	// TODO: Implementer toutes les methodes
	Membre();
	Membre(const string& nom_);

	// TODO: Implementer si necessaire
	~Membre();

	// Getters
	string getNom() const;
	int getPoints() const;
	Billet** getBillets() const;
	int getNbBillets() const;
	int getCapaciteBillets() const;
	Coupon** getCoupons() const;
	int getNbCoupons() const;
	int getCapaciteCoupons() const;

	// Setters
	void setNom(const string& nom);

	void modifierPoints(int points);
	void ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol);
	void ajouterCoupon(Coupon* coupon);
	void retirerCoupon(Coupon* coupon);

	void acheterCoupon(Coupon* coupon);
	double calculerPoints(Billet* billet);

	void afficherMembre() const;

private:
	string nom_;
	int points_;
	Billet** billets_;
	int nbBillets_;
	int capaciteBillets_;
	Coupon** coupons_;
	int nbCoupons_;
	int capaciteCoupons_;
};


#endif
