cv::Mat createLPFilter(cv::Size size, cv::Point center, float radius, int type, int n)
{
	cv::Mat lpFilter = cv::Mat::zeros(size, CV_32FC1);
	int rows = size.height;
	int cols = size.width;
	if (radius <= 0)
	{
		return lpFilter;
	}
	// 构建理想低通滤波器
	if (type == 0)
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				float norm2 = pow(abs(float(r - center.y)), 2) + pow(abs(float(c - center.x)), 2);
				if (sqrt(norm2) < radius)
				{
					lpFilter.at<float>(r, c) = 1;
				}
				else
				{
					lpFilter.at<float>(r, c) = 0;
				}
			}
		}
	}
	// 构建巴特沃斯低通滤波器
	if (type == 1)
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				float norm2 = pow(abs(float(r - center.y)), 2) + pow(abs(float(c - center.x)), 2);
				lpFilter.at<float>(r, c) = float(1.0 / (1.0 + pow(sqrt(norm2) / radius, 2.0 * n)));
			}
		}
	}
	// 构建 高斯低通滤波器
	if (type == 2) {
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				float norm2 = pow(abs(float(r - center.y)), 2) + pow(abs(float(c - center.x)), 2);
				lpFilter.at<float>(r, c) = float(exp(-norm2 / (2 * pow(radius, 2.0))));
			}
		}
	}
	return lpFilter;
}

void fft2Image(cv::Mat& I, cv::Mat& F)
{
	int rows = I.rows;
	int cols = I.cols;
	// 满足快速傅里叶变换的最优行数和列数
	int rPadded = cv::getOptimalDFTSize(rows);
	int cPadded = cv::getOptimalDFTSize(cols);
	// 左侧和下侧补零
	cv::Mat f;
	copyMakeBorder(I, f, 0, rPadded - rows, 0, cPadded - cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
	// 快速傅里叶变换（双通道，用于存储实部和虚部）
	dft(f, F, cv::DFT_COMPLEX_OUTPUT);
}

// 计算幅度谱
void amplitudeSpectrum(cv::Mat& _srcFFT, cv::Mat& _dstSpectrum)
{
	// 判断傅里叶变换有两个通道
	CV_Assert(_srcFFT.channels() == 2);
	// 分离通道
	std::vector<cv::Mat> FFT2Channel;
	split(_srcFFT, FFT2Channel);
	// 计算傅里叶变换的幅度谱
	magnitude(FFT2Channel[0], FFT2Channel[1], _dstSpectrum);
}

cv::Mat graySpectrum(cv::Mat spectrum)
{
	cv::Mat dst;
	log(spectrum + 1, dst);
	// 归一化
	normalize(dst, dst, 0, 1, cv::NORM_MINMAX);
	// 为了进行灰度级显示，做类型转换
	dst.convertTo(dst, CV_8UC1, 255, 0);
	return dst;
}

// 计算相位谱
cv::Mat phaseSpectrum(cv::Mat _srcFFT)
{
	// 相位谱
	cv::Mat phase;
	phase.create(_srcFFT.size(), CV_64FC1);
	// 分离通道
	std::vector<cv::Mat> FFT2Channel;
	split(_srcFFT, FFT2Channel);
	// 计算相位谱
	for (int r = 0; r < phase.rows; r++)
	{
		for (int c = 0; c < phase.cols; c++)
		{
			// 实部 虚部
			double real = FFT2Channel[0].at<double>(r, c);
			double imaginary = FFT2Channel[1].at<double>(r, c);
			// atan2 的返回值范围： [0, 180], [-180, 0]
			phase.at<double>(r, c) = atan2(imaginary, real);
		}
	}
	return phase;
}




int main()
{
    Mat I; // 输入的图像矩阵
	Mat F; //图像的傅里叶变换
	Point maxLoc; // 傅里叶谱的最大值的坐标
	int radius = 60; // 截断频率
	const int MAX_RADIUS = 100; //最大截断频率
	Mat lpFilter; // 低通滤波器
	int lpType = 0; // 低通滤波器的类型
	const int MAX_LPTYPE = 2;
	Mat F_lpFilter; // 低通傅里叶变换
	Mat FlpSpectrum; // 低通傅里叶变换的傅里叶谱的灰度级
	Mat result; // 低通滤波后的效果

	cv::Mat fGray;
	rnaSrc.convertTo(fGray, CV_32F);

	for (int r = 0; r < fGray.rows; r++)
	{
		for (int c = 0; c < fGray.cols; c++)
		{
			if ((r + c) % 2)
			{
				fGray.at<float>(r, c) *= -1;
			}
		}
	}

	/* 3,4.快速傅里叶变换 */
	fft2Image(fGray, F);

	// 幅度谱
	Mat amplSpec;
	amplitudeSpectrum(F, amplSpec);
	Mat spectrum = graySpectrum(amplSpec);

	//【temp】
	Mat Ftemp;
	cv::Mat fGraytemp;
	rnaTemp.convertTo(fGraytemp, CV_32F);

	for (int r = 0; r < fGraytemp.rows; r++)
	{
		for (int c = 0; c < fGraytemp.cols; c++)
		{
			if ((r + c) % 2)
			{
				fGraytemp.at<float>(r, c) *= -1;
			}
		}
	}

	fft2Image(fGraytemp, Ftemp);

	// 找到幅度谱的最大值的坐标
	minMaxLoc(spectrum, NULL, NULL, NULL, &maxLoc);


	/* 5.构建低通滤波器 */
	lpFilter = createLPFilter(F.size(), maxLoc, radius, lpType, 2);
	/* 6.低通滤波器和图像的傅里叶变换点乘 */
	F_lpFilter.create(F.size(), F.type());
	for (int r = 0; r < F_lpFilter.rows; r++)
	{
		for (int c = 0; c < F_lpFilter.cols; c++)
		{
			//分别取出当前位置的快速傅里叶变换和理想低通滤波器的值
			Vec2f F_rc = F.at<Vec2f>(r, c);
			float lpFilter_rc = lpFilter.at<float>(r, c);
			// 低通滤波器和图像的快速傅里叶变换的对应位置相乘


			F_lpFilter.at<Vec2f>(r, c) = F_rc * lpFilter_rc;
		}
	}

	// 低通傅里叶变换的傅里叶谱
	amplitudeSpectrum(F_lpFilter, FlpSpectrum);

	// 低通傅里叶谱的灰度级显示
	FlpSpectrum = graySpectrum(FlpSpectrum);

	/* 7,8. 对低通傅里叶变换执行傅里叶逆变换，并只取实部 */
	dft(F_lpFilter, result, DFT_SCALE + DFT_INVERSE + DFT_REAL_OUTPUT);
	/* 9.乘以 (-1)^(r+c) */
	for (int r = 0; r < result.rows; r++)
	{
		for (int c = 0; c < result.cols; c++)
		{
			if ((r + c) % 2)
			{
				result.at<float>(r, c) *= -1;
			}
		}
	}
	
	// 将结果转换为 CV_8U 类型
	result.convertTo(result, CV_8UC1, 1.0, 0);
	/* 10.截取左上部分，其大小与输入图像大小相同 */
	result = result(Rect(0, 0, rnaSrc.cols, rnaSrc.rows)).clone();

	medianBlur(rnaSrc, rnaSrc, 5);
	GaussianBlur(rnaTemp, rnaTemp, cv::Size(5, 5), 0);
}