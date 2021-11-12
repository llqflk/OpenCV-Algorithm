cv::Mat M = getRotationMatrix2D(center, angle, 1.0);
warpAffine(src, dst, rotMat, src.size());

