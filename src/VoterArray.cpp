#include "VoterArray.hpp"

constexpr int VoterArray::stateSymbols[];

VoterArray::State& VoterArray::operator()(int row, int col)
{
    // Take into account periodic boundary conditions.
    row = (row + m_rowCount) % m_rowCount;
    col = (col + m_colCount) % m_colCount;

    // Return 1D index of 1D array corresponding to the 2D index.
    return m_boardData[col + row * m_colCount];
}

const VoterArray::State& VoterArray::operator()(int row, int col) const
{
    // Take into account periodic boundary conditions we add extra m_rowCount and m_colCount
    // terms here to take into account the fact that the caller may be indexing with -1.
    row = (row + m_rowCount) % m_rowCount;
    col = (col + m_colCount) % m_colCount;

    // Return 1D index of 1D array corresponding to the 2D index.
    return m_boardData[col + row * m_colCount];
}


VoterArray::VoterArray(
	std::default_random_engine &generator,
	int rows,
	int cols,
	double initialOrder
	) : m_rowCount{rows},
		m_colCount{cols},
    m_boardData(rows*cols,VoterArray::Democrat)
{
  // Map the order parameter onto the interval [0:1].
  initialOrder = (initialOrder+1.0)/2.0;

  // Calculate the required number of republican voters.
  int republicanNumber = std::round(initialOrder*(rows*cols));



  // Create a distribution for the lattice sites.
  std::uniform_int_distribution<int> latticeDistribution(0,(rows*cols)-1);

  // Choose the correct number of sites and convert them from democrat to republican.
  int i = 0;
  while(i < republicanNumber)
  {
    // Generate index for site.
    int site = latticeDistribution(generator);
    if(m_boardData[site] != VoterArray::Republican)
    {
      m_boardData[latticeDistribution(generator)] = VoterArray::Republican;
      ++i;
    }
  }


}



int VoterArray::getRows() const
{
    return m_rowCount;
}

int VoterArray::getCols() const
{
    return m_colCount;
}

int VoterArray::getSize() const
{
    return m_colCount * m_rowCount;
}


VoterArray::State VoterArray::update(std::default_random_engine& generator)
{
	// Create a uniform distribution for the rows and columns remembering to subtract 1 for the closed limits.
	std::uniform_int_distribution<int> rowDistribution(0,m_rowCount-1);
	std::uniform_int_distribution<int> colDistribution(0,m_colCount-1);

  int row = rowDistribution(generator);
  int col = colDistribution(generator);



  // Check to see if the selected voter is of the stubborn type and id so return early.
  if((*this)(row,col) == VoterArray::DemocratStubborn ||  (*this)(row,col) == VoterArray::RepublicanStubborn)
  {
    return (*this)(row,col);
  }
  else
  {
    // pick a random nearest neighbour and update the state of the original cell to be this state.
    std::uniform_int_distribution<int> neighbourDistribution(0,3);

    int neighbourRow = row;
    int neighbourCol = col;

    switch (neighbourDistribution(generator))
    {
      case 0:
        neighbourCol++;
        break;

      case 1:
        neighbourRow++;
        break;

      case 2:
        neighbourCol--;
        break;

      case 3:
        neighbourRow--;
        break;
    }

    if((*this)(neighbourRow,neighbourCol) == VoterArray::Republican
    || (*this)(neighbourRow,neighbourCol) == VoterArray::RepublicanStubborn)
    {
      (*this)(row,col) = VoterArray::Republican;
    }
    else
    {
      (*this)(row,col) = VoterArray::Democrat;
    }

    return (*this)(row,col);
  }

}

double VoterArray::orderParameter() const
{
  double sum = 0;
    for(auto const& voter : m_boardData)
    {
      sum += static_cast<int>(stateSymbols[voter]);
    }
  return sum/(m_rowCount*m_colCount);
}


std::ostream& operator<<(std::ostream& out, const VoterArray &board)
{


    int maxRows = board.getRows();
    int maxCols = board.getCols();

    for(int row = 0; row < maxRows; ++row)
    {
        for(int col = 0; col < maxCols; ++ col)
        {
            out << std::showpos << VoterArray::stateSymbols[board(row,col)] << ' ';
        }

        out << '\n';
    }

    return out;
}
