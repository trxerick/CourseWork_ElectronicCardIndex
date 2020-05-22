#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>

#define MAXLENGTH 512

#ifdef linux
#define CLS system("clear")
#else
#define CLS system("cls")
#endif

typedef struct carlHead carHead;
typedef struct carlNode carNode;
typedef struct carStruct car;
typedef struct queryStruct query;

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

struct queryStruct
{
    char is_good;
    char *name;
    char *company;
    int low_year;
    int max_year;
    int low_price;
    int max_price;
    int low_speed_max;
    int max_speed_max;
    int low_speed_min;
    int max_speed_min;
};