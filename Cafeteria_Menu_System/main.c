/*
    Fatih YELBOĞA - 270201028
    Berkay BAYRAK - 270201068
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

#define CSV_FILE_NAME "cafeteria_march_menu.csv"

typedef struct Normal_menu{

    char* date;
    char* soup;
    char* main_dish;
    char* side_dish;
    char* extra;
    int* sale_count_array;

} Normal_menu;

typedef struct Vegan_menu{

    char* date;
    char* soup;
    char* main_dish;
    char* side_dish;
    char* extra;
    int* sale_count_array;

} Vegan_menu;

typedef struct Vegetarian_menu
{
    char* date;
    char* soup;
    char* main_dish;
    char* side_dish;
    char* extra;
    int* sale_count_array;

} Vegetarian_menu;

typedef struct Cafeteria{

    char* name_of_month;
    Normal_menu* normal_menu_array;
    Vegan_menu* vegan_menu_array;
    Vegetarian_menu* vegetarian_menu_array;

} Cafeteria; 

int size_of_menu_array(char* csv_file_name){

    FILE* fpointer = fopen(csv_file_name, "r");
    int size_of_array = 0;
    if (fpointer != NULL)
    {
        char line[255];
        while (fgets(line, 255, fpointer))
        {
            size_of_array++;
        }
    }
    else
    {
        printf("File Reading ERROR!");
    }
    fclose(fpointer);

    return size_of_array/3;
}

void initialize_menus(Cafeteria *cafeteria, char* csv_file_name){

    int size = size_of_menu_array(csv_file_name);

    cafeteria -> normal_menu_array = (Normal_menu*) malloc(size * sizeof(Normal_menu));
    cafeteria -> vegan_menu_array = (Vegan_menu*) malloc(size * sizeof(Vegan_menu));
    cafeteria -> vegetarian_menu_array = (Vegetarian_menu*) malloc(size * sizeof(Vegetarian_menu));

    FILE* fpointer = fopen(csv_file_name, "r");
    if (fpointer != NULL)
    {

        int assingment_of_month = 0;
        int normal_menu_index = 0;
        int vegan_menu_index = 0;
        int vegetarian_menu_index = 0;

        char line[255];
        while (fgets(line, 255, fpointer))
        {

            char* menu_name = strtok(line, ",");
            char* date = strtok(NULL, ",");
            char* soup = strtok(NULL, ",");
            char* main_dish = strtok(NULL, ",");
            char* side_dish = strtok(NULL, ",");
            char* extra = strtok(NULL, ",");

            if (assingment_of_month == 0){
                
                char* day = strtok(date, "-");
                char* month = strtok(NULL, "-");
                char exact_month [64] = "\"";
                strcat(exact_month, month);
                cafeteria -> name_of_month = (char*) malloc(64* sizeof(char));
                strcpy(cafeteria -> name_of_month, exact_month);
                assingment_of_month = 1;

                char* hyphen = "-";
                char* day_month = malloc(strlen(day) + strlen(month) + strlen(hyphen) + 1);
                strcpy(day_month, day);
                strcat(day_month, hyphen);
                strcat(day_month, month);
                strcpy(date, day_month);
            }

            if (strcmp(menu_name, "\"Normal\"") == 0){

                cafeteria -> normal_menu_array[normal_menu_index].date  = (char*) malloc(64 * sizeof(char));
                strcpy(cafeteria -> normal_menu_array[normal_menu_index].date, date);

                cafeteria -> normal_menu_array[normal_menu_index].soup  = (char*) malloc(64 * sizeof(char));
                strcpy(cafeteria -> normal_menu_array[normal_menu_index].soup, soup);

                cafeteria -> normal_menu_array[normal_menu_index].main_dish = (char*) malloc(64 * sizeof(char));
                strcpy(cafeteria -> normal_menu_array[normal_menu_index].main_dish, main_dish);

                cafeteria -> normal_menu_array[normal_menu_index].side_dish  = (char*) malloc(64 * sizeof(char));
                strcpy(cafeteria -> normal_menu_array[normal_menu_index].side_dish, side_dish);

                cafeteria -> normal_menu_array[normal_menu_index].extra  = (char*) malloc(64 * sizeof(char));
                strcpy(cafeteria -> normal_menu_array[normal_menu_index].extra, extra);

                cafeteria -> normal_menu_array[normal_menu_index].sale_count_array = (int*) malloc(3 * sizeof(int));
                cafeteria -> normal_menu_array[normal_menu_index].sale_count_array[0] = 0;
                cafeteria -> normal_menu_array[normal_menu_index].sale_count_array[1] = 0;
                cafeteria -> normal_menu_array[normal_menu_index].sale_count_array[2] = 0;

                normal_menu_index++;
            } 
            else if (strcmp(menu_name, "\"Vegan\"") == 0){

                cafeteria -> vegan_menu_array[vegan_menu_index].date  = (char*) malloc(64 * sizeof(char));
                strcpy(cafeteria -> vegan_menu_array[vegan_menu_index].date, date);

                cafeteria -> vegan_menu_array[vegan_menu_index].soup  = (char*) malloc(64 * sizeof(char));
                strcpy(cafeteria -> vegan_menu_array[vegan_menu_index].soup, soup);

                cafeteria -> vegan_menu_array[vegan_menu_index].main_dish = (char*) malloc(64 * sizeof(char));
                strcpy(cafeteria -> vegan_menu_array[vegan_menu_index].main_dish, main_dish);

                cafeteria -> vegan_menu_array[vegan_menu_index].side_dish  = (char*) malloc(64 * sizeof(char));
                strcpy(cafeteria -> vegan_menu_array[vegan_menu_index].side_dish, side_dish);

                cafeteria -> vegan_menu_array[vegan_menu_index].extra  = (char*) malloc(64 * sizeof(char));
                strcpy(cafeteria -> vegan_menu_array[vegan_menu_index].extra, extra);

                cafeteria -> vegan_menu_array[vegan_menu_index].sale_count_array = (int*) malloc(3 * sizeof(int));
                cafeteria -> vegan_menu_array[vegan_menu_index].sale_count_array[0] = 0;
                cafeteria -> vegan_menu_array[vegan_menu_index].sale_count_array[1] = 0;
                cafeteria -> vegan_menu_array[vegan_menu_index].sale_count_array[2] = 0;

                vegan_menu_index++;
            }
            else if (strcmp(menu_name, "\"Vegetarian\"") == 0){

                cafeteria -> vegetarian_menu_array[vegetarian_menu_index].date  = (char*) malloc(64 * sizeof(char));
                strcpy(cafeteria -> vegetarian_menu_array[vegetarian_menu_index].date, date);

                cafeteria -> vegetarian_menu_array[vegetarian_menu_index].soup  = (char*) malloc(64 * sizeof(char));
                strcpy(cafeteria -> vegetarian_menu_array[vegetarian_menu_index].soup, soup);

                cafeteria -> vegetarian_menu_array[vegetarian_menu_index].main_dish = (char*) malloc(64 * sizeof(char));
                strcpy(cafeteria -> vegetarian_menu_array[vegetarian_menu_index].main_dish, main_dish);

                cafeteria -> vegetarian_menu_array[vegetarian_menu_index].side_dish  = (char*) malloc(64 * sizeof(char));
                strcpy(cafeteria -> vegetarian_menu_array[vegetarian_menu_index].side_dish, side_dish);

                cafeteria -> vegetarian_menu_array[vegetarian_menu_index].extra  = (char*) malloc(64 * sizeof(char));
                strcpy(cafeteria -> vegetarian_menu_array[vegetarian_menu_index].extra, extra);

                cafeteria -> vegetarian_menu_array[vegetarian_menu_index].sale_count_array = (int*) malloc(3 * sizeof(int));
                cafeteria -> vegetarian_menu_array[vegetarian_menu_index].sale_count_array[0] = 0;
                cafeteria -> vegetarian_menu_array[vegetarian_menu_index].sale_count_array[1] = 0;
                cafeteria -> vegetarian_menu_array[vegetarian_menu_index].sale_count_array[2] = 0;

                vegetarian_menu_index++;
            }
        }
    }
    else
    {
        printf("File Reading ERROR!");
    }

    fclose(fpointer);
}

void record_customer_counts(Cafeteria* cafeteria){

    srand(time(NULL));
    int size = size_of_menu_array(CSV_FILE_NAME);

    for (int i = 0; i < size; i++)
    {
        for(int j = 0; j < 3; j++){

            cafeteria->normal_menu_array[i].sale_count_array[j] = rand() % 50;
            cafeteria->vegan_menu_array[i].sale_count_array[j] = rand() % 50;
            cafeteria->vegetarian_menu_array[i].sale_count_array[j] = rand() % 50;
        }
    }
}

void display_normal_menu_content(Normal_menu normal_menu){

    printf("Date: %s\n", normal_menu.date);
    printf("Soup: %s\n", normal_menu.soup);
    printf("Main dish: %s\n", normal_menu.main_dish);
    printf("Side dish: %s\n", normal_menu.side_dish);
    printf("Extra: %s\n", normal_menu.extra);
}

void display_counts_of_normal_menu(Cafeteria* cafeteria, char* day_of_month){

    int size = size_of_menu_array(CSV_FILE_NAME);
    for (int i = 0; i < size; i++)
    {
        Normal_menu normal_menu = cafeteria->normal_menu_array[i];
        if (strcmp(normal_menu.date, day_of_month) == 0){

            int student_counts = normal_menu.sale_count_array[0];
            int academic_counts = normal_menu.sale_count_array[1];
            int administrative_counts = normal_menu.sale_count_array[2];

            printf("Students: %d, Academic: %d, Administrative: %d\n", student_counts, academic_counts, administrative_counts);
        }
    }
}

void display_vegan_menu_content(Vegan_menu vegan_menu){

    printf("Date: %s\n", vegan_menu.date);
    printf("Soup: %s\n", vegan_menu.soup);
    printf("Main dish: %s\n", vegan_menu.main_dish);
    printf("Side dish: %s\n", vegan_menu.side_dish);
    printf("Extra: %s\n", vegan_menu.extra);
}

void display_counts_of_vegan_menu(Cafeteria* cafeteria, char* day_of_month){

    int size = size_of_menu_array(CSV_FILE_NAME);
    for (int i = 0; i < size; i++)
    {
        Vegan_menu vegan_menu = cafeteria->vegan_menu_array[i];
        if (strcmp(vegan_menu.date, day_of_month) == 0){

            int student_counts = vegan_menu.sale_count_array[0];
            int academic_counts = vegan_menu.sale_count_array[1];
            int administrative_counts = vegan_menu.sale_count_array[2];

            printf("Students: %d, Academic: %d, Administrative: %d\n", student_counts, academic_counts, administrative_counts);
        }
    }
}

void display_vegetarian_menu_content(Vegetarian_menu vegetarian_menu){

    printf("Date: %s\n", vegetarian_menu.date);
    printf("Soup: %s\n", vegetarian_menu.soup);
    printf("Main dish: %s\n", vegetarian_menu.main_dish);
    printf("Side dish: %s\n", vegetarian_menu.side_dish);
    printf("Extra: %s\n", vegetarian_menu.extra);
}

void display_counts_of_vegetarian_menu(Cafeteria* cafeteria, char* day_of_month){

    int size = size_of_menu_array(CSV_FILE_NAME);
    for (int i = 0; i < size; i++)
    {
        Vegetarian_menu vegetarian_menu = cafeteria->vegetarian_menu_array[i];
        if (strcmp(vegetarian_menu.date, day_of_month) == 0){

            int student_counts = vegetarian_menu.sale_count_array[0];
            int academic_counts = vegetarian_menu.sale_count_array[1];
            int administrative_counts = vegetarian_menu.sale_count_array[2];

            printf("Students: %d, Academic: %d, Administrative: %d\n", student_counts, academic_counts, administrative_counts);
        }
    }
}

void calc_and_show_income(Cafeteria *cafeteria){

    int size = size_of_menu_array(CSV_FILE_NAME);

    printf("\n~ ~ ~ ~ Normal menu for the first and last days of the month\n");
    display_normal_menu_content(cafeteria -> normal_menu_array[0]);
    printf("~ ~ ~ ~ Normal menu for the first and last days of the month\n");
    display_normal_menu_content(cafeteria -> normal_menu_array[size-1]);
    printf("~ ~ ~ ~ Vegan menu for the first and last days of the month\n");
    display_vegan_menu_content(cafeteria -> vegan_menu_array[0]);
    printf("~ ~ ~ ~ Vegan menu for the first and last days of the month\n");
    display_vegan_menu_content(cafeteria -> vegan_menu_array[size-1]);
    printf("~ ~ ~ ~ Vegetarian menu for the first and last days of the month\n");
    display_vegetarian_menu_content(cafeteria -> vegetarian_menu_array[0]);
    printf("~ ~ ~ ~ Vegetarian menu for the first and last days of the month\n");
    display_vegetarian_menu_content(cafeteria -> vegetarian_menu_array[size-1]);
    
    printf("\n~ ~ ~ ~ Example output for Normal menu\n");
    display_normal_menu_content(cafeteria -> normal_menu_array[5]);
    printf("~ ~ ~ ~ Example output for Vegan menu\n");
    display_normal_menu_content(cafeteria -> normal_menu_array[10]);
    printf("~ ~ ~ ~ Example output for Vegetarian menu\n");
    display_normal_menu_content(cafeteria -> normal_menu_array[15]);

    printf("~ ~ ~ ~ Counts for the example normal menu output for March 7th\n");
    display_counts_of_normal_menu(cafeteria, "\"7-Mar\"");
    printf("~ ~ ~ ~ Counts for the example vegan menu output for March 14th\n");
    display_counts_of_vegan_menu(cafeteria, "\"14-Mar\"");
    printf("~ ~ ~ ~ Counts for the example vegetarian menu output for March 21th\n");
    display_counts_of_vegetarian_menu(cafeteria, "\"21-Mar\"");

    printf("\n------------------------------ The Sale Results ------------------------------\n");
    int student_sales = 0;
    int academic_personel_sales = 0;
    int administrative_personel_sales = 0;
    int normal_menu_sales = 0;
    int vegan_menu_sales = 0;
    int vegetarian_menu_sales = 0;
    int total_sales = 0;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 3; j++){

            switch (j)
            {
                case 0:
                    normal_menu_sales += cafeteria->normal_menu_array[i].sale_count_array[j] * 6;
                    vegan_menu_sales += cafeteria->vegan_menu_array[i].sale_count_array[j] * 6;
                    vegetarian_menu_sales += cafeteria->vegetarian_menu_array[i].sale_count_array[j] * 6;
                    student_sales += cafeteria->normal_menu_array[i].sale_count_array[j] * 6 + cafeteria->vegan_menu_array[i].sale_count_array[j] * 6 + cafeteria->vegetarian_menu_array[i].sale_count_array[j] * 6;
                    break;
                case 1:
                    normal_menu_sales += cafeteria->normal_menu_array[i].sale_count_array[j] * 16;
                    vegan_menu_sales += cafeteria->vegan_menu_array[i].sale_count_array[j] * 16;
                    vegetarian_menu_sales += cafeteria->vegetarian_menu_array[i].sale_count_array[j] * 16;
                    academic_personel_sales += cafeteria->normal_menu_array[i].sale_count_array[j] * 16 + cafeteria->vegan_menu_array[i].sale_count_array[j] * 16 + cafeteria->vegetarian_menu_array[i].sale_count_array[j] * 16;
                    break;
                case 2:
                    normal_menu_sales += cafeteria->normal_menu_array[i].sale_count_array[j] * 12;
                    vegan_menu_sales += cafeteria->vegan_menu_array[i].sale_count_array[j] * 12;
                    vegetarian_menu_sales += cafeteria->vegetarian_menu_array[i].sale_count_array[j] * 12;
                    administrative_personel_sales += cafeteria->normal_menu_array[i].sale_count_array[j] * 12 + cafeteria->vegan_menu_array[i].sale_count_array[j] * 12 + cafeteria->vegetarian_menu_array[i].sale_count_array[j] * 12;
                    break;
        
                default:
                    break;
            }
        }
    }

    printf("Normal menu sales: %d TL, Vegan menu sales: %d TL, Vegetarian menu sales: %d TL\n", normal_menu_sales, vegan_menu_sales, vegetarian_menu_sales);
    printf("Student sales: %d TL, Academic personel sales: %d TL, Administrative personel sales: %d TL\n", student_sales, academic_personel_sales, administrative_personel_sales);
    total_sales = normal_menu_sales + vegan_menu_sales + vegetarian_menu_sales;
    printf("Total sale income: %d TL\n\n", total_sales);
}

int main(){

    Cafeteria cafeteria; 
    cafeteria.name_of_month = NULL;
    cafeteria.normal_menu_array = NULL;
    cafeteria.vegan_menu_array = NULL;
    cafeteria.vegetarian_menu_array = NULL;

    initialize_menus(&cafeteria, CSV_FILE_NAME);
    record_customer_counts(&cafeteria);
    calc_and_show_income(&cafeteria);

    return 0;
}