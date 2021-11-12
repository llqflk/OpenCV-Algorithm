cv::Point2f srcTri[3];
	cv::Point2f dstTri[3];
	srcTri[0] = cv::Point2f(0, 0);
	srcTri[1] = cv::Point2f(image_temp.cols - 1, 0);
	srcTri[2] = cv::Point2f(0, image_temp.rows - 1);

	dstTri[0] = tl;
	dstTri[1] = tr;
	dstTri[2] = bl;

	cv::Mat mat_rot_temp = getAffineTransform(srcTri, dstTri);