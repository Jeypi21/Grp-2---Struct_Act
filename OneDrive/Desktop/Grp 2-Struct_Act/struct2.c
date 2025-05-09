#include <stdio.h>
#include <string.h>

#define ROWS 5
#define COLUMNS 4

// Define a structure for a seat
struct Seat {
    int row;
    char letter;
    int isAssigned; // 0 = available, 1 = taken
};

void initializeSeats(struct Seat seats[ROWS][COLUMNS]);

void displaySeats(struct Seat seats[ROWS][COLUMNS]);

int allSeatsAssigned(struct Seat seats[ROWS][COLUMNS]);

int main() {
    struct Seat seats[ROWS][COLUMNS];
    char input[4], letter;
    int rowIndex, colIndex, row;
    
    initializeSeats(seats);

    printf("Welcome to the Airplane Seat Reservation System!\n");

    while (!allSeatsAssigned(seats)) {
        displaySeats(seats);
        printf("\nEnter a seat (e.g., 2B) or type Q to quit: ");
        scanf("%s", input);

        if (input[0] == 'Q' || input[0] == 'q') {
            printf("Exiting program.\n");
            break;
        }

        // Parse the seat input
        if (sscanf(input, "%d%c", &row, &letter) != 2 || row < 1 || row > ROWS || letter < 'A' || letter > 'D') {
            printf("Invalid seat input. Please try again.\n");
            continue;
        }

        rowIndex = row - 1;
        colIndex = letter - 'A';

        if (seats[rowIndex][colIndex].isAssigned) {
            printf("Seat %d%c is already occupied. Please choose another.\n", row, letter);
        } else {
            seats[rowIndex][colIndex].isAssigned = 1;
            printf("Seat %d%c assigned successfully.\n", row, letter);
        }
    }

    if (allSeatsAssigned(seats)) {
        printf("\nAll seats are now occupied. Thank you!\n");
        displaySeats(seats);
    }

    return 0;
}

// Function to initialize seats  
void initializeSeats(struct Seat seats[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            seats[i][j].row = i + 1;
            seats[i][j].letter = 'A' + j;
            seats[i][j].isAssigned = 0;
        }
    }
}

// Function to display current seat map
void displaySeats(struct Seat seats[ROWS][COLUMNS]) {
    printf("\nCurrent Seat Map:\n\n");
    for (int i = 0; i < ROWS; ++i) {
        printf("%d\t", i + 1);
        for (int j = 0; j < COLUMNS; ++j) {
            if (seats[i][j].isAssigned)
                printf("X\t");
            else
                printf("%c\t", seats[i][j].letter);
        }
        printf("\n");
    }
}

// Function to check if all seats are assigned
int allSeatsAssigned(struct Seat seats[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < COLUMNS; ++j)
            if (!seats[i][j].isAssigned)
                return 0; // Found one available
    return 1; // All are assigned
}