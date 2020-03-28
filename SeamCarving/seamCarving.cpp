#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <math.h>

cv::Mat gradient(cv::Mat input)
{
	cv::Mat Dx(input.rows, input.cols, CV_32F);
	cv::Mat Dy(input.rows, input.cols, CV_32F);
	for (int i = 0; i < Dx.rows; i++)
	{
		for (int j = 0; j < Dx.cols; j++)
		{
			if (i == 0)
			{
				Dx.at<float>(i, j) = abs(input.at<uchar>(i + 1, j) - input.at<uchar>(i, j));
			}
			else if (i == Dx.rows - 1)
			{
				Dx.at<float>(i, j) = abs(input.at<uchar>(i, j) - input.at<uchar>(i - 1, j));
			}
			else
			{
				Dx.at<float>(i, j) = abs(input.at<uchar>(i + 1, j) - input.at<uchar>(i - 1, j));
			}

			if (j == 0)
			{
				Dy.at<float>(i, j) = abs(input.at<uchar>(i, j + 1) - input.at<uchar>(i, j));
			}
			else if (j == Dx.cols - 1)
			{
				Dy.at<float>(i, j) = abs(input.at<uchar>(i, j) - input.at<uchar>(i, j - 1));
			}
			else
			{
				Dy.at<float>(i, j) = abs(input.at<uchar>(i, j + 1) - input.at<uchar>(i, j - 1));
			}
		}
	}
	return Dx + Dy;
}

cv::Mat seamCarving(cv::Mat input)
{
	cv::Mat temp;
	cv::cvtColor(input, temp, cv::COLOR_BGR2GRAY);
	cv::Mat D = gradient(temp);
	cv::Mat B = D.clone();
	cv::Mat C(input.rows, input.cols, CV_8U);
	for (int i = 1; i < input.rows; i++)
	{
		for (int j = 0; j < input.cols; j++)
		{
			float min = B.at<float>(i - 1, j);
			C.at<uchar>(i, j) = j;
			if (j - 1 >= 0 && B.at<float>(i - 1, j - 1) < min)
			{
				min = B.at<float>(i - 1, j - 1);
				C.at<uchar>(i, j) = j - 1;
			}
			if (j + 1 <= input.cols - 1 && B.at<float>(i - 1, j + 1) < min)
			{
				min = B.at<float>(i - 1, j + 1);
				C.at<uchar>(i, j) = j + 1;
			}
			B.at<float>(i, j) = min + D.at<float>(i, j);
		}
	}
	int index;
	float min = B.at<float>(input.rows - 1, 0);
	for (int j = 1; j < input.cols; j++)
	{
		if (B.at<float>(input.rows - 1, j) < min)
		{
			min = B.at<float>(input.rows - 1, j);
			index = j;
		}
	}
	std::vector<int> path;
	for (int i = input.rows - 1; i >= 0; i--)
	{
		path.push_back(index);
		if (i >= 1)
			index = C.at<uchar>(i, index);
	}

	cv::Mat output(input.rows, input.cols - 1, input.type());
	for (int i = 0; i < input.rows; i++)
	{
		for (int j = 0; j < input.cols - 1; j++)
		{
			if (j >= path[path.size() - 1 - i])
			{
				output.at<cv::Vec3b>(i, j) = input.at<cv::Vec3b>(i, j + 1);
			}
			else
			{
				output.at<cv::Vec3b>(i, j) = input.at<cv::Vec3b>(i, j);
			}
		}
	}
	return output;
}

cv::Mat clip(cv::Mat img, int m, int n)
{
	cv::Mat output = img.clone();
	// 裁剪n
	while (output.cols > n)
	{
		output = seamCarving(output);
	}
	cv::Mat temp = output.clone();
	cv::transpose(output, temp);
	while (temp.cols > m)
	{
		temp = seamCarving(temp);
	}
	cv::transpose(temp, output);
	return output;
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		std::cout << "Please Input Image FileNames" << std::endl;
	}
	else
	{
		for (int i = 1; i < argc; i++)
		{
			char *fileName = argv[i];
			cv::Mat img = cv::imread(fileName, 1);
			cv::Mat transformedImg = clip(img, img.rows / 2, img.cols / 2);
			cv::imwrite(std::string("trans_") + std::string(fileName), transformedImg);
		}
	}
	return 0;
}