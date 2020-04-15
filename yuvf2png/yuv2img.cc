
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <getopt.h>
// boost
#include <boost/filesystem.hpp>
#include <chrono>

namespace fs = boost::filesystem;
using namespace std;
using namespace cv;


std::string input_path_ = "./";
std::string output_path_ = "./";
int width_  = 1920;
int height_ = 1280;
/**
 * read file list by path
 * */
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
 
	imshow("show", rgbImg);
	waitKey(1);
 
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
            YUV2PNG(in_dir + "/" + name, out_dir + "/" + out_name);
        }
    }
}
/**
 * read yuv file and output png image
 * */
int main(int argc, char *argv[])
{
    const char *optstring = "hi:o:s";
    struct option opts[] = {
        {"help", 0, NULL, 'h'},
        {"input", 1, NULL, 'i'},
        {"output", 1, NULL, 'o'},
        {"size", 1, NULL, 's'}
    };
    int c;
    int used_argc = 0;
    while((c = getopt_long(argc, argv, optstring, opts, NULL)) != -1) {  
        used_argc ++;      
        switch(c) {            
        case 'h':
            printf("Usage1: \n\t%s \n\t[--help]\n\t"
                   "[--input={ input image path }]\n\t"
                   "[--output={ output image path }]\n\t"
                   "[--size={1080p | 1280p}]\n", argv[0]
                   );
            printf("Usage2:\n\t ./yuv2img [yuv path ] [out path]\n");
            return 1;       
        case 'i':
            input_path_ = std::string(optarg);
            if(output_path_ == "./")
                output_path_ = input_path_;
            break;
        case 'o':
            output_path_ = std::string(optarg);
            break;        
        case 's':
            if(std::string(optarg) == "1080p")
            {
                width_ = 1920;
                width_ = 1080;
            }            
            break;       
        default:
            break;
        }
    }
    printf("input path:\t%s\n\toutput path:\t%s\n\twidth= %d; height = %d\n",
        input_path_.c_str(), output_path_.c_str(), width_, height_);
    if(argc - used_argc >= 2 && input_path_ == "./")
    {        
        // return 1;
        if(argc- used_argc >=3)
            batchYUV2PNG(argv[used_argc+1], argv[used_argc+2]);
        else 
            batchYUV2PNG(argv[used_argc+1], argv[used_argc+1]);
    }   
	else
    {
        batchYUV2PNG(input_path_, output_path_);
    }
    
    return 0;
}
