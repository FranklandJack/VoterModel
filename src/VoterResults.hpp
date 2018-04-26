#ifndef VoterResults_hpp
#define VoterResults_hpp
#include <iostream>
#include <iomanip>

/**
 *\file
 *\class VoterResults
 *\brief Class for easily handling results of Voter simulation.
 *
 * This class essentially just holds some values and has an operator to easily output
 * them to a stream.
 */
class VoterResults
{
public:
	/// Order parameter.
	double orderParameter;

	/**
	 *\brief operator<< overload for outputting the results.
	 *\param out std::ostream reference that is the stream being outputted to.
	 *\param results constant VoterResults instance to be output.
	 *\return std::ostream reference so the operator can be chained.
	 *
	 * Results will be output in a formatted table for easy viewing in the command line or a file.
	 */
	friend std::ostream& operator<<(std::ostream& out, const VoterResults &results);
};

#endif /* VoterResults_hpp */
