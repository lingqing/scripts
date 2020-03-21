
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// boost
#include <boost/filesystem.hpp>
#include <chrono>
namespace fs = boost::filesystem;


std::vector<std::string> get_file_name_list(const std::string &path)
{
    std::vector<std::string> list;
    for (const auto & entry : fs::directory_iterator(path))
    {
        list.push_back(entry.path().filename().string());
    }
    std::sort(list.begin(), list.end(), [](const std::string &a, const std::string &b)->bool{
            return a.compare(b) < 0;
        });
    return list;
}


void YUV2PNG(string inputFileName, string savepath) 
{
	int iWidth, iHeight, iImageSize;
	iWidth = 1920;
	iHeight = 1280;
	iImageSize = iWidth * iHeight * 3 / 2;
	
	FILE * fpln;
	fpln = fopen(inputFileName.data(), "rb+");
	//cout << fpln << endl;
	if (fpln == NULL) {
		printf("read yuv error.\n");
	}
 
	cv::Mat yuvImg;
	cv::Mat rgbImg(iHeight, iWidth, CV_8UC3);
	yuvImg.create(iHeight * 3 / 2, iWidth, CV_8UC1);
	
	unsigned char *pYUVbuf = new unsigned char[iImageSize];
	fread(pYUVbuf, iImageSize * sizeof(unsigned char), 1, fpln);
	memcpy(yuvImg.data, pYUVbuf, iImageSize * sizeof(unsigned char));
	cv::cvtColor(yuvImg, rgbImg, CV_YUV2RGBA_NV21);
 
	imshow("test", rgbImg);
	waitKey(10);
 
	imwrite(savepath, rgbImg);
}

void batchYUV2PNG(const std::string &in_dir, const std::string &out_dir)
{
    auto lists = get_file_name_list(in_dir);
    for(auto name : lists)
    {
        int k = name.find("yuv");
        if(k > 0)
        {
            auto out_name = name;
            out_name.replace(out_name.size()-3, 3, "png");
            YUV2PNG(in_dir + name, out_dir + out_name);
        }
    }
}

int main(int argc, char const *argv[])
{
    // string base_dir = "/home/andy/share/share_private/LYH/weima_test/20200320/GTR_1/";
    if(argc < 2)
    {
        printf("Usage: ./yuv2img [yuv path ] [out path]\n");
        return 1;
    }
    if(argc >=3)
	    batchYUV2PNG(argv[1], argv[2]);
    else 
	    batchYUV2PNG(argv[1], argv[1]);
	
    return 0;
}
