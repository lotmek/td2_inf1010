/**********************************************************************
 * Cours : INF1010
 * Travail pratique 5
 * Nom: foncteur.h
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussi�res    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/
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
	/****************************************************************************
	 * Fonction:	AjouterCoupon::AjouterCoupon
	 * Description: Constructeur par param�tres qui initialise le conteneur de la classe avec le vecteur pass� en param�tre
	 * Param�tres:	(vector<Coupon*>&) conteneur
	 * Retour:		aucun
	 ****************************************************************************/
	AjouterCoupon(vector<Coupon*>& conteneur) : conteneur_(conteneur) {}

	/****************************************************************************
	 * Fonction:	AjouterCoupon::operator()
	 * Description: Surcharge l'op�rateur () pour ajouter un coupon et retourner le vecteur avec ce nouveau coupon. 
	 * Param�tres:	(Coupon*) coupon � ajouter
	 * Retour:		(vector<Coupon*>) conteneur avec le nouveau coupon
	 ****************************************************************************/
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
	/****************************************************************************
	 * Fonction:	AjouterMembre::AjouterMembre
	 * Description: Constructeur par param�tres qui initialise le conteneur de la classe avec le vecteur pass� en param�tre
	 * Param�tres:	(map<string, Membre*>&) conteneur
	 * Retour:		aucun
	 ****************************************************************************/
	AjouterMembre(map<string, Membre*>& conteneur) : conteneur_(conteneur) {}


	/****************************************************************************
	 * Fonction:	AjouterMembre::AjouterMembre
	 * Description: Surcharge l'op�rateur () pour ajouter un membre et retourner le vecteur avec ce nouveau membre  
	 * Param�tres:	(pair <string, Membre*>) membre
	 * Retour:		(map<string, Membre*>) conteneur avec le nouveau membre
	 ****************************************************************************/
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
	/****************************************************************************
	 * Fonction:	IntervallePrixBillet::IntervallePrixBillet
	 * Description: Constructeur par param�tres qui permet d�initialiser les attributs borne sup�rieure et inf�rieure de la classe. 
	 * Param�tres:	(<string, Membre*>) membre
	 * Retour:		(map<string, Membre*>) conteneur avec le nouveau membre
	 ****************************************************************************/
	IntervallePrixBillet(double borneInf, double borneSup) : borneInf_(borneInf), borneSup_(borneSup) {}

	/****************************************************************************
	 * Fonction:	AjouterMembre::AjouterMembre
	 * Description: Surcharge l'op�rateur () pour v�rifier si le billet passer en param�tre est compris dans l'' intervalle
	 * Param�tres:	(Billet*) billet
	 * Retour:		(bool) vrai ou faux
	 ****************************************************************************/
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