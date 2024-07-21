#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include<string>
using namespace std;
using namespace cv;
int main(int argc, char** argv) {
    Mat video_stream;
    int inp;string path;
    namedWindow("Face Detection");
    VideoCapture real_time(0);
    string trained_classifier_location = "C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml";
    CascadeClassifier faceDetector;
    faceDetector.load(trained_classifier_location);
    vector<Rect>faces;
   while (true) {
         faceDetector.detectMultiScale(video_stream, faces, 1.1, 4, CASCADE_SCALE_IMAGE, Size(30, 30));
         real_time.read(video_stream);
         for (int i = 0; i < faces.size(); i++){
         Mat faceROI = video_stream(faces[i]);
         int x = faces[i].x;
         int y = faces[i].y;
         int h = y + faces[i].height;
         int w = x + faces[i].width;
         //rectangle(video_stream, Point(x, y), Point(w, h), Scalar(255, 0, 255), 2, 8, 0);//50 50 255
         rectangle(video_stream, faces[i].tl(), faces[i].br(), Scalar(0,255,0), 3);
         rectangle(video_stream, Point(0,0), Point(300,70), Scalar(50,50,255), FILLED);
          putText(video_stream,to_string(faces.size())+" Face Detected", Point(10, 40), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 1);
         if(!faces.empty()){
            for(const Rect&face:faces){
                rectangle(video_stream,face,Scalar(0,255,0),2);
                putText(video_stream," face found",Point(face.x,face.y-10),FONT_HERSHEY_SIMPLEX,0.7,Scalar(0,255,0),2);
            }
         }
         else{
            putText(video_stream,"face not found",Point(20,50),FONT_HERSHEY_SIMPLEX,0.7,Scalar(0,0,255),2);
         }
         }
         imshow("Face Detection", video_stream);

      if (waitKey(10) == 27){
         break;
      }
   }
   return 0;
}


