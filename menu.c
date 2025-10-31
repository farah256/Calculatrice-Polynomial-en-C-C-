#include "polynomial.h"

void displayMenu() {
    printf("               ***************************\n");
    printf("                Polynomial Calculator     \n");
    printf("               ***************************\n");
    printf("1.  Input polynomial P\n");
    printf("2.  Input polynomial Q\n");
    printf("3.  Display polynomials P and Q\n");
    printf("4.  Update polynomial P\n");
    printf("5.  Update polynomial Q\n");
    printf("6.  Add P and Q\n");
    printf("7.  Subtract Q from P\n");
    printf("8.  Multiply P and Q\n");
    printf("9.  Raise P to power n\n");
    printf("10. Assign P to Q\n");
    printf("11. Calculate derivative of P\n");
    printf("12. Calculate integral of P\n");
    printf("13. Evaluate P for given X\n");
    printf("0.  Quit\n");
    printf("Enter your choice: ");
}

void runMenu(void) {
    Polynome P, Q, result;
    int choice, exponent;
    double value;

    P.head = Q.head = result.head = NULL;

    do {
        displayMenu();
        scanf("%d", &choice);
        while (getchar() != '\n'); // Clear input buffer

        switch (choice) {
            case 1:
                P = INPUT_POLYNOMIAL();
                break;
            case 2:
                Q = INPUT_POLYNOMIAL();
                break;
            case 3:
                printf("Polynomial P: ");
                DISPLAY_POLYNOMIAL(P);
                printf("Polynomial Q: ");
                DISPLAY_POLYNOMIAL(Q);
                break;
            case 4:
                UPDATE_POLYNOMIAL(&P);
                break;
            case 5:
                UPDATE_POLYNOMIAL(&Q);
                break;
            case 6:
                result = ADD_POLYNOMIALS(P, Q);
                printf("Addition result: ");
                DISPLAY_POLYNOMIAL(result);
                FREE_POLYNOMIAL(&result);
                break;
            case 7:
                result = SUBTRACT_POLYNOMIALS(P, Q);
                printf("Subtraction result: ");
                DISPLAY_POLYNOMIAL(result);
                FREE_POLYNOMIAL(&result);
                break;
            case 8:
                result = MULTIPLY_POLYNOMIALS(P, Q);
                printf("Multiplication result: ");
                DISPLAY_POLYNOMIAL(result);
                FREE_POLYNOMIAL(&result);
                break;
            case 9:
                printf("Enter power n: ");
                scanf("%d", &exponent);
                result = POWER_POLYNOMIAL(P, exponent);
                printf("Power result: ");
                DISPLAY_POLYNOMIAL(result);
                FREE_POLYNOMIAL(&result);
                break;
            case 10:
                ASSIGN_POLYNOMIAL(&Q, P);
                printf("Polynomial Q assigned successfully.\n");
                DISPLAY_POLYNOMIAL(Q);
                break;
            case 11:
                result = DERIVATIVE(P);
                printf("Derivative: ");
                DISPLAY_POLYNOMIAL(result);
                FREE_POLYNOMIAL(&result);
                break;
            case 12:
                result = INTEGRAL(P);
                printf("Integral: ");
                DISPLAY_POLYNOMIAL(result);
                FREE_POLYNOMIAL(&result);
                break;
            case 13:
                printf("Enter value of X: ");
                scanf("%lf", &value);
                printf("Evaluation result: %.2f\n", EVALUATE_POLYNOMIAL(P, value));
                break;
            case 0:
                FREE_POLYNOMIAL(&P);
                FREE_POLYNOMIAL(&Q);
                FREE_POLYNOMIAL(&result);
                printf("Program stopped.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid choice.\n");
                break;
        }

        if (choice != 0) {
            printf("\n\nOptions:\n\t[1] Menu\n\t[0] Quit\n");
            scanf("%d", &choice);
        }

    } while (choice != 0);
}