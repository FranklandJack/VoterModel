#include "VoterArray.hpp"
#include "getTimeStamp.hpp"
#include "makeDirectory.hpp"
#include "VoterInputParameters.hpp"
#include "DataArray.hpp"
#include "VoterResults.hpp"
#include "Timer.hpp"
#include <random>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <boost/program_options.hpp>
#include <fstream>
#include <iomanip>
#include <string>

int main(int argc, char const *argv[])
{
/*************************************************************************************************************************
************************************************* Preparations **********************************************************
*************************************************************************************************************************/

    // Start the clock so execution time can be calculated.
    Timer timer;

    // Seed the pseudo random number generator using the system clock.
    unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());

    // Create a generator that can be fed to any distribution to produce pseudo random numbers according to that distribution.
    std::default_random_engine generator(seed);

    // Input parameters.
    int rowCount;
    int colCount;
    double initialOrder;
    int totalSweeps;
    int stubbornNumber;
    std::string outputName;

    // Set up optional command line arguments.
    boost::program_options::options_description desc("Options for Voter simulation");

    // Add all optional command line arguments.
    desc.add_options()

        ("column-count,c", boost::program_options::value<int>(&rowCount)->default_value(50), "The number of rows in the lattice.")
        ("row-count,r", boost::program_options::value<int>(&colCount)->default_value(50), "The number of columns in the lattice.")
        ("initail-order,i", boost::program_options::value<double>(&initialOrder)->default_value(0.0), "Initial value of order parameter.")
        ("sweeps,s", boost::program_options::value<int>(&totalSweeps)->default_value(10000), "The number of sweeps in the simulation.")
        ("stubborn-number,n", boost::program_options::value<int>(&stubbornNumber)->default_value(0), "The number of Stubborn boters in the population.")
        ("output,o",boost::program_options::value<std::string>(&outputName)->default_value(getTimeStamp()), "Name of output directory to save output files into.")
        ("animate,a","Animate the program by printing the current state of the lattice to an output file during simulation")
        ("help,h", "Produce help message");

    // Make arguments available to program.
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc,argv,desc), vm);
    boost::program_options::notify(vm);

    // If the user asks for help display it then exit.
    if(vm.count("help"))
    {
        std::cout << desc << '\n';
        return 1;
    }

    // Create an output directory from either the default time stamp or the user defined string.
    makeDirectory(outputName);

    // Create an output file for the lattice so it can be animated.
    std::fstream latticeOutput(outputName+"/Lattice.dat", std::ios::out);

    // Create an output file for the order parameter which in this case is the fraction of infected states.
    std::fstream orderParameterOutput(outputName+"/OrderParameter.dat", std::ios::out);

    // Create an output file for the input parameters.
    std::fstream inputParametersOutput(outputName+"/Input.txt", std::ios::out);

    // Create an output file for the results.
    std::fstream resultsOutput(outputName+"/Results.txt", std::ios::out);

    // Create a Voter lattice that will be used in the simulation.
    VoterArray lattice(generator,rowCount, colCount, initialOrder);

    // Make the correct number of voters stubborn.

    // Print the initial lattice to an output file.
    latticeOutput << lattice;

    // Create an object to hold the input parameters.
    VoterInputParameters inputParameters
    {
      rowCount,
      colCount,
      initialOrder,
      totalSweeps,
      stubbornNumber,
      outputName
    };

    // Print the input parameters to the command line and to the output file.
    std::cout << inputParameters << '\n';
    inputParametersOutput << inputParameters << '\n';



/*************************************************************************************************************************
************************************************* Main Loop *************************************************************
*************************************************************************************************************************/


   for(int sweep = 0; sweep < totalSweeps; ++sweep )
   {
      // Update the lattice by performing row*col sweeps.
      for(int i = 0; i < lattice.getSize(); ++i)
      {
        lattice.update(generator);
      }

        // Calculate the fraction of infected sites on this sweep.
        double orderParameter = lattice.orderParameter();

        // Output the fraction of infected states and the current sweep.
        orderParameterOutput << sweep << ' ' <<  orderParameter << '\n';

      if(vm.count("animate"))
      {
        // Move to the top of the file.
      latticeOutput.seekg(0,std::ios::beg);

      // Output the current state of the lattice.
      latticeOutput << lattice << std::flush;
      }
   }


/*************************************************************************************************************************
******************************************** Output/Clean Up *************************************************************
**************************************************************************************************************************/

   // Output the results to the command line.
   //std::cout << results << '\n';

   // Output the results to the output file.
   //resultsOutput << results << '\n';

   // Report how long the program took to execute.
   std::cout << std::setw(30) << std::setfill(' ') << std::left << "Time take to execute(s) =    " <<
   std::right << timer.elapsed() << '\n';

   return 0;
}
