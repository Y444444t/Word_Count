#include <stdio.h>  
#include <stdlib.h>  
#include <ctype.h>  
#include <string.h>  
  
// ��������  
int count_characters(FILE *file);  
int count_words(FILE *file);  
  
int main(int argc, char *argv[]) {  
    FILE *file;  
    int count;  
  
    // ��������в�������  
    if (argc != 3) {  
        fprintf(stderr, "Usage: %s [-c|-w] <input_file_name>\n", argv[0]);  
        return 1;  
    }  
  
    // �������Ƿ���Ч  
    if (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-w") != 0) {  
        fprintf(stderr, "Invalid parameter: %s\n", argv[1]);  
        return 1;  
    }  
  
    // ���ļ�  
    file = fopen(argv[2], "r");  
    if (!file) {  
        perror("Error opening file");  
        return 1;  
    }  
  
    // ���ݲ���ͳ���ַ��򵥴�  
    if (strcmp(argv[1], "-c") == 0) {  
        count = count_characters(file);  
        printf("�ַ�����%d\n", count);  
    } else if (strcmp(argv[1], "-w") == 0) {  
        count = count_words(file);  
        printf("��������%d\n", count);  
    }  
  
    // �ر��ļ�  
    fclose(file);  
  
    return 0;  
}  
  
// ͳ���ַ���  
int count_characters(FILE *file) {  
    int ch, count = 0;  
    while ((ch = fgetc(file)) != EOF) {  
        count++;  
    }  
    rewind(file); // �����Ҫ�ٴζ�ȡ�ļ������������ļ�ָ��  
    return count;  
}  
  
// ͳ�Ƶ�����  
int count_words(FILE *file) {  
    int ch, in_word = 0, count = 0;  
    while ((ch = fgetc(file)) != EOF) {  
        if (isspace(ch) || ch == ',') { // �ո��Ʊ�������з��򶺺�  
            if (in_word) {  
                in_word = 0;  
                count++;  
            }  
        } else {  
            in_word = 1; // �����е��ַ�  
        }  
    }  
    // ����ļ��ڵ����н��������Ӽ���  
    if (in_word) {  
        count++;  
    }  
    rewind(file); // �����Ҫ�ٴζ�ȡ�ļ������������ļ�ָ��  
    return count;  
}
