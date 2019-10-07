/**********************************************************************
 * Cours : INF1010
 * Travail pratique 3
 * Nom: membreRegulier.h
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#ifndef MEMBRE_REGULIER_H
#define MEMBRE_REGULIER_H
#include "membre.h"

class MembreRegulier : public Membre {
public:

	//à faire
	MembreRegulier(const string& nom, TypeMembre typeMembre);

	int getPoints() const;
	vector<Coupon*> getCoupons() const;
	

	void acheterCoupon(Coupon* coupon);
	Membre& operator+=(Coupon* coupon);
	Membre& operator-=(Coupon* coupon);
	void modifierPoints(int points);

	//à faire 
	virtual void ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol) override;


	double calculerPoints(Billet* billet) const;

	//à faire
	virtual void afficherMembre(ostream& o) const;

protected:
	int points_;
	vector<Coupon*> coupons_;
};

#endif