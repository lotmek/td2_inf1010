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
};


class AjouterMembre
{
//TODO
};

class IntervallePrixBillet
{
public:
	IntervallePrixBillet(double borneInf, double borneSup)
		:borneInf_(borneInf), borneSup_(borneSup){}

	bool operator()(Billet* billet) const{ //verifie si le prix du billet est dans un intervalle
		if (billet->getPrix() > borneInf_ && billet->getPrix() < borneSup_)
			return true;
		return false;
	}

private:	
	double borneInf_;
	double borneSup_;
};