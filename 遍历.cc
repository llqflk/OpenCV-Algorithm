for(int k=0;k<nr;k++)  
{  
    const uchar* inData=image.ptr<uchar>(k);  
    for(int i=0;i<nl;i++)  
    {  
        outData[i]=inData[i]/div*div+div/2;  
    }  
}  

