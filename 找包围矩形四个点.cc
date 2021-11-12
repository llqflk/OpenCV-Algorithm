cv::Point2f points_angle_temp[4];
temprect.points(points_angle_temp);

cv::Point2f tl, tr, bl, br;
for (int i = 0; i < 4; i++) 
{
	cv::Point vec(points_angle_temp[i].x - temprect.center.x, points_angle_temp[i].y - temprect.center.y);
	if (vec.x < 0 && vec.y < 0) 
	{
		tl = points_angle_temp[i];
	} else if (vec.x > 0 && vec.y < 0) 
	{
		tr = points_angle_temp[i];
	} else if (vec.x < 0 && vec.y > 0) 
	{
		bl = points_angle_temp[i];
	} else if (vec.x > 0 && vec.y > 0) 
	{
		br = points_angle_temp[i];
	}
}


