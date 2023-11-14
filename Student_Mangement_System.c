#include <stdio.h>
#include <string.h>

#define M_MARKS 6

struct student
{
    char name[30];
    int roll;
    float marks[M_MARKS];
    int class;
    int cgp;
};

struct student S;

void add_student()
{
    FILE *file = fopen("rahadnew.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    printf("\nEnter student name: ");
    fflush(stdin);
    scanf("%[^\n]s", &S.name);

    printf("Enter roll number: ");
    scanf("%d", &S.roll);

    printf("Enter class: ");
    scanf("%d", &S.class);

    fwrite(&S, sizeof(struct student), 1, file);
    fclose(file);

    printf("Student data added successfully\n\n");
}

void search_student_roll()
{
    FILE *file = fopen("rahadnew.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    int search_roll, count = 0;
    printf("Enter the roll number you want to search: ");
    scanf("%d", &search_roll);

    while (fread(&S, sizeof(struct student), 1, file))
    {
        if (search_roll == S.roll)
        {
            printf("\nStudent name: %s\n", S.name);
            printf("Class roll: %d\n", S.roll);
            printf("cgp : %.2f\n", S.cgp);
            printf("Student marks:\n");
            for (int j = 0; j < M_MARKS; j++)
            {
                printf("Marks for subject %d: %.2f\n", j + 1, S.marks[j]);
            }
            count++;
            break;
        }
    }

    fclose(file);

    if (count == 0)
    {
        printf("Student data not found.\n");
    }
}

void search_student_name()
{
    FILE *file = fopen("rahadnew.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char search_name[30];
    int count = 0;
    printf("Enter the name you want to search: ");
    fflush(stdin);
    gets(search_name);

    while (fread(&S, sizeof(struct student), 1, file))
    {
        if (strcmp(search_name, S.name) == 0)
        {
            printf("\nStudent name: %s\n", S.name);
            printf("Admission roll: %d\n", S.roll);
            printf("Student marks:\n");
            for (int j = 0; j < M_MARKS; j++)
            {
                printf("Marks for subject %d: %.2f\n", j + 1, S.marks[j]);
            }
            count++;
            break;
        }
    }

    fclose(file);

    if (count == 0)
    {
        printf("Student data not found.\n");
    }
}

void delete_student()
{
    FILE *f;
    f = fopen("temp.txt", "a");
    int search_roll;
    int count = 0;
    printf("Enter the roll number you want to delete: ");
    scanf("%d", &search_roll);

    FILE *file = fopen("rahadnew.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&S, sizeof(struct student), 1, file) == 1)
    {
        if (search_roll == S.roll)
        {
            count = 1;
        }
        else
        {
            fwrite(&S, sizeof(struct student), 1, f);
        }
    }

    fclose(file);
    fclose(f);

    remove("rahadnew.txt");
    rename("temp.txt", "rahadnew.txt");

    if (count == 0)
    {
        printf("Student data not found.\n");
    }
    else
    {
        printf("Student data deleted successfully.\n");
    }
}

void show_student()

{

    FILE *file = fopen("rahadnew.txt", "r");

    while (fread(&S, sizeof(struct student), 1, file) == 1)
    {
        printf("\nStudent name: %s\n", S.name);
        printf("Roll number: %d\n", S.roll);
        printf("Class: %d\n", S.class);
        // printf("cgp %f\n", S.cgp);

        printf("Student marks:\n");
        for (int j = 0; j < M_MARKS; j++)
        {
            printf("Marks for subject %d: %.2f\n", j + 1, S.marks[j]);
        }
    }

    fclose(file);
}

void edit_student()
{

    int search_roll;
    int count = 0;
    printf("Enter the roll number you want to edit: ");
    scanf("%d", &search_roll);

    FILE *file = fopen("rahadnew.txt", "r+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&S, sizeof(struct student), 1, file))
    {
        if (search_roll == S.roll)
        {
            printf("Enter the new name: ");
            fflush(stdin);
            scanf("%[^\n]s", &S.name);
            printf("enter the new roll");
            scanf("%d", &S.roll);
            printf("Enter the new class: ");
            scanf("%d", &S.class);
            printf("Enter marks for each subject:\n");
            for (int j = 0; j < M_MARKS; j++)
            {
                printf("Subject %d: ", j + 1);
                scanf("%f", &S.marks[j]);
            }
            count++;

            fseek(file, -sizeof(struct student), SEEK_CUR);
            fwrite(&S, sizeof(struct student), 1, file);
            fclose(file);
            break;
        }
    }

    if (count == 0)
    {
        printf("Student data not found.\n");
    }
    else
    {
        printf("Student data edited successfully.\n");
    }
}

void add_exam_marks()
{
    FILE *file = fopen("rahadnew.txt", "r+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    int search_roll;
    int count = 0;
    // int total_marks =0;
    printf("Enter the roll number of the student: ");
    scanf("%d", &search_roll);

    while (fread(&S, sizeof(struct student), 1, file))
    {
        if (search_roll == S.roll)
        {
            printf("Enter marks for each subject:\n");
            for (int j = 0; j < M_MARKS; j++)
            {
                printf("Subject %d: ", j + 1);
                scanf("%f", &S.marks[j]);
            }

            fseek(file, -sizeof(struct student), SEEK_CUR);
            fwrite(&S, sizeof(struct student), 1, file);

            count++;
            break;
        }
    }

    fclose(file);

    if (count == 0)
    {
        printf("Student data not found.\n");
    }
    else
    {
        printf("Exam marks added successfully.\n");
    }
}

void show_cgp()
{
    int roll, count = 0, countt = 0;
    int res[100];
    FILE *file = fopen("rahadnew.txt", "r");

    printf("roll for cgp : ");
    scanf("%d", &roll);

    int found = 0, sum = 0;
    while (fread(&S, sizeof(struct student), 1, file) == 1)
    {
        if (roll == S.roll)
        {
            for (int j = 0; j < 6; j++)
            {
                if (S.marks[j] >= 80)
                {
                    res[j] = 5.00;
                }
                else if (S.marks[j] >= 75 && S.marks[j] < 80)
                {
                    res[j] = 4.75;
                }
                else if (S.marks[j] >= 70 && S.marks[j] < 75)
                {
                    res[j] = 4.50;
                }
                else if (S.marks[j] >= 65 && S.marks[j] < 70)
                {
                    res[j] = 4.00;
                }
                else if (S.marks[j] >= 60 && S.marks[j] < 65)
                {
                    res[j] = 3.75;
                }
                else if (S.marks[j] >= 55 && S.marks[j] < 60)
                {
                    res[j] = 3.50;
                }
                else if (S.marks[j] >= 50 && S.marks[j] < 55)
                {
                    res[j] = 3.00;
                }
                else if (S.marks[j] >= 45 && S.marks[j] < 50)
                {
                    res[j] = 2.5;
                }
                else if (S.marks[j] >= 33 && S.marks[j] < 45)
                {
                    res[j] = 2;
                }
                else if (S.marks[j] < 33 && S.marks[j] >= 0)
                {
                    res[j] = 0.0;
                }

                found = 1;
            }
        }
        if (found == 1)
            break;
    }

    fclose(file);

    if (found == 1)
    {
        for (int j = 0; j < 6; j++)
        {
            sum = sum + res[j];
        }
        float res2 = sum / 6;
        for (int j = 0; j < 6; j++)
        {
            if (res[j] == 0)
            {
                countt++;
            }
        }
        if (countt != 0)
        {
            printf("cgp is 0.00");
        }
        else if (countt == 0)
        {
            printf("cgp is %.2f", res2);
        }
    }

    else
    {
        printf("Student roll not found in the database\n");
    }
}

void about_us()
{

    printf("  \n NAME:Md Nazmul Islam ID:0242310005101183\n\n,Mosabbir Maruf ID:0242310005101182\n\nTowhidul Islam ID:0242310005101069\n\nMahir Faysal ID:0242310005101060\n\n");
}

int main()
{
    int option;
    int choice;
    char key;
    printf("\t\t\t\t-------------Daffodil Kindergarten School-------------------\t\t\t\t\n");
    printf("option-----------------------------------------------------------------------------------------------------------------\n");
    do
    {

        printf("\n1. Enter Category\n\n");
        printf("2. Search Student Info\n");
        printf("3. Add Student Info\n");
        printf("4. Delete Student Info\n");
        printf("5. Show Student Details\n");
        printf("6. Add Exam marks\n");
        printf("7. Show CGPA\n");
        printf("8. Edit Info\n");
        printf("9. Exit\n");
        printf("10. About Us\n");
        printf("\nEnter your option: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("Option will be available from (2-9)\n");
            break;
        case 2:
            printf("press 1 to search by roll and press 2 search by name: ");
            scanf("%d", &choice);
            if (choice == 1)
                search_student_roll();
            if (choice == 2)
                search_student_name();

            break;
        case 3:
            add_student();
            break;
        case 4:
            delete_student();
            break;
        case 5:
            show_student();
            break;
        case 6:
            add_exam_marks();
            break;
        case 7:
            show_cgp();
            break;
        case 8:
            edit_student();
            break;
        case 9:
            printf("Press Y to continue and N to exit\n");
            printf("Enter key: ");
            fflush(stdin);
            scanf("%c", &key);
            break;
        case 10:
            about_us();
            break;
        }
    } while (key != 'N' && key != 'n');

    return 0;
}