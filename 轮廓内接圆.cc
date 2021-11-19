for (int i = 0; i < contours.size(); i++)
{
	Mat  dist = Mat::zeros(src.size(), CV_32F);		//定义一个Mat对象，存放原图中每个点到该轮廓的距离，为浮点型数据
	//遍历每个点，计算该点到轮廓距离
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			//通过点多边形检测计算获得点到轮廓距离，并存放至dist中
			dist.at<float>(row, col) = pointPolygonTest(contours[i], Point(col, row), true);
		}
	}

	//计算dist中，最大值和最小值，以及其位置坐标
	double minVal, maxVal;
	Point maxloc, minloc;
	minMaxLoc(dist, &minVal, &maxVal, &minloc, &maxloc);
	int radio = abs(maxVal);			//对最大值求绝对值，即为内接圆半径
	Point center;
	center = maxloc;			//某点与轮廓距离为最大值，则该点为内接圆圆心
	circle(src, center, radio, Scalar(0, 0, 255), 2, 8, 0);

}
