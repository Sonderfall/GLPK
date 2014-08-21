/*
 * all.h
 *
 *  Created on: 25 juin 2014
 *      Author: valentin
 */

#ifndef ALL_H_
# define ALL_H_

# include <cstdio>
# include <cstdint>
# include <cstdlib>
# include <iostream>
# include <sstream>
# include <fstream>

# include <string>
# include <vector>
# include <map>
# include <iterator>
# include <algorithm>
# include <cmath>
# include <cstddef>
# include <climits>

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <glpk.h>
# include <assert.h>

enum GreatValue {
	pInf,
	mInf,
	pBigM,
	mBigM
};

namespace tyr {
	typedef typename std::istream_iterator<std::string> stream_string_type;
	typedef typename std::vector<std::string> vector_string_type;
}

#endif /* ALL_H_ */
