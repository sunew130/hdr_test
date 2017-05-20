#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <string.h>
#include <opencv/cv.h>
#include <stdio.h>
#include "opencv2/photo/photo.hpp"
#include "imageeditor.h"
using namespace cv;

char highpicName[20];
char normalpicName[20];
char lowpicName[20];
Mat mat1, mat2, mat3, dst_mat, tmp_mat;
int highWidth, highHeight;
int normalWidth, normalHeight;
int lowWidth, lowHeight;
IplImage src1, src2, src3, dst_src, tmp_src;
double weight=0.5;


void hdrCale(Mat pic1, Mat pic2, Mat pic3){
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



void photoToHdr(uint8_t lowyuv,uint8_t normalyuv,uint8_t highyuv,int photowidth,int photoheight)
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

    imwrite("HDR.jpg", dst_mat);
}


int main(int argc, char *argv[]){

    ImageEditor *iv = new ImageEditor;

    IplImage* image_1 = cvLoadImage("/media/yateks/3CE3-BF68/2016/11/10/0.jpg");
    IplImage* image_2= cvLoadImage("/media/yateks/3CE3-BF68/2016/11/10/1.jpg");
    IplImage* image_3 = cvLoadImage("/media/yateks/3CE3-BF68/2016/11/10/2.jpg");

    //IplImage *dst = cvCreateImage(cvGetSize(image_1),image_1->depth,image_1->nChannels);

    //cvSmooth(image_1,dst,CV_BLUR,5);

    //cvNamedWindow("TEST");
    //cvShowImage("TEST",dst);
    //cvWaitKey(0);


    mat1 = cvarrToMat(image_1);
    mat2 = cvarrToMat(image_2);
    mat3 = cvarrToMat(image_3);
    //highWidth = mat1.rows;
    //highHeight = mat1.cols;
    normalWidth = mat2.rows;
    normalHeight = mat2.cols;
    //lowWidth = mat3.rows;
    //lowHeight = mat3.cols;
    dst_mat = Mat(normalWidth, normalHeight, CV_8UC3, cv::Scalar(0, 0, 0));
    tmp_mat = Mat(normalWidth, normalHeight, CV_8UC1, cv::Scalar(0, 0, 0));

    hdrCale(mat1, mat2, mat3);

    imshow("normal", mat2);
    imshow("HDR", dst_mat);
    imwrite("HDR.jpg", dst_mat);
    cv::waitKey(0);
    return 0;
}
