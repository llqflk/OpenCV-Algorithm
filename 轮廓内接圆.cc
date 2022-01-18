for (int i = 0; i < contours.size(); i++)
{
	Mat  dist = Mat::zeros(src.size(), CV_32F);		//����һ��Mat���󣬴��ԭͼ��ÿ���㵽�������ľ��룬Ϊ����������
	//����ÿ���㣬����õ㵽��������
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			//ͨ�������μ������õ㵽�������룬�������dist��
			dist.at<float>(row, col) = pointPolygonTest(contours[i], Point(col, row), true);
		}
	}

	//����dist�У����ֵ����Сֵ���Լ���λ������
	double minVal, maxVal;
	Point maxloc, minloc;
	minMaxLoc(dist, &minVal, &maxVal, &minloc, &maxloc);
	int radio = abs(maxVal);			//�����ֵ�����ֵ����Ϊ�ڽ�Բ�뾶
	Point center;
	center = maxloc;			//ĳ������������Ϊ���ֵ����õ�Ϊ�ڽ�ԲԲ��
	circle(src, center, radio, Scalar(0, 0, 255), 2, 8, 0);

}
