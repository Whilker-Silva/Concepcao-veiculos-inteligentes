#include <opencv2/opencv.hpp>

int main() {
    // Abre a webcam
    cv::VideoCapture cap(0);

    // Verifica se a webcam foi aberta com sucesso
    if (!cap.isOpened()) {
        std::cerr << "Erro ao abrir a webcam." << std::endl;
        return -1;
    }

    // Cria uma janela para exibir o vídeo
    cv::namedWindow("Webcam", cv::WINDOW_NORMAL);

    
    while (true) {
        cv::Mat frame;
        
        // Captura um frame da webcam
        cap >> frame;

        // Verifica se o frame foi capturado com sucesso
        if (frame.empty()) {
            std::cerr << "Erro ao capturar o frame." << std::endl;
            break;
        }

        // Converte o frame para escala de cinza
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Aplica o filtro Canny
        cv::Mat edges;
        cv::Canny(gray, edges, 50, 150);
       
        // Exibe o frame com a detecção de corpos e a segmentação de bordas na janela
        cv::imshow("Webcam", edges);

        // Aguarda 30 milissegundos. Se a tecla 'ESC' for pressionada, encerra o loop.
        if (cv::waitKey(30) == 27) {
            break;
        }
    }

    // Libera os recursos da webcam
    cap.release();

    // Fecha a janela
    cv::destroyAllWindows();

    return 0;
}
