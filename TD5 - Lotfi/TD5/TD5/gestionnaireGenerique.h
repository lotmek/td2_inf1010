/********************************************
* Titre: Travail pratique #5 - GestionnaireGenerique.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#pragma once

#include <algorithm>
#include "foncteur.h"

using namespace  std;

/*
    class GestionnaireGenerique

    Méthodes :
    C getConteneur() const;
    void ajouter(const T& t);
    int getNombreElements() const;
 
    Attributs :
    C conteneur_;
*/

/*              
	* T   = pair<string, Membre*> ou Coupon*; 
	* Conteneur   = map<string, Membre*> ou vector<Coupon*>; 
	* FoncteurAjouter = AjouterMembre ou AjouterCoupon
*/

template<typename T, typename C, typename FoncteurAjouter>
class GestionnaireGenerique
{
public:
	C getConteneur() const 
	{
		return conteneur_;
	}

	void ajouter(T t) 
	{
		FoncteurAjouter c = FoncteurAjouter(conteneur_);
		c(t);
	}

	int getNombreElements() const
	{
		return conteneur_.size();
	}

protected:
	C conteneur_;
};
