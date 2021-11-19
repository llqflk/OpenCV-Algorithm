// CMakeProject1.cpp: 定义应用程序的入口点。
//
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

using namespace std;

void maketemplate()
{
	cv::Mat image_1 = cv::imread("C:\\Users\\92580\\Desktop\\IMAGE2\\1.bmp", cv::IMREAD_GRAYSCALE);
	image_1 = image_1(cv::Rect(670, 437, image_1.cols - 1120, image_1.rows - 1120));
	cv::Mat image_2 = cv::imread("C:\\Users\\92580\\Desktop\\IMAGE2\\2.bmp", cv::IMREAD_GRAYSCALE);
	image_2 = image_2(cv::Rect(536, 330, image_2.cols - 1120, image_2.rows - 1120));
	cv::Mat image_3 = cv::imread("C:\\Users\\92580\\Desktop\\IMAGE2\\3.bmp", cv::IMREAD_GRAYSCALE);
	image_3 = image_3(cv::Rect(545, 312, image_3.cols - 1120, image_3.rows - 1120));
	cv::Mat image_4 = cv::imread("C:\\Users\\92580\\Desktop\\IMAGE2\\4.bmp", cv::IMREAD_GRAYSCALE);
	image_4 = image_4(cv::Rect(400, 526, image_4.cols - 1120, image_4.rows - 1120));
	cv::Mat image_5 = cv::imread("C:\\Users\\92580\\Desktop\\IMAGE2\\5.bmp", cv::IMREAD_GRAYSCALE);
	image_5 = image_5(cv::Rect(256, 432, image_5.cols - 1120, image_5.rows - 1120));
	cv::Mat image_6 = cv::imread("C:\\Users\\92580\\Desktop\\IMAGE2\\6.bmp", cv::IMREAD_GRAYSCALE);
	image_6 = image_6(cv::Rect(266, 417, image_6.cols - 1120, image_6.rows - 1120));
	cv::Mat image_7 = cv::imread("C:\\Users\\92580\\Desktop\\IMAGE2\\7.bmp", cv::IMREAD_GRAYSCALE);
	image_7 = image_7(cv::Rect(284, 464, image_7.cols - 1120, image_7.rows - 1120));
	cv::Mat image_8 = cv::imread("C:\\Users\\92580\\Desktop\\IMAGE2\\8.bmp", cv::IMREAD_GRAYSCALE);
	image_8 = image_8(cv::Rect(291, 524, image_8.cols - 1120, image_8.rows - 1120));
	cv::Mat image_9 = cv::imread("C:\\Users\\92580\\Desktop\\IMAGE2\\9.bmp", cv::IMREAD_GRAYSCALE);
	image_9 = image_9(cv::Rect(699, 299, image_9.cols - 1120, image_9.rows - 1120));
	cv::Mat image_10 = cv::imread("C:\\Users\\92580\\Desktop\\IMAGE2\\10.bmp", cv::IMREAD_GRAYSCALE);
	image_10 = image_10(cv::Rect(324, 507, image_10.cols - 1120, image_10.rows - 1120));
	cv::Mat image_11 = cv::imread("C:\\Users\\92580\\Desktop\\IMAGE2\\11.bmp", cv::IMREAD_GRAYSCALE);
	image_11 = image_11(cv::Rect(486, 420, image_11.cols - 1120, image_11.rows - 1120));
	cv::Mat image_12 = cv::imread("C:\\Users\\92580\\Desktop\\IMAGE2\\12.bmp", cv::IMREAD_GRAYSCALE);
	image_12 = image_12(cv::Rect(573, 327, image_12.cols - 1120, image_12.rows - 1120));
	cv::Mat image_13 = cv::imread("C:\\Users\\92580\\Desktop\\IMAGE2\\13.bmp", cv::IMREAD_GRAYSCALE);
	image_13 = image_13(cv::Rect(355, 386, image_13.cols - 1120, image_13.rows - 1120));
	cv::Mat image_14 = cv::imread("C:\\Users\\92580\\Desktop\\IMAGE2\\14.bmp", cv::IMREAD_GRAYSCALE);
	image_14 = image_14(cv::Rect(284, 447, image_14.cols - 1120, image_14.rows - 1120));
	cv::Mat image_15 = cv::imread("C:\\Users\\92580\\Desktop\\IMAGE2\\15.bmp", cv::IMREAD_GRAYSCALE);
	image_15 = image_15(cv::Rect(294, 431, image_15.cols - 1120, image_15.rows - 1120));
	cv::Mat image_16 = cv::imread("C:\\Users\\92580\\Desktop\\IMAGE2\\16.bmp", cv::IMREAD_GRAYSCALE);
	image_16 = image_16(cv::Rect(389, 478, image_16.cols - 1120, image_16.rows - 1120));
	std::vector<cv::Mat> images;
	images.push_back(image_1);
	images.push_back(image_2);
	images.push_back(image_3);
	images.push_back(image_4);
	images.push_back(image_5);
	images.push_back(image_6);
	images.push_back(image_7);
	images.push_back(image_8);
	images.push_back(image_9);
	images.push_back(image_10);
	images.push_back(image_11);
	images.push_back(image_12);
	images.push_back(image_13);
	images.push_back(image_14);
	images.push_back(image_15);
	images.push_back(image_16);


	std::vector<cv::Mat> temps_out;
	for (int i = 0; i < 16; i++)
	{
		cv::Mat image_src = images.at(0);
		cv::Mat image_temp = images.at(i);

		double l = -1;
		double r = 1;
		double mid = 0;
		double max_value = 0;

		class Registration {
		public:
			double angle;
			double score;
			cv::Point point;

		public:
			double hs(cv::Mat src, cv::Mat temp, double angle, cv::Point& point) {
				cv::Mat temp_l;
				cv::Mat M_iter = cv::getRotationMatrix2D(cv::Point(temp.cols / 2, temp.rows / 2), angle, 1.0);
				cv::warpAffine(temp, temp_l, M_iter, temp.size());

				temp_l = temp_l(cv::Rect(20, 20, temp.cols - 40, temp.rows - 40));
				cv::Mat mat_result_iter;
				matchTemplate(src, temp_l, mat_result_iter, cv::TM_CCOEFF_NORMED);   //最好匹配为1,值越小匹配越差
				double max_val_iter;
				cv::Point max_loc_iter;
				minMaxLoc(mat_result_iter, NULL, &max_val_iter, NULL, &max_loc_iter, cv::Mat());

				point = cv::Point(max_loc_iter.x - 20, max_loc_iter.y - 20);

				return max_val_iter;
			}
		} scoreangle;

		std::vector<Registration>registrations;

		Registration init_scorevalue{ 0,0 };
		registrations.push_back(init_scorevalue);

		bool leftchanged = true;
		bool rightchanged = true;
		double last_l_value = 0;
		double last_r_value = 0;

		cv::Mat image_src_resize_4;
		cv::Mat image_temp_resize_4;
		cv::resize(image_temp, image_temp_resize_4, cv::Size(image_temp.cols / 4, image_temp.rows / 4));
		cv::resize(image_src, image_src_resize_4, cv::Size(image_src.cols / 4, image_src.rows / 4));

		while (r - l > 0.1)
		{
			Registration score_angle;

			cv::Point pl, pr, pmid;
			double l_value, r_value, mid_value;
			if (leftchanged)
				l_value = scoreangle.hs(image_src_resize_4, image_temp_resize_4, l, pl);
			else
				l_value = last_l_value;

			if (rightchanged)
				r_value = scoreangle.hs(image_src_resize_4, image_temp_resize_4, r, pr);
			else
				r_value = last_r_value;

			mid_value = scoreangle.hs(image_src_resize_4, image_temp_resize_4, mid, pmid);

			score_angle.angle = mid;
			score_angle.score = mid_value;
			score_angle.point = pmid;

			std::cout << mid << " " << mid_value << std::endl;

			if ((mid_value - l_value) > (mid_value - r_value))
			{
				l = mid;
				mid = (l + r) / 2;
				leftchanged = true;
				rightchanged = false;
			}
			else
			{
				r = mid;
				mid = (l + r) / 2;
				leftchanged = false;
				rightchanged = true;
			}

			last_l_value = l_value;
			last_r_value = r_value;
		}

		cv::Mat image_src_resize_2;
		cv::Mat image_temp_resize_2;
		cv::resize(image_temp, image_temp_resize_2, cv::Size(image_temp.cols / 2, image_temp.rows / 2));
		cv::resize(image_src, image_src_resize_2, cv::Size(image_src.cols / 2, image_src.rows / 2));

		while (r - l > 0.01)
		{
			Registration score_angle;

			cv::Point pl, pr, pmid;
			double l_value, r_value, mid_value;
			if (leftchanged)
				l_value = scoreangle.hs(image_src_resize_2, image_temp_resize_2, l, pl);
			else
				l_value = last_l_value;

			if (rightchanged)
				r_value = scoreangle.hs(image_src_resize_2, image_temp_resize_2, r, pr);
			else
				r_value = last_r_value;

			mid_value = scoreangle.hs(image_src_resize_2, image_temp_resize_2, mid, pmid);

			score_angle.angle = mid;
			score_angle.score = mid_value;
			score_angle.point = pmid;

			//registrations.push_back(score_angle);

			std::cout << mid << " " << mid_value << std::endl;

			if ((mid_value - l_value) > (mid_value - r_value))
			{
				l = mid;
				mid = (l + r) / 2;
				leftchanged = true;
				rightchanged = false;
			}
			else
			{
				r = mid;
				mid = (l + r) / 2;
				leftchanged = false;
				rightchanged = true;
			}

			last_l_value = l_value;
			last_r_value = r_value;
		}

		cv::Mat image_src_resize_1 = image_src.clone();
		cv::Mat image_temp_resize_1 = image_temp.clone();

		while (r - l > 0.002)
		{
			Registration score_angle;

			cv::Point pl, pr, pmid;
			double l_value, r_value, mid_value;
			if (leftchanged)
				l_value = scoreangle.hs(image_src_resize_1, image_temp_resize_1, l, pl);
			else
				l_value = last_l_value;

			if (rightchanged)
				r_value = scoreangle.hs(image_src_resize_1, image_temp_resize_1, r, pr);
			else
				r_value = last_r_value;

			mid_value = scoreangle.hs(image_src_resize_1, image_temp_resize_1, mid, pmid);

			score_angle.angle = mid;
			score_angle.score = mid_value;
			score_angle.point = pmid;

			registrations.push_back(score_angle);

			std::cout << mid << " " << mid_value << std::endl;

			if ((mid_value - l_value) > (mid_value - r_value))
			{
				l = mid;
				mid = (l + r) / 2;
				leftchanged = true;
				rightchanged = false;
			}
			else
			{
				r = mid;
				mid = (l + r) / 2;
				leftchanged = false;
				rightchanged = true;
			}

			last_l_value = l_value;
			last_r_value = r_value;
		}

		std::sort(registrations.begin(), registrations.end(), [](Registration& a, Registration& b) {return a.score > b.score; });
		Registration bestmatch = registrations.at(0);

		cv::Mat M = cv::getRotationMatrix2D(cv::Point(image_temp.cols / 2, image_temp.rows / 2), bestmatch.angle, 1.0);
		cv::warpAffine(image_temp, image_temp, M, image_temp.size());

		cv::Mat background_temp = cv::Mat::zeros(cv::Size(image_temp.cols + 40, image_temp.rows + 40), image_temp.type());
		image_temp.copyTo(background_temp(cv::Rect(20 + bestmatch.point.x, 20 + bestmatch.point.y, image_temp.cols, image_temp.rows)));
		
		background_temp = background_temp(cv::Rect(20, 20, background_temp.cols - 40, background_temp.rows - 40));
		temps_out.push_back(background_temp);
	}

	cv::Mat image_blend_0_1;
	cv::Mat image_blend_2_3;
	cv::Mat image_blend_4_5;
	cv::Mat image_blend_6_7;
	cv::Mat image_blend_8_9;
	cv::Mat image_blend_10_11;
	cv::Mat image_blend_12_13;
	cv::Mat image_blend_14_15;
	cv::addWeighted(temps_out.at(0), 0.5, temps_out.at(1), 0.5, 0, image_blend_0_1);
	cv::addWeighted(temps_out.at(2), 0.5, temps_out.at(3), 0.5, 0, image_blend_2_3);
	cv::addWeighted(temps_out.at(4), 0.5, temps_out.at(5), 0.5, 0, image_blend_4_5);
	cv::addWeighted(temps_out.at(6), 0.5, temps_out.at(7), 0.5, 0, image_blend_6_7);
	cv::addWeighted(temps_out.at(8), 0.5, temps_out.at(9), 0.5, 0, image_blend_8_9);
	cv::addWeighted(temps_out.at(10), 0.5, temps_out.at(11), 0.5, 0, image_blend_10_11);
	cv::addWeighted(temps_out.at(12), 0.5, temps_out.at(13), 0.5, 0, image_blend_12_13);
	cv::addWeighted(temps_out.at(14), 0.5, temps_out.at(15), 0.5, 0, image_blend_14_15);
	
	cv::Mat image_blend_0to3;
	cv::Mat image_blend_4to7;
	cv::Mat image_blend_8to11;
	cv::Mat image_blend_12to15;
	cv::addWeighted(image_blend_0_1, 0.5, image_blend_2_3, 0.5, 0, image_blend_0to3);
	cv::addWeighted(image_blend_4_5, 0.5, image_blend_6_7, 0.5, 0, image_blend_4to7);
	cv::addWeighted(image_blend_8_9, 0.5, image_blend_10_11, 0.5, 0, image_blend_8to11);
	cv::addWeighted(image_blend_12_13, 0.5, image_blend_14_15, 0.5, 0, image_blend_12to15);

	cv::Mat image_blend_0to7;
	cv::Mat image_blend_8to15;
	cv::addWeighted(image_blend_0to3, 0.5, image_blend_4to7, 0.5, 0, image_blend_0to7);
	cv::addWeighted(image_blend_8to11, 0.5, image_blend_12to15, 0.5, 0, image_blend_8to15);

	cv::Mat image_blend_0to15;
	cv::addWeighted(image_blend_0to7, 0.5, image_blend_8to15, 0.5, 0, image_blend_0to15);
}


int main()
{
	cv::Mat image_src = cv::imread("C:\\Users\\92580\\Desktop\\IMAGE2\\1.bmp", cv::IMREAD_GRAYSCALE);
	image_src = image_src(cv::Rect(670, 437, image_src.cols - 1120, image_src.rows - 1120));
	cv::Mat image_temp = cv::imread("C:\\Users\\92580\\Desktop\\IMAGE\\temp.png", cv::IMREAD_GRAYSCALE);
	//maketemplate();

	//187 243
	//image_src = image_src(cv::Rect(187, 243, image_src.cols - 300 , image_src.rows - 300));
	//image_temp = image_temp(cv::Rect(10, 227, image_temp.cols - 300, image_temp.rows - 300));

	if (image_src.empty() || image_temp.empty()) {
		return -1;
	}

	double l = -1;
	double r = 1;
	double mid = 0;
	double max_value = 0;

	class Registration {
	public:
		double angle;
		double score;
		cv::Point point;

	public:
		double hs(cv::Mat src, cv::Mat temp, double angle, cv::Point& point) {
			cv::Mat temp_l;
			cv::Mat M_iter = cv::getRotationMatrix2D(cv::Point(temp.cols / 2, temp.rows / 2), angle, 1.0);
			cv::warpAffine(temp, temp_l, M_iter, temp.size());

			temp_l = temp_l(cv::Rect(20, 20, temp.cols - 40, temp.rows - 40));
			cv::Mat mat_result_iter;
			matchTemplate(src, temp_l, mat_result_iter, cv::TM_CCOEFF_NORMED);   //最好匹配为1,值越小匹配越差
			double max_val_iter;
			cv::Point max_loc_iter;
			minMaxLoc(mat_result_iter, NULL, &max_val_iter, NULL, &max_loc_iter, cv::Mat());

			point = cv::Point(max_loc_iter.x - 20, max_loc_iter.y - 20);

			return max_val_iter;
		}
	} scoreangle;

	std::vector<Registration>registrations;

	Registration init_scorevalue{ 0,0 };
	registrations.push_back(init_scorevalue);

	bool leftchanged = true;
	bool rightchanged = true;
	double last_l_value = 0;
	double last_r_value = 0;

	cv::Mat image_src_resize_4;
	cv::Mat image_temp_resize_4;
	cv::resize(image_temp, image_temp_resize_4, cv::Size(image_temp.cols / 4, image_temp.rows / 4));
	cv::resize(image_src, image_src_resize_4, cv::Size(image_src.cols / 4, image_src.rows / 4));

	while (r - l > 0.1)
	{
		Registration score_angle;

		cv::Point pl, pr, pmid;
		double l_value, r_value, mid_value;
		if (leftchanged)
			l_value = scoreangle.hs(image_src_resize_4, image_temp_resize_4, l, pl);
		else
			l_value = last_l_value;

		if (rightchanged)
			r_value = scoreangle.hs(image_src_resize_4, image_temp_resize_4, r, pr);
		else
			r_value = last_r_value;

		mid_value = scoreangle.hs(image_src_resize_4, image_temp_resize_4, mid, pmid);

		score_angle.angle = mid;
		score_angle.score = mid_value;
		score_angle.point = pmid;

		std::cout << mid << " " << mid_value << std::endl;

		if ((mid_value - l_value) > (mid_value - r_value))
		{
			l = mid;
			mid = (l + r) / 2;
			leftchanged = true;
			rightchanged = false;
		}
		else
		{
			r = mid;
			mid = (l + r) / 2;
			leftchanged = false;
			rightchanged = true;
		}

		last_l_value = l_value;
		last_r_value = r_value;
	} 

	cv::Mat image_src_resize_2;
	cv::Mat image_temp_resize_2;
	cv::resize(image_temp, image_temp_resize_2, cv::Size(image_temp.cols / 2, image_temp.rows / 2));
	cv::resize(image_src, image_src_resize_2, cv::Size(image_src.cols / 2, image_src.rows / 2));

	while (r - l > 0.01)
	{
		Registration score_angle;

		cv::Point pl, pr, pmid;
		double l_value, r_value, mid_value;
		if (leftchanged)
			l_value = scoreangle.hs(image_src_resize_2, image_temp_resize_2, l, pl);
		else
			l_value = last_l_value;

		if (rightchanged)
			r_value = scoreangle.hs(image_src_resize_2, image_temp_resize_2, r, pr);
		else
			r_value = last_r_value;

		mid_value = scoreangle.hs(image_src_resize_2, image_temp_resize_2, mid, pmid);

		score_angle.angle = mid;
		score_angle.score = mid_value;
		score_angle.point = pmid;

		//registrations.push_back(score_angle);

		std::cout << mid << " " << mid_value << std::endl;

		if ((mid_value - l_value) > (mid_value - r_value))
		{
			l = mid;
			mid = (l + r) / 2;
			leftchanged = true;
			rightchanged = false;
		}
		else
		{
			r = mid;
			mid = (l + r) / 2;
			leftchanged = false;
			rightchanged = true;
		}

		last_l_value = l_value;
		last_r_value = r_value;
	}

	cv::Mat image_src_resize_1 = image_src.clone();
	cv::Mat image_temp_resize_1 = image_temp.clone();

	while (r - l > 0.002)
	{
		Registration score_angle;

		cv::Point pl, pr, pmid;
		double l_value, r_value, mid_value;
		if (leftchanged)
			l_value = scoreangle.hs(image_src_resize_1, image_temp_resize_1, l, pl);
		else
			l_value = last_l_value;

		if (rightchanged)
			r_value = scoreangle.hs(image_src_resize_1, image_temp_resize_1, r, pr);
		else
			r_value = last_r_value;

		mid_value = scoreangle.hs(image_src_resize_1, image_temp_resize_1, mid, pmid);

		score_angle.angle = mid;
		score_angle.score = mid_value;
		score_angle.point = pmid;

		registrations.push_back(score_angle);

		std::cout << mid << " " << mid_value << std::endl;

		if ((mid_value - l_value) > (mid_value - r_value))
		{
			l = mid;
			mid = (l + r) / 2;
			leftchanged = true;
			rightchanged = false;
		}
		else
		{
			r = mid;
			mid = (l + r) / 2;
			leftchanged = false;
			rightchanged = true;
		}

		last_l_value = l_value;
		last_r_value = r_value;
	}

	std::sort(registrations.begin(), registrations.end(), [](Registration& a, Registration& b) {return a.score > b.score; });
	Registration bestmatch = registrations.at(0);

	cv::Mat M = cv::getRotationMatrix2D(cv::Point(image_temp.cols / 2, image_temp.rows / 2), bestmatch.angle, 1.0);
	cv::warpAffine(image_temp, image_temp, M, image_temp.size());

	cv::Mat background_src = cv::Mat::zeros(cv::Size(image_src.cols + 40, image_src.rows + 40), image_src.type());
	image_src.copyTo(background_src(cv::Rect(20, 20, image_src.cols, image_src.rows)));

	cv::Mat background_temp = cv::Mat::zeros(cv::Size(image_temp.cols + 40, image_temp.rows + 40), image_temp.type());
	image_temp.copyTo(background_temp(cv::Rect(20 + bestmatch.point.x, 20 + bestmatch.point.y, image_temp.cols, image_temp.rows)));

	cv::Mat mask = cv::Mat::zeros(image_temp.size(), image_temp.type());
	cv::inRange(mask, 0, 255, mask);
	cv::warpAffine(mask, mask, M, mask.size());
	cv::inRange(mask, 254, 255, mask);
	cv::Mat background_mask = cv::Mat::zeros(cv::Size(mask.cols + 40, mask.rows + 40), mask.type());
	mask.copyTo(background_mask(cv::Rect(20 + bestmatch.point.x, 20 + bestmatch.point.y, mask.cols, mask.rows)));
	mask = background_mask(cv::Rect(20, 20, image_src.cols, image_src.rows));

	cv::bitwise_not(background_temp, background_temp);

	cv::Mat image_blend;

	cv::GaussianBlur(background_temp, background_temp, cv::Size(3, 3), 0);
	cv::GaussianBlur(background_src, background_src, cv::Size(3, 3), 0);

	cv::addWeighted(background_temp, 0.5, background_src, 0.5, 0, image_blend);

	image_blend = image_blend(cv::Rect(20, 20, image_src.cols, image_src.rows));

	cv::Mat aa;
	image_blend.copyTo(aa, mask);

	///////////////////////////////
	cv::inRange(aa, 0, 118, aa);
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(aa, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

	cv::Mat a;
	cv::cvtColor(image_blend, a, cv::COLOR_GRAY2BGR);
	cv::drawContours(a, contours, -1, cv::Scalar(0,0,255));





	return 0;
} 