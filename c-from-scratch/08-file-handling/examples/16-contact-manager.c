#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CONTACT_FILE "contacts.dat"

struct Contact {
    int id;
    char name[50];
    char phone[15];
    char email[50];
};

int getNextId() {
    FILE *fp;
    struct Contact c;
    int maxId = 0;
    
    fp = fopen(CONTACT_FILE, "rb");
    if(fp == NULL) {
        return 1;
    }
    
    while(fread(&c, sizeof(struct Contact), 1, fp) == 1) {
        if(c.id > maxId) {
            maxId = c.id;
        }
    }
    
    fclose(fp);
    return maxId + 1;
}

void addContact() {
    FILE *fp;
    struct Contact c;
    
    fp = fopen(CONTACT_FILE, "ab");
    if(fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    
    c.id = getNextId();
    
    printf("Enter Name: ");
    getchar();
    fgets(c.name, sizeof(c.name), stdin);
    c.name[strcspn(c.name, "\n")] = 0;
    
    printf("Enter Phone: ");
    fgets(c.phone, sizeof(c.phone), stdin);
    c.phone[strcspn(c.phone, "\n")] = 0;
    
    printf("Enter Email: ");
    fgets(c.email, sizeof(c.email), stdin);
    c.email[strcspn(c.email, "\n")] = 0;
    
    fwrite(&c, sizeof(struct Contact), 1, fp);
    
    fclose(fp);
    printf("\nContact added successfully! (ID: %d)\n", c.id);
}

void viewContacts() {
    FILE *fp;
    struct Contact c;
    int count = 0;
    
    fp = fopen(CONTACT_FILE, "rb");
    if(fp == NULL) {
        printf("No contacts found\n");
        return;
    }
    
    printf("\n%-5s %-25s %-15s %-30s\n", "ID", "Name", "Phone", "Email");
    printf("=======================================================================\n");
    
    while(fread(&c, sizeof(struct Contact), 1, fp) == 1) {
        printf("%-5d %-25s %-15s %-30s\n", c.id, c.name, c.phone, c.email);
        count++;
    }
    
    printf("\nTotal contacts: %d\n", count);
    
    fclose(fp);
}

void searchContact() {
    FILE *fp;
    struct Contact c;
    char searchName[50];
    int found = 0;
    
    fp = fopen(CONTACT_FILE, "rb");
    if(fp == NULL) {
        printf("No contacts found\n");
        return;
    }
    
    printf("Enter name to search: ");
    getchar();
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;
    
    printf("\nSearch Results:\n");
    printf("%-5s %-25s %-15s %-30s\n", "ID", "Name", "Phone", "Email");
    printf("=======================================================================\n");
    
    while(fread(&c, sizeof(struct Contact), 1, fp) == 1) {
        if(strstr(c.name, searchName) != NULL) {
            printf("%-5d %-25s %-15s %-30s\n", c.id, c.name, c.phone, c.email);
            found = 1;
        }
    }
    
    if(!found) {
        printf("No matching contacts found\n");
    }
    
    fclose(fp);
}

void deleteContact() {
    FILE *fp, *temp;
    struct Contact c;
    int deleteId, found = 0;
    
    fp = fopen(CONTACT_FILE, "rb");
    if(fp == NULL) {
        printf("No contacts found\n");
        return;
    }
    
    temp = fopen("temp.dat", "wb");
    if(temp == NULL) {
        printf("Error creating temporary file\n");
        fclose(fp);
        return;
    }
    
    printf("Enter Contact ID to delete: ");
    scanf("%d", &deleteId);
    
    while(fread(&c, sizeof(struct Contact), 1, fp) == 1) {
        if(c.id == deleteId) {
            found = 1;
            printf("Contact '%s' deleted\n", c.name);
        } else {
            fwrite(&c, sizeof(struct Contact), 1, temp);
        }
    }
    
    fclose(fp);
    fclose(temp);
    
    if(found) {
        remove(CONTACT_FILE);
        rename("temp.dat", CONTACT_FILE);
    } else {
        remove("temp.dat");
        printf("Contact not found\n");
    }
}

void updateContact() {
    FILE *fp;
    struct Contact c;
    int updateId, found = 0;
    
    fp = fopen(CONTACT_FILE, "rb+");
    if(fp == NULL) {
        printf("No contacts found\n");
        return;
    }
    
    printf("Enter Contact ID to update: ");
    scanf("%d", &updateId);
    
    while(fread(&c, sizeof(struct Contact), 1, fp) == 1) {
        if(c.id == updateId) {
            found = 1;
            
            printf("\nCurrent Details:\n");
            printf("Name: %s\n", c.name);
            printf("Phone: %s\n", c.phone);
            printf("Email: %s\n", c.email);
            
            printf("\nEnter new details:\n");
            printf("Name: ");
            getchar();
            fgets(c.name, sizeof(c.name), stdin);
            c.name[strcspn(c.name, "\n")] = 0;
            
            printf("Phone: ");
            fgets(c.phone, sizeof(c.phone), stdin);
            c.phone[strcspn(c.phone, "\n")] = 0;
            
            printf("Email: ");
            fgets(c.email, sizeof(c.email), stdin);
            c.email[strcspn(c.email, "\n")] = 0;
            
            fseek(fp, -(long)sizeof(struct Contact), SEEK_CUR);
            fwrite(&c, sizeof(struct Contact), 1, fp);
            
            printf("\nContact updated successfully!\n");
            break;
        }
    }
    
    if(!found) {
        printf("Contact not found\n");
    }
    
    fclose(fp);
}

void displayMenu() {
    printf("\n===================================\n");
    printf("   CONTACT MANAGER SYSTEM\n");
    printf("===================================\n");
    printf(" 1. Add Contact\n");
    printf(" 2. View All Contacts\n");
    printf(" 3. Search Contact\n");
    printf(" 4. Update Contact\n");
    printf(" 5. Delete Contact\n");
    printf(" 6. Exit\n");
    printf("===================================\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    
    printf("\n===================================\n");
    printf("  Welcome to Contact Manager\n");
    printf("===================================\n");
    
    while(1) {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                updateContact();
                break;
            case 5:
                deleteContact();
                break;
            case 6:
                printf("\nThank you for using Contact Manager!\n");
                return 0;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }
    
    return 0;
}