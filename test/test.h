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

void student_print(void *data)
{
    if (!data) {
        return;
    }

    Student *stu = (Student *)data;
    printf("(%d, %d, %s) ", stu->no, stu->age, stu->name);
}