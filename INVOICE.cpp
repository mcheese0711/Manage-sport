#include <stdio.h>
#include <string.h>

#define MAX_INVOICES 100
#define MAX_CUSTOMER_NAME_LENGTH 100
#define MAX_PRODUCT_ID_LENGTH 20

int customerIDs[MAX_INVOICES];
char customerNames[MAX_INVOICES][MAX_CUSTOMER_NAME_LENGTH];
char productIds[MAX_INVOICES][MAX_PRODUCT_ID_LENGTH];
int quantities[MAX_INVOICES];
double totals[MAX_INVOICES];
int numInvoices = 0;

// Functions to manage invoices
void loadInvoicesFromFile() {
    FILE *file = fopen("invoices.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    while (fscanf(file, "%d-%[^-]-%[^-]-%d-%lf\n", &customerIDs[numInvoices], customerNames[numInvoices], productIds[numInvoices], &quantities[numInvoices], &totals[numInvoices]) == 5) {
        numInvoices++;
    }
    fclose(file);
}

void saveInvoicesToFile() {
    FILE *file = fopen("invoices.txt", "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    for (int i = 0; i < numInvoices; i++) {
        fprintf(file, "%d-%s-%s-%d-%.2f\n", customerIDs[i], customerNames[i], productIds[i], quantities[i], totals[i]);
    }
    fclose(file);
}

void addInvoice() {
    if (numInvoices >= MAX_INVOICES) {
        printf("Invoice limit reached.\n");
        return;
    }

    printf("Enter customer ID: ");
    scanf("%d", &customerIDs[numInvoices]);

    printf("Enter customer name: ");
    getchar(); 
    fgets(customerNames[numInvoices], MAX_CUSTOMER_NAME_LENGTH, stdin);
    customerNames[numInvoices][strlen(customerNames[numInvoices]) - 1] = '\0'; // remove newline character

    printf("Enter product ID: ");
    fgets(productIds[numInvoices], MAX_PRODUCT_ID_LENGTH, stdin);
    productIds[numInvoices][strlen(productIds[numInvoices]) - 1] = '\0'; // remove newline character

    printf("Enter quantity: ");
    scanf("%d", &quantities[numInvoices]);

    printf("Enter total price: ");
    scanf("%lf", &totals[numInvoices]);

    numInvoices++;
    saveInvoicesToFile();
}

void printInvoices() {
    printf("Invoice List:\n");
    for (int i = 0; i < numInvoices; i++) {
        printf("Customer ID: %d, Customer Name: %s, Product ID: %s, Quantity: %d, Total: %.2f\n", customerIDs[i], customerNames[i], productIds[i], quantities[i], totals[i]);
    }
}

int main() {
    int choice;
    loadInvoicesFromFile();

    while (1) {
        printf("\nInvoice Management System\n");
        printf("1. Print invoices\n");
        printf("2. Add invoice\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printInvoices();
                break;
            case 2:
                addInvoice();
                break;
            case 3:
                printf("Thank you\n");
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}