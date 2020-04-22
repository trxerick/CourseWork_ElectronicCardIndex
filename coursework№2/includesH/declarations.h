#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 512

#ifdef linux
#define CLS system("clear")
#else
#define CLS system("cls")
#endif

typedef struct carlHead carHead;
typedef struct carlNode carNode;
typedef struct carStruct car;

struct carStruct
{
    char *name;
    char *company;
    int year;
    int price;
    float weight;
    float mileage;
    int speed[1];
};

struct carlNode
{
    int id;
    car *data;
    carNode *next;
    carNode *prev;
};

struct carlHead
{
    int count;
    carNode *first;
    carNode *last;
};