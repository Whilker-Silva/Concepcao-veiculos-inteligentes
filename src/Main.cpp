#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    // Abre a webcam
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cerr << "Erro ao abrir a webcam." << endl;
        return -1;
    }

    // Define o tamanho do frame
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);

    // Loop principal
    while (true)
    {
        Mat frame;
        cap.read(frame);

        // Exibe o frame
        imshow("Webcam", frame);

        // Sai do loop se a tecla 'q' for pressionada
        if (waitKey(1) == 'q')
            break;
    }

    // Libera os recursos
    cap.release();
    destroyAllWindows();

    return 0;
}