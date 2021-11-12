cv::Mat mat_result;
matchTemplate(image_background_src_otsu, image_background_temp_otsu, mat_result, cv::TM_CCOEFF_NORMED);   //最好匹配为1,值越小匹配越差
double max_val;
cv::Point max_loc;
minMaxLoc(mat_result, NULL, &max_val, NULL, &max_loc, cv::Mat());