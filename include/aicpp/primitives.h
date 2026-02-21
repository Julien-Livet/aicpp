#ifndef AICPP_PRIMITIVES_H
#define AICPP_PRIMITIVES_H

#include <any>
#include <vector>

namespace aicpp
{
    namespace primitives
    {
        ///std::map<int, int> inferColorMapping(std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> > arg0); // Map given locations of arrays
        std::any inferColorMapping(std::vector<std::any> const& args);

        ///std::vector<Eigen::MatrixXi> fliplr(std::vector<Eigen::MatrixXi> arg0); // Flip left and right columns
        std::any fliplr(std::vector<std::any> const& args);

        ///std::vector<Eigen::MatrixXi> flipud(std::vector<Eigen::MatrixXi> arg0); // Flip up and down rows
        std::any flipud(std::vector<std::any> const& args);

        ///std::vector<Eigen::MatrixXi> map(std::vector<Eigen::MatrixXi> arg0, std::map<int, int> arg1); // Map cells of arrays from a mapping
        std::any map(std::vector<std::any> const& args);

        ///std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > sameElement(std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > arg0, bool arg1); // Pair a list of index pairs where the elements are the same considering first or second element of a pair (a pair is a grid location)
        std::any sameElement(std::vector<std::any> const& args);

        ///std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > regionPairs(std::vector<std::vector<std::vector<std::pair<int, int> > > > arg0); // Pair a list of regions (a region is a list of connected pairs of same value, a pair is a grid location)
        std::any regionPairs(std::vector<std::any> const& args);

        ///std::vector<Eigen::MatrixXi> segments(std::vector<Eigen::MatrixXi> arg0, std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > arg1, int arg2, bool arg3, bool arg4); // Pair a list of regions (a region is a list of connected pairs of same value, a pair is a grid location)
        std::any segments(std::vector<std::any> const& args);
    }
}

#endif // AICPP_PRIMITIVES_H
