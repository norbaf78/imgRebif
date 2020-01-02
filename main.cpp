#include <QCoreApplication>
#include <QDir>
#include <QTextStream>
#include <QDirIterator>
#include <QTime>
#include <QString>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <QFile>

//#define DEBUG



//#define IMAGES_ALREADY_AVAILABLE

using namespace std;
using namespace cv;

Point capturePoint;// point coordinates, global variable;
bool continue_procedure = false;


int main(int argc, char *argv[])

{
    QCoreApplication a(argc, argv);

    QTextStream out(stdout);
    Mat image;
//    Mat image_new;
//    Mat image_small_clipped;
//    Rect roi;
    int count = 0;
    int rand_number_from0tothis = 10000;
    const int images_in_x = 5;
    const int images_in_y =6;
    const int border_pixel = 20;    //
    const int border_pixel_new = 30;  // 170:30(mm) = 12:x(mm) -> 2.1mm
//    const int circle_center_x = 58;
//    const int circle_center_y = 58;
//    const int circle_center_x_new = 30;
//    const int circle_center_y_new = 30;
//    const int dimension_x =(int)150;
//    const int dimension_y =(int)150;
    const int resized_X_dim = 512;
    const int resized_Y_dim = 512;
    const int polaroid_X_dim = 584;
    const int polaroid_Y_dim = 650;
    const int offset_X = 36;
    const int offset_Y = 36;
    const QString last_year = "2017";
    const QString last_month = "12";
    const QString last_day = "27";
    QString save_path = "C:\\Users\\Fabio Roncato\\Documents\\Photo\\Cell\\Takeout\\saved_image_\\";
    QString save_path2 = "C:\\Users\\Fabio Roncato\\Documents\\Photo\\Cell\\Takeout\\saved_image_new\\";
    QString save_path_polaroid = "C:\\Users\\Fabio Roncato\\Documents\\Photo\\Cell\\Takeout\\saved_image_polaroid\\";
    //QDirIterator it("C:\\Users\\Fabio Roncato\\Documents\\Photo\\Cell\\Takeout\\Google Foto", QStringList() << "*_org.jpg", QDir::Files, QDirIterator::Subdirectories);
    QDirIterator it("C:\\Users\\Fabio Roncato\\Documents\\Photo\\Cell\\Takeout\\Google Foto - 2019-12-28", QStringList() << "*_org.jpg", QDir::Files, QDirIterator::Subdirectories);
    //QDirIterator it("C:\\Users\\Fabio Roncato\\Documents\\Photo\\Cell\\Takeout\\test_image_", QStringList() << "*_org.jpg", QDir::Files, QDirIterator::Subdirectories);
    int anno_2015[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int anno_2016[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int anno_2017[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int anno_2018[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int anno_2019[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int anno_2020[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int anno_have_to_be[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

#ifndef IMAGES_ALREADY_AVAILABLE
    while (it.hasNext()/* && count < 110 */){
        it.next();
        QString year = it.fileName().mid(5,4);
        QString month = it.fileName().mid(10,2);
        QString day = it.fileName().mid(13,2);
        QString hour = it.fileName().mid(16,2);
        QString minute = it.fileName().mid(19,2);
        QString second = it.fileName().mid(22,2);
        out << year << " " << month << " " << day << " " << hour << " " << minute << " " << second << endl;
        image = imread(it.filePath().toStdString(),CV_LOAD_IMAGE_COLOR);
        cout << it.filePath().toStdString() << endl;
        //Size size(image.rows/6, image.cols/6);//the dst image size,e.g.100x100
        Size size(resized_Y_dim, resized_X_dim);//the dst image size,e.g.512x512
        resize(image,image,size);//resize image
        Mat polaroid_image(polaroid_Y_dim, polaroid_X_dim, CV_8UC3, Scalar(255,255,255));

        image.copyTo(polaroid_image(cv::Rect(offset_X,offset_Y,image.cols, image.rows)));


        if(year.toInt()==2015)
          anno_2015[month.toInt()-1]++;
        else if(year.toInt()==2016)
          anno_2016[month.toInt()-1]++;
        else if(year.toInt()==2017)
          anno_2017[month.toInt()-1]++;
        else if(year.toInt()==2018)
          anno_2018[month.toInt()-1]++;
        else if(year.toInt()==2019)
          anno_2019[month.toInt()-1]++;
        else if(year.toInt()==2020)
          anno_2020[month.toInt()-1]++;
        else
            cout << "error" << endl;

        if((hour != "00") || (minute != "00") || (second != "00")){
            putText(polaroid_image, year.toStdString() + "-" + month.toStdString() + "-" + day.toStdString() + " " + hour.toStdString() + ":" +
                    minute.toStdString() + ":" + second.toStdString(), Point(36, 570), FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(0,0,0), 1.0);
        }
        else{
            cout << "no pills" << endl;
            putText(polaroid_image, year.toStdString() + "-" + month.toStdString() + "-" + day.toStdString() + " --:--:--", Point(36, 570), FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(0,0,0), 1.0);
            //putText(crop, year.toStdString() + "-" + month.toStdString() + "-" + day.toStdString() + " --:--:--", Point(10, 145), FONT_HERSHEY_COMPLEX_SMALL, 0.5, CV_RGB(0,0,0), 0.9);
        }
        cvtColor(polaroid_image,polaroid_image,CV_BGR2GRAY);
        cvtColor(polaroid_image,polaroid_image,CV_GRAY2BGR);



///////////////////////////////////////////////////////////////////////////
       /* QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        int randomValue = qrand() % rand_number_from0tothis;
        if(count>1000) randomValue += 20000;
        QString number = QString::number(randomValue);        
        imwrite( (save_path_polaroid + number  + it.fileName()).toStdString() + ".jpg" , polaroid_image ); */
        imwrite( (save_path_polaroid + it.fileName()).toStdString() + ".jpg" , polaroid_image );


        count++;
        cout << "images: " << count << endl;
    //    namedWindow( it.fileName().toStdString(), WINDOW_AUTOSIZE);// Create a window for display.
    //    imshow( it.fileName().toStdString(), image );
    //    waitKey(0);
    //    destroyWindow(it.fileName().toStdString());
    }


    out << "images available: " << count << endl;
    out << "anno 2015" << endl;
    for(int i =0;i<12;i++){
        out << i+1 << ": " << anno_2015[i] << "  -   " << anno_have_to_be[i];
        if(anno_2015[i] == anno_have_to_be[i])
            out << " OK" << endl;
        else
            out << " -- NO --" << endl;
    }

    out << "anno 2016" << endl;
    for(int i =0;i<12;i++){
        if(i==1) out << i+1 << ": " << anno_2016[i] << "  -   " << anno_have_to_be[i]+1;
        else out << i+1 << ": " << anno_2016[i] << "  -   " << anno_have_to_be[i] ;
        if(i==1 && anno_2016[i] == anno_have_to_be[i]+1)
            out << " OK" << endl;
        else if(i!=1 && anno_2016[i] == anno_have_to_be[i])
            out << " OK" << endl;
        else
            out << " -- NO --" << endl;
    }

    out << "anno 2017" << endl;
    for(int i =0;i<12;i++){
        out << i+1 << ": " << anno_2017[i] << "  -   " << anno_have_to_be[i];
        if(anno_2017[i] == anno_have_to_be[i])
            out << " OK" << endl;
        else
            out << " -- NO --" << endl;
    }

    out << "anno 2018" << endl;
    for(int i =0;i<12;i++){
        out << i+1 << ": " << anno_2018[i] << "  -   " << anno_have_to_be[i];
        if(anno_2018[i] == anno_have_to_be[i])
            out << " OK" << endl;
        else
            out << " -- NO --" << endl;
    }

    out << "anno 2019" << endl;
    for(int i =0;i<12;i++){
        out << i+1 << ": " << anno_2019[i] << "  -   " << anno_have_to_be[i];
        if(anno_2019[i] == anno_have_to_be[i])
            out << " OK" << endl;
        else
            out << " -- NO --" << endl;
    }

    out << "anno 2020" << endl;
    for(int i =0;i<12;i++){
        if(i==1) out << i+1 << ": " << anno_2020[i] << "  -   " << anno_have_to_be[i]+1;
        else out << i+1 << ": " << anno_2020[i] << "  -   " << anno_have_to_be[i];
        if(i==1 && anno_2020[i] == anno_have_to_be[i]+1)
            out << " OK" << endl;
        else if(i!=1 && anno_2020[i] == anno_have_to_be[i])
            out << " OK" << endl;
        else
            out << " -- NO --" << endl;
    }
#endif


    // create  big image
    int counter=0;

    int image_cols_new = polaroid_X_dim;
    int image_rows_new = polaroid_Y_dim;

    int index_x=0, index_y=0;
    bool images_completed = false;
    Mat big_image_polaroid(2*border_pixel_new+(images_in_y*image_rows_new)+(images_in_y-1)*1, 2*border_pixel_new+(images_in_x*image_cols_new)+(images_in_x-1)*1, CV_8UC3, Scalar(0,0,0));



    QString filename_images_available = "C:\\Users\\Fabio Roncato\\Documents\\Photo\\Cell\\Takeout\\saved_image_polaroid\\images.txt";
    QFile file(filename_images_available);
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);

    QDirIterator it_bn_images_polaroid("C:\\Users\\Fabio Roncato\\Documents\\Photo\\Cell\\Takeout\\saved_image_polaroid", QStringList() << "*.jpg", QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (it_bn_images_polaroid.hasNext() && images_completed==false){
        it_bn_images_polaroid.next();
        int index = it_bn_images_polaroid.fileName().indexOf('_');
        QString year = it_bn_images_polaroid.fileName().mid(index+1,4);
        QString month = it_bn_images_polaroid.fileName().mid(index+6,2);
        QString day = it_bn_images_polaroid.fileName().mid(index+9,2);
        out << year << " " << month << " " << day << endl;
        stream << endl << year << "-" << month << "-" << day << ",  " << it_bn_images_polaroid.fileName();

        QDate last_day, current_image_day;
      // here we have to set the two QDateTime object to compare them (see below)
        last_day.setDate(2020,12,26);
        current_image_day.setDate(year.toInt(),month.toInt(),day.toInt());

        if(current_image_day < last_day){ // here I want verify the actual image is part of the images taken I am using
            stream << "*";
            cout << "---" << it_bn_images_polaroid.fileName().toStdString() << "  " << endl;
            Mat image_small_polaroid = imread(it_bn_images_polaroid.filePath().toStdString(),CV_LOAD_IMAGE_COLOR);
            out << "index_x: " << index_x << " index_y: " << index_y << "   -    " << "image_smallcols: " << image_small_polaroid.cols << "  -  " << "image_smallrows: " << image_small_polaroid.rows << endl;
            image_small_polaroid.copyTo(big_image_polaroid(cv::Rect(border_pixel_new+index_x*(image_cols_new+1),border_pixel_new+index_y*(image_rows_new+1),image_small_polaroid.cols, image_small_polaroid.rows)));

            index_x++;
            if(index_x>images_in_x-1){
                index_y++;
                index_x=0;
            }
            if(index_y>images_in_y-1)
                images_completed = true;
            counter++;
        }
        cout << "index_x: " << index_x << " - index_y: " << index_y << endl;
    }
    file.close();


    cout << save_path_polaroid.toStdString() + "\\big_image_.jpg" << endl;
    imwrite(save_path_polaroid.toStdString() + "\\big_image_.jpg" , big_image_polaroid);

    out << "finish !!!" << endl;
    cout << "small images polaroid in big image polaroid: " << counter << endl;


    out << "temporary finish !!!" << endl;
    waitKey(0);
    return a.exec();
}



