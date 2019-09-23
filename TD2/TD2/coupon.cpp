/**********************************************************************
 * Cours : INF1010
 * Travail pratique 2
 * Nom: coupon.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/
#include "coupon.h"


 /****************************************************************************
   * Fonction:	  Coupon::Coupon
   * Description: Constructeur par défaut.
   * Paramètres:	aucun
   * Retour:		aucun
   ****************************************************************************/
Coupon::Coupon() : 
	code_(""),
	rabais_(0),
	cout_(0)
{
}

/****************************************************************************
 * Fonction:	Coupon::Coupon
 * Description: Constructeur par paramètres.
 * Paramètres:	(const string&) code
 *			    (double) rabais
 *              (int) cout
 * Retour:		aucun
 ****************************************************************************/
Coupon::Coupon(const string& code, double rabais, int cout) :
	code_(code),
	rabais_(rabais),
	cout_(cout)
{
}

/****************************************************************************
 * Fonction:	Coupon::~Coupon
 * Description: Destructeur de Coupon.
 * Paramètres:	aucun
 * Retour:		aucun
 ****************************************************************************/
Coupon::~Coupon()
{
}

/****************************************************************************
 * Fonction:	Coupon::getCode
 * Description: Retourne le code du coupon.
 * Paramètres:	aucun
 * Retour:		(string) code
 ****************************************************************************/
string Coupon::getCode() const
{
	return code_;
}

/****************************************************************************
 * Fonction:	Coupon::getRabais
 * Description: Retourne la valeur du rabais qu<offre le coupon.
 * Paramètres:	aucun
 * Retour:		(double) rabais
 ****************************************************************************/
double Coupon::getRabais() const
{
	return rabais_;
}

/****************************************************************************
 * Fonction:	Coupon::getCout
 * Description: Retourne le coût du coupon (en points).
 * Paramètres:	aucun
 * Retour:		(int) cout
 ****************************************************************************/
int Coupon::getCout() const
{
	return cout_;
}

/****************************************************************************
 * Fonction:	Coupon::setCode
 * Description: Modifie le code du coupon.
 * Paramètres:	(const string&) code
 * Retour:		aucun
 ****************************************************************************/
void Coupon::setCode(const string& code)
{
	code_ = code;
}

/****************************************************************************
 * Fonction:	Coupon::setRabais
 * Description: Modifie la valeur de rabais qu'offre le coupon.
 * Paramètres:	(double) rabais
 * Retour:		aucun
 ****************************************************************************/
void Coupon::setRabais(double rabais)
{
	rabais_ = rabais;
}

/****************************************************************************
 * Fonction:	Coupon::setCout
 * Description: Modifie le coût du coupon.
 * Paramètres:	(int) cout
 * Retour:		aucun
 ****************************************************************************/
void Coupon::setCout(int cout)
{
	cout_ = cout;
}

/****************************************************************************
 * Fonction:	friend operator>
 * Description:	Surcharge l'operateur >
 *				Verifie si le coupon de gauche est supérieur au coupon de droite
 * Paramètres:	(Coupon& coupon1, Coupon& coupon2)
 * Retour:		bool vrai ou faux
 ****************************************************************************/
bool operator>(Coupon& coupon1, Coupon& coupon2) {
	return (coupon1.rabais_ > coupon2.rabais_);
}

/****************************************************************************
 * Fonction:	friend operator<
 * Description:	Surcharge l'operateur <
 *				Verifie si le coupon de gauche est inférieur au coupon de droite
 * Paramètres:	(Coupon& coupon1, Coupon& coupon2)
 * Retour:		bool vrai ou faux
 ****************************************************************************/
bool operator<(Coupon& coupon1, Coupon& coupon2) {
	return (coupon1.rabais_ < coupon2.rabais_);
}

/****************************************************************************
 * Fonction:	friend operator<<
 * Description:	Surcharge l'operateur <<
 *				Affiche les informations du coupon
 * Paramètres:	(ostream& o, const Coupon& coupon)
 * Retour:		ostream& affichage
 ****************************************************************************/
ostream& operator<<(ostream& o, const Coupon& coupon) {
	return o << "\t\t- Coupon " << coupon.code_ << ". Rabais : " << coupon.rabais_ << "." << endl;

}
