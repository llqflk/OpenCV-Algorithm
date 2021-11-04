for(int k=0;k<nr;k++)  
    {  
        // 每一行图像的指针  
        const uchar* inData=image.ptr<uchar>(k);  
        uchar* outData=outImage.ptr<uchar>(k);  
        for(int i=0;i<nl;i++)  
        {  
            outData[i]=inData[i]/div*div+div/2;  
        }  
    }  

