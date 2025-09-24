// GaussionBlur,高斯模糊

#include "opencv2/opencv.hpp"

void example_2_5(const cv::Mat& image)
{
    cv::namedWindow("Example_2_5-in", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Example_2_5-out", cv::WINDOW_AUTOSIZE);

    cv::imshow("Example_2_5-in", image);
    cv::Mat out;
    cv::GaussianBlur(image, out, cv::Size(5, 5), 3, 3);
    cv::GaussianBlur(out, out, cv::Size(5, 5), 3, 3);

    cv::imshow("Example_2_5-out", out);

    cv::waitKey(0);
}

int main()
{
    cv::Mat img = cv::imread("./google.png");
    if(img.empty()) return -1;

    example_2_5(img);

    return 0;

}