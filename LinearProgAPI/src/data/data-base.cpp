/*
 * data-base.cpp
 *
 *  Created on: 13 août 2014
 *      Author: valentin
 */

# include "data-base.h"

DataBase* DataBase::sDataBase = nullptr;

DataBase::DataBase()
: mNbTotalSites (0)
, mNbWareHouseToBuild (0) {}

DataBase::~DataBase() {}

DataBase*
DataBase::getInstance() {
	return sDataBase == nullptr ? sDataBase = new DataBase() : sDataBase;
}

void
DataBase::fillData(tyr::vector_string_type iVector) {
	if (iVector.size() == 2) {
		mNbTotalSites = tool::stringToInteger(iVector[0]);
		mNbWareHouseToBuild = tool::stringToInteger(iVector[1]);
		mSites.reserve(mNbTotalSites);
	} else if (iVector.size() == 4) {
		Site lNewSite(tool::stringToInteger(iVector[0]),
					  tool::stringToInteger(iVector[1]),
					  tool::stringToInteger(iVector[2]),
					  tool::stringToInteger(iVector[3]));
		mSites.push_back(lNewSite);
	}
}

void
DataBase::readFile(const char* iPath) {
	std::ifstream lIfStream;
	lIfStream.open(iPath);
	std::string lLine;
	if (lIfStream.is_open()) {
	    while (!lIfStream.eof()) {
	      getline(lIfStream, lLine);
	      if (lLine != "") {
	    	  fillData(tool::splitLine(lLine));
	      }
	    }
	} else {
		std::cout << "FAIL : File not found" << std::endl;
	}
}

std::pair<int, int>
DataBase::getCoordinates(std::string iName) {
	for (Site lSite : mSites) {
		if (iName == lSite.mName) {
			return std::make_pair(lSite.mX, lSite.mY);
			break;
		}
	}

	return std::make_pair(0, 0);
}
