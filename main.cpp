#include <iostream>
#include <omp.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    // Cargar imagen
    std::string imagePath = "../imagenes/20250712_173015.jpg";
    cv::Mat imagenColor = cv::imread(imagePath);

    if (imagenColor.empty()) {
        std::cerr << "Error: Could not open image at " << imagePath << std::endl;
        return -1;
    }

    // Cambiar tamaño de la Imagen
    cv::Mat resizedImage;
    cv::resize(imagenColor, resizedImage, Size(350, 300));

    // Crear una salida con un unico canal para dar ese efecto de escala de grises
    cv::Mat outputImage(resizedImage.rows, resizedImage.cols, CV_8UC1);

    // Conversion a escala de grises en paralelo
    #pragma omp parallel for
    for (int y = 0; y < resizedImage.rows; ++y) {
        for (int x = 0; x < resizedImage.cols; ++x) {
            // Conseguir valores RGB
            cv::Vec3b color = resizedImage.at<cv::Vec3b>(y, x);

            // Aplicar la formula de luminencia 
            uchar gray = static_cast<uchar>(
                0.299 * color[2] + 0.587 * color[1] + 0.114 * color[0]
            );

            // Escribir el valor de la escala de grises
            outputImage.at<uchar>(y, x) = gray;
        }
    }

    // Enseñar resultados
    cv::imshow("Original", imagenColor);
    cv::imshow("Grayscale", outputImage);
    cv::waitKey(0);

    // Guardar imagen resultado
    cv::imwrite("../imagenes/output_gray.jpg", outputImage);

    return 0;
}
