#pragma once
/********************************************
* Titre: Travail pratique #5 - gestionnaireCoupons.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#ifndef GESTIONNAIRECOUPONS_H
#define	GESTIONNAIRECOUPONS_H	

#include <vector>

#include "membrePremium.h"
#include "solde.h"
#include "gestionnaireGenerique.h"

class GestionnaireCoupons : public GestionnaireGenerique<Membre, double> {
public:

	double appliquerCoupon(Membre* membre, double prix);
	void acheterCoupon(Membre* membre);
	//int GestionnaireGenerique< Membre, double >::getNombreElements() const {
	//	return 0;														/////////////////A changer 
	//}
};
#endif // !GESTIONNAIRECOUPONS_H



