// 加入了滑动条的基本浏览窗口

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>

int g_slider_posion = 0;
int g_run = 1;
int g_dontset = 0;
cv::VideoCapture g_cap;

void OnTrackbarSlide(int pos, void *)
{
    g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);
    if(!g_dontset) g_run = 1;
    g_dontset = 0;
}

int main()
{
    cv::namedWindow("Example_2_4", cv::WINDOW_AUTOSIZE);
    g_cap.open("./2024-04-21-104541.webm");

    int frames = (int)g_cap.get(cv::CAP_PROP_FRAME_COUNT);
    int tmpw = (int)g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int tmph = (int)g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    std::cout << "Video has " << frames << " frames of dimensions(" << tmpw << ", " << tmph << ")." << std::endl;

    cv::createTrackbar("Position", "Example_2_4", &g_slider_posion, frames, OnTrackbarSlide);

    cv::Mat frame;

    for(;;)
    {
        if(g_run != 0)
        {
            g_cap >> frame; 
            if(!frame.data) break;
            int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
            g_dontset = 1;
            
            cv::setTrackbarPos("Position", "Example_2_4", current_pos);
            cv::imshow("Example_2_4", frame);

            g_run -= 1; 
        }

        char c = (char)cv::waitKey(10);
        if(c == 's')
        {
            g_run = 1;
            std::cout << "Single step, run = " << g_run << std::endl;
        }
        if(c == 'r')
        {
            g_run = -1;
            std::cout << "Run mode, run = " << g_run << std::endl;
        }
        if(c == 27) break; // ESC键
    }

    return 0;
}