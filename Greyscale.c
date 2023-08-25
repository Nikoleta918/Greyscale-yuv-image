#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define N 332 /* frame dimension for QCIF format */
#define M 498 /* frame dimension for QCIF format */
#define filename "cat_498x332_444.yuv"
#define file_yuv "cat_yuv_output.yuv"

/* code for armulator*/
#pragma arm section zidata="ram"
int current_y[N][M];
int current_u[N][M];
int current_v[N][M];
#pragma arm section

int i,j;
double current_r[N][M];
double current_g[N][M];
double current_b[N][M];
double current_gray[N][M];



void read()
{
  FILE *frame_c;
  if((frame_c=fopen(filename,"rb"))==NULL)
  {
    printf("current frame doesn't exist\n");
    exit(-1);
  }

  for(i=0;i<N;i=i+1)            //--->instead of i++ we have i=i+1
  {
    for(j=0;j<M;j=j+1)          //--->instead of j++ we have j=j+1    we do not use ++ because it slows down the program.
    {
      current_y[i][j]=fgetc(frame_c);
    }
  }
  for(i=0;i<N;i=i+1)
  {
    for(j=0;j<M;j=j+1)
    {
      current_u[i][j]=fgetc(frame_c);
    }
  }
  for(i=0;i<N;i=i+1)
  {
    for(j=0;j<M;j=j+1)
    {
      current_v[i][j]=fgetc(frame_c);
    }
  }
  fclose(frame_c);
}


void write()
{
  FILE *frame_yuv;
  frame_yuv=fopen(file_yuv,"wb");
  for(i=0;i<N;i=i+1)
  {
	  for(j=0;j<M;j=j+1)
	  {
		  fputc(current_gray[i][j],frame_yuv);
	  }
  }
  fclose(frame_yuv);
}

//-------original convert_to_rgb()------------------
void convert_to_rgb()
{
	for(i=0;i<N;i=i+1)
  {
    for(j=0;j<M;j=j+1)
    {
		current_r[i][j]=current_y[i][j] + 1.140*current_v[i][j];
		current_g[i][j]=current_y[i][j] -0.395*current_u[i][j]-0.581*current_v[i][j];
		current_b[i][j]=current_y[i][j] +2.032*current_u[i][j];
	}
  }
}

//------------greyscale()-------------------
void grayscale()
{
	for(i=0;i<N;i=i+1)
	{
		for(j=0;j<M;j=j+1)
		{
		current_gray[i][j]=(current_r[i][j]+current_g[i][j]+current_b[i][j])/3;
		}
	}
}






int main()
{
	read();
  convert_to_rgb();
  grayscale();
  for(i=0;i<N;i=i+1)   
  {
    for(j=0;j<M;j=j+1)
    {
      printf("%f ",current_gray[i][j]);
    }
	printf("\n");
  }
  write();
}
