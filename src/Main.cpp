#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>

using namespace cv;

// Carrega o modelo CNN
//Net net = readNetFromCaffe("model.caffemodel", "model.prototxt");

// Inicializa a webcam
VideoCapture cap(0);

// Verifica se a webcam está conectada
if (!cap.isOpened())
{
    cout << "A webcam não está conectada." << endl;
    return;
}

// Loop principal
while (true)
{

    // Captura uma imagem da webcam
    Mat image;
    cap >> image;

    // Aplica um pré-processamento à imagem
    Mat processedImage = preProcessImage(image);

    // Identifica as placas na imagem
    vector<int> labels = identifyPlates(processedImage);

    // Imprime os rótulos das placas
    for (int i = 0; i < labels.size(); i++)
    {
        cout << labels[i] << endl;
    }

    // Espera por um novo frame
    waitKey(1);
}

// Função para aplicar um pré-processamento à imagem
Mat preProcessImage(Mat image)
{
    // Equaliza o histograma da imagem
    image = equalizeHist(image);

    // Normaliza a imagem
    image = normalize(image, 0, 1, NORM_MINMAX);

    // Reduz o ruído da imagem
    image = GaussianBlur(image, Size(3, 3), 0);

    return image;
}

// Função para identificar as placas na imagem
vector<int> identifyPlates(Mat image)
{
    // Converte a imagem para o formato de entrada da CNN
    Mat inputImage = blobFromImage(image, 1.0, Size(32, 32), Scalar(0, 0, 0), false);

    // Ativa a CNN
    net.setInput(inputImage);

    // Obtém as previsões da CNN
    Mat predictions = net.forward();

    // Converte as previsões para rótulos
    vector<int> labels;
    for (int i = 0; i < predictions.rows; i++)
    {
        labels.push_back(predictions.at<float>(i, 0));
    }

    return labels;
}
