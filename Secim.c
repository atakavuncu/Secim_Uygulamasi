#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int toplama(int oySayisi[][4],int sehirNo){	//Toplama Fonksiyonu
	
	int i,toplam=0;
	for(i=0;i<4;i++)
	{
		toplam+=oySayisi[sehirNo][i];
	}
	return toplam;
}

void siralama(int oySayisi[][4],int size,int sehirNo){	//S�ralama Fonksiyonu
	
	int i,j;
	for(i=0;i<size;i++)
	{
		for(j=1;j<size-i;j++)
		{
			if(oySayisi[sehirNo][j-1]<oySayisi[sehirNo][j])		//E�er bir sonraki say� bir �ncekinden b�y�kse yerlerini de�i�tir
			{
				int temp=oySayisi[sehirNo][j-1];
				oySayisi[sehirNo][j-1]=oySayisi[sehirNo][j];
				oySayisi[sehirNo][j]=temp;
			}
		}
	}
}

void yuzdebul(int kent[][4],float yuzdelik[][4],int sehirNo){	// Y�zde Hesaplama Fonksiyonu
	
	int i;
	float toplam=kent[sehirNo][0]+kent[sehirNo][1]+kent[sehirNo][2]+kent[sehirNo][3];
	for(i=0;i<4;i++)
	{
		yuzdelik[sehirNo][i]=(kent[sehirNo][i]/toplam)*100;
	}
}

void mvhesap(int kent[][4],int milletvekili[][4],int mvkont,int sehirNo){	// Milletvekili Hesaplama Fonksiyonu
	
	int i,j,k,n=0,il[4][4],il_kontrol[4][4];
	for(k=0;k<4;k++)
	{
		il[sehirNo][k]=kent[sehirNo][k];
		il_kontrol[sehirNo][k]=kent[sehirNo][k];
		milletvekili[sehirNo][k]=0;	// Hesaplamadan �nce her partinin mv say�s�n� 0'a e�itleme
	}
	while(n<mvkont)
	{
		siralama(il,4,sehirNo);
		
		if(il[sehirNo][0]==il_kontrol[sehirNo][0])
		{
			milletvekili[sehirNo][0]++;	// Milletvekili say�s�n� artt�r
			il_kontrol[sehirNo][0]/=2;		// Oy say�s�n� yar�ya d���r
		}
		else if(il[sehirNo][0]==il_kontrol[sehirNo][1])
		{
			milletvekili[sehirNo][1]++;
			il_kontrol[sehirNo][1]/=2;
		}
		else if(il[sehirNo][0]==il_kontrol[sehirNo][2])
		{
			milletvekili[sehirNo][2]++;
			il_kontrol[sehirNo][2]/=2;
		}
		else if(il[sehirNo][0]==il_kontrol[sehirNo][3])
		{
			milletvekili[sehirNo][3]++;
			il_kontrol[sehirNo][3]/=2;
		}
		il[sehirNo][0]/=2;
		n++;
	}
}

int main(){
	
	setlocale(LC_ALL,"Turkish");
	
	int i,j,genel_kont;
	int il[4]={1,2,3,4},kont[4],oy[4][4],genel_oy[1][4];		//il[4]-->�ehirlerin numaralar�n� yazd�rmak i�in / oy[sehirNumarasi][parti_oySayisi]
	int mv[4][4],genel_mv[1][4]={0,0,0,0};						//mv[sehirNumaras�][parti_mvSayisi]   �r:1.�ehir, A Partisi'nin Mv. Say�s�: mv[0][0]
	float yuzde[4][4],genel_yuzde[1][4],mv_yuzde[1][4];			//yuzde[sehirNumarasi][parti_oyYuzdesi]
	//genel_mv, genel_oy, genel_yuzde ve mv_yuzde de�i�kenlerini fonksiyonlara parametre olarak g�nderebilmek i�in iki boyutlu olarak tan�ml�yoruz.
	
	for(i=0;i<4;i++)
	{
		printf("---%d.�EH�R---\n",il[i]);
		printf("Milletvekili Kontenjan�: ");
		scanf("%d",&kont[i]);
		printf("A Partisi'nin Ald��� Ge�erli Oy Say�s�: ");	 
		scanf("%d",&oy[i][0]);
		printf("B Partisi'nin Ald��� Ge�erli Oy Say�s�: ");
		scanf("%d",&oy[i][1]);
		printf("C Partisi'nin Ald��� Ge�erli Oy Say�s�: ");
		scanf("%d",&oy[i][2]);
		printf("D Partisi'nin Ald��� Ge�erli Oy Say�s�: ");
		scanf("%d",&oy[i][3]);
		printf("\n");
	}
	
	for(i=0;i<4;i++)
		genel_oy[0][i]=oy[0][i]+oy[1][i]+oy[2][i]+oy[3][i];	// Partilerin �lke geneli oy say�lar�n� hesaplama
		
	genel_kont=kont[0]+kont[1]+kont[2]+kont[3];   // �lke geneli milletvekili kontenjan�n� hesaplama
	
	for(i=0;i<4;i++)
	{
		//Oy-Parti kontrol�n� sa�lamak i�in
		int a=oy[i][0];	
		int b=oy[i][1];
		int c=oy[i][2];
		int d=oy[i][3];
		
		yuzdebul(oy,yuzde,i);
		siralama(oy,4,i);
		mvhesap(oy,mv,kont[i],i);
		
		printf("\n\n-----------------------\n");
		printf("%d.�EH�R SE��M SONU�LARI\n",il[i]);
		printf("-----------------------\n\n");
		printf("Milletvekili Kontenjan�: %d\n",kont[i]);
		printf("Ge�erli Oy Say�s�: %d\n\n",toplama(oy,i));
		printf("		Oy Say�s�	Oy Y�zdesi	Mv. Say�s�\n");
		printf("		---------	----------	----------\n");
		for(j=0;j<4;j++)
		{
			if(oy[i][j]==a)   //Oy-Parti kontrol�
			{
				printf("A Partisi %13d		  %.2f		    %d\n",oy[i][j],yuzde[i][0],mv[i][j]);
				genel_mv[0][0]+=mv[i][j];   //Partinin �lke geneli milletvekili say�s�na ekleme
			}
			if(oy[i][j]==b)
			{
				printf("B Partisi %13d		  %.2f		    %d\n",oy[i][j],yuzde[i][1],mv[i][j]);
				genel_mv[0][1]+=mv[i][j];
			}
			if(oy[i][j]==c)
			{
				printf("C Partisi %13d		  %.2f		    %d\n",oy[i][j],yuzde[i][2],mv[i][j]);
				genel_mv[0][2]+=mv[i][j];
			}
			if(oy[i][j]==d)
			{
				printf("D Partisi %13d		  %.2f		    %d\n",oy[i][j],yuzde[i][3],mv[i][j]);
				genel_mv[0][3]+=mv[i][j];
			}
		}
		
		printf("\n\nDevam etmek i�in herhangi bir tu�a bas�n�z...");
		getch();  //Kullan�c�dan herhangi bir giri� beklemek i�in
	}
	
	int parti_mvoy[4][2];	//parti_mvoy[parti][mv-oy] => [parti][0]=mv,[parti][1]=oy    �r:[0][0]=A Partisinin Mv.Say�s�, [0][1]=Oy Say�s�
	// Not: parti_mvoy dizisi iktidar ve muhalefeti belirlemede kullan�lacak.
	
	for(i=0;i<4;i++)
	{
		parti_mvoy[i][0]=genel_mv[0][i];
		parti_mvoy[i][1]=genel_oy[0][i];
	}
	
	//Oy-Parti kontrol�n� sa�lamak i�in
	int a=genel_oy[0][0];
	int b=genel_oy[0][1];
	int c=genel_oy[0][2];
	int d=genel_oy[0][3];
	
	yuzdebul(genel_oy,genel_yuzde,0);
	yuzdebul(genel_mv,mv_yuzde,0);
	siralama(genel_oy,4,0);
	
	printf("\n\n\n===========================\n");
	printf("�LKE GENEL� SE��M SONU�LARI\n");
	printf("===========================\n\n");
	printf("Milletvekili Kontenjan�: %d\n",genel_kont);
	printf("Ge�erli Oy Say�s�: %d\n\n",toplama(genel_oy,0));
	printf("		Oy Say�s�	Oy Y�zdesi	Mv. Say�s�	Mv. Y�zdesi\n");
	printf("		---------	----------	----------	-----------\n");
	for(i=0;i<4;i++)
	{
		if(genel_oy[0][i]==a)
			printf("A Partisi %13d		  %.2f		    %d		   %.2f\n",genel_oy[0][i],genel_yuzde[0][0],genel_mv[0][0],mv_yuzde[0][0]);
		if(genel_oy[0][i]==b)
			printf("B Partisi %13d		  %.2f		    %d		   %.2f\n",genel_oy[0][i],genel_yuzde[0][1],genel_mv[0][1],mv_yuzde[0][1]);
		if(genel_oy[0][i]==c)
			printf("C Partisi %13d		  %.2f		    %d		   %.2f\n",genel_oy[0][i],genel_yuzde[0][2],genel_mv[0][2],mv_yuzde[0][2]);
		if(genel_oy[0][i]==d)
			printf("D Partisi %13d		  %.2f		    %d		   %.2f\n",genel_oy[0][i],genel_yuzde[0][3],genel_mv[0][3],mv_yuzde[0][3]);
	}
	
	//�ktidar-Muhalefet Kontrol� i�in Partileri Mv.Say�lar�na G�re S�ralama
	for(i=0;i<4;i++)
	{
		for(j=1;j<4-i;j++)
		{
			if(parti_mvoy[j-1][0]<parti_mvoy[j][0])
			{
				int k;
				for(k=0;k<2;k++)	//Partilerin yerlerini de�i�tirirken oy say�lar�n� da de�i�tiriyoruz.	0-->mv	1-->oy
				{
					int temp=parti_mvoy[j-1][k];
					parti_mvoy[j-1][k]=parti_mvoy[j][k];
					parti_mvoy[j][k]=temp;
				}
			}
		}
	}
	
	//Milletvekili say�lar� ayn� olan partileri, oy say�lar�na g�re s�ral�yoruz.
	int n=0,m=1;
	while(n<m)		//D�ng�, mv say�lar� ayn� olan parti say�s� kadar d�necek.
	{
		m-=1;
		for(i=1;i<4;i++)
		{
			j=i-1;
			if(parti_mvoy[j][0]==parti_mvoy[i][0])
			{
				if(parti_mvoy[j][1]<parti_mvoy[i][1])
				{
					int temp=parti_mvoy[j][1];
					parti_mvoy[j][1]=parti_mvoy[i][1];
					parti_mvoy[i][1]=temp;
					m++;
				}
			}
		}
		n++;
	}
	
	char parti[4];	//Parti isimilerini yazd�rmak i�in
	for(i=0;i<4;i++)
	{
		if(parti_mvoy[i][1]==a)
			parti[i]='A';
		if(parti_mvoy[i][1]==b)
			parti[i]='B';
		if(parti_mvoy[i][1]==c)
			parti[i]='C';
		if(parti_mvoy[i][1]==d)
			parti[i]='D';
	}
	
	//�ktidar ve Muhalefetin Yazd�r�lmas�
	printf("\n\n- - - - - - - - - \n");
	printf("�KT�DAR: %c Partisi\n",parti[0]);
	printf("- - - - - - - - - \n\n");
	printf("ANA MUHALEFET: %c Partisi\n\n",parti[1]);
	printf("MUHALEFET: %c Partisi\n",parti[2]);
	printf("MUHALEFET: %c Partisi\n",parti[3]);
	
	printf("\n\nNot: �ktidar�n ve Muhalefetin belirlenmesinde milletvekili say�s� �l��t olarak al�nm��t�r.\n");
	
	return 0;
}
