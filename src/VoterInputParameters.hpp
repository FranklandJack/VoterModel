#ifndef VoterInputParameters_hpp
#define VoterInputParameters_hpp
#include <iostream>
#include <iomanip>
#include <string>
/**
 *\file
 *\class VoterInputParameters
 *\brief Class for easily handling input parameters of Voter simulation.
 *
 * This class essentially just holds some values and has an operator to easily output
 * them to a stream.
 */
class VoterInputParameters
{
public:

	/// Number of rows in lattice.
	int rowCount;
	/// Number of columns in lattice.
	int colCount;

	double initialOrder;

	/// Total number of sweeps in the simulation.
	int sweeps;
	int stubbornNumber;
	/// Output directory.
	std::string outputDirectory;




    /**
	 *\brief operator<< overload for outputting the results.
	 *\param out std::ostream reference that is the stream being outputted to.
	 *\param params constant VoterInputParameters instance to be output.
	 *\return std::ostream reference so the operator can be chained.
	 *
	 * Results will be output in a formatted table for easy viewing in the command line or a file.
	 */
    friend std::ostream& operator<<(std::ostream& out, const VoterInputParameters& params);

};
#endif /* VoterInputParameters_hpp */
