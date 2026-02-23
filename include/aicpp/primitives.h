#ifndef AICPP_PRIMITIVES_H
#define AICPP_PRIMITIVES_H

#include <any>
#include <vector>

namespace aicpp
{
    namespace primitives
    {
        ///std::vector<Eigen::MatrixXi> hmirror(std::vector<Eigen::MatrixXi> arg0); // mirroring along horizontal
        std::any hmirror(std::vector<std::any> const& args);

        ///std::vector<Eigen::MatrixXi> vmirror(std::vector<Eigen::MatrixXi> arg0); // mirroring along vertical
        std::any vmirror(std::vector<std::any> const& args);

        ///std::vector<Eigen::MatrixXi> dmirror(std::vector<Eigen::MatrixXi> arg0); // mirroring along diagonal
        std::any dmirror(std::vector<std::any> const& args);

        ///std::vector<Eigen::MatrixXi> rot90(std::vector<Eigen::MatrixXi> arg0); // quarter clockwise rotation
        std::any rot90(std::vector<std::any> const& args);
		
        ///std::vector<Eigen::MatrixXi> rot180(std::vector<Eigen::MatrixXi> arg0); // half rotation
        std::any rot180(std::vector<std::any> const& args);
		
        ///std::vector<Eigen::MatrixXi> rot270(std::vector<Eigen::MatrixXi> arg0); // quarter anticlockwise rotation
        std::any rot270(std::vector<std::any> const& args);
		
        ///std::vector<Eigen::MatrixXi> swap(std::vector<Eigen::MatrixXi> arg0, int arg1, int arg2); // color switching
        std::any swap(std::vector<std::any> const& args);
		
        ///std::vector<std::pair<int, int> > ofcolor(std::vector<Eigen::MatrixXi> arg0, int arg1); // indices of all grid cells with value
        std::any ofcolor(std::vector<std::any> const& args);
		
        ///std::vector<Eigen::MatrixXi> fill(std::vector<Eigen::MatrixXi> arg0, int arg1, std::vector<std::pair<int, std::pair<int, int> > > arg2); // fill value at indices
        std::any fill(std::vector<std::any> const& args);
        
        ///std::vector<Eigen::MatrixXi> upscale(std::vector<Eigen::MatrixXi> arg0, int arg1); // upscale grid
        std::any upscale(std::vector<std::any> const& args);
        
        ///std::vector<Eigen::MatrixXi> hconcat(std::vector<Eigen::MatrixXi> arg0, std::vector<Eigen::MatrixXi> arg1); // concatenate two grids horizontally
        std::any hconcat(std::vector<std::any> const& args);
        
        ///std::vector<Eigen::MatrixXi> vconcat(std::vector<Eigen::MatrixXi> arg0, std::vector<Eigen::MatrixXi> arg1); // concatenate two grids vertically
        std::any vconcat(std::vector<std::any> const& args);
        
        ///std::vector<Eigen::MatrixXi> replace(std::vector<Eigen::MatrixXi> arg0, int arg1, int arg2); // color substitution
        std::any replace(std::vector<std::any> const& args);
    }
}

#endif // AICPP_PRIMITIVES_H
