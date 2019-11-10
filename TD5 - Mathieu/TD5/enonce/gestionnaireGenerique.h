/********************************************
* Titre: Travail pratique #5 - GestionnaireGenerique.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#pragma once
#ifndef GESTIONNAIREGENERIQUE_H
#define GESTIONNAIREGENERIQUE_H


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
	GestionnaireGenerique() {};
	C getConteneur() const {};
	void ajouter(const T& t) {};
	int getNombreElements() const;

protected:
	C conteneur_;
};


#endif // !GESTIONNAIREGENERIQUE_H

		//////Implementation
template<typename T, typename C, typename FoncteurAjouter>
C GestionnaireGenerique< T, C, FoncteurAjouter>::getConteneur() const {
	return conteneur_;
}

template<typename T, typename C, typename FoncteurAjouter>
int GestionnaireGenerique< T, C, FoncteurAjouter>::getNombreElements() const {
	return conteneur_.size();														/////////////////A changer 
}

//template<typename T, typename C>






