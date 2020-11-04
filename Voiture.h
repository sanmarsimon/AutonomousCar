
#ifndef VOITURE_H
#define VOITURE_H

#include <string>

class Voiture {
public:

	Voiture();
	Voiture(std::string type, int autoMax, int coeffPerte);

	void setType(std::string type);
	void setAutoMax(int autoMax);
	void setAutoRestance(int autoRestante);
	void setCoeffPerte(int coeffPerte);

	std::string getType();
	int getAutoMax();
	int getAutoRestante();
	int getCoeffPerte();

	void conduireVoiture(int distance);
	
private:

	std::string type_;
	int autoMax_;
	int autoRestante_;
	int coeffPerte_;

};
#endif 
