/**********************************************************************
 * Cours : INF1010
 * Travail pratique 1
 * Nom: coupon.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussi�res    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#include "coupon.h"

 /****************************************************************************
   * Fonction:	Coupon::Coupon
   * Description: Constructeur par d�faut.
   * Param�tres:	aucun
   * Retour:		aucun
   ****************************************************************************/
Coupon::Coupon() //constructeur par d�faut
{
	code_ = "0000000000";
	rabais_ = 0.0; //aucun rabais
	cout_ = 0;
}

/****************************************************************************
 * Fonction:	Coupon::Coupon
 * Description: Constructeur par param�tres.
 * Param�tres:	(const string&) code
 *			    (double) rabais
 *              (int) cout
 * Retour:		aucun
 ****************************************************************************/
Coupon::Coupon(const string& code, double rabais, int cout)
{
	code_ = code;
	rabais_ = rabais;
	cout_ = cout;
}

/****************************************************************************
 * Fonction:	Coupon::~Coupon
 * Description: Destructeur de Coupon.
 * Param�tres:	aucun
 * Retour:		aucun
 ****************************************************************************/
Coupon::~Coupon() {}



	// Getters

/****************************************************************************
 * Fonction:	Coupon::getCode
 * Description: Retourne le code du coupon.
 * Param�tres:	aucun
 * Retour:		(string) code
 ****************************************************************************/
string Coupon::getCode() const
{
	return code_;
}

/****************************************************************************
 * Fonction:	Coupon::getRabais
 * Description: Retourne la valeur du rabais qu<offre le coupon.
 * Param�tres:	aucun
 * Retour:		(double) rabais
 ****************************************************************************/
double Coupon::getRabais() const
{
	return rabais_;
}

/****************************************************************************
 * Fonction:	Coupon::getRCout
 * Description: Retourne le co�t du coupon (en points).
 * Param�tres:	aucun
 * Retour:		(int) cout
 ****************************************************************************/
int Coupon::getCout() const
{
	return cout_;
}

	// Setters

/****************************************************************************
 * Fonction:	Coupon::setCode
 * Description: Modifie le code du coupon.
 * Param�tres:	(const string&) code
 * Retour:		aucun
 ****************************************************************************/
void Coupon::setCode(const string& code)
{
	code_ = code;
}

/****************************************************************************
 * Fonction:	Coupon::setRabais
 * Description: Modifie la valeur de rabais qu'offre le coupon.
 * Param�tres:	(double) rabais
 * Retour:		aucun
 ****************************************************************************/
void Coupon::setRabais(double rabais)		
{
	rabais_ = rabais;
}

/****************************************************************************
 * Fonction:	Coupon::setCout
 * Description: Modifie le co�t du coupon.
 * Param�tres:	(int) cout
 * Retour:		aucun
 ****************************************************************************/
void Coupon::setCout(int cout)		
{
	cout_ = cout;
}

	//M�thodes d'affichage

/****************************************************************************
 * Fonction:	Coupon::afficherCoupon
 * Description: Affiche le code et le rabais du coupon.
 * Param�tres:	aucun
 * Retour:		aucun
 ****************************************************************************/
void Coupon::afficherCoupon() const
{
	cout << "\t\t-Coupons " << code_ << ".  Rabais : " << rabais_ << "." << endl ; 
}

