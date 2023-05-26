#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int no;
    int age;
    char name[20];
} Student;

Student *student_create(int no, int age, const char *name)
{
    int len = 0;
    Student *stu = (Student *)malloc(sizeof(Student));

    stu->no = no;
    stu->age = age;

    if (name) {
        len = strlen(name) > 19 ? strlen(name) : 19;
        strncpy(stu->name, name, len);
    } 

    stu->name[len] = '\0';
    return stu;
}

int student_tostr(const void *data, char *dst, int len)
{
    if (!data || !dst || len <= 0) {
        return -1;
    }

    Student *stu = (Student *)data;
    snprintf(dst, len, "{no: %d, age: %d, name: %s} ", stu->no, stu->age, stu->name);

    return 0;
}

int student_free(void *data)
{
    if (!data) {
        return -1;
    }

    free(data);

    return 0;
}

int student_compare(const void *data1, const void *data2)
{
    // undo
    return 0;
}
