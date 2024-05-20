#include <stdio.h>  
#include <stdlib.h>  
#include <ctype.h>  
#include <string.h>  
  
// 函数声明  
int count_characters(FILE *file);  
int count_words(FILE *file);  
  
int main(int argc, char *argv[]) {  
    FILE *file;  
    int count;  
  
    // 检查命令行参数数量  
    if (argc != 3) {  
        fprintf(stderr, "Usage: %s [-c|-w] <input_file_name>\n", argv[0]);  
        return 1;  
    }  
  
    // 检查参数是否有效  
    if (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-w") != 0) {  
        fprintf(stderr, "Invalid parameter: %s\n", argv[1]);  
        return 1;  
    }  
  
    // 打开文件  
    file = fopen(argv[2], "r");  
    if (!file) {  
        perror("Error opening file");  
        return 1;  
    }  
  
    // 根据参数统计字符或单词  
    if (strcmp(argv[1], "-c") == 0) {  
        count = count_characters(file);  
        printf("字符数：%d\n", count);  
    } else if (strcmp(argv[1], "-w") == 0) {  
        count = count_words(file);  
        printf("单词数：%d\n", count);  
    }  
  
    // 关闭文件  
    fclose(file);  
  
    return 0;  
}  
  
// 统计字符数  
int count_characters(FILE *file) {  
    int ch, count = 0;  
    while ((ch = fgetc(file)) != EOF) {  
        count++;  
    }  
    rewind(file); // 如果需要再次读取文件，可以重置文件指针  
    return count;  
}  
  
// 统计单词数  
int count_words(FILE *file) {  
    int ch, in_word = 0, count = 0;  
    while ((ch = fgetc(file)) != EOF) {  
        if (isspace(ch) || ch == ',') { // 空格、制表符、换行符或逗号  
            if (in_word) {  
                in_word = 0;  
                count++;  
            }  
        } else {  
            in_word = 1; // 单词中的字符  
        }  
    }  
    // 如果文件在单词中结束，增加计数  
    if (in_word) {  
        count++;  
    }  
    rewind(file); // 如果需要再次读取文件，可以重置文件指针  
    return count;  
}
