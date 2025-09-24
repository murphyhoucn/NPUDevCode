// pyrdown两次然后使用canny进行边缘检测

#include <opencv2/opencv.hpp>

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

    cv::waitKey(0);

    return 0;    
}