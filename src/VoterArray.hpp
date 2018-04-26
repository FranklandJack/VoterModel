#ifndef VoterArray_hpp
#define VoterArray_hpp

#include <vector> // For holding the data in the array.
#include <random> // For generating random numbers.
#include <iostream> // For outputting board.
#include <utility> // For std::pair.
#include <cmath> // For round.

/**
 * \file
 * \brief Class to model a 2D lattice of cells in the Voter model that can be Susceptible, Infected
 * or recovered and can move between those states stochastically.
 */
class VoterArray
{
public:
    /**
     * \enum State
     * \brief Enumeration type to hold the state of the cell, dead or alive.
     */
    enum State
    {
        Republican,
        Democrat,
        RepublicanStubborn,
        DemocratStubborn,
        MAXSTATE,
    };

    /// Look-up table for voter values.
    static constexpr int stateSymbols[MAXSTATE] = {+1,-1,+1,-1};

private:
    /// Member variable that holds number of rows in lattice.
    int m_rowCount;

    /// Member variable that holds number of columns in lattice.
    int m_colCount;

    /// Member variable that holds the actual data in the lattice.
    std::vector<State> m_boardData;

public:
    /**
     *\brief operator overload for getting the state at a site.
     *
     * This method is implemented since the states are stored internally as a 1D vector, hence
     * they need to be indexed in a special way in order to get the site that would correspond to
     * the (i,j) site in matrix notation. This function allows the caller to treat the lattice as a
     * 2D matrix without having to worry about the internal implementation.
     *
     *\param row row index of site.
     *\param col column index of site.
     *\return reference to state stored at site so called can use it or set it.
     */
    VoterArray::State& operator()(int row, int col);

    /**
     *\brief constant version of non-constant counterpart for use with constant VoterArray object.
     *
     * See non-constant version for description.
     *
     *\param row row index of site.
     *\param col column index of site.
     *\return constant reference to state stored at site so called can use it only.
     */
    const VoterArray::State& operator()(int row, int col) const;

    /**
     *\brief Constructor that randomises lattice to an even mix of states.
     *\param rows number of rows on the board.
     *\param cols number of columns on the board.
     *\param probSI probability of going from susceptible to infected state if cell is in contact with infected cell.
     *\param probIR probability of infected site going from infected to recovered.
     *\param probRS probability of recovered site becoming susceptible again.
     *\param generator std::default_random_engine reference for generating random numbers.
     *\param immuneFraction floating point instance representing the fraction of the population who are completely immune to the infection.
     */
    VoterArray(
        std::default_random_engine &generator,
    	int rows = 50,
    	int cols = 50,
    	double initalOrder = 0.5
    	);


    /**
     *\brief Getter for the number of rows.
     *\return Integer value representing the number of rows.
     */
    int getRows() const;

    /**
     *\brief Getter for number of columns.
     *\return Integer value representing the number of columns.
     */
    int getCols() const;

    /**
     *\brief Getter for size of lattice #rows * #columns.
     *\return Integer value representing the size of the lattice.
     */
    int getSize() const;

    /**
     *\brief Updates a random cell in the grid.
     *\param std::default_random_engine reference for random number generation.
     *\return the new updated state of the cell.
     */
    VoterArray::State update(std::default_random_engine& generator);

    double orderParameter() const;

    /**
     *\brief streams the board to an output stream in a nicely formatted way
     *\param out std::ostream reference that is being streamed to
     *\param board VoterArray reference to be printed
     *\return std::ostream reference to output can be chained.
     */
     friend std::ostream& operator<<(std::ostream& out, const VoterArray &board);

};

#endif /* VoterArray_hpp */
