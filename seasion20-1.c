#include <stdio.h>
#include <string.h>

#define MAX_SACH 100

typedef struct {
    char ma_sach[20];
    char ten_sach[50];
    char tac_gia[50];
    float gia_tien;
    char the_loai[30];
} Sach;

Sach danh_sach[MAX_SACH];
int so_luong_sach = 0;

void nhap_sach() {
    Sach sach;
    printf("Nhap ma sach: ");
    scanf("%s", sach.ma_sach);
    printf("Nhap ten sach: ");
    getchar();
    fgets(sach.ten_sach, sizeof(sach.ten_sach), stdin);
    sach.ten_sach[strcspn(sach.ten_sach, "\n")] = '\0';
    printf("Nhap tac gia: ");
    fgets(sach.tac_gia, sizeof(sach.tac_gia), stdin);
    sach.tac_gia[strcspn(sach.tac_gia, "\n")] = '\0'; 
    printf("Nhap gia tien: ");
    scanf("%f", &sach.gia_tien);
    printf("Nhap the loai: ");
    getchar();
    fgets(sach.the_loai, sizeof(sach.the_loai), stdin);
    sach.the_loai[strcspn(sach.the_loai, "\n")] = '\0'; 

    danh_sach[so_luong_sach++] = sach;
}

void hien_thi_sach() {
    if (so_luong_sach == 0) {
        printf("Danh sach sach rong! ");
    } else {
        for (int i = 0; i < so_luong_sach; i++) {
            printf("Ma sach: %s ", danh_sach[i].ma_sach);
            printf("Ten sach: %s ", danh_sach[i].ten_sach);
            printf("Tac gia: %s ", danh_sach[i].tac_gia);
            printf("Gia tien: %.2f ", danh_sach[i].gia_tien);
            printf("The loai: %s ", danh_sach[i].the_loai);
            printf("------------------------------- ");
        }
    }
}

void them_sach() {
    if (so_luong_sach >= MAX_SACH) {
        printf("Danh sach sach da day! ");
        return;
    }
    Sach sach;
    printf("Nhap thong tin sach moi: ");
    nhap_sach();
    int vi_tri;
    printf("Nhap vi tri de them sach (0-%d): ", so_luong_sach);
    scanf("%d", &vi_tri);
    if (vi_tri < 0 || vi_tri > so_luong_sach) {
        printf("Vi tri khong hop le. ");
        return;
    }

    for (int i = so_luong_sach; i > vi_tri; i--) {
        danh_sach[i] = danh_sach[i - 1];
    }
    danh_sach[vi_tri] = danh_sach[so_luong_sach - 1];
    so_luong_sach++;
}

void xoa_sach() {
    char ma_sach[20];
    printf("Nhap ma sach can xoa: ");
    scanf("%s", ma_sach);
    int i;
    for (i = 0; i < so_luong_sach; i++) {
        if (strcmp(danh_sach[i].ma_sach, ma_sach) == 0) {
            for (int j = i; j < so_luong_sach - 1; j++) {
                danh_sach[j] = danh_sach[j + 1];
            }
            so_luong_sach--;
            printf("Da xoa sach voi ma %s. ", ma_sach);
            return;
        }
    }
    printf("Khong tim thay sach voi ma %s. ", ma_sach);
}

void cap_nhat_sach() {
    char ma_sach[20];
    printf("Nhap ma sach can cap nhat: ");
    scanf("%s", ma_sach);
    int i;
    for (i = 0; i < so_luong_sach; i++) {
        if (strcmp(danh_sach[i].ma_sach, ma_sach) == 0) {
            printf("Cap nhat thong tin sach: ");
            nhap_sach();
            danh_sach[i] = danh_sach[so_luong_sach - 1];
            printf("Thong tin sach da duoc cap nhat. ");
            return;
        }
    }
    printf("Khong tim thay sach voi ma %s. ", ma_sach);
}

void sap_xep_sach() {
    int lua_chon;
    printf("Sap xep theo gia (1: Tang dan, 2: Giam dan): ");
    scanf("%d", &lua_chon);
    for (int i = 0; i < so_luong_sach - 1; i++) {
        for (int j = i + 1; j < so_luong_sach; j++) {
            if ((lua_chon == 1 && danh_sach[i].gia_tien > danh_sach[j].gia_tien) || 
                (lua_chon == 2 && danh_sach[i].gia_tien < danh_sach[j].gia_tien)) {
                Sach temp = danh_sach[i];
                danh_sach[i] = danh_sach[j];
                danh_sach[j] = temp;
            }
        }
    }
    printf("Danh sach sach da duoc sap xep theo gia. ");
}

void tim_kiem_sach() {
    char ten_sach[50];
    printf("Nhap ten sach can tim: ");
    getchar();  
    fgets(ten_sach, sizeof(ten_sach), stdin);
    ten_sach[strcspn(ten_sach, "\n")] = '\0'; 
    
    int tim_thay = 0;
    for (int i = 0; i < so_luong_sach; i++) {
        if (strstr(danh_sach[i].ten_sach, ten_sach) != NULL) {
            tim_thay = 1;
            printf("Ma sach: %s ", danh_sach[i].ma_sach);
            printf("Ten sach: %s ", danh_sach[i].ten_sach);
            printf("Tac gia: %s ", danh_sach[i].tac_gia);
            printf("Gia tien: %.2f ", danh_sach[i].gia_tien);
            printf("The loai: %s ", danh_sach[i].the_loai);
            printf("------------------------------- ");
        }
    }
    if (!tim_thay) {
        printf("Khong tim thay sach theo ten '%s'. ", ten_sach);
    }
}

int main() {
    int lua_chon;
    while (1) {
        printf("\nMENU ");
        printf("1. Nhap so luong va thong tin sach ");
        printf("2. Hien thi thong tin sach ");
        printf("3. Them sach vao vi tri ");
        printf("4. Xoa sach theo ma sach ");
        printf("5. Cap nhat thong tin sach theo ma sach ");
        printf("6. Sap xep sach theo gia (tang/giam) ");
        printf("7. Tim kiem sach theo ten sach ");
        printf("8. Thoat ");
        printf("Lua chon cua ban: ");
        scanf("%d", &lua_chon);
        
        switch (lua_chon) {
            case 1:
                printf("Nhap so luong sach: ");
                int so_luong;
                scanf("%d", &so_luong);
                for (int i = 0; i < so_luong; i++) {
                    nhap_sach();
                }
                break;
            case 2:
                hien_thi_sach();
                break;
            case 3:
                them_sach();
                break;
            case 4:
                xoa_sach();
                break;
            case 5:
                cap_nhat_sach();
                break;
            case 6:
                sap_xep_sach();
                break;
            case 7:
                tim_kiem_sach();
                break;
            case 8:
                printf("Thoat chuong trinh. ");
                return 0;
            default:
                printf("Lua chon khong hop le. Vui long chon lai. ");
        }
    }
}

