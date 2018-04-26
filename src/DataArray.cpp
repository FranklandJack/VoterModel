#include "DataArray.hpp"

DataArray::DataArray():m_size{0}{}

DataArray::DataArray(int size)
{
    m_data.reserve(size);
}

double& DataArray::operator[](int index)
{
    return m_data[index];
}

const double& DataArray::operator[](int index) const
{
    return m_data[index];
}

void DataArray::push_back(double point) 
{
    m_data.push_back(point);
    m_size++;
}

void DataArray::pop_back()
{
    m_data.pop_back();
    m_size--;
}

void DataArray::reserve(int size)
{
    m_data.reserve(size);
}

double DataArray::sum() const
{
    double sum = 0;
    for(const auto& point : m_data)
    {
        sum += point;
    }

    return sum;
}


double DataArray::mean() const
{
    double sum = 0;

    for(const auto& point : m_data)
    {
        sum += point;
    }

    return sum/m_size;
}

double DataArray::squareMean() const
{
	double sum = 0;

    for(const auto& point : m_data)
    {
        sum += point*point;
    }

    return sum/m_size;

}


double DataArray::error() const
{
    double sum = 0;

    for(const auto& point : m_data)
    {
        sum += point*point;
    }

    double meanSquared = sum / m_size;
    double mean        = (*this).mean();

    return sqrt((meanSquared - mean * mean) / (m_size - 1));

}




std::ostream& operator<<(std::ostream& out, const DataArray& data)
{
    int index = 0;
    for(const auto& point : data.m_data)
    {
        out << index++ << ' ' << point << '\n';
    }

    return out;
}

double DataArray::autoCorrelation(int t) const
{
    double term1          = 0;
    double mean_m         = 0;
    double mean_mSquared  = 0;

    for(int point = 0; point < m_size; ++point)
    {
        term1 += m_data[point]*m_data[(point+t)%m_size];
        mean_m += m_data[point];
        mean_mSquared += m_data[point] * m_data[point];
    }

    term1         /= m_size;
    mean_m        /= m_size;
    mean_mSquared /= m_size;

    double normalisation = mean_mSquared - mean_m * mean_m;
    double term2 = mean_m * mean_m;

    return (term1-term2)/normalisation;
}

std::vector<double> DataArray::autoCorrelation(int t1, int t2) const
{
    std::vector<double> autoCorrelationData;
    autoCorrelationData.reserve(t2-t1);
    for(int t = t1; t < t2; ++t)
    {
        autoCorrelationData.push_back(autoCorrelation(t));
    }

    return autoCorrelationData;
}

int DataArray::getSize() const
{
	return m_size;
}