cv::Point2f tl_point_temp, bl_point_temp, br_point_temp, tr_point_temp;

		int min_index = -1;
		int max_index = -1;
		int min_num = template_image.cols + template_image.rows;
		int max_num = 0;
		for (int i = 0; i < 4; i++)
		{
			if (angle_points_temp[i].x + angle_points_temp[i].y < min_num)
			{
				min_num = angle_points_temp[i].x + angle_points_temp[i].y;
				min_index = i;
			}

			if (angle_points_temp[i].x + angle_points_temp[i].y > max_num)
			{
				max_num = angle_points_temp[i].x + angle_points_temp[i].y;
				max_index = i;
			}
		}

		tl_point_temp = angle_points_temp[min_index];
		br_point_temp = angle_points_temp[max_index];
		tr_point_temp = angle_points_temp[(min_index + 1) % 4];
		bl_point_temp = angle_points_temp[(max_index + 1) % 4];
