/**********************************************************************
 * Cours : INF1010
 * Travail pratique 5
 * Nom: gestionnaireGenerique.h
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#pragma once

#include <algorithm>
#include "foncteur.h"

using namespace  std;

/*              
	* T   = pair<string, Membre*> ou Coupon*; 
	* Conteneur   = map<string, Membre*> ou vector<Coupon*>; 
	* FoncteurAjouter = AjouterMembre ou AjouterCoupon
*/

template<typename T, typename C, typename FoncteurAjouter>
class GestionnaireGenerique
{
public:
	C getConteneur() const;
	void ajouter(T t);
	int getNombreElements() const;

protected:
	C conteneur_;
};


/****************************************************************************
 * Fonction:	GestionnaireGenerique<T,C,FoncteurAjouter>::getConteneur
 * Description: Retourne une copie du conteneur
 * Paramètres:	aucun
 * Retour:		(C) copie du conteneur
 ****************************************************************************/
template<typename T, typename C, typename FoncteurAjouter>
C GestionnaireGenerique<T, C, FoncteurAjouter>::getConteneur() const
{
	return conteneur_;
}

/****************************************************************************
 * Fonction:	GestionnaireGenerique<T,C, FoncteurAjouter>::ajouter
 * Description: Ajoute un objet de type T dans le conteneur
 * Paramètres:	(T) t
 * Retour:		aucun
 ****************************************************************************/
template<typename T, typename C, typename FoncteurAjouter>
void GestionnaireGenerique<T, C, FoncteurAjouter>::ajouter(T t)
{
	FoncteurAjouter c = FoncteurAjouter(conteneur_);
	c(t);
}


/****************************************************************************
 * Fonction:	GestionnaireGenerique<T,C, FoncteurAjouter>::getNombreElements
 * Description: Retourne le nombre d'élements dans le conteneur
 * Paramètres:	aucun
 * Retour:		(int) taille du conteneur
 ****************************************************************************/
template<typename T, typename C, typename FoncteurAjouter>
int GestionnaireGenerique<T, C, FoncteurAjouter>::getNombreElements() const
{
	return conteneur_.size();
}
