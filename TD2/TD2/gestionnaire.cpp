/**********************************************************************
 * Cours : INF1010
 * Travail pratique 2
 * Nom: gestionnaire.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#include "gestionnaire.h"

 /****************************************************************************
  * Fonction:	 Gestionnaire::Gestionnaire
  * Description: Constructeur par défaut.
  * Paramètres:	aucun
  * Retour:		aucun
  ****************************************************************************/
Gestionnaire::Gestionnaire()
{
}

/****************************************************************************
 * Fonction:	Gestionnaire::~Gestionnaire
 * Description: Destructeur de gestionnaire, désaloue aussi la mémoire.
 * Paramètres:	aucun
 * Retour:		aucun
 ****************************************************************************/
Gestionnaire::~Gestionnaire()
{ 
	for (unsigned i = 0; i < membres_.size(); i++) 
	{
		delete membres_[i];
	}
	membres_.clear();

	for (unsigned i = 0; i < coupons_.size(); i++)
	{
		delete coupons_[i];
	}
	coupons_.clear();
}

/****************************************************************************
 * Fonction:	Gestionnaire::getMembres
 * Description: Retourne le vecteur des pointeurs vers les membres.
 * Paramètres:	aucun
 * Retour:		vector<Membre*> vecteur de pointeurs membres
 ****************************************************************************/
vector<Membre*> Gestionnaire::getMembres() const
{
	return membres_;
}

/****************************************************************************
 * Fonction:	Gestionnaire::getCoupons
 * Description: Retourne le vecteur de pointeurs coupons dans le gestionnaire.
 * Paramètres:	aucun
 * Retour:		vector<Coupon*> vecteur de pointeurs coupons
 ****************************************************************************/
vector<Coupon*> Gestionnaire::getCoupons() const
{
	return coupons_;
}

/****************************************************************************
 * Fonction:	Gestionnaire::ajouterMembre
 * Description: Ajoute un membre dans le vecteur de pointeurs membres du
 *				gestionnaire. On alloue un espace mémoire pour le membre en 
 *				parametre. Ainsi, on fera une deep copy, donc de la composition.
 * Paramètres:	(const string&) nomMembre
 * Retour:		aucun
 ****************************************************************************/
void Gestionnaire::ajouterMembre(const string& nomMembre)
{
	Membre* membre = new Membre(nomMembre);
	membres_.push_back(membre);
}

/****************************************************************************
 * Fonction:	Gestionnaire::ajouterCoupon
 * Description: Ajoute un coupon dans le vecteur de pointeurs coupons du 
 *				gestionnaire. On alloue un espace mémoire pour le coupon en 
 *				parametre. Ainsi, on fera une deep copy, donc de la composition.
 * Paramètres:	(const string&) code
 *				(double) rabais
 *				(int) cout
 * Retour:		aucun
 ****************************************************************************/
void Gestionnaire::ajouterCoupon(const string& code, double rabais, int cout)
{
	Coupon* coupon = new Coupon(code, rabais, cout);
	coupons_.push_back(coupon);
}

/****************************************************************************
 * Fonction:	Gestionnaire::trouverMembre
 * Description: Cherche un membre dans le vecteur de pointeurs membres du 
 *				gestionnaire à l'aide du nom fourni en paramètre et de l'operateur ==
 *				que l'on a surcharge dans la classe membre.
 * Paramètres:	(const string&) nomMembre
 * Retour:		(Membre*) le pointeur membre qui a le même nom que le paramètre
 ****************************************************************************/
Membre* Gestionnaire::trouverMembre(const string& nomMembre) const
{
	for (unsigned i = 0; i < membres_.size(); i++) {
		// TODO: Faite cette comparaison avec la surcharge de l'operateur == de la classe Membre
		if (*membres_[i] == nomMembre) {
			return membres_[i];
		}
	}
	cout << "Le membre " << nomMembre << " n'existe pas\n";

	return nullptr;
}

/****************************************************************************
 * Fonction:	Gestionnaire::assignerBillet
 * Description: Ajoute un billet dans le vecteur de pointeurs billets d'un membre.
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
	double prixReel;
	Membre* membre = trouverMembre(nomMembre);

	if (membre == nullptr) {
		return;
	}

	if (utiliserCoupon) {
		prixReel = prixBase - appliquerCoupon(membre, prixBase);
	}
	else {
		prixReel = prixBase;
	}
	membre->ajouterBillet(pnr, prixReel, od, tarif, dateVol);
}

/****************************************************************************
 * Fonction:	Gestionnaire::appliquerCoupon
 * Description: Calcule le meilleur coupon que possède le membre et retourne
 *				la différence à appliquer. On utilise l'operateur > de la
 *				classe coupon ainsi que l'operateur -= que nous avons surchargé dans 
 *				la classe Membre
 * Paramètres:	(Membre*) membre
 *				(double) prix
 * Retour:		(double) la différence à appliquer sur le prix
 ****************************************************************************/
double Gestionnaire::appliquerCoupon(Membre* membre, double prix)
{
	if (membre->getCoupons().size() == 0) {
		cout << "Le membre n'a pas de coupon utilisable\n";
		return 0;
	}

	Coupon* meilleurCoupon = membre->getCoupons()[0];
	vector<Coupon*> coupons = membre->getCoupons();
	for (unsigned i = 1; i < membre->getCoupons().size(); i++) {
		// TODO: Faites cette comparaison par la surcharge de l'operateur > de la classe Coupon
		if (*coupons[i] > *meilleurCoupon) {
			meilleurCoupon = coupons[i];
		}
	}

	// TODO: Utiliser la surcharge de l'operateur -= de la classe Membre plutot qu'utiliser la methode retirerCoupon
	*membre -= meilleurCoupon;

	return prix * meilleurCoupon->getRabais();
}

/****************************************************************************
 * Fonction:	Gestionnaire::acheterCoupon
 * Description: Achète un coupon pour un client (s'il a assez de points).
 * Paramètres:	(const string&) nomMembre
 * Retour:		aucun
 ****************************************************************************/
void Gestionnaire::acheterCoupon(const string& nomMembre)
{
	if (coupons_.size() == 0) {
		cout << "Le gestionnaire n'a pas de coupon!" << endl;
		return;
	}

	Membre* membre = trouverMembre(nomMembre);

	if (membre == nullptr) {
		return;
	}

	Coupon* meilleurCoupon = nullptr;

	for (unsigned i = 0; i < coupons_.size(); i++) {
		if (membre->getPoints() >= coupons_[i]->getCout()) {
			// Si on avait pas encore trouve de meilleur coupon, on fait la premiere assignation
			if (meilleurCoupon == nullptr) {
				meilleurCoupon = coupons_[i];
			}
			// Sinon on compare si le coupon courant a un rabais superieur au meilleur coupon
			// TODO: Faites cette comparaison avec la surcharge de l'operateur > de la classe Coupon
			else if (*coupons_[i] > *meilleurCoupon) {
				meilleurCoupon = coupons_[i];
			}
		}
	}

	if (meilleurCoupon) {
		membre->acheterCoupon(meilleurCoupon);
	}
	else {
		cout << "Le membre ne peut acheter de coupon\n";
	}
}

/****************************************************************************
 * Fonction:	Gestionnaire::operator<<
 * Description: Affiche les informations de tous les membres dans le vecteur de 
 *				membres. On utilise la surcharge d'operateur pour que << renvoie
 *				toutes les informations du membre et que << puisse être appelé
 *				en cascade.
 * Paramètres:	aucun
 * Retour:		(ostream&) o
 ****************************************************************************/
ostream& operator<<(ostream& o, const Gestionnaire& gestionnaire)
{
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";
	for (unsigned i = 0; i < gestionnaire.membres_.size(); i++) {
		o << *(gestionnaire.membres_[i]);
	}

	return o;
}
