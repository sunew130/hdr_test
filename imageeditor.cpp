#include "imageeditor.h"

ImageEditor::ImageEditor()
{
    weight = 0.5;
}

void ImageEditor::hdrCale(Mat pic1, Mat pic2, Mat pic3){
    int i, j;
    CvScalar s1, s2, s3;

    src1 = pic1;
    src2 = pic2;
    src3 = pic3;
    dst_src = dst_mat;
    tmp_src = tmp_mat;

    cvCvtColor(&src2, &tmp_src, CV_BGR2GRAY);
    for(i=0; i< normalWidth; i++){
        for(j=0; j<normalHeight; j++){
            s1 = cvGet2D(&src1, i, j);
            s2 = cvGet2D(&tmp_src, i, j);
            s3 = cvGet2D(&src3, i, j);
            weight = 0.5 + (127 - s2.val[0]) * 0.002;
            s3.val[0] = (s1.val[0] * weight) + (s3.val[0] * (1-weight));
            s3.val[1] = (s1.val[1] * weight) + (s3.val[1] * (1-weight));
            s3.val[2] = (s1.val[2] * weight) + (s3.val[2] * (1-weight));
            cvSet2D(&dst_src, i, j, s3);
        }
    }

}



void ImageEditor::photoToHdr(uint8_t lowyuv,uint8_t normalyuv,uint8_t highyuv,int photowidth,int photoheight,char *photopath)
{
    IplImage *lowimage ;
    lowimage = cvCreateImage(cvSize(photowidth,photoheight),8,3);
    lowimage->imageData = (char *)lowyuv;

    IplImage *normalimage ;
    normalimage = cvCreateImage(cvSize(photowidth,photoheight),8,3);
    normalimage->imageData = (char *)normalyuv;

    IplImage *highlimage ;
    highlimage = cvCreateImage(cvSize(photowidth,photoheight),8,3);
    highlimage->imageData = (char *)highyuv;

    mat1 = cvarrToMat(lowimage);
    mat2 = cvarrToMat(normalimage);
    mat3 = cvarrToMat(highlimage);

    normalWidth = mat2.rows;
    normalHeight = mat2.cols;
    dst_mat = Mat(photowidth, photoheight, CV_8UC3, cv::Scalar(0, 0, 0));
    tmp_mat = Mat(photowidth, photoheight, CV_8UC1, cv::Scalar(0, 0, 0));

    hdrCale(mat1, mat2, mat3);

    imwrite(photopath, dst_mat);
}
