#include "VoterInputParameters.hpp"

std::ostream& operator<<(std::ostream& out, const VoterInputParameters& params)
{
	int outputColumnWidth = 30;
    out << "Input-Parameters..." << '\n';
    out << std::setw(outputColumnWidth) << std::setfill(' ') << std::left << "Rows: " << std::right << params.rowCount << '\n';
    out << std::setw(outputColumnWidth) << std::setfill(' ') << std::left << "Columns: " << std::right << params.colCount << '\n';
    out << std::setw(outputColumnWidth) << std::setfill(' ') << std::left << "Inital-Order: " << std::right << params.initialOrder << '\n';
    out << std::setw(outputColumnWidth) << std::setfill(' ') << std::left << "Sweeps: " << std::right << params.sweeps << '\n';
    out << std::setw(outputColumnWidth) << std::setfill(' ') << std::left << "Stubborn-Number: " << std::right << params.stubbornNumber << '\n';
	out << std::setw(outputColumnWidth) << std::setfill(' ') << std::left << "Output-Directory: " << std::right << params.outputDirectory << '\n';
    return out;
}
