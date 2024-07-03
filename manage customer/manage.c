#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>

#define MAX_CUSTOMERS 100
#define MAX_NAME_LENGTH 100
#define MAX_ADDRESS_LENGTH 100

char name[MAX_CUSTOMERS][MAX_NAME_LENGTH];
char address[MAX_CUSTOMERS][MAX_ADDRESS_LENGTH];
int customerID[MAX_CUSTOMERS];
int  numCustomers= 0;

void loadCustomersFromFile() {
    FILE *file = fopen("customers.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    numCustomers = 0;
    while (fscanf(file, "%d-%[^-]-%[^\n]", &customerID[numCustomers], name[numCustomers], address[numCustomers]) == 3) {
        numCustomers++;
    }
    fclose(file);
}

void saveCustomersToFile() {
    FILE *file = fopen("customers.txt", "a");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    for (int i = 0; i < numCustomers; i++) {
        fprintf(file, "%d-%s-%s\n", customerID[i], name[i], address[i]);
    }
    fclose(file);
}

void addCustomer() {
    printf("Enter customer name: ");
    getchar(); // consume newline left by previous input
    fgets(name[numCustomers], MAX_NAME_LENGTH, stdin);
    name[numCustomers][strlen(name[numCustomers]) - 1] = '\0'; // remove newline character

    printf("Enter customer address: ");
    fgets(address[numCustomers], MAX_ADDRESS_LENGTH, stdin);
    address[numCustomers][strlen(address[numCustomers]) - 1] = '\0'; // remove newline character

    printf("Enter customer ID: ");
    scanf("%d", &customerID[numCustomers]);

    numCustomers++;
    saveCustomersToFile();
}

void printCustomerList() {
    printf("Customer List:\n");
    for (int i = 0; i < numCustomers; i++) {
        printf("ID: %d, Name: %s, Address: %s\n", customerID[i], name[i], address[i]);
    }
}

void findCustomer() {
    int id;
    printf("Enter customer ID to find: ");
    scanf("%d", &id);

    for (int i = 0; i < numCustomers; i++) {
        if (customerID[i] == id) {
            printf("Customer found: ID: %d, Name: %s, Address: %s\n", customerID[i], name[i], address[i]);
            return;
        }
    }

    printf("Customer not found\n");
}

void editCustomer() {
    int id;
    printf("Enter customer ID to edit: ");
    scanf("%d", &id);

    for (int i = 0; i < numCustomers; i++) {
        if (customerID[i] == id) {
        	getchar();
            printf("Enter new customer name: ");
            fgets(name[i], MAX_NAME_LENGTH, stdin);
            name[i][strlen(name[i]) - 1] = '\0'; // remove newline character

            printf("Enter new customer address: ");
            fgets(address[i], MAX_ADDRESS_LENGTH, stdin);
            address[i][strlen(address[i]) - 1] = '\0'; // remove newline character

            saveCustomersToFile();
            printf("Customer updated successfully\n");
            return;
        }
    }

    printf("Customer not found\n");
}

void deleteCustomer() {
    int id;
    printf("Enter customer ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < numCustomers; i++) {
        if (customerID[i] == id) {
            for (int j = i; j < numCustomers - 1; j++) {
                customerID[j] = customerID[j + 1];
                strcpy(name[j], name[j + 1]);
                strcpy(address[j], address[j + 1]);
            }
            numCustomers--;
            saveCustomersToFile();
            printf("Customer deleted successfully\n");
            return;
        }
    }

    printf("Customer not found\n");
}

int main() {
    loadCustomersFromFile();
    printf("%d",numCustomers);
    int choice;

    while (1) {
        printf("Customer Management System\n");
        printf("1. Add customer\n");
        printf("2. Print customer list\n");
        printf("3. Find customer\n");
        printf("4. Edit customer\n");
        printf("5. Delete customer\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCustomer();
                break;
            case 2:
                printCustomerList();
                break;
            case 3:
                findCustomer();
                break;
            case 4:
                editCustomer();
                break;
            case 5:
            	deleteCustomer();
                break;
            case 6:
			 	printf("thank you");
				 break;
		}
	}
		return 0;
	}