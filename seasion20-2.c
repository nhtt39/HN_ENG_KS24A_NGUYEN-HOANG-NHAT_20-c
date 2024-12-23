#include <stdio.h>
#include <string.h>

#define MAX_SP 100

typedef struct {
    char ma_sp[20];
    char ten_sp[50];
    float gia_nhap;
    float gia_ban;
    int so_luong;
} SanPham;

SanPham danh_sach[MAX_SP];
int so_luong_sp = 0;
float doanh_thu = 0;

void nhap_san_pham() {
    SanPham sp;
    printf("Nhap ma san pham: ");
    scanf("%s", sp.ma_sp);
    printf("Nhap ten san pham: ");
    getchar();
    fgets(sp.ten_sp, sizeof(sp.ten_sp), stdin);
    sp.ten_sp[strcspn(sp.ten_sp, "\n")] = '\0';
    printf("Nhap gia nhap: ");
    scanf("%f", &sp.gia_nhap);
    printf("Nhap gia ban: ");
    scanf("%f", &sp.gia_ban);
    printf("Nhap so luong: ");
    scanf("%d", &sp.so_luong);

    for (int i = 0; i < so_luong_sp; i++) {
        if (strcmp(danh_sach[i].ma_sp, sp.ma_sp) == 0) {
            danh_sach[i].so_luong += sp.so_luong;
            printf("San pham da ton tai, so luong moi: %d\n", danh_sach[i].so_luong);
            return;
        }
    }

    if (so_luong_sp < MAX_SP) {
        danh_sach[so_luong_sp++] = sp;
        doanh_thu -= sp.so_luong * sp.gia_nhap;
    } else {
        printf("Danh sach san pham da day.\n");
    }
}

void hien_thi_san_pham() {
    if (so_luong_sp == 0) {
        printf("Danh sach san pham rong!\n");
    } else {
        printf("Danh sach san pham:\n");
        for (int i = 0; i < so_luong_sp; i++) {
            printf("Ma SP: %s, Ten SP: %s, Gia nhap: %.2f, Gia ban: %.2f, So luong: %d\n",
                   danh_sach[i].ma_sp, danh_sach[i].ten_sp, danh_sach[i].gia_nhap,
                   danh_sach[i].gia_ban, danh_sach[i].so_luong);
        }
    }
}

void cap_nhat_san_pham() {
    char ma_sp[20];
    printf("Nhap ma san pham can cap nhat: ");
    scanf("%s", ma_sp);
    int i;
    for (i = 0; i < so_luong_sp; i++) {
        if (strcmp(danh_sach[i].ma_sp, ma_sp) == 0) {
            printf("Nhap thong tin moi cho san pham: \n");
            printf("Nhap ten san pham: ");
            getchar();
            fgets(danh_sach[i].ten_sp, sizeof(danh_sach[i].ten_sp), stdin);
            danh_sach[i].ten_sp[strcspn(danh_sach[i].ten_sp, "\n")] = '\0';
            printf("Nhap gia nhap: ");
            scanf("%f", &danh_sach[i].gia_nhap);
            printf("Nhap gia ban: ");
            scanf("%f", &danh_sach[i].gia_ban);
            printf("Nhap so luong: ");
            scanf("%d", &danh_sach[i].so_luong);
            return;
        }
    }
    printf("San pham khong tim thay.\n");
}

void sap_xep_san_pham() {
    int lua_chon;
    printf("Sap xep theo gia (1: Tang dan, 2: Giam dan): ");
    scanf("%d", &lua_chon);
    for (int i = 0; i < so_luong_sp - 1; i++) {
        for (int j = i + 1; j < so_luong_sp; j++) {
            if ((lua_chon == 1 && danh_sach[i].gia_ban > danh_sach[j].gia_ban) ||
                (lua_chon == 2 && danh_sach[i].gia_ban < danh_sach[j].gia_ban)) {
                SanPham temp = danh_sach[i];
                danh_sach[i] = danh_sach[j];
                danh_sach[j] = temp;
            }
        }
    }
    printf("Danh sach san pham da duoc sap xep.\n");
}

void tim_kiem_san_pham() {
    char ten_sp[50];
    printf("Nhap ten san pham can tim: ");
    getchar();
    fgets(ten_sp, sizeof(ten_sp), stdin);
    ten_sp[strcspn(ten_sp, "\n")] = '\0';
    
    int tim_thay = 0;
    for (int i = 0; i < so_luong_sp; i++) {
        if (strstr(danh_sach[i].ten_sp, ten_sp) != NULL) {
            tim_thay = 1;
            printf("Ma SP: %s, Ten SP: %s, Gia nhap: %.2f, Gia ban: %.2f, So luong: %d\n",
                   danh_sach[i].ma_sp, danh_sach[i].ten_sp, danh_sach[i].gia_nhap,
                   danh_sach[i].gia_ban, danh_sach[i].so_luong);
        }
    }
    if (!tim_thay) {
        printf("Khong tim thay san pham theo ten '%s'.\n", ten_sp);
    }
}

void ban_san_pham() {
    char ma_sp[20];
    printf("Nhap ma san pham can ban: ");
    scanf("%s", ma_sp);
    int so_luong_ban;
    printf("Nhap so luong can ban: ");
    scanf("%d", &so_luong_ban);
    
    for (int i = 0; i < so_luong_sp; i++) {
        if (strcmp(danh_sach[i].ma_sp, ma_sp) == 0) {
            if (danh_sach[i].so_luong == 0) {
                printf("San pham het hang!\n");
            } else if (so_luong_ban > danh_sach[i].so_luong) {
                printf("Khong con du hang.\n");
            } else {
                danh_sach[i].so_luong -= so_luong_ban;
                doanh_thu += so_luong_ban * danh_sach[i].gia_ban;
                printf("Ban %d san pham. Doanh thu tang: %.2f\n", so_luong_ban, so_luong_ban * danh_sach[i].gia_ban);
            }
            return;
        }
    }
    printf("San pham khong tim thay.\n");
}

void hien_thi_doanh_thu() {
    printf("Doanh thu hien tai: %.2f\n", doanh_thu);
}

int main() {
    int lua_chon;
    while (1) {
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin san pham\n");
        printf("2. Hien thi danh sach san pham\n");
        printf("3. Nhap san pham\n");
        printf("4. Cap nhat thong tin san pham\n");
        printf("5. Sap xep san pham theo gia (tang/giam)\n");
        printf("6. Tim kiem san pham\n");
        printf("7. Ban san pham\n");
        printf("8. Doanh thu hien tai\n");
        printf("9. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &lua_chon);
        
        switch (lua_chon) {
            case 1:
                nhap_san_pham();
                break;
            case 2:
                hien_thi_san_pham();
                break;
            case 3:
                nhap_san_pham();
                break;
            case 4:
                cap_nhat_san_pham();
                break;
            case 5:
                sap_xep_san_pham();
                break;
            case 6:
                tim_kiem_san_pham();
                break;
            case 7:
                ban_san_pham();
                break;
            case 8:
                hien_thi_doanh_thu();
                break;
            case 9:
                printf("Thoat chuong trinh.\n");
                return 0;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    }
}

               

