#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<iostream>
#include<regex>
#include<string>
#define PI 3.14159265
using namespace std;

FILE *fd,*fs;
int numFil,numCol,grayScale,mayorX,mayorY,menorX,menorY;
int matrizImg[900][900],matrizAux[900][900],matrizOriginal[900][900];
string nomSalida,nomEntrada;
struct PuntoLimite
{ 
   	int x; 
   	int y;
   	void create(int a,int b)
   	{
   		x=a;
   		y=b;
	}
   	void rotateP(float t) 
   	{
   		int cx,cy,xAux=x;
   		float coseno,seno;
   		coseno=cos(-t*PI/180.0);
   		seno=sin(-t*PI/180.0);
		cx=(mayorX-menorX)/2 + menorX;
		cy=(mayorY-menorY)/2  + menorY;
		x=coseno*(x-cx) - seno*(y-cy) +cx;
		y=seno*(xAux-cx) + coseno*(y-cy) +cy;
	} 
   	void traslateP(float d,int op)
	{
		if(op==1) // 1 ES HORIZONTAL 
		   	y=y+d;	 	   		
		else if(op==2)  // 2 ES VERTICAL
		   	x=x-d;					
	} 
   	void reflexionP(int op)
	{ 
		if(op==1)  // 1 ES HORIZONTAL
		   	y=mayorY-y+menorY;
		else if(op==2) // 2 ES VERTICAL
		   	x=mayorX-x+menorX;		   		
	}
	bool fueraLimite()
	{
		if(x<1||x>numFil||y<1||y>numCol)
			return true;
		else 
			return false;
	}
} lim[4]; //Pontos limites para verificar se a tartaruga está totalmente fora do quadro
void medidas()
{
	int m=lim[0].x;
	for(int i=1;i<4;i++)
	{
		if(lim[i].x<m)
			m=lim[i].x;
	}
	menorX=m;
	m=lim[0].x;
	for(int i=1;i<4;i++)
	{
		if(lim[i].x>m)
			m=lim[i].x;
	}
	mayorX=m;
	m=lim[0].y;
	for(int i=1;i<4;i++)
	{
		if(lim[i].y>m)
			m=lim[i].y;
	}
	mayorY=m;
	m=lim[0].y;
	for(int i=1;i<4;i++)
	{
		if(lim[i].y<m)
			m=lim[i].y;
	}
	menorY=m;
}
int lenNumero(int Num) //Calcular o número de dígitos de um número
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

void copiarMatriz(int A[900][900],int B[900][900])
{
	for(int i=1;i<=numFil;i++)
		for(int j=1;j<=numCol;j++)
		{
			A[i][j]=B[i][j];
		}
}

void reflexion(int op)
{
	medidas();
	int x,y,x2,y2;
	for(x2=1;x2<=numFil;x2++)
		for(y2=1;y2<=numCol;y2++)
		{
		   	if(op==1)  // 1 ES HORIZONTAL
		   	{
		   		x=x2;
		   		y=mayorY-y2+menorY;
			}
		   	else if(op==2) // 2 ES VERTICAL
		   	{
		   		x=mayorX-x2+menorX;
		   		y=y2;	   			   		
			}
		    if((x>=1) && (y>=1) &&(x<=numFil)&&(y<=numCol))
 				matrizAux[x2][y2]=matrizImg[x][y];
 		   	else
 		      	matrizAux[x2][y2]=255;
		}
	lim[0].reflexionP(op);
	lim[1].reflexionP(op);
	lim[2].reflexionP(op);
	lim[3].reflexionP(op);		
	copiarMatriz(matrizImg,matrizAux);
}
void traslate(float d,int op)
{
	int x,y,x2,y2;
	for(x2=1;x2<=numFil;x2++)
		for(y2=1;y2<=numCol;y2++)
		{
		   	if(op==1) // 1 ES HORIZONTAL 
		   	{
		   		x=x2;
		   		y=y2-d;	 	   		
			}
		   	else if(op==2)  // 2 ES VERTICAL
		   	{
		   		x=x2+d;
		   		y=y2; 		
			}				
		   	if((x>0) && (y>0) &&(x<=numFil)&&(y<=numCol))
		      	matrizAux[x2][y2]=matrizImg[x][y];
		   	else
		      	matrizAux[x2][y2]=255;//aqui le pones un valor que quieras
		}
	lim[0].traslateP(d,op);
	lim[1].traslateP(d,op);
	lim[2].traslateP(d,op);
	lim[3].traslateP(d,op);		
	copiarMatriz(matrizImg,matrizAux);   
}
void rotate(float t)
{
	medidas();		
	int x,y,x2,y2,cx,cy;
	float coseno=cos(-t*PI/180.0);
   	float seno=sin(-t*PI/180.0);
	cx=(mayorX-menorX)/2 + menorX;
	cy=(mayorY-menorY)/2  + menorY;
	for(x2=1;x2<=numFil;x2++)
		for(y2=1;y2<=numCol;y2++)
		   {
			   x=coseno*(x2-cx) + seno*(y2-cy)+cx;
			   y=coseno*(y2-cy) - seno*(x2-cx)+cy ;
		   	if((x>=menorX && (y>=menorY)) &&(x<=mayorX&&(y<=mayorY)))
		      	matrizAux[x2][y2]=matrizImg[x][y];
		   	else
		      	matrizAux[x2][y2]=255;//aqui le pones un valor que quieras
		   }
	lim[0].rotateP(t);
	lim[1].rotateP(t);
	lim[2].rotateP(t);
	lim[3].rotateP(t);		
	copiarMatriz(matrizImg,matrizAux);  
}
void procImagem()
{
	char registro[150];
	string reg;
    cout<<"--Programa tarefa 4--\n";
	nomEntrada+="tartaruga.pgm";  //Nome de arquivo entrada PGM
    cout<<"Ele programa esta usando o arquivo "<<nomEntrada<<"\n";	
	 
	//O arquivo de teste Ã© aberto para leitura
	if((fd=fopen(nomEntrada.c_str(),"r"))==NULL)
	{
		cout<<"Não pode abrir o arquivo "<<nomEntrada<<endl;
		return;
	}    
     
	cout<<"Inserir o nome do arquivo de saída:";
    cin>>nomSalida;
    nomSalida+=".pgm";  //Nome de arquivo saida PGM*/
    
    if(nomEntrada==nomSalida)
    {
    	cout<<"O nome do arquivo de saída deve ser diferente do arquivo de entrada\n";
    	return;
	}

	//Ele cria ou sobrescreve o arquivo onde o resultado Ã© salvo
	if((fs=fopen(nomSalida.c_str(),"w+"))==NULL)
	{
	  	cout<<"Não pode abrir o arquivo "<<nomSalida<<endl;
	  	return;
	}   
 
 	//O cabeÃ§alho Ã© copiado para o arquivo de saÃ­da
 	fgets(registro,100,fd);
 	fputs(registro,fs);
 	fflush(stdin);
 	cout<<"tipo:"<<registro;
 	if(registro[0]!='P'||(registro[1]!='2'&&registro[1]!='5'))
 	{
        cout<<"\nERROR: a imagem de entrada não está no formato PGM P2\n";
        system("pause");
        return ;
 	}
 
	//Ler comentários
 	fgets(registro,100,fd);
 	fflush(stdin);   
 	while(registro[0]=='#')
 	{
     	cout<<"Comentário :"<<registro;                                      
     	fputs(registro,fs);  
     	fflush(stdin);   
     	fgets(registro,100,fd);
 	}
 
 	//Ler DE numFil Y numCol
 	reg=(string)registro;
 	numFil=stoi(reg.substr(0,reg.find(" ")));
 	numCol=stoi(reg.substr(reg.find(" "),reg.size()-reg.find(" ")));
 	cout<<"numFilas y numColumnas: "<<numFil<<" "<<numCol;
 	fputs(registro,fs);
 	fflush(stdin);
 
 	//LECTURA DE grayScale
 	fgets(registro,100,fd);
 	fputs(registro,fs);
 	reg=(string)registro;
 	grayScale=stoi(reg);
 	cout<<"\ngrayscale: "<<grayScale<<endl;   
 	fflush(stdin);
 	
 	//Matriz de entrada de leitura
 	int pixel;   			
 	for(int i=1;i<=numFil;i++)
 	{
    	for(int j=1;j<=numCol&&!feof(fd);j++)
    	{
 				fscanf(fd,"%d",&pixel);
 				matrizImg[i][j]=pixel;
 				fflush(stdin);
		}
	}		
	copiarMatriz(matrizOriginal,matrizImg);		

	// Lendo linha de comando
		//  ((\\+|-)?[[:digit:]]+)(\\.[[:digit:]]+)?          NUMERO REAL
		//  ((\\+|-)?[[:digit:]]+)                            NUMERO ENTERO
		//  RO\\(((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?\\)    RO()
		//  (M(H|V)\\(((\\+|-)?[[:digit:]]+)\\))                     MH(),MV()
		//  (R(H|V)))												RH,RV	
	
		//((R((O\\(((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?\\))|H|V))|(M(H|V)\\(((\\+|-)?[[:digit:]]+)\\)))     RO(),MH(),MV(),RH.RV
	bool band=false;
    lim[0].create(94,96);
    lim[1].create(94,252);
    lim[2].create(282,96);
    lim[3].create(282,252);
	do{
		regex sintaxi("(((R((O\\(((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?\\))|H|V))|(M(H|V)\\(((\\+|-)?[[:digit:]]+)\\)));)*((R((O\\(((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?\\))|H|V))|(M(H|V)\\(((\\+|-)?[[:digit:]]+)\\)))");
		string linea;
		band=false;
		//limpiamos el buffer antes de la siguiente lectura
		//cin.ignore(256,'\n');
		cout<<"Digite uma linha de comando!"<<endl;
		getline(cin, linea);
		linea=linea.substr(0,linea.find(" "));
		if(regex_match(linea,sintaxi))
		{	
			cout<<"good :)"<<endl;
			linea+=";";
			do
			{
				string comando,codigo,arg;
				int pos=linea.find(";");
				comando=linea.substr(0,pos);
				linea=linea.substr(pos+1,linea.size()-pos);
				codigo=comando.substr(0,2);
				cout<<"substring: "<<comando<<endl;
				if(codigo=="RH")
					reflexion(1);
				else if(codigo=="RV")
					reflexion(2);
				else
				{
					float numArg;
					pos=comando.find(")");
					arg=comando.substr(3,pos-3);
					numArg=stof(arg);				
					if(codigo=="MH")
						traslate(numArg,1);
					else if(codigo=="MV")
						traslate(numArg,2);		
					else if(codigo=="RO")
					{					
						rotate(numArg);				
					}
					cout<<" com o argumento: "<<numArg<<endl;	
				}
				cout<<"menorX: "<<menorX<<" mayorX: "<<mayorX<<" menorY: "<<menorY<<" mayorY: "<<mayorY<<endl;   
			}
			while(!linea.empty());		
			if(lim[0].fueraLimite()&&lim[1].fueraLimite()&&lim[2].fueraLimite()&&lim[3].fueraLimite())	
			{
				fflush(stdin);
				cout<<"A tartaruga é TOTALMENTE FORA do quadro!!\n";
				cout<<"Ele quer tentar novamente?(s/n):";
				cin>>linea;
				if(linea=="s"||linea=="S")
				{
					copiarMatriz(matrizImg,matrizOriginal);
				    lim[0].create(94,96);
				    lim[1].create(94,252);
				    lim[2].create(282,96);
				    lim[3].create(282,252);	
					band=true;
				}
				else if(linea=="n"||linea=="N") 
					band=false;
				fflush(stdin);
			}

		}
		else
		{
			cout<<"Erro de sintaxe na linha de comando introduzido!!!"<<endl;
			cout<<"Tente de novo\n\n";
			fflush(stdin);
			band=true;
		}
	}
	while(band);		

 	//Escritura de la matriz de salida
 	for(int i=1;i<=numFil;i++)
 	{
    	for(int j=1;j<=numCol;j++)
    	{
    		int x=matrizImg[i][j];
     		int lenNum=lenNumero(x);
     		if(lenNum==1)
     			fprintf(fs,"  %d ",x);
     		else if(lenNum==2)
     			fprintf(fs," %d ",x);
     		else
     			fprintf(fs,"%d ",x);
       		fflush(stdin);
        
    	}
    	fprintf(fs,"%s\n"," ");
 	}  
 	cout<<"\nFinal de processamento de imagem "<<nomEntrada<<endl;
 	fclose(fs);
 	fclose(fd);

}

int main()
{
    procImagem();
    getch ();
    return 0;
}
