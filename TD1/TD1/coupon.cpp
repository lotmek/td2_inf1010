

#include "coupon.h"

Coupon::Coupon() //constructeur par défaut
{
	code_ = "0000000000";
	rabais_ = 0.0 ; //aucun rabais
	cout_ = 0;
}


Coupon::Coupon(const string& code, double rabais, int cout) 
{
	code_ = code;
	rabais_ = rabais;
	cout_ = cout;
}


Coupon::~Coupon(){}

//Méthodes d'accès
string Coupon::getCode()
{
	return code_;
}

double Coupon::getRabais() 
{
	return rabais_;
}

int Coupon::getCout()
{
	return cout_;
}

//Méthodes de modification
void Coupon::setCode(const string& code)
{
	code_ = code;
}

void Coupon::setRabais(double rabais)
{
	rabais_ = rabais;
}

void Coupon::setCout(int cout)
{
	cout_ = cout;
}

//Méthodes d'affichage
void Coupon::afficherCoupon()
{
	cout << "\t\t-Coupons " << code_ << ".  Rabais : " << rabais_ << "." << endl;
}
