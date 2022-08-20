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

void siralama(int oySayisi[][4],int size,int sehirNo){	//Sýralama Fonksiyonu
	
	int i,j;
	for(i=0;i<size;i++)
	{
		for(j=1;j<size-i;j++)
		{
			if(oySayisi[sehirNo][j-1]<oySayisi[sehirNo][j])		//Eðer bir sonraki sayý bir öncekinden büyükse yerlerini deðiþtir
			{
				int temp=oySayisi[sehirNo][j-1];
				oySayisi[sehirNo][j-1]=oySayisi[sehirNo][j];
				oySayisi[sehirNo][j]=temp;
			}
		}
	}
}

void yuzdebul(int kent[][4],float yuzdelik[][4],int sehirNo){	// Yüzde Hesaplama Fonksiyonu
	
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
		milletvekili[sehirNo][k]=0;	// Hesaplamadan önce her partinin mv sayýsýný 0'a eþitleme
	}
	while(n<mvkont)
	{
		siralama(il,4,sehirNo);
		
		if(il[sehirNo][0]==il_kontrol[sehirNo][0])
		{
			milletvekili[sehirNo][0]++;	// Milletvekili sayýsýný arttýr
			il_kontrol[sehirNo][0]/=2;		// Oy sayýsýný yarýya düþür
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
	int il[4]={1,2,3,4},kont[4],oy[4][4],genel_oy[1][4];		//il[4]-->þehirlerin numaralarýný yazdýrmak için / oy[sehirNumarasi][parti_oySayisi]
	int mv[4][4],genel_mv[1][4]={0,0,0,0};						//mv[sehirNumarasý][parti_mvSayisi]   ör:1.Þehir, A Partisi'nin Mv. Sayýsý: mv[0][0]
	float yuzde[4][4],genel_yuzde[1][4],mv_yuzde[1][4];			//yuzde[sehirNumarasi][parti_oyYuzdesi]
	//genel_mv, genel_oy, genel_yuzde ve mv_yuzde deðiþkenlerini fonksiyonlara parametre olarak gönderebilmek için iki boyutlu olarak tanýmlýyoruz.
	
	for(i=0;i<4;i++)
	{
		printf("---%d.ÞEHÝR---\n",il[i]);
		printf("Milletvekili Kontenjaný: ");
		scanf("%d",&kont[i]);
		printf("A Partisi'nin Aldýðý Geçerli Oy Sayýsý: ");	 
		scanf("%d",&oy[i][0]);
		printf("B Partisi'nin Aldýðý Geçerli Oy Sayýsý: ");
		scanf("%d",&oy[i][1]);
		printf("C Partisi'nin Aldýðý Geçerli Oy Sayýsý: ");
		scanf("%d",&oy[i][2]);
		printf("D Partisi'nin Aldýðý Geçerli Oy Sayýsý: ");
		scanf("%d",&oy[i][3]);
		printf("\n");
	}
	
	for(i=0;i<4;i++)
		genel_oy[0][i]=oy[0][i]+oy[1][i]+oy[2][i]+oy[3][i];	// Partilerin ülke geneli oy sayýlarýný hesaplama
		
	genel_kont=kont[0]+kont[1]+kont[2]+kont[3];   // Ülke geneli milletvekili kontenjanýný hesaplama
	
	for(i=0;i<4;i++)
	{
		//Oy-Parti kontrolünü saðlamak için
		int a=oy[i][0];	
		int b=oy[i][1];
		int c=oy[i][2];
		int d=oy[i][3];
		
		yuzdebul(oy,yuzde,i);
		siralama(oy,4,i);
		mvhesap(oy,mv,kont[i],i);
		
		printf("\n\n-----------------------\n");
		printf("%d.ÞEHÝR SEÇÝM SONUÇLARI\n",il[i]);
		printf("-----------------------\n\n");
		printf("Milletvekili Kontenjaný: %d\n",kont[i]);
		printf("Geçerli Oy Sayýsý: %d\n\n",toplama(oy,i));
		printf("		Oy Sayýsý	Oy Yüzdesi	Mv. Sayýsý\n");
		printf("		---------	----------	----------\n");
		for(j=0;j<4;j++)
		{
			if(oy[i][j]==a)   //Oy-Parti kontrolü
			{
				printf("A Partisi %13d		  %.2f		    %d\n",oy[i][j],yuzde[i][0],mv[i][j]);
				genel_mv[0][0]+=mv[i][j];   //Partinin ülke geneli milletvekili sayýsýna ekleme
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
		
		printf("\n\nDevam etmek için herhangi bir tuþa basýnýz...");
		getch();  //Kullanýcýdan herhangi bir giriþ beklemek için
	}
	
	int parti_mvoy[4][2];	//parti_mvoy[parti][mv-oy] => [parti][0]=mv,[parti][1]=oy    ör:[0][0]=A Partisinin Mv.Sayýsý, [0][1]=Oy Sayýsý
	// Not: parti_mvoy dizisi iktidar ve muhalefeti belirlemede kullanýlacak.
	
	for(i=0;i<4;i++)
	{
		parti_mvoy[i][0]=genel_mv[0][i];
		parti_mvoy[i][1]=genel_oy[0][i];
	}
	
	//Oy-Parti kontrolünü saðlamak için
	int a=genel_oy[0][0];
	int b=genel_oy[0][1];
	int c=genel_oy[0][2];
	int d=genel_oy[0][3];
	
	yuzdebul(genel_oy,genel_yuzde,0);
	yuzdebul(genel_mv,mv_yuzde,0);
	siralama(genel_oy,4,0);
	
	printf("\n\n\n===========================\n");
	printf("ÜLKE GENELÝ SEÇÝM SONUÇLARI\n");
	printf("===========================\n\n");
	printf("Milletvekili Kontenjaný: %d\n",genel_kont);
	printf("Geçerli Oy Sayýsý: %d\n\n",toplama(genel_oy,0));
	printf("		Oy Sayýsý	Oy Yüzdesi	Mv. Sayýsý	Mv. Yüzdesi\n");
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
	
	//Ýktidar-Muhalefet Kontrolü için Partileri Mv.Sayýlarýna Göre Sýralama
	for(i=0;i<4;i++)
	{
		for(j=1;j<4-i;j++)
		{
			if(parti_mvoy[j-1][0]<parti_mvoy[j][0])
			{
				int k;
				for(k=0;k<2;k++)	//Partilerin yerlerini deðiþtirirken oy sayýlarýný da deðiþtiriyoruz.	0-->mv	1-->oy
				{
					int temp=parti_mvoy[j-1][k];
					parti_mvoy[j-1][k]=parti_mvoy[j][k];
					parti_mvoy[j][k]=temp;
				}
			}
		}
	}
	
	//Milletvekili sayýlarý ayný olan partileri, oy sayýlarýna göre sýralýyoruz.
	int n=0,m=1;
	while(n<m)		//Döngü, mv sayýlarý ayný olan parti sayýsý kadar dönecek.
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
	
	char parti[4];	//Parti isimilerini yazdýrmak için
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
	
	//Ýktidar ve Muhalefetin Yazdýrýlmasý
	printf("\n\n- - - - - - - - - \n");
	printf("ÝKTÝDAR: %c Partisi\n",parti[0]);
	printf("- - - - - - - - - \n\n");
	printf("ANA MUHALEFET: %c Partisi\n\n",parti[1]);
	printf("MUHALEFET: %c Partisi\n",parti[2]);
	printf("MUHALEFET: %c Partisi\n",parti[3]);
	
	printf("\n\nNot: Ýktidarýn ve Muhalefetin belirlenmesinde milletvekili sayýsý ölçüt olarak alýnmýþtýr.\n");
	
	return 0;
}
