// pyrdown两次然后使用canny进行边缘检测

#include <opencv2/opencv.hpp>
#include <iostream>


int main()
{
    cv::Mat img_rgb = cv::imread("./opencv.png");
    cv::Mat img_gray, img_pyr, img_pyr2, img_cny;

    cv::cvtColor(img_rgb, img_gray, cv::COLOR_BGR2GRAY);
    cv::pyrDown(img_gray, img_pyr);
    cv::pyrDown(img_pyr, img_pyr2);
    cv::Canny(img_pyr2, img_cny, 10, 100, 3, true);
    
    cv::namedWindow("Example_2_8", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example_2_8", img_cny);

    int x = 16, y = 32;
    cv::Vec3b intensity = img_rgb.at<cv::Vec3b>(y, x);

    uchar blue = intensity[0];
    uchar green = intensity[1];
    uchar red = intensity[2];

    std::cout << "At (x, y) = (" << x << ", " << y  << "): \
    (blue, green, red) = (" << (uchar)blue << ", "<< (uchar)green << ", "<< (uchar)red << ")"\ 
    << std::endl;

    std::cout << "Gray pixel there is: " << (unsigned int)img_gray.at<uchar>(y,x) << std::endl;

    x /= 4; y /= 4;

    std::cout << "Pyramid2 pixel there is: " << (unsigned int)img_pyr2.at<uchar>(y, x) << std::endl;

    img_cny.at<uchar>(x, y) = 128;
    cv::waitKey(0);

    return 0;    
}