/*
 * data-base.hxx
 *
 *  Created on: 13 août 2014
 *      Author: valentin
 */

inline std::vector<Site>
DataBase::getSites() {
	return mSites;
}

inline int
DataBase::getNbTotalSites() {
	return mNbTotalSites;
}

inline int
DataBase::getNbWareHouseToBuild() {
	return mNbWareHouseToBuild;
}
