#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <lapacke.h>
#include <cblas.h>
#include <svd.h>
#include <matrixmul.h>
#include <xnorm.h>

float subf(int n, int nn, int n1 ,int t,int t1, float *input, float **inter, float **output,int * change)
{
	int i,j,l,nnn=n1;
	float sum=0,sum1=0,x,norm;
	printf("11111\n");
	if(nn==n1)
	{
		printf("22222\n");
		float **basis,**u, **s, **v, **s1, **v1, **MMM;
		basis=(float **)malloc(n*sizeof(float *));
		u=(float **)malloc(n*sizeof(float *));
		s=(float **)malloc(n*sizeof(float *));
		v=(float **)malloc(nnn*sizeof(float *));
		for (i=0;i<n;i++)
		{
			basis[i]=(float *)calloc(nnn,sizeof(float));
			u[i]=(float *)calloc(n,sizeof(float));
			s[i]=(float *)calloc(nnn,sizeof(float));
		}
		for(i=0;i<nnn;i++)
			v[i]=(float *)calloc(nnn,sizeof(float));
		for (i=0;i<n;i++)
			for(j=0;j<nnn;j++)
				basis[i][j]=inter[i][j];
		svd(n,nnn,basis,u,s,v);


		printf("the s matrix is=\n");
		for (i=0;i<n1;i++)
		{
			for (j=0;j<n1;j++)
				printf("%.4f  ",s[i][j]);
			printf("\n");
		}
		printf("%d\n",t1);
		float maximum;
		int ttt;
		for (i=0;i<n1;i++)
		{
			if(i==0)
				maximum=s[i][i];
			if(i>0)
				if(s[i][i]<maximum*0.1)
				{
					ttt=i;
					i=n1;
				}
		}
		float ** basiss;

		s1=(float **)malloc(n*sizeof(float *));
		v1=(float **)malloc(ttt*sizeof(float *));
		MMM=(float **)malloc(n*sizeof(float *));
		basiss=(float **)malloc(n*sizeof(float *));
		for(i=0;i<n;i++)
		{
			s1[i]=(float *)calloc(ttt,sizeof(float));
			MMM[i]=(float *)calloc(ttt,sizeof(float));
			basiss[i]=(float *)calloc(ttt,sizeof(float));
		}

		for(i=0;i<ttt;i++)
			v1[i]=(float *)calloc(nnn,sizeof(float));
		for(i=0;i<n;i++)
			for(j=0;j<ttt;j++)
			{
				
				s1[i][j]=s[i][j];
			}
		for (i=0;i<ttt;i++)
			for(j=0;j<nnn;j++)
			{
				
	       			v1[i][j]=v[i][j];
			}
		matrixmul(n,n,ttt,u,s,MMM);
		matrixmul(n,ttt,ttt,MMM,v,basiss);
		for(i=0;i<n;i++)
			for(j=0;j<ttt;j++)
			{
				int iii=*change+j;
				output[i][iii]=basiss[i][j];
			}
		*change=*change+ttt;
		for(i=0;i<n;i=i+8)
		{	
			for(j=0;j<n1*t1;j++)
			{
				printf("%7.3f ",output[i][j]);
			}
			printf("\n");
		}

		for (i=0;i<ttt;i++)
			free(v1[i]);
		for(i=0;i<n;i++)
		{
			free(basiss[i]);
			free(MMM[i]);
			free(s1[i]);
		}
		free(basiss);
		free(MMM);
		free(v1);
		free(s1);
		for(i=0;i<nnn;i++)
			free(v[i]);
		for(i=0;i<n;i++)
		{
			free(s[i]);
			free(u[i]);
			free(basis[i]);
		}
		free(v);
		free(s);
		free(u);
		free(basis);


	}
	if(t>t1)
	{
		for(i=0;i<nnn;i++)
		{
			sum=xnorm(input,output,i,n);
			if((i==0 || sum<sum1) && sum>0)
				sum1=sum; 
		}

		norm=sum1;
	
	printf("norm=%e\n",norm);
	}


}


