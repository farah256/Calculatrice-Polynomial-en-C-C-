#include "polynomial.h"

// Search for character in string
int searchChar(char c, char* str) {
    if (*str == '\0') return 0;
    if (*str == c) return 1;
    return searchChar(c, str + 1);
}

// Add monomial to polynomial
void addMonomial(Monome* monome, Polynome* P) {
    if (P->head == NULL) {
        P->head = monome;
    } else {
        Monome* temp = P->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = monome;
    }
}

// Input polynomial from user
Polynome INPUT_POLYNOMIAL(void) {
    char input[MAX_INPUT];
    int exp, num, den;
    Polynome poly;
    poly.head = NULL;

    printf("Enter polynomial (Example: X^3+7/2X+11): ");
    fgets(input, MAX_INPUT, stdin);

    // Remove newline character
    if (input[strlen(input) - 1] == '\n') {
        input[strlen(input) - 1] = '\0';
    }

    // Skip "P=" if present
    char* start = input;
    if (strlen(input) >= 2 && input[1] == '=') {
        start = input + 2;
    }

    char* delimiter = "+";
    char* token = strtok(start, delimiter);

    while (token != NULL) {
        Monome* monome = (Monome*)malloc(sizeof(Monome));
        monome->next = NULL;

        // Parse different formats
        if (searchChar('/', token) && searchChar('X', token) && searchChar('^', token)) {
            sscanf(token, "%d/%dX^%d", &num, &den, &exp);
            monome->coefficient.numerator = num;
            monome->coefficient.denominator = den;
            monome->exponent = exp;
        } else if (searchChar('/', token) && searchChar('X', token) && (!searchChar('^', token))) {
            sscanf(token, "%d/%dX", &num, &den);
            monome->coefficient.numerator = num;
            monome->coefficient.denominator = den;
            monome->exponent = 1;
        } else if (searchChar('/', token) && (!searchChar('X', token)) && (!searchChar('^', token))) {
            sscanf(token, "%d/%d", &num, &den);
            monome->coefficient.numerator = num;
            monome->coefficient.denominator = den;
            monome->exponent = 0;
        } else if ((!searchChar('/', token)) && (!searchChar('X', token)) && (!searchChar('^', token))) {
            sscanf(token, "%d", &num);
            monome->coefficient.numerator = num;
            monome->coefficient.denominator = 1;
            monome->exponent = 0;
        } else if ((!searchChar('/', token)) && (searchChar('X', token)) && (searchChar('^', token))) {
            if (sscanf(token, "%dX^%d", &num, &exp)) {
                monome->coefficient.numerator = num;
                monome->coefficient.denominator = 1;
                monome->exponent = exp;
            } else if (sscanf(token, "X^%d", &exp)) {
                monome->coefficient.numerator = 1;
                monome->coefficient.denominator = 1;
                monome->exponent = exp;
            }
        } else if ((!searchChar('/', token)) && (searchChar('X', token)) && (!searchChar('^', token))) {
            if (sscanf(token, "%dX", &num)) {
                monome->coefficient.numerator = num;
                monome->coefficient.denominator = 1;
                monome->exponent = 1;
            } else if (strcmp(token, "X") == 0) {
                monome->coefficient.numerator = 1;
                monome->coefficient.denominator = 1;
                monome->exponent = 1;
            }
        }
        
        addMonomial(monome, &poly);
        token = strtok(NULL, delimiter);
    }

    printf("Polynomial added successfully.\n");
    return poly;
}

// Update polynomial
void UPDATE_POLYNOMIAL(Polynome* P) {
    FREE_POLYNOMIAL(P);
    *P = INPUT_POLYNOMIAL();
    printf("Polynomial updated successfully.\n");
}

// Display polynomial
void DISPLAY_POLYNOMIAL(Polynome P) {
    Monome* monome = P.head;
    int firstTerm = 1;

    while (monome != NULL) {
        // Handle sign for non-first terms
        if (!firstTerm && monome->coefficient.numerator > 0) {
            printf("+");
        }
        firstTerm = 0;

        // Display coefficient
        if (monome->coefficient.denominator == 1) {
            if (monome->coefficient.numerator != 1 || monome->exponent == 0) {
                printf("%d", monome->coefficient.numerator);
            }
        } else {
            printf("%d/%d", monome->coefficient.numerator, monome->coefficient.denominator);
        }

        // Display variable and exponent
        if (monome->exponent > 0) {
            printf("X");
            if (monome->exponent > 1) {
                printf("^%d", monome->exponent);
            }
        }

        monome = monome->next;
    }
    
    if (firstTerm) {
        printf("0");
    }
    printf("\n");
}

// Add two polynomials
Polynome ADD_POLYNOMIALS(Polynome P, Polynome Q) {
    Polynome result;
    result.head = NULL;

    Monome *monome1 = P.head;
    Monome *monome2 = Q.head;
    Monome *lastMonome = NULL;

    while (monome1 != NULL || monome2 != NULL) {
        Monome *newMonome = (Monome *)malloc(sizeof(Monome));
        newMonome->next = NULL;

        if (monome1 != NULL && monome2 != NULL) {
            if (monome1->exponent == monome2->exponent) {
                newMonome->coefficient.numerator = 
                    (monome1->coefficient.numerator * monome2->coefficient.denominator) + 
                    (monome2->coefficient.numerator * monome1->coefficient.denominator);
                newMonome->coefficient.denominator = 
                    monome1->coefficient.denominator * monome2->coefficient.denominator;
                newMonome->exponent = monome1->exponent;
                monome1 = monome1->next;
                monome2 = monome2->next;
            } else if (monome1->exponent > monome2->exponent) {
                *newMonome = *monome1;
                monome1 = monome1->next;
            } else {
                *newMonome = *monome2;
                monome2 = monome2->next;
            }
        } else if (monome1 != NULL) {
            *newMonome = *monome1;
            monome1 = monome1->next;
        } else {
            *newMonome = *monome2;
            monome2 = monome2->next;
        }

        if (result.head == NULL) {
            result.head = newMonome;
        } else {
            lastMonome->next = newMonome;
        }
        lastMonome = newMonome;
    }

    return result;
}

// Subtract two polynomials
Polynome SUBTRACT_POLYNOMIALS(Polynome P, Polynome Q) {
    Polynome result;
    result.head = NULL;

    Monome *monome1 = P.head;
    Monome *monome2 = Q.head;
    Monome *lastMonome = NULL;

    while (monome1 != NULL || monome2 != NULL) {
        Monome *newMonome = (Monome *)malloc(sizeof(Monome));
        newMonome->next = NULL;

        if (monome1 != NULL && monome2 != NULL) {
            if (monome1->exponent == monome2->exponent) {
                newMonome->coefficient.numerator = 
                    (monome1->coefficient.numerator * monome2->coefficient.denominator) - 
                    (monome2->coefficient.numerator * monome1->coefficient.denominator);
                newMonome->coefficient.denominator = 
                    monome1->coefficient.denominator * monome2->coefficient.denominator;
                newMonome->exponent = monome1->exponent;
                monome1 = monome1->next;
                monome2 = monome2->next;
            } else if (monome1->exponent > monome2->exponent) {
                *newMonome = *monome1;
                monome1 = monome1->next;
            } else {
                *newMonome = *monome2;
                newMonome->coefficient.numerator *= -1;
                monome2 = monome2->next;
            }
        } else if (monome1 != NULL) {
            *newMonome = *monome1;
            monome1 = monome1->next;
        } else {
            *newMonome = *monome2;
            newMonome->coefficient.numerator *= -1;
            monome2 = monome2->next;
        }

        if (result.head == NULL) {
            result.head = newMonome;
        } else {
            lastMonome->next = newMonome;
        }
        lastMonome = newMonome;
    }

    return result;
}

// Multiply two polynomials - CORRECTED VERSION
Polynome MULTIPLY_POLYNOMIALS(Polynome P, Polynome Q) {
    Polynome result;
    result.head = NULL;
    
    if (P.head == NULL || Q.head == NULL) {
        return result;
    }
    
    Monome* monome1 = P.head;
    
    while (monome1 != NULL) {
        Monome* monome2 = Q.head;
        
        while (monome2 != NULL) {
            // Create new monomial for the product
            Monome* newMonome = (Monome*)malloc(sizeof(Monome));
            if (newMonome == NULL) {
                printf("Memory allocation failed!\n");
                FREE_POLYNOMIAL(&result);
                result.head = NULL;
                return result;
            }
            
            // Calculate product
            newMonome->coefficient.numerator = monome1->coefficient.numerator * monome2->coefficient.numerator;
            newMonome->coefficient.denominator = monome1->coefficient.denominator * monome2->coefficient.denominator;
            newMonome->exponent = monome1->exponent + monome2->exponent;
            newMonome->next = NULL;
            
            // Add to result, combining like terms
            if (result.head == NULL) {
                result.head = newMonome;
            } else {
                // Check if we already have a term with this exponent
                Monome* current = result.head;
                Monome* prev = NULL;
                int found = 0;
                
                while (current != NULL) {
                    if (current->exponent == newMonome->exponent) {
                        // Combine coefficients
                        int num1 = current->coefficient.numerator * newMonome->coefficient.denominator;
                        int num2 = newMonome->coefficient.numerator * current->coefficient.denominator;
                        current->coefficient.numerator = num1 + num2;
                        current->coefficient.denominator = current->coefficient.denominator * newMonome->coefficient.denominator;
                        free(newMonome);
                        found = 1;
                        break;
                    }
                    prev = current;
                    current = current->next;
                }
                
                if (!found) {
                    // Insert in sorted order (highest exponent first)
                    current = result.head;
                    prev = NULL;
                    
                    while (current != NULL && current->exponent > newMonome->exponent) {
                        prev = current;
                        current = current->next;
                    }
                    
                    if (prev == NULL) {
                        // Insert at beginning
                        newMonome->next = result.head;
                        result.head = newMonome;
                    } else {
                        // Insert in middle or end
                        newMonome->next = current;
                        prev->next = newMonome;
                    }
                }
            }
            
            monome2 = monome2->next;
        }
        monome1 = monome1->next;
    }
    
    return result;
}
// Power of polynomial - SAFE VERSION
Polynome POWER_POLYNOMIAL(Polynome P, int n) {
    Polynome result;
    result.head = NULL;
    
    if (n < 0) {
        printf("Error: Negative powers not supported.\n");
        return result;
    }
    
    if (n == 0) {
        // Return constant polynomial 1
        Monome* constant = (Monome*)malloc(sizeof(Monome));
        if (constant == NULL) {
            printf("Memory allocation failed!\n");
            return result;
        }
        constant->coefficient.numerator = 1;
        constant->coefficient.denominator = 1;
        constant->exponent = 0;
        constant->next = NULL;
        result.head = constant;
        return result;
    }
    
    if (n == 1) {
        // Return a copy of P
        ASSIGN_POLYNOMIAL(&result, P);
        return result;
    }
    
    // Start with P
    ASSIGN_POLYNOMIAL(&result, P);
    
    // Multiply by P (n-1) times
    for (int i = 1; i < n; i++) {
        Polynome temp = MULTIPLY_POLYNOMIALS(result, P);
        FREE_POLYNOMIAL(&result);
        result = temp;
    }
    
    return result;
}
// Assign polynomial
void ASSIGN_POLYNOMIAL(Polynome* dest, Polynome src) {
    FREE_POLYNOMIAL(dest);
    
    Monome* srcMonome = src.head;
    while (srcMonome != NULL) {
        Monome* newMonome = (Monome*)malloc(sizeof(Monome));
        newMonome->coefficient = srcMonome->coefficient;
        newMonome->exponent = srcMonome->exponent;
        newMonome->next = NULL;

        addMonomial(newMonome, dest);
        srcMonome = srcMonome->next;
    }
}

// Derivative of polynomial
Polynome DERIVATIVE(Polynome P) {
    Polynome result;
    result.head = NULL;

    Monome *monome = P.head;

    while (monome != NULL) {
        if (monome->exponent > 0) {
            Monome *newMonome = (Monome *)malloc(sizeof(Monome));
            newMonome->next = NULL;

            newMonome->coefficient.numerator = monome->coefficient.numerator * monome->exponent;
            newMonome->coefficient.denominator = monome->coefficient.denominator;
            newMonome->exponent = monome->exponent - 1;

            addMonomial(newMonome, &result);
        }
        monome = monome->next;
    }

    return result;
}

// Integral of polynomial
Polynome INTEGRAL(Polynome P) {
    Polynome result;
    result.head = NULL;

    Monome *monome = P.head;

    while (monome != NULL) {
        Monome *newMonome = (Monome *)malloc(sizeof(Monome));
        newMonome->next = NULL;

        newMonome->coefficient.numerator = monome->coefficient.numerator;
        newMonome->coefficient.denominator = monome->coefficient.denominator * (monome->exponent + 1);
        newMonome->exponent = monome->exponent + 1;

        addMonomial(newMonome, &result);
        monome = monome->next;
    }

    return result;
}

// Evaluate polynomial at x
double EVALUATE_POLYNOMIAL(Polynome P, double x) {
    double result = 0.0;
    Monome *monome = P.head;

    while (monome != NULL) {
        double term = (double)monome->coefficient.numerator / monome->coefficient.denominator;
        term *= pow(x, monome->exponent);
        result += term;
        monome = monome->next;
    }
    
    return result;
}

// Free polynomial memory
void FREE_POLYNOMIAL(Polynome* P) {
    Monome* current = P->head;
    while (current != NULL) {
        Monome* next = current->next;
        free(current);
        current = next;
    }
    P->head = NULL;
}