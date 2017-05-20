#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <string.h>
#include <opencv/cv.h>
#include <stdio.h>
#include "opencv2/photo/photo.hpp"

using namespace cv;
using namespace std;


class ImageEditor
{
public:
    ImageEditor();

    void photoToHdr(uint8_t lowyuv,uint8_t normalyuv,uint8_t highyuv,int photowidth,int photoheight,char *photopath);

private:
    void hdrCale(Mat pic1, Mat pic2, Mat pic3);


private:
    Mat mat1, mat2, mat3, dst_mat, tmp_mat;
    int normalWidth, normalHeight;
    IplImage src1, src2, src3, dst_src, tmp_src;
    double weight;

};

#endif // IMAGEEDITOR_H
