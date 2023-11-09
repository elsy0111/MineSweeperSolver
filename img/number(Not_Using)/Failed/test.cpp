#include<opencv2/opencv.hpp>

int main (int argc, char *argv[])
{
  cv::Mat bgr = cv::imread("c:/opencv/sources/samples/data/fruits.jpg");
  cv::imshow("", bgr);
  cv::waitKey(0);
  cv::destroyAllWindows();

  return 0;
}
