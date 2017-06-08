#include "stdio.h"    
#include "stdlib.h"   

#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXEDGE 20
#define MAXVEX 20
#define INFINITY 65535

typedef int Status;	/* Status�Ǻ��������,��ֵ�Ǻ�����״̬���룬��OK�� */ 


typedef struct
{
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

typedef int Patharc[MAXVEX];    /* ���ڴ洢���·���±������ */
typedef int ShortPathTable[MAXVEX];/* ���ڴ洢���������·����Ȩֵ�� */

/* ����ͼ */
void CreateMGraph(MGraph *G)
{
	int i, j;

	/* printf("���������Ͷ�����:"); */
	G->numEdges=16;
	G->numVertexes=9;

	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
	{
		G->vexs[i]=i;
	}

	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
	{
		for ( j = 0; j < G->numVertexes; j++)
		{
			if (i==j)
				G->arc[i][j]=0;
			else
				G->arc[i][j] = G->arc[j][i] = INFINITY;
		}
	}

	G->arc[0][1]=1;
	G->arc[0][2]=5; 
	G->arc[1][2]=3; 
	G->arc[1][3]=7; 
	G->arc[1][4]=5; 

	G->arc[2][4]=1; 
	G->arc[2][5]=7; 
	G->arc[3][4]=2; 
	G->arc[3][6]=3; 
	G->arc[4][5]=3;

	G->arc[4][6]=6;
	G->arc[4][7]=9; 
	G->arc[5][7]=5; 
	G->arc[6][7]=2; 
	G->arc[6][8]=7;

	G->arc[7][8]=4;


	for(i = 0; i < G->numVertexes; i++)
	{
		for(j = i; j < G->numVertexes; j++)
		{
			G->arc[j][i] =G->arc[i][j];
		}
	}

}

/*  Dijkstra�㷨����������G��v0���㵽���ඥ��v�����·��P[v]����Ȩ����D[v] */    
/*  P[v]��ֵΪǰ����±�,D[v]��ʾv0��v�����·�����Ⱥ� */  
void ShortestPath_Dijkstra(MGraph G, int v0, Patharc *P, ShortPathTable *D)
{    
	int v,w,k,min;    
	int final[MAXVEX];/* final[w]=1��ʾ��ö���v0��vw�����·�� */
	for(v=0; v<G.numVertexes; v++)    /* ��ʼ����� */
	{        
		final[v] = 0;			/* ȫ�������ʼ��Ϊδ֪���·��״̬ */
		(*D)[v] = G.arc[v0][v];/* ����v0�������ߵĶ������Ȩֵ */
		(*P)[v] = -1;				/* ��ʼ��·������PΪ-1  */       
	}

	(*D)[v0] = 0;  /* v0��v0·��Ϊ0 */  
	final[v0] = 1;    /* v0��v0����Ҫ��·�� */        
	/* ��ʼ��ѭ����ÿ�����v0��ĳ��v��������·�� */   
	for(v=1; v<G.numVertexes; v++)   
	{
		min=INFINITY;    /* ��ǰ��֪��v0����������� */        
		for(w=0; w<G.numVertexes; w++) /* Ѱ����v0���Ķ��� */    
		{            
			if(!final[w] && (*D)[w]<min)             
			{                   
				k=w;                    
				min = (*D)[w];    /* w������v0������ */            
			}        
		}        
		final[k] = 1;    /* ��Ŀǰ�ҵ������Ķ�����Ϊ1 */
		for(w=0; w<G.numVertexes; w++) /* ����ǰ���·�������� */
		{
			/* ����v�����·������������·���ĳ��ȶ̵Ļ� */
			if(!final[w] && (min+G.arc[k][w]<(*D)[w]))   
			{ /*  ˵���ҵ��˸�̵�·�����޸�D[w]��P[w] */
				(*D)[w] = min + G.arc[k][w];  /* �޸ĵ�ǰ·������ */               
				(*P)[w]=k;        
			}       
		}   
	}
}

int main(void)
{   
	int i,j,v0;
	MGraph G;    
	Patharc P;    
	ShortPathTable D; /* ��ĳ�㵽�����������·�� */   
	v0=0;
	
	CreateMGraph(&G);
	
	ShortestPath_Dijkstra(G, v0, &P, &D);  

	printf("���·����������:\n");    
	for(i=1;i<G.numVertexes;++i)   
	{       
		printf("v%d - v%d : ",v0,i);
		j=i;
		while(P[j]!=-1)
		{
			printf("%d ",P[j]);
			j=P[j];
		}
		printf("\n");
	}    
	printf("\nԴ�㵽����������·������Ϊ:\n");  
	for(i=1;i<G.numVertexes;++i)        
		printf("v%d - v%d : %d \n",G.vexs[0],G.vexs[i],D[i]);     
	return 0;
}
