#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <ctime>
#include <string>

using boost::asio::ip::tcp;
using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0); /* open webcam */
    if (!cap.isOpened())
    {
        return -1;
    }

    Mat frame;
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);  /* set width */
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240); /* set height */

    // capture.read(frame);

    // frame=imread("g://tinyproxy.jpg");
    while (true)
    {
        cap >> frame;
        imshow("client", frame);
        waitKey(100);

        frame = (frame.reshape(0, 1)); // to make it continuous
        int num = frame.total();       /* num = 320*240 */
        int num2 = frame.elemSize();   /* mun2 =3 channel */
        int imgSize = frame.total() * frame.elemSize();
        try
        {
            boost::asio::io_service io_service;
            tcp::endpoint end_point(boost::asio::ip::address::from_string("127.0.0.1"), 3200);

            tcp::socket socket(io_service);
            socket.connect(end_point);
            boost::system::error_code ignored_error;

            /*time_t now = time(0);

            std::string message = ctime(&now);
            socket.write_some(boost::asio::buffer(message), ignored_error);*/

            // std::string message(frame.begin<unsigned char>(),frame.end<unsigned char>());
            std::string message((char *)frame.data, 230400); /* the size of mat data is 320*240*3 */
            cout << "sending...." << endl;
            socket.write_some(boost::asio::buffer(message), ignored_error);

            cout << "send image finished" << endl;
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    return 0;
}
