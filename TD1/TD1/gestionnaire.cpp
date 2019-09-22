/**********************************************************************
 * Cours : INF1010
 * Travail pratique 1
 * Nom: gestionnaire.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#include "gestionnaire.h"


/*****************************************************************************************
*							  RÉPONSES AUX QUESTIONS DU TD				  		         *
*																						 *
* 1) La classe membre contient un attribut de type Coupon** qui est un double pointeur,	 *
*	ce dernier possède un destructeur externe, provenant de la classe Coupon et 		 *
*	n'est pas inclut dans la classe Membre. Par conséquent, le lien qui relit ces		 *
*	deux classes est une aggrégation par pointeur.										 *
*																						 *
* 2) Un const s'assure que la méthode codée n'entrainera aucune modification sur		 *
*	les attributs de l'objet															 *
******************************************************************************************/



// TODO: Implementer toutes les methodes

 /****************************************************************************
  * Fonction:	 Gestionnaire::Gestionnaire
  * Description: Constructeur par défaut.
  * Paramètres:	aucun
  * Retour:		aucun
  ****************************************************************************/
Gestionnaire::Gestionnaire()
{
	capaciteMembres_ = capaciteCoupons_ = CAPACITE_INITIALE;
	membres_ = new Membre *[capaciteMembres_];
	nbMembres_ = 0;
	coupons_ = new Coupon *[capaciteCoupons_];
	nbCoupons_ = 0;

}

/****************************************************************************
 * Fonction:	Gestionnaire::~Gestionnaire
 * Description: Destructeur de gestionnaire
 * Paramètres:	aucun
 * Retour:		aucun
 ****************************************************************************/
Gestionnaire::~Gestionnaire() {}

	// Getters

/****************************************************************************
 * Fonction:	Gestionnaire::getMembres
 * Description: Retourne la liste des membres.
 * Paramètres:	aucun
 * Retour:		(Membre**) tableau de membres
 ****************************************************************************/
Membre** Gestionnaire::getMembres() const
{
	return membres_;
}

/****************************************************************************
 * Fonction:	Gestionnaire::getNbMembres
 * Description: Retourne le nombre membres.
 * Paramètres:	aucun
 * Retour:		(int) nombre de membres
 ****************************************************************************/
int Gestionnaire::getNbMembres() const
{
	return nbMembres_;
}

/****************************************************************************
 * Fonction:	Gestionnaire::getCapaciteMembres
 * Description: Retourne la capacité du tableau de membres.
 * Paramètres:	aucun
 * Retour:		(int) capacité du tableau de membres
 ****************************************************************************/
int Gestionnaire::getCapaciteMembres() const
{
	return capaciteMembres_;
}

/****************************************************************************
 * Fonction:	Gestionnaire::getCoupons
 * Description: Retourne la liste de coupons dans le gestionnaire.
 * Paramètres:	aucun
 * Retour:		(Coupon**) tableau de coupona
 ****************************************************************************/
Coupon** Gestionnaire::getCoupons() const
{
	return coupons_;
}

/****************************************************************************
 * Fonction:	Gestionnaire::getCoupons
 * Description: Retourne le nombre de coupons.
 * Paramètres:	aucun
 * Retour:		(int) nombre de coupons
 ****************************************************************************/
int Gestionnaire::getNbCoupons() const
{
	return nbCoupons_;
}

/****************************************************************************
 * Fonction:	Gestionnaire::getCapaciteCoupons
 * Description: Retourne la capacité du tableau de coupons.
 * Paramètres:	aucun
 * Retour:		(int) capacité du tableau de coupons
 ****************************************************************************/
int Gestionnaire::getCapaciteCoupons() const
{
	return capaciteCoupons_;
}

	// Setters

/****************************************************************************
 * Fonction:	Gestionnaire::ajouterMembre
 * Description: Ajoute un membre dans le tableau de membres du gestionnaire.
 *				On vérifie si la capacité du tableau est suffisante.
 *				Si ce n'est pas le cas, on double la capacité.
 * Paramètres:	(const string&) nomMembre
 * Retour:		aucun
 ****************************************************************************/
void Gestionnaire::ajouterMembre(const string& nomMembre)
{

	if (capaciteMembres_ <= nbMembres_) {
		capaciteMembres_ *= 2;
		Membre** nouveauTableau = new Membre *[capaciteMembres_];
		for (int i = 0; i < nbMembres_; i++) {
			nouveauTableau[i] = membres_[i];
		}
		delete[] membres_;
		membres_ = nouveauTableau;
	}

	Membre* nouveauMembrePtr = new Membre(nomMembre);
	membres_[nbMembres_++] = nouveauMembrePtr;

}

/****************************************************************************
 * Fonction:	Gestionnaire::ajouterCoupon
 * Description: Ajoute un coupon dans le tableau de coupons du gestionnaire.
 *				On vérifie si la capacité du tableau est suffisante.
 *				Si ce n'est pas le cas, on double la capacité.
 * Paramètres:	(const string&) code
 *				(double) rabais
 *				(int) cout
 * Retour:		aucun
 ****************************************************************************/
void Gestionnaire::ajouterCoupon(const string& code, double rabais, int cout)
{
	if (capaciteCoupons_ <= nbCoupons_) {
		capaciteCoupons_ *= 2;
		Coupon** nouveauCoupon = new Coupon *[capaciteCoupons_];
		for (int i = 0; i < nbCoupons_; i++) {
			nouveauCoupon[i] = coupons_[i];
		}
		delete[] coupons_;
		coupons_ = nouveauCoupon;
	}

	Coupon* nouveauCouponPtr = new Coupon(code, rabais, cout);
	coupons_[nbCoupons_++] = nouveauCouponPtr;

}

/****************************************************************************
 * Fonction:	Gestionnaire::trouverMembre
 * Description: Cherche un membre dans le tableau de membres du gestionnaire
 *				à l'aide du nom fourni en paramètre.
 * Paramètres:	(const string&) nomMembre
 * Retour:		(Membre*) le membre qui a le même nom que le paramètre
 ****************************************************************************/
Membre* Gestionnaire::trouverMembre(const string& nomMembre)
{
	for (int i = 0; i < nbMembres_; i++) {
		if (membres_[i]->getNom() == nomMembre)
			return membres_[i];
	}
	cout << "Le membre " << nomMembre << " n'existe pas.\n";
	return nullptr;
}

/****************************************************************************
 * Fonction:	Gestionnaire::assignerBillet
 * Description: Ajoute un billet dans le tableau de billets d'un membre.
 *				Permet aussi d'appliquer un coupon pour baisser le prix du billet.
 * Paramètres:	(const string&) nomMembre
 *				(const string&) pnr
 *				(double) prixBase
 *				(const string&) od
 *				(TarifBillet tarif)
 *				(const string&) dateVol
 *				(bool) utiliserCoupon)
 * Retour:		aucun
 ****************************************************************************/
void Gestionnaire::assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol, bool utiliserCoupon)
{
	Membre* membreAssigne = trouverMembre(nomMembre);
	if (utiliserCoupon == true)
	{
		prixBase = prixBase - appliquerCoupon(membreAssigne, prixBase);
	}
	membreAssigne->ajouterBillet(pnr, prixBase, od, tarif, dateVol);

}

/****************************************************************************
 * Fonction:	Gestionnaire::appliquerCoupon
 * Description: Calcule le meilleur coupon que possède le membre et retourne
 *				la différence à appliquer.
 * Paramètres:	(Membre*) membre
 *				(double) prix
 * Retour:		(double) la différence à appliquer sur le prix
 ****************************************************************************/
double Gestionnaire::appliquerCoupon(Membre* membre, double prix)
{
	double rabais = 0.0;
	int indiceCoupon;
	Coupon** tableauCouponsMembre = membre->getCoupons();
	for (int i = 0; i < membre->getNbCoupons(); i++) {
		if (rabais < tableauCouponsMembre[i]->getRabais()) {		
			rabais = tableauCouponsMembre[i]->getRabais();			
			indiceCoupon = i;										
		}															
	}

	if (rabais == 0.0) {
		cout << "Le membre n'a pas de coupon utilisable\n";
	}
	else 
		membre->retirerCoupon(membre->getCoupons()[indiceCoupon]);		
	return rabais * prix;
}

/****************************************************************************
 * Fonction:	Gestionnaire::acheterCoupon
 * Description: Achète un coupon pour un client (s'il a assez de points).
 * Paramètres:	(const string&) nomMembre
 * Retour:		aucun
 ****************************************************************************/
void Gestionnaire::acheterCoupon(const string& nomMembre)
{

	Membre* membreAcheteur = trouverMembre(nomMembre);
	int nbPointsClient = membreAcheteur->getPoints();
	Coupon* meilleurCoupon = new Coupon;
	bool trouverCoupon = false;
	for (int i = 0; i < nbCoupons_; i++)
	{
		if ((coupons_[i]->getCout() >= meilleurCoupon->getCout()) && (nbPointsClient >= coupons_[i]->getCout())) {
			meilleurCoupon = coupons_[i];
			trouverCoupon = true;
		}

	}
	if (trouverCoupon == true)
		membreAcheteur->acheterCoupon(meilleurCoupon);
	else cout << "Le membre ne peut pas acheter de coupon\n";
}

/****************************************************************************
 * Fonction:	Gestionnaire::afficherInfos
 * Description: Affiche les informations de tous les membres dans 
 *				le tableau de membres.
 * Paramètres:	aucun
 * Retour:		aucun
 ****************************************************************************/
void Gestionnaire::afficherInfos() const
{
	for (int i = 0; i < nbMembres_; i++)
		membres_[i]->afficherMembre();

}
