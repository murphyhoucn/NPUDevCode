// pyrDown 降采样

#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat img1, img2;

    cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Example2", cv::WINDOW_AUTOSIZE);

    img1 = cv::imread("./google.png");
    cv::imshow("Example1", img1);

    cv::pyrDown(img1, img2);
    cv::imshow("Example2", img2);

    cv::waitKey(0);

    return 0;
}
