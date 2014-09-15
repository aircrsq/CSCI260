    #include<iostream>  
    #include<iomanip>   
    #include<stdlib.h>
    #include "math.h"  
    using namespace std;  
      
    void tromino(int **,int ,int ,int ,int ,int );  
    int flag=2;  
    int main()  
    {  
        int n;  
        cout<<"?2n?";  
        cin>>n;  
        int i=(int)pow((double)2,(double)n);  
        int **chessboard=NULL;  
        chessboard=new int* [i];        //?   
      
        for(int j=0;j<i;j++)            //   
        {  
           chessboard[j]=new int[i];  
        }  
      
        for(int j=0;j<i;j++)            //   
           for(int k=0;k<i;k++)  
              chessboard[j][k]=0;  
        cout<<"?"<<i<<"??";   
        int a,b;   //a?b  
        cin>>a>>b;  
        chessboard[a][b]=1;            //1   
        cout<<"1?"<<a+1<<"?"<<b+1<<""<<endl;  
        tromino(chessboard,0,0,i,a,b);  
        cout<<"tromino?"<<endl;   
      
        for(int j=0;j<i;j++)  
        {  
           for(int k=0;k<i;k++)  
               cout<<setw(4)<<left<<chessboard[j][k];  
           cout<<endl;  
        }  
        delete chessboard;  
        system("pause");  
        return 0;  
    }  
    //a?x1,y1? length?x,y   
    void tromino(int **a,int x1,int y1,int length,int x,int y)   
    {                                                            
        int i=length/2;              
        if(i-1==0)  
        {  
            if(x<=x1+i-1&&y>y1+i-1)    //  
                a[x1+i-1][y1+i-1]=a[x1+i][y1+i-1]=a[x1+i][y1+i]=flag++;  //2,3,4   
            else if(x<=x1+i-1&&y<=y1+i-1)   //  
                a[x1+i-1][y1+i]=a[x1+i][y1+i]=a[x1+i][y1+i-1]=flag++;    //1,4,3   
            else if(x>x1+i-1&&y<=y1+i-1)    //  
                a[x1+i-1][y1+i-1]=a[x1+i-1][y1+i]=a[x1+i][y1+i]=flag++;  //2,1,4   
            else  
                a[x1+i-1][y1+i-1]=a[x1+i-1][y1+i]=a[x1+i][y1+i-1]=flag++;//2,1,3   
        }  
        else  
        {  
            if(x<=x1+i-1&&y>y1+i-1)   
            {     
                a[x1+i-1][y1+i-1]=a[x1+i][y1+i-1]=a[x1+i][y1+i]=flag++;  
                tromino(a,x1,y1+i,i,x,y);             //   
                tromino(a,x1,y1,i,x1+i-1,y1+i-1);       //       
                tromino(a,x1+i,y1,i,x1+i,y1+i-1);         //   
                tromino(a,x1+i,y1+i,i,x1+i,y1+i);           //   
            }  
            else if(x<=x1+i-1&&y<=y1+i-1)  
            {  
                a[x1+i-1][y1+i]=a[x1+i][y1+i]=a[x1+i][y1+i-1]=flag++;  
                tromino(a,x1,y1+i,i,x1+i-1,y1+i);         //   
                tromino(a,x1,y1,i,x,y);           //   
                tromino(a,x1+i,y1,i,x1+i,y1+i-1);         //   
                tromino(a,x1+i,y1+i,i,x1+i,y1+i);           //   
            }  
            else if(x>x1+i-1&&y<=y1+i-1)  
            {  
                a[x1+i-1][y1+i-1]=a[x1+i-1][y1+i]=a[x1+i][y1+i]=flag++;  
                tromino(a,x1,y1+i,i,x1+i-1,y1+i);         //   
                tromino(a,x1,y1,i,x1+i-1,y1+i-1);       //   
                tromino(a,x1+i,y1,i,x,y);           //   
                tromino(a,x1+i,y1+i,i,x1+i,y1+i);           //   
            }  
            else  
            {  
                a[x1+i-1][y1+i-1]=a[x1+i-1][y1+i]=a[x1+i][y1+i-1]=flag++;//2,1,3   
                tromino(a,x1,y1+i,i,x1+i-1,y1+i);         //   
                tromino(a,x1,y1,i,x1+i-1,y1+i-1);       //  
                tromino(a,x1+i,y1,i,x1+i,y1+i-1);         //  
                tromino(a,x1+i,y1+i,i,x,y);           //   
            }  
        }  
    }  
