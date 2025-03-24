#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100

typedef struct SinhVien 
{
    char *maSo;
    char hoTen[MAX_NAME];
    float diemSo;
    struct SinhVien *tiepTheo;
} SinhVien;

typedef struct DanhSach 
{
    SinhVien *dau;
} DanhSach;

SinhVien* taoSinhVien(char *maSo, char *ten, float diemSo) 
{
	
    SinhVien *sinhVien = (SinhVien*)malloc(sizeof(SinhVien));
    sinhVien->maSo = (char*)malloc(strlen(maSo) + 1);
    
    strcpy(sinhVien->maSo, maSo);
    strcpy(sinhVien->hoTen, ten);
    
    sinhVien->diemSo = diemSo;
    sinhVien->tiepTheo = NULL;
    
    return sinhVien;
}

void themSinhVien(DanhSach *danhSach, SinhVien *sinhVien) 
{
    if (danhSach->dau == NULL)
    {
    	danhSach->dau = sinhVien;
	}       
    else 
	{
        SinhVien *tam = danhSach->dau;
        while (tam->tiepTheo != NULL) tam = tam->tiepTheo;
        tam->tiepTheo = sinhVien;
    }
}

void inDanhSach(DanhSach danhSach) 
{
    SinhVien *tam = danhSach.dau;
    printf("-----------------------------------------------------");
    printf("\n|%-10s | %-30s | %-5s|\n", "Ma SV", "Ho va ten", "Diem");
    printf("-----------------------------------------------------\n");
    while (tam != NULL) 
	{
        printf("|%-10s | %-30s | %-5.2f|\n", tam->maSo, tam->hoTen, tam->diemSo);
        tam = tam->tiepTheo;
    }
    printf("-----------------------------------------------------\n");
}

void ghiFile(DanhSach danhSach, const char *tenTep) 
{
    FILE *tep = fopen(tenTep, "w");
    SinhVien *tam = danhSach.dau;
    while (tam != NULL) 
	{
        fprintf(tep, "%s,%s,%.2f\n", tam->maSo, tam->hoTen, tam->diemSo);
        tam = tam->tiepTheo;
    }
    fclose(tep);
}

void docFile(DanhSach *danhSach, const char *tenTep) 
{
    FILE *tep = fopen(tenTep, "r");
    if (!tep) return;
    char maSo[20], hoTen[MAX_NAME];
    float diemSo;
    
    while (fscanf(tep, "%[^,],%[^,],%f\n", maSo, hoTen, &diemSo) == 3) 
	{
        themSinhVien(danhSach, taoSinhVien(maSo, hoTen, diemSo));
    }
    fclose(tep);
}

int soSanhTheoDiem(SinhVien *a, SinhVien *b) 
{
    return a->diemSo > b->diemSo;
}

void sapXepTheoDiem(DanhSach *danhSach, int (*cmp)(SinhVien*, SinhVien*)) 
{
    SinhVien *i = danhSach->dau, *j;
    for (; i != NULL; i = i->tiepTheo) 
	{
        for (j = i->tiepTheo; j != NULL; j = j->tiepTheo) 
		{
            if (!cmp(i, j)) 
			{
                char tamMa[20], tamTen[MAX_NAME];
                
                strcpy(tamMa, i->maSo); 
				strcpy(tamTen, i->hoTen);
				
                float tamDiem = i->diemSo;
                
                strcpy(i->maSo, j->maSo); 
				strcpy(i->hoTen, j->hoTen); 
				
				i->diemSo = j->diemSo;
				
                strcpy(j->maSo, tamMa); 
				strcpy(j->hoTen, tamTen); 
				
				j->diemSo = tamDiem;
            }
        }
    }
}

void locSinhVienGioi(DanhSach danhSach) 
{
    SinhVien *tam = danhSach.dau;
    printf("Sinh vien gioi:\n");
    while (tam != NULL) 
	{
        if (tam->diemSo >= 8.0)
            printf("MaSV: %s - %s - %.2f\n", tam->maSo, tam->hoTen, tam->diemSo);
        	tam = tam->tiepTheo;
    }
}

void mangConTro() 
{
    char *monHoc[] = {"Toan", "Ly", "Hoa"};
    char **ptr = monHoc;
    for (int i = 0; i < 3; i++)
        printf("Mon %d: %s\n", i + 1, *(ptr + i));
}

void thongKeHocLuc(DanhSach danhSach) 
{
    SinhVien *tam = danhSach.dau;
    int gioi = 0, kha = 0, trungBinh = 0, yeu = 0;
    while (tam != NULL) 
	{
        if (tam->diemSo >= 8) gioi++;
        else if (tam->diemSo >= 6.5) kha++;
        else if (tam->diemSo >= 5) trungBinh++;
        else yeu++;
        tam = tam->tiepTheo;
    }
    printf("\n--- Thong ke hoc luc ---\n");
    printf("Gioi: %d | Kha: %d | Trung Binh: %d | Yeu: %d\n", gioi, kha, trungBinh, yeu);
}

void capNhatSinhVien(DanhSach *danhSach, char *maSo) 
{
    SinhVien *tam = danhSach->dau;
    while (tam != NULL) 
	{
        if (strcmp(tam->maSo, maSo) == 0) 
		{
            printf("Nhap ho ten moi: ");
            gets(tam->hoTen);
            printf("Nhap diem moi: ");
            scanf("%f", &tam->diemSo); 
				getchar();
            printf("Cap nhat thanh cong!\n");
            return;
        }
        tam = tam->tiepTheo;
    }
    printf("Khong tim thay sinh vien!\n");
}

void xoaSinhVien(DanhSach *danhSach, char *maSo) 
{
    SinhVien *truoc = NULL, *hienTai = danhSach->dau;
    while (hienTai != NULL && strcmp(hienTai->maSo, maSo) != 0) 
	{
        truoc = hienTai;
        hienTai = hienTai->tiepTheo;
    }
    if (hienTai == NULL) 
	{
        printf("Khong tim thay sinh vien!\n");
        return;
    }
    if (truoc == NULL)
	{
		danhSach->dau = hienTai->tiepTheo;
	} 
    else 
	{
		truoc->tiepTheo = hienTai->tiepTheo;
   		free(hienTai->maSo);
    	free(hienTai);
    	printf("Da xoa sinh vien!\n");
	}
}

void sapXepTheoTen(DanhSach *danhSach) 
{
    SinhVien *i = danhSach->dau, *j;
    for (; i != NULL; i = i->tiepTheo) 
	{
        for (j = i->tiepTheo; j != NULL; j = j->tiepTheo) 
		{
            if (strcmp(i->hoTen, j->hoTen) > 0) 
			{
                char tamMa[20], tamTen[MAX_NAME];
                strcpy(tamMa, i->maSo); 
				strcpy(tamTen, i->hoTen);
                float tamDiem = i->diemSo;
                strcpy(i->maSo, j->maSo); 
				strcpy(i->hoTen, j->hoTen); 
				i->diemSo = j->diemSo;
                strcpy(j->maSo, tamMa); 
				strcpy(j->hoTen, tamTen); 
				j->diemSo = tamDiem;
            }
        }
    }
}

void timKiemTheoMa(DanhSach danhSach, char *maSo) 
{
    SinhVien *tam = danhSach.dau;
    while (tam != NULL) 
	{
        if (strcmp(tam->maSo, maSo) == 0) 
		{
            printf("Tim thay: %s - %s - %.2f\n", tam->maSo, tam->hoTen, tam->diemSo);
            return;
        }
        tam = tam->tiepTheo;
    }
    printf("Khong tim thay!\n");
}

void timKiemTheoTen(DanhSach danhSach, char *tenCanTim) 
{
    SinhVien *tam = danhSach.dau;
    int timThay = 0;
    while (tam != NULL) 
	{
        if (strstr(tam->hoTen, tenCanTim) != NULL) 
		{
            printf("Tim thay: %s - %s - %.2f\n", tam->maSo, tam->hoTen, tam->diemSo);
            timThay = 1;
        }
        tam = tam->tiepTheo;
    }
    if (!timThay)
	{
		printf("Khong tim thay!\n");
	} 
}

void menu() {
    DanhSach danhSach = {NULL};
    int luaChon;
    char maSo[20], hoTen[MAX_NAME];
    float diemSo;
    do {
        printf("\n==================================================== MENU ===================================================\n");
            printf("|%-25s | %-25s | %-25s|%-25s|\n", "1. Them sinh vien", "2. In danh sach", "3. Ghi file","4. Doc file");
            printf("|%-25s | %-25s | %-25s|%-25s|\n", "5. Sap xep theo diem", "6. Loc sinh vien gioi", "7. Demo mang con tro","8. Thong ke hoc luc");
            printf("|%-25s | %-25s | %-25s|%-25s|\n", "9. Cap nhat sinh vien", "10. Xoa sinh vien", "11. Sap xep theo ten","12. Tim theo ma");
            printf("|%-25s | %-25s | %-25s|%-25s|\n", "13. Tim theo ten", "0. De thoat", "....","....");
        printf("=============================================================================================================\n");

		printf("====> Chon : ");
        scanf("%d", &luaChon); getchar();
        switch(luaChon) {
            case 1: printf("Ma SV: "); 
					gets(maSo);
                    printf("Ho ten: "); 
					gets(hoTen);
                    printf("Diem: "); 
					scanf("%f", &diemSo); 
					getchar();
                    themSinhVien(&danhSach, taoSinhVien(maSo, hoTen, diemSo));
                    	break;
            case 2: inDanhSach(danhSach); 
						break;
            case 3: ghiFile(danhSach, "sinhvien.txt"); 
						break;
            case 4: docFile(&danhSach, "sinhvien.txt"); 
						break;
            case 5: sapXepTheoDiem(&danhSach, soSanhTheoDiem); 
						break;
            case 6: locSinhVienGioi(danhSach); 
						break;
            case 7: mangConTro(); 
						break;
            case 8: thongKeHocLuc(danhSach); 
						break;
            case 9: printf("Nhap ma SV muon cap nhat: "); 
					gets(maSo);
                    capNhatSinhVien(&danhSach, maSo); 
						break;
            case 10: printf("Nhap ma SV muon xoa: "); 
						gets(maSo);
                     xoaSinhVien(&danhSach, maSo); 
					 	break;
            case 11: sapXepTheoTen(&danhSach); 
						break;
            case 12: printf("Nhap ma SV can tim: "); 
						gets(maSo);
                     timKiemTheoMa(danhSach, maSo); 
					 	break;
            case 13: printf("Nhap ten SV can tim: "); 
					 gets(hoTen);
                     timKiemTheoTen(danhSach, hoTen); 
					 	break;
            case 0: printf("(== Da Thoat ==)\n"); 
						break;
        }
    } while (luaChon != 0);
}

int main() {
    menu();
    return 0;
}

