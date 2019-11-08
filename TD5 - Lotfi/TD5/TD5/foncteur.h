/********************************************
* Titre: Travail pratique #5 - foncteur.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/
#pragma once

#include <string>
#include <vector>
#include <map>

#include "coupon.h"
#include "membrePremium.h"

class AjouterCoupon
{
//TODO
public:
	AjouterCoupon(vector<Coupon*>& conteneur) : conteneur_(conteneur) {}
	vector<Coupon*> operator()(Coupon* coupon) {
		for(vector<Coupon*>::iterator it = conteneur_.begin(); it != conteneur_.end(); it++) {
			if (coupon == *it) return conteneur_;
		}

		conteneur_.push_back(coupon);
		return conteneur_;

	}
private :
	vector<Coupon*>& conteneur_;
};


class AjouterMembre
{
//TODO
public:
	AjouterMembre(map<string, Membre*>& conteneur) : conteneur_(conteneur) {}
	map<string, Membre*> operator()(pair<string, Membre*> membre) {
		for (map<string, Membre*>::iterator it = conteneur_.begin(); it != conteneur_.end(); it++) {
			if (membre.second == it->second) return conteneur_;
		}

		conteneur_.insert(membre);
		return conteneur_;

	}
private:
	map<string, Membre*>& conteneur_;
};

class IntervallePrixBillet
{
//TODO
public:
	IntervallePrixBillet(double borneInf, double borneSup) : borneInf_(borneInf), borneSup_(borneSup) {}
	bool operator()(Billet* billet) const {

		if (billet->getPrix() >= borneInf_ && billet->getPrix() <= borneSup_)
			return true;
		else
			return false;
	}
private:
	// Attribut qui represente l'intervalle.
	double borneInf_;
	double borneSup_;
};