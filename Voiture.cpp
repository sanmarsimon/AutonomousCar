#include "Voiture.h"

Voiture::Voiture()
{
	type_ = "null";
	autoMax_ = 0;
	autoRestante_ = 0;
	coeffPerte_ = 0;
}

Voiture::Voiture(std::string type, int autoMax, int coeffPerte):
	type_(type),
	autoMax_(autoMax),
	autoRestante_(autoMax),
	coeffPerte_(coeffPerte)
{
}

void Voiture::setType(std::string type)
{
	type_ = type;
}

void Voiture::setAutoMax(int autoMax)
{
	autoMax_ = autoMax;
	autoRestante_ = autoMax_;
}

void Voiture::setAutoRestance(int autoRestante)
{
	autoRestante_ = autoRestante;
}

void Voiture::setCoeffPerte(int coeffPerte)
{
	coeffPerte_ = coeffPerte;
}

std::string Voiture::getType()
{
	return type_;
}

int Voiture::getAutoMax()
{
	return autoMax_;
}

int Voiture::getAutoRestante()
{
	return autoRestante_;
}

int Voiture::getCoeffPerte()
{
	return coeffPerte_;
}

void Voiture::conduireVoiture(int distance)
{
	autoRestante_ = autoRestante_ - (coeffPerte_ * distance);
}



