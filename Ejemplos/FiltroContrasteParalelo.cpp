#include <opencv2/opencv.hpp>

Mat applyContrast(const Mat& inputImage, double contrastValue)
{
Mat outputImage;
resize(inputImage, outputImage, Size(350, 300));// Redimensionar la imagen
#pragma omp parallel for // Aplicar paralelismo en el bucle for externo que itera sobre las filas de la imagen de salida
for (int y = 0; y < outputImage.rows; ++y)// Iterar sobre las filas de la imagen de salida
{
for (int x = 0; x < outputImage.cols; ++x)// Iterar sobre las columnas de la imagen de salida
{
for (int c = 0; c < outputImage.channels(); ++c)// Iterar sobre los canales de color (BGR)
{
outputImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(
contrastValue * (outputImage.at<Vec3b>(y, x)[c] - 128) + 128// Aplicar el valor de
contraste a cada píxel, utilizando la fórmula de ajuste de contraste
);
}
}
}
return outputImage;
}