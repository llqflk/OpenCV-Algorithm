//在整数表示的颜色空间中，数值范围是0-255，但在浮点数表示的颜色空间中，数值范围是0-1.0，所以要把0-255归一化。
src.convertTo(src, CV_32FC1, 1/255.0);




//像素转换
cv::Scalar scalar;
int color = scalar[0];