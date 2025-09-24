// 显示图片
#include "opencv2/highgui/highgui.hpp"

int main()
{
    cv::Mat img = cv::imread("./ubuntu-vim-1080p.jpg");
    if(img.empty()) return -1;
    cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example1", img);
    cv::waitKey(0);
    cv::destroyWindow("Example1");
    return 0;
}