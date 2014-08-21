/*
 * data-base.h
 *
 *  Created on: 13 août 2014
 *      Author: valentin
 */

#ifndef DATA_BASE_H_
# define DATA_BASE_H_

# include "../header/all.h"
# include "../tools/tools.h"

struct Site {
	int mNb;
	int mX;
	int mY;
	int mStock;
	std::string	mName;

	Site(int iNb, int iX, int iY, int iStock)
	 : mNb (iNb)
	, mX (iX)
	, mY (iY)
	, mStock (iStock)
	, mName ("Site "){
		mName.append(tool::integerToString(iNb));
	}
};

class DataBase {
public:
	virtual ~DataBase();

public:
	static DataBase* getInstance();

public:
	void readFile(const char* iPath);
	std::pair<int, int> getCoordinates(std::string iName);
	std::vector<Site> getSites();
	int getNbWareHouseToBuild();
	int getNbTotalSites();

private:
	void fillData(tyr::vector_string_type iVector);

private:
	DataBase();
	static DataBase* sDataBase;

private:
	int mNbTotalSites;
	int mNbWareHouseToBuild;
	std::vector<Site> mSites;

};

# include "data-base.hxx"

#endif /* DATA_BASE_H_ */
