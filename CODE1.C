#include <stdio.h>
#include <stdlib.h>
struct taxcalculator
{
 int id;
 char name[50];
 double income;
 double tax;
};
void add(FILE *fp)
{
 struct taxcalculator newrecord;
 printf("\nEnter the ID of the person: ");
 scanf("%d", &newrecord.id);
 printf("Enter the name of the person: ");
 scanf("%s", newrecord.name);
 printf("Enter the income of the person: ");
 scanf("%lf", &newrecord.income);
 if (newrecord.income <= 250000)
 {
 newrecord.tax = 0;
 }
 else if (newrecord.income <= 500000)
 {
 newrecord.tax = (newrecord.income - 250000) * 0.05;
 }
 else if (newrecord.income <= 750000)
 {
 newrecord.tax = 12500 + (newrecord.income - 500000) * 0.1;
 }
 else if (newrecord.income <= 1000000)
 {
 newrecord.tax = 37500 + (newrecord.income - 750000) * 0.15;
 }
 else if (newrecord.income <= 1250000)
 {
 newrecord.tax = 75000 + (newrecord.income - 1000000) * 0.2;
 }
 else if (newrecord.income <= 1500000)
 {
 newrecord.tax = 125000 + (newrecord.income - 1250000) * 0.25;
 }
 else
 {
 newrecord.tax = 187500 + (newrecord.income - 1500000) * 0.3;
 }
 fwrite(&newrecord, sizeof(struct taxcalculator), 1, fp);
 printf("Congrats!, Record added successfully.\n");
}
void list_records(FILE *fp)
{
 struct taxcalculator record;
 int found = 0;
 printf("\nList of all Tax Payers:\n");
 rewind(fp);
 while (fread(&record, sizeof(struct taxcalculator), 1, fp) == 1)
 {
 found = 1;
 printf("ID: %d, Name: %s, Income: %lf, Tax: %lf\n",
 record.id, record.name, record.income, record.tax);
 }
 if (!found)
 {
 printf("Sorry, There is no record found in our file.Press 1 to add.\n");
 }
}
void search_record(FILE *fp)
{
 int search_id;
 struct taxcalculator record;
 printf("\nEnter ID of the person whose details you want to search: ");
 scanf("%d", &search_id);
 rewind(fp);
 while (fread(&record, sizeof(struct taxcalculator), 1, fp) == 1)
 {
 if (record.id == search_id)
 {
 printf("ID: %d, Name: %s, Income: %lf, Tax: %lf\n",
 record.id, record.name, record.income, record.tax);
 return;
 }
 }
 printf("Sorry, There is no record found in our file.Press 1 to add.\n");
}
void edit_record(FILE *fp)
{
 int edit_id;
 struct taxcalculator record;
 printf("\nEnter ID to edit: ");
 scanf("%d", &edit_id);
 rewind(fp);
 while (fread(&record, sizeof(struct taxcalculator), 1, fp) == 1)
 {
 if (record.id == edit_id)
 {
 printf("Enter new Name: ");
 scanf("%s", record.name);
 printf("Enter new Income (or press 0 to keep the same): ");
 scanf("%lf", &record.income);
 if (record.income <= 250000)
 {
 record.tax = 0;
 }
 else if (record.income > 250000 && record.income <= 500000)
 {
 record.tax = (record.income - 250000) * 0.05;
 }
 else if (record.income > 500000 && record.income <= 750000)
 {
 record.tax = 12500 + (record.income - 500000) * 0.1;
 }
 else if (record.income > 750000 && record.income <= 1000000)
 {
 record.tax = 37500 + (record.income - 750000) * 0.15;
 }
 else if (record.income > 1000000 && record.income <= 1250000)
 {
 record.tax = 75000 + (record.income - 1000000) * 0.2;
 }
 else if (record.income > 1250000 && record.income <= 1500000)
 {
 record.tax = 125000 + (record.income - 1250000) * 0.25;
 }
 else
 {
 record.tax = 187500 + (record.income - 1500000) * 0.3;
 }
 fseek(fp, -sizeof(struct taxcalculator), SEEK_CUR);
 fwrite(&record, sizeof(struct taxcalculator), 1, fp);
 printf(".You succeeded.Record edited successfully.\n");
 return;
 }
 }
 printf("Sorry, There is no record found in our file.Press 1 to add.\n");
}
void delete_record(FILE *fp)
{
 int delete_id, found = 0;
 struct taxcalculator record;
 FILE *temp_fp;
 temp_fp = fopen("temp", "w");
 if (temp_fp == NULL)
 {
 printf("file can't be created due to no entry.\n");
 return;
 }
 printf("\nEnter the ID of the person whose record you want to delete: ");
 scanf("%d", &delete_id);
 rewind(fp);
 while (fread(&record, sizeof(struct taxcalculator), 1, fp) == 1)
 {
 if (record.id == delete_id)
 {
 found = 1;
 continue;
 }
 fwrite(&record, sizeof(struct taxcalculator), 1, temp_fp);
 }
 fclose(fp);
 fclose(temp_fp);
 remove("taxcalculators");
 rename("temp", "taxcalculators");
 fp = fopen("taxcalculators", "r+");
 if (fp == NULL)
 {
 printf("Error opening file.\n");
 return;
 }
 if (found)
 {
 printf("Congrats!, Record deleted successfully.\n");
 }
 else
 {
 printf("Sorry!, Record not found,please press 5 again and enter a valid id.\n");
 }
}
int main()
{
 FILE *fp;
 fp = fopen("taxcalculators", "r+");
 if (fp == NULL)
 {
 fp = fopen("taxcalculators", "w+");
 if (fp == NULL)
 {
 printf("file can't be created due to no entry.\n");
 return 1;
 }
 }
 int choice;
 printf("WELCOME! MA'AM,ACCORDING TO THE TASK GIVEN TO US THE OUTPUT IS AS FOLLOWING.PLEASE ENTER THE NUMBER OF THE MENUS WRITTEN INFRONT OF EVERY MENU RESPECTIVELY.WE ARE GIVEN THE TASK TO MAKE INCOME TAX CALCULATOR.CHOOSE THE MODULES FROM THE MENU ");
 do
 {
 printf("\nMenu:\n");
 printf("1. Add Record\n");
 printf("2. List Records\n");
 printf("3. Search Record\n");
 printf("4. Edit Record\n");
 printf("5. Delete Record\n");
 printf("6. Exit\n");
 printf("Enter your choice: ");
 scanf("%d", &choice);
 switch (choice)
 {
 case 1:
 add(fp);
 break;
 case 2:
 list_records(fp);
 break;
 case 3:
 search_record(fp);
 break;
 case 4:
 edit_record(fp);
 break;
 case 5:
 delete_record(fp);
 break;
 case 6:
 fclose(fp);
 printf("Exiting...Hope you find my code well.THANKYOU MA'AM\n");
 break;
 default:
 printf("Sorry!, Invalid choice.Choose a valid option\n");
 break;
 }
 }
 while (choice != 6);
 return 0;
}
