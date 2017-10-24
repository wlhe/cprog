#include <openssl/md5.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int md5cal(char *file, char *md5, size_t size)
{
    int ret = 0;
    if (file == NULL || md5 == NULL || size < 2 * MD5_DIGEST_LENGTH + 1) {
        ret = -1;
        printf("passed error parameter, point null or buffer size too short\n");
        return ret;
    }
    unsigned char buf[MD5_DIGEST_LENGTH] = {0};
    MD5_CTX ctx;
    const size_t CAL_LEN = 8192;
    char read[CAL_LEN] = {0};

    MD5_Init(&ctx);

    FILE *fd = fopen(file, "r");
    if (fd == NULL) {
        printf("open %s error!!!\n", file);
        ret = -1;
        return ret;
    }
    size_t n = 0;
    do {
        n = fread(read, 1, CAL_LEN, fd);
        if (n > 0) {
            MD5_Update(&ctx, read, n);
        }
    } while (n > 0);

    if (feof(fd) != 0) {
        MD5_Final(buf, &ctx);
        for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
            snprintf(&md5[2 * i], size - 2 * i, "%02x", buf[i]);
        }
        ret = 0;
    } else {
        printf("read file error\n");
        ret = -1;
    }
    fclose(fd);

    return ret;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf(
            "Usage:\n"
            "./md5cal filename\n");
        return 0;
    }
    char *file = argv[1];
    printf("file: %s\n", file);
    char md5[33] = {0};
    md5cal(file, md5, 33);
    printf("%s  %s\n", md5, file);
    return 1;
}