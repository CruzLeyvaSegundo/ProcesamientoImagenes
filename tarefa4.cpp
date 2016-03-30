#include<stdio.h>
#include<string.h>
#include<conio.h>
#include <iostream>
#include <math.h>
#define PI 3.14159265
using namespace std;
FILE *fd,*fs;
int origenX,origenY,numFil,numCol,lenR=0;
int matrizImg[800][800],salida[800][800];
char nomSalida[50],nomEntrada[50];
int lenNumero(int Num) //Calcula o número de dígitos de um número
{ 
    int i=0;
    if(Num==0)
      return 1;
    while(Num!=0) 
    { 
      Num=Num/10; 
      i=i+1; 
    } 
    return i; 
} 
int parseInt(char *cadena)
{   
   int potencias[3]={1,10,100};  
   int valor=0,i; 
   int lon=strlen(cadena);
   for(i=lon-1; i>=0; i--) 
   {
      valor+=(cadena[i]-'0')*potencias[lon-i-1]; 
   }
   return valor; 
}
void reflexion(int op)
{
	int x,y,x2,y2,cx,cy;
	for(x=1;x<=numFil;x++)
	for(y=1;y<=numCol;y++)
	   {
	   	if(op==1)  // 1 ES HORIZONTAL
	   	{
	   		x2=x;
	   		y2=numCol-y+1;
		}
	   	else if(op==2) // 2 ES VERTICAL
	   	{
	   		x2=numFil-x+1;
	   		y2=y;	   			   		
		}
	    salida[x2][y2]=matrizImg[x][y];
	   }
}
void mover(int d,int op)
{
	int x,y,x2,y2,cx,cy;
	for(x=1;x<=numFil;x++)
	for(y=1;y<=numCol;y++)
	   {
	   	if(op==1)  // 1 ES HORIZONTAL
	   	{
	   		x2=x+d;
	   		y2=y; 		
		}
	   	else if(op==2) // 2 ES VERTICAL
	   	{
	   		x2=x;
	   		y2=y+d;	 	   		
		}
	   	if((x2>0) && (y2>0) &&(x2<=numFil)&&(y2<=numCol))
	      salida[x2][y2]=matrizImg[x][y];
	   else
	      salida[x2][y2]=0;//aqui le pones un valor que quieras
	   }
}
void rotate(int t)
{
	int x,y,x2,y2,cx,cy;
	cx=numFil/2;
	cy=numCol/2;
	for(x2=1;x2<=numFil;x2++)
	for(y2=1;y2<=numCol;y2++)
	   {
	   x=cos(t*PI/180.0)*(x2-cx) + sin(t*PI/180.0)*(y2-cy)+cx;
	   y=cos(t*PI/180.0)*(y2-cy) - sin(t*PI/180.0)*(x2-cx)+cy ;
	   if((x>0) && (y>0) &&(x<=numFil)&&(y<=numCol))
	      salida[x2][y2]=matrizImg[x][y];
	   else
	      salida[x2][y2]=0;//aqui le pones un valor que quieras
	   }
}
void procImagem()
{
 char formato[4],registro[5000],c[3];;
 int e=4;
 //O arquivo de teste é aberto para leitura
 if((fd=fopen(nomEntrada,"rt"))==NULL)
 {
  cout<<"no se puede abrir "<<nomEntrada<<endl;
  return;
 }        
 //Ele cria ou sobrescreve o arquivo onde o resultado é salvo
 if((fs=fopen(nomSalida,"w"))==NULL)
 {
  cout<<"no se puede abrir "<<nomSalida<<endl;
  return;
 }   
 //O cabeçalho é copiado para o arquivo de saída
 fgets(formato,4,fd);
 fputs(formato,fs);
 cout<<"Tipo: "<<formato;
 fflush(stdin);
 if(formato[0]!='P'||(formato[1]!='2'&&formato[1]!='5'))
 {
               cout<<"\nERROR: la imagen de entrada no esta en formato PGM P2\n";
               system("pause");
               return ;
 }
//LECTURA DE COMENTARIOS
 int j=0,band=0;
 fgets(registro,90,fd);
 fflush(stdin);   
 while(registro[0]=='#')
 {
     e++;
     cout<<"Comentario :"<<registro;                                      
     fputs(registro,fs);  
     fflush(stdin);   
     fgets(registro,90,fd);
 }
 for(int i=0;i<strlen(registro);i++)
     {
     	
             if(registro[i]==' '||registro[i]=='\n')
             {    
                  c[j]='\0';            
                  int tam=parseInt(c);  
                  if(band==0)
                  {
                     numFil=tam;
                     band=1;
                  }
                  else if(band==1)
                     numCol=tam;
                  strcpy(c,"   ");                 
                  j=0;
             }  
             else
             {   
                 c[j]=registro[i];    
                 j++;     
             }
     } 
 cout<<"numFilas y numColumnas: "<<numFil<<" "<<numCol;
 fprintf(fs,"%d %d\n", numFil,numCol);
 fflush(stdin);
 fgets(registro,90,fd);
 fputs(registro,fs);
 cout<<"\ngrayscale: "<<registro;   
 fflush(stdin);
/* cout<<"\nIngrese coordenadas de pixel P(x,y)\n";
 cout<<"x: ";
 cin>>origenX;
 cout<<"y: ";
 cin>>origenY; */
 fflush(stdin);
 //Processamento de imagem
 int p=1,q=1,numPixeles=0;
 bool pR=true;
 while(!feof(fd))
 {
     int j=0,i=0,num;
     strcpy(c,"");
     c[3]='\0';     
     fgets(registro,4000,fd);
     while(registro[i]==' ')
            i++;    
     for(;i<strlen(registro);i++)
     {
     	
             if((registro[i]==' ')&&p<=numFil)
             {    
                  c[j]='\0';
                  while(registro[i+1]==' ')
                      i++;                
                  num=parseInt(c);  
				  matrizImg[p][q]=num;
				  numPixeles++;
				  if(q==numCol)
				  {
				  	p++;
				  	q=0;
				  }
                  fflush(stdin);
                  strcpy(c,"   ");                 
                  j=0;
                  q++;
                  if(pR)
                  	lenR++;
             }  
             else
             {   
                 c[j]=registro[i];    
                 j++;     
             }
     } 
     pR=false;
     fflush(stdin);
 }
 fflush(stdin);
 cout<<"lenRegistro: "<<lenR<<"  numPixeles: "<<numPixeles<<endl;
/* cout<<"\nEl pixel pivote escogido P("<<origenX<<","<<origenY<<") "<<endl;
 cout<<"esta ubicado en la linea "<<(((origenX-1)*numCol+origenY)/lenR) + e<<" y columna "<<((origenX-1)*numCol+origenY)%lenR<<" del archivo PGM \n";
 cout<<matrizImg[origenX][origenY-4]<<"  "<<matrizImg[origenX][origenY-3]<<"  "<<matrizImg[origenX][origenY-2]<<"\n";
 cout<<matrizImg[origenX][origenY-1]<<"  "<<matrizImg[origenX][origenY]<<"  "<<matrizImg[origenX][origenY+1]<<"\n";
 cout<<matrizImg[origenX][origenY+2]<<"  "<<matrizImg[origenX][origenY+3]<<"  "<<matrizImg[origenX][origenY+4]<<"\n";*/
 int t;
 /*cout<<"Angulo a rotar:";
 cin>>t;
 rotate(t);*/
 /*cout<<"Distancia a mover:";
 cin>>t;
 mover(t,2);*/
 cout<<"Reflexion en X (1) o Y (2):";
 cin>>t;
 reflexion(t);
 int k=0,lenNum;
 for(int i=1;i<=numFil;i++)
 {
    for(int j=1;j<=numCol;j++)
    {
     	lenNum=lenNumero(salida[i][j]);
     	int x=salida[i][j];
     	if(lenNum==1)
     		fprintf(fs,"  %d ",x);
     	else if(lenNum==2)
     		fprintf(fs," %d ",x);
     	else
     		fprintf(fs,"%d ",x);
        k++;
        /*if(k%lenR==0)
            fprintf(fs,"%s\n"," ");*/
        fflush(stdin);
        
    }
    fprintf(fs,"%s\n"," ");
 }  
 cout<<"\nFin de procesamiento de la imagen "<<nomEntrada<<endl;
 fclose(fs);
 fclose(fd);

}

int main()
{
	strcpy(nomEntrada,"tortuga.pgm");  //Nome de arquivo entrada PGM
    cout<<"--Programa para calcular as frequências de ocorrência de cada valor na imagem--\n";
    cout<<"Ele programa esta usando o arquivo "<<nomEntrada<<"\n";
    /*cout<<"Ingrese nombre del archivo salida:";
    cin>>nomSalida;
    strcat(nomSalida,".pgm");*/
    strcpy(nomSalida,"salida.pgm");  //Nome de arquivo entrada PGM
    procImagem();
    getch ();
    return 0;
}
//Valores a probar posicion (475 , 20)
