#include <Eigen/Core>
#include <emscripten.h>
#include <iostream>
#include "helpers.h"

extern "C" {

EMSCRIPTEN_KEEPALIVE
void computeHomography(double sourcePts[8], double targetPts[8], double homography[9]) {
    Eigen::Vector2d source[4];
    Eigen::Vector2d target[4];
    for (size_t ptIdx = 0; ptIdx < 4; ptIdx++) {
        source[ptIdx](0) = sourcePts[2*ptIdx];
        source[ptIdx](1) = sourcePts[2*ptIdx+1];
        target[ptIdx](0) = targetPts[2*ptIdx];
        target[ptIdx](1) = targetPts[2*ptIdx+1];
        std::cout << "source[" << ptIdx << "] = " << source[ptIdx] << std::endl;
        std::cout << "target[" << ptIdx << "] = " << target[ptIdx] << std::endl;
    }
    Eigen::Matrix3d H = WPD::Helpers::computeHomography(source, target);
    size_t hIdx = 0;
    for (size_t rowi = 0; rowi < 3; rowi++) {
        for (size_t coli = 0; coli < 3; coli++) {
            homography[hIdx] = H(rowi, coli);
            hIdx++;
        }
    }    
}

}

int main() {
    std::cout << "WebPlotDigitizer WebAssembly Module Loaded" << std::endl;
    return 0;
}