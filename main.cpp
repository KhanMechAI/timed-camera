#include <iostream>
#include <opencv2/opencv.hpp>
#include <ctime>
#include <chrono>
#include <thread>

cv::CommandLineParser init_command_line_parser(int argc, const char** argv ) {
    const std::string keys = "{@delay d |5|Delay in seconds between captures}"
                             "{out-folder o| images | Output directory for images}";
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("This program captures an image from a local camera, if it exists, every 'delay' seconds.");
    return parser;
}

bool is_frame_black(const cv::Mat &frame) {
    cv::Mat gray_frame;
    cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);
    return cv::countNonZero(gray_frame) < 1;
}

int main(int argc, const char** argv) {

    cv::CommandLineParser parser = init_command_line_parser(argc, argv);

    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        exit(-1);
    }

    cv::Mat frame;

    int delay{1};
    bool display{true};

    while (cap.read(frame)) {

        if (display and !is_frame_black(frame) and not frame.empty()) {
            cv::imshow("Capture", frame);
            cap.release();
            int keyboard = cv::waitKey(1);
            if (keyboard == 'q' || keyboard == 27)
                break;
            std::this_thread::sleep_for(std::chrono::seconds (delay));
            if (!cap.isOpened()) {
                cap.open(0);
            }
        }
    }

    return 0;
}
