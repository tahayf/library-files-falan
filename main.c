#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Ogrenci{
    char OgrID[9]; // 8 degil 9 olmasi lazim
    char ad[30];
    char soyad[30];
    int puan;
    struct Ogrenci *next;
    struct Ogrenci *prev;
}OGRENCI;
typedef struct Yazar{
    int yazarID;
    char yazarAd[30];
    char yazarSoyad[30];
    struct Yazar *next;
}YAZAR;
typedef struct KitapOrnek{
    char etiketNo[30];
    char durum[8];
    struct KitapOrnek *next;
}KITAPORNEK;
typedef struct Kitap{
    char kitapAdi[30];
    char ISBN[13];
    struct Kitap *next;
    struct KitapOrnek *head;
}KITAP;
typedef struct KitapYazar{
    char ISBN[13];
    int yazarID;
}KITAPYAZAR;
typedef struct Tarih{
    unsigned int gun:5;
    unsigned int ay:4;
    unsigned int yil:12;
}TARIH;
typedef struct KitapOdunc{
    char etiketNo[20];
    char ogrID[8];
    unsigned int IslemTipi;
    struct Tarih *islemTarihi;
}KITAPODUNC;
YAZAR* yazarEkle(YAZAR **yzr){
	char name[30];
	char surname[30];
	YAZAR *tmp = *yzr;
	
	while(tmp->next != NULL){
		tmp = tmp->next;
	}
 	tmp->next = (YAZAR*)malloc(sizeof(YAZAR));
 	
 	
 	printf("Isim giriniz: ");
 	scanf("%s",name);
 	printf("Soyisim giriniz: ");
 	scanf("%s",surname);
 	tmp->next->yazarID = tmp->yazarID + 1;
 	strcpy(tmp->next->yazarAd,name);
 	strcpy(tmp->next->yazarSoyad,surname);
 	tmp->next->next = NULL;
 	
 	return *yzr;
}
YAZAR* yazarSil(YAZAR **yzr){
	int ID;
	YAZAR *tmp = *yzr;
	YAZAR *prev;
	int flag = 1;
	
	printf("Silmek istediginiz ID'yi giriniz: ");
	scanf("%d",&ID);
	
 	prev = tmp;
 	if(ID == tmp->yazarID){
 		prev = tmp->next;
 		return prev;
	 }
 	while(tmp != NULL && (flag == 1)){
 		if(tmp->next->yazarID == ID){
 			
 			tmp->next = tmp->next->next;
 			flag = 0;
		 }else{
			tmp = tmp->next;
		 }
	 }
 	return prev;
}
YAZAR* yazarGuncelle(YAZAR **yzr){
	char name[30];
	char surname[30];
	int ID;
	YAZAR *tmp = *yzr;
	YAZAR *prev;
	int flag = 1;
	
	printf("Guncellemek istediginiz ID'yi giriniz: ");
	scanf("%d",&ID);
	printf("Guncel ismi giriniz: ");
	scanf("%s",name);
	printf("Guncel soyismi giriniz: ");
	scanf("%s",surname);
	
 	prev = tmp;
 	while(tmp != NULL && (flag == 1)){
 		if(tmp->yazarID == ID){
 			strcpy(tmp->yazarAd,name);
 			strcpy(tmp->yazarSoyad,surname);
 			flag = 0;
		 }else{
			tmp = tmp->next; 	
		 }
	 }
	 if(flag == 1){
	 	printf("Bu ID'de birisi bulunmadigi icin guncelleme yapilamadi.\n");
	 }
 	return prev;
}
void yazarListele(YAZAR **yzr){
	YAZAR *tmp = *yzr;
	while(tmp != NULL){
		printf("%d,%s,%s\n",tmp->yazarID,tmp->yazarAd,tmp->yazarSoyad);
		tmp = tmp->next;
	}
}
void splitYazar(YAZAR *holder, char buf[80]){
	char *token;
	token = strtok(buf,",");
	holder->yazarID = atoi(token);
	token = strtok(NULL,",");
	strcpy(holder->yazarAd,token);
	token = strtok(NULL,",");
	token[strlen(token)-1] = '\0';
	strcpy(holder->yazarSoyad,token);
}
YAZAR* fitosYazar(){
	FILE *fp;
    char buf[80];

    fp = fopen("Yazarlar.csv","r");
    if (fp == NULL){
        printf("Yazarlar.csv acilamadi.");
        exit(1);
    }
    YAZAR *head = (YAZAR*)malloc(sizeof(YAZAR));
    YAZAR *curr;
    YAZAR *prev;
    if(fgets(buf,80,fp)!=NULL){
    	splitYazar(head,buf);
	}else{
		return NULL;
	}
	prev = head;
	while(fgets(buf,80,fp)!=NULL){
		curr = (YAZAR*)malloc(sizeof(YAZAR));
		prev->next = curr;
		splitYazar(curr,buf);
		prev = curr;
	}
	prev->next = NULL;
	fclose(fp);
	return head;
}
void stofiYazar(YAZAR *yzr){
	FILE *fp;
	
	fp = fopen("Yazarlar.csv","w");
    if (fp == NULL){
        printf("Yazarlar.csv acilamadi.");
        exit(1);
    }
    
    while(yzr != NULL){
    	fprintf(fp,"%d,%s,%s\n",yzr->yazarID,yzr->yazarAd,yzr->yazarSoyad);
    	yzr = yzr->next;
	}
	fclose(fp);
}
OGRENCI* ogrenciEkle(OGRENCI **ogr){
	char ID[9];
	char name[30];
	char surname[30];
	int puan;
	
	OGRENCI *tmp = *ogr;
	
	printf("ID giriniz: ");
 	scanf("%s",ID);
 	
	while(tmp->next != NULL){
		if(!strcmp(ID,tmp->OgrID)){
			printf("Boyle bir ID bulunmaktadir. Bu ID ile ekleme yapamazsiniz.\n");
			return *ogr;
		}
		tmp = tmp->next;
	}
	if(!strcmp(ID,tmp->OgrID)){
		printf("Boyle bir ID bulunmaktadir. Bu ID ile ekleme yapamazsiniz.\n");
		return *ogr;
	}
 	tmp->next = (OGRENCI*)malloc(sizeof(OGRENCI));
 	
 	
	printf("Isim giriniz:");
	scanf("%s",name);
	printf("Soyisim giriniz: ");
	scanf("%s",surname);
	
	tmp->next->puan = 100;
	strcpy(tmp->next->OgrID,ID);
	strcpy(tmp->next->ad,name);
	strcpy(tmp->next->soyad,surname);
	tmp->next->next = NULL;
	tmp->next->prev = tmp;
	return *ogr;
}
OGRENCI* ogrenciSil(OGRENCI **ogr){
	char ID[9];
	OGRENCI *tmp = *ogr;
	OGRENCI *head;

	int flag = 1;
	
	printf("Silmek istediginiz ID'yi giriniz: ");
	scanf("%s",ID);
	
 	head = tmp;
 	while(tmp != NULL && (flag == 1)){
 		if((!strcmp(tmp->OgrID,ID)) && (tmp->next != NULL)){
 			if(tmp == head){
 				head = tmp->next;
			 }
			 if(tmp->prev != NULL){
			 	tmp->prev->next = tmp->next;
			 }
			 if(tmp->next != NULL){
			 	tmp->next->prev = tmp->prev;
			 }
			 flag = 0;
		 }else{
		 	tmp = tmp->next;
		 }
	 }
	 if (tmp == NULL){
	 	printf("Boyle bir ID bulunamadi.\n");
	 }
	 
 	return head;
}
OGRENCI* ogrenciGuncelle(OGRENCI **ogr){
	char ID[9];
	char ID2[9];
	char name[30];
	char surname[30];
	int puan;
	OGRENCI *tmp = *ogr;
	OGRENCI *prev;
	int flag = 1;
	
	printf("Guncellemek istediginiz ID'yi giriniz: ");
	scanf("%s",ID);
	printf("Guncel ID'yi giriniz: ");
	scanf("%s",ID2);
	printf("Guncel ismi giriniz: ");
	scanf("%s",name);
	printf("Guncel soyismi giriniz: ");
	scanf("%s",surname);
	printf("Guncel puani giriniz: ");
	scanf("%d",&puan);
	
 	prev = tmp;
 	while(tmp != NULL && (flag == 1)){
 		if(!strcmp(ID,tmp->OgrID)){
 			strcpy(tmp->OgrID,ID2);
 			strcpy(tmp->ad,name);
 			strcpy(tmp->soyad,surname);
 			tmp->puan = puan;
 			flag = 0;
		 }else{
			tmp = tmp->next; 	
		 }
	 }
	 if(flag == 1){
	 	printf("Bu ID'de birisi bulunamadigi icin guncelleme yapilamadi.\n");
	 }
 	return prev;
}
void ogrenciListele(OGRENCI **ogr){
	OGRENCI *tmp = *ogr;
	while(tmp != NULL){
		printf("%s,%s,%s,%d\n",tmp->OgrID,tmp->ad,tmp->soyad,tmp->puan);
		tmp = tmp->next;
	}
}
void splitOgrenci(OGRENCI *holder,char buf[160]){
	char *token;
	token = strtok(buf,",\0");
	strcpy(holder->OgrID,token);
	token = strtok(NULL,",\0");
	strcpy(holder->ad,token);
	token = strtok(NULL,",\0");
	strcpy(holder->soyad,token);
	token = strtok(NULL,",\0");
	holder->puan = atoi(token);
}
OGRENCI* fitosOgrenci(){
	FILE *fp;
    char buf[160];

    fp = fopen("Ogrenciler.csv","r");
    if (fp == NULL){
        printf("Ogrenciler.csv acilamadi.");
        exit(1);
    }
    OGRENCI *head = (OGRENCI*)malloc(sizeof(OGRENCI));
    OGRENCI *curr;
    OGRENCI *prev;
    OGRENCI *tmp;
    if(fgets(buf,160,fp)!=NULL){
    	splitOgrenci(head,buf);
    	head->prev = NULL;
	}else{
		return NULL;
	}
	tmp = head;
	prev = head;
	while(fgets(buf,160,fp)!=NULL){
		curr = (OGRENCI*)malloc(sizeof(OGRENCI));
		curr->prev = prev;
		prev->next = curr;
		splitOgrenci(curr,buf);
		prev = curr;
	}
	prev->next = NULL;
	fclose(fp);
	return head;
}
void stofiOgrenci(OGRENCI *ogr){
	FILE *fp;
	
	fp = fopen("Ogrenciler.csv","w");
    if (fp == NULL){
        printf("Ogrenciler.csv acilamadi.");
        exit(1);
    }
    
    while(ogr != NULL){
    	fprintf(fp,"%s,%s,%s,%d\n",ogr->OgrID,ogr->ad,ogr->soyad,ogr->puan);
    	ogr = ogr->next;
	}
	fclose(fp);
}
int main(){
   	YAZAR *yzr = NULL;

	OGRENCI *ogr =  NULL;

	int flag = 1;
	int choice;
	int chochoice;
	
	yzr = fitosYazar();
	ogr = fitosOgrenci();
	
	while(flag == 1){
		printf("1-Yazar islemleri\n2-Ogrenci Islemleri\n3-Kitap Islemleri\n4-Cikis\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				printf("1-Yazar Ekle\n2-Yazar Sil\n3-Yazar Guncelle\n4-Yazar Listele\n");
				scanf("%d",&chochoice);
				switch(chochoice){
					case 1:
						yzr = yazarEkle(&yzr);
						break;
					case 2:
						yazarListele(&yzr);
						yzr = yazarSil(&yzr);
						break;
					case 3:
						yazarListele(&yzr);
						yzr = yazarGuncelle(&yzr);
						break;
					case 4:
						yazarListele(&yzr);
						break;
					default:
						printf("Gecersiz secim.");
						break;
				}
				break;
			case 2:
				printf("1-Ogrenci Ekle\n2-Ogrenci Sil\n3-Ogrenci Guncelle\n4-Ogrenci Listele\n");
				scanf("%d",&chochoice);
				switch(chochoice){
					case 1:
						ogr = ogrenciEkle(&ogr);
						break;
					case 2:
						ogrenciListele(&ogr);
						ogr = ogrenciSil(&ogr);
						break;
					case 3:
						ogrenciListele(&ogr);
						ogr = ogrenciGuncelle(&ogr);
						break;
					case 4:
						ogrenciListele(&ogr);
						break;
					default:
						printf("Gecersiz secim.");
						break;
				}
				break;
			case 3:
				printf("Henuz yapim asamasindadir anlayisiniz icin tesekkurler.\n");
				break;
			case 4:
				flag =0;
				break;
			default:
				printf("Gecersiz menu secimi.");
				break;
		}
		if(flag != 0){
			printf("Devam etmek istiyorsaniz 1'i tuslayiniz: ");
			scanf("%d",&flag);
		}
	}
	
	stofiYazar(yzr);
	stofiOgrenci(ogr);

    return 0;
}

