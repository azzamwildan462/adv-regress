#include <bits/stdc++.h>
#include <fstream>

int main()
{
    int arr[6] = {0, 1, 2, 3, 4, 5};
    char buf[12];
    memcpy(buf + 0, &arr[0], 2);
    memcpy(buf + 2, &arr[1], 2);
    memcpy(buf + 4, &arr[2], 2);
    memcpy(buf + 6, &arr[3], 2);
    memcpy(buf + 8, &arr[4], 2);
    memcpy(buf + 10, &arr[5], 2);

    uint16_t cek;
    memcpy(&cek, buf + 4, 2);
    printf("cek: %d\n", cek);
    // FILE *fp;
    // fp = fopen("file.bin", "r");

    // std::ofstream of("file.bin", std::ios::binary | std::ios::out);
    // of.write(buf, 12);
    // of.close();

    char rd_buf[230400];
    std::ifstream file("LUT_fr2lap.bin", std::ios::binary | std::ios::in);
    file.read(rd_buf, 230400);
    file.close();
    uint16_t cek2;
    memcpy(&cek2, rd_buf + 230398, 2);
    printf("cek2: %d\n", cek2);
    return 0;
}