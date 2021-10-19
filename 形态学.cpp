Mat element = getStructuringElement(MORPH_RECT, Size(17, 3) );
morphologyEx(img_threshold, img_threshold, CV_MOP_CLOSE, element);
