/**********************************************************************
 * Cours : INF1010
 * Travail pratique 2
 * Nom: membre.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#ifndef COUPON_H
#define COUPON_H

#include <string>
#include <iostream>

using namespace std;

class Coupon {
public:
	// Constructeurs
	Coupon();
	Coupon(const string& code, double rabais, int cout);
	
	~Coupon();

	// Getters
	string getCode() const;
	double getRabais() const;
	int getCout() const;

	// Setters
	void setCode(const string& code);
	void setRabais(double rabais);
	void setCout(int cout);

	// TODO: Surcharger l'operateur >
	friend bool operator>(Coupon& coupon1, Coupon& coupon2);

	// TODO: Surcharger l'operateur <
	friend bool operator<(Coupon& coupon1, Coupon& coupon2);

	// TODO: Remplacer cette methode par l'operateur <<
	friend ostream& operator<<(ostream& o, const Coupon& coupon);
private:
	string code_;
	double rabais_;
	int cout_;
};
#endif // !COUPON_H

