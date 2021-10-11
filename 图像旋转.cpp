cv::Mat rotateImg(cv::Mat src, cv::Point center, double angle)
{
	cv::Mat dst;
	cv::Mat rotMat = getRotationMatrix2D(center, angle, 1.0);
	warpAffine(src, dst, rotMat, src.size());
	return dst;
}