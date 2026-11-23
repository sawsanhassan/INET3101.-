
#include <stdio.h>
#include <string.h>

#define SEATS 128
#define FLIGHTS 4

struct Seat {
    int number;
    int taken;
    char firstName[30];
    char lastName[30];
};

void saveSeats(struct Seat seats[FLIGHTS][SEATS])
{
    FILE *fp = fopen("reservations.txt", "w");

    if (fp == NULL)
    {
        printf("Error saving seats.\n");
        return;
    }

    for (int i = 0; i < FLIGHTS; i++)
    {
        for (int j = 0; j < SEATS; j++)
        {
            if (seats[i][j].taken == 1)
            {
                fprintf(fp, "%d %d %s %s\n",
                        i, seats[i][j].number,
                        seats[i][j].firstName,
                        seats[i][j].lastName);
            }
        }
    }

    fclose(fp);
}

void loadSeats(struct Seat seats[FLIGHTS][SEATS])
{
    FILE *fp = fopen("reservations.txt", "r");

    if (fp == NULL)
        return;

    int flightNum, seatNum;
    char firstName[30], lastName[30];

    while (fscanf(fp, "%d %d %29s %29s",
                  &flightNum, &seatNum,
                  firstName, lastName) == 4)
    {
        if (flightNum >= 0 && flightNum < FLIGHTS &&
            seatNum >= 1 && seatNum <= SEATS)
        {
            seats[flightNum][seatNum - 1].taken = 1;

            strcpy(seats[flightNum][seatNum - 1].firstName, firstName);
            strcpy(seats[flightNum][seatNum - 1].lastName, lastName);
        }
    }

    fclose(fp);
}

int main(void)
{
    struct Seat seats[FLIGHTS][SEATS];
    int flights[FLIGHTS] = {101, 102, 201, 202};
    char choice, pick, seatChoice;
    int i, j, flight, seat, emptySeats;

    for (i = 0; i < FLIGHTS; i++)
    {
        for (j = 0; j < SEATS; j++)
        {
            seats[i][j].number = j + 1;
            seats[i][j].taken = 0;
        }
    }

    loadSeats(seats);

    while (1)
    {
        printf("\nColossus Airlines\n");
        printf("a. Outbound Flights\n");
        printf("b. Inbound Flights\n");
        printf("c. Exit\n");
        printf("Enter choice: ");
        scanf(" %c", &choice);

        if (choice == 'c')
            break;

        if (choice != 'a' && choice != 'b')
        {
            printf("Invalid choice.\n");
            continue;
        }

        while (1)
        {
            printf("\na. Choose a flight\n");
            printf("b. Go back\n");
            printf("Enter choice: ");
            scanf(" %c", &pick);

            if (pick == 'b')
                break;

            if (pick != 'a')
            {
                printf("Invalid choice.\n");
                continue;
            }

            if (choice == 'a')
                printf("Outbound flights: 101, 102\n");
            else
                printf("Inbound flights: 201, 202\n");

            printf("Enter flight number: ");
            scanf("%d", &flight);

            int flightIndex = -1;

            for (i = 0; i < FLIGHTS; i++)
            {
                if (flights[i] == flight)
                    flightIndex = i;
            }

            if (flightIndex == -1 ||
                (choice == 'a' && flightIndex >= 2) ||
                (choice == 'b' && flightIndex < 2))
            {
                printf("Invalid flight number.\n");
                continue;
            }

            while (1)
            {
                printf("\nFlight %d Menu\n", flight);
                printf("a. Count empty seats\n");
                printf("b. Show empty seats\n");
                printf("c. Show passenger list\n");
                printf("d. Save a seat\n");
                printf("e. Cancel a seat\n");
                printf("f. Go back\n");
                printf("Enter choice: ");
                scanf(" %c", &seatChoice);

                if (seatChoice == 'f')
                    break;

                if (seatChoice == 'a')
                {
                    emptySeats = 0;

                    for (i = 0; i < SEATS; i++)
                    {
                        if (seats[flightIndex][i].taken == 0)
                            emptySeats++;
                    }

                    printf("Empty seats: %d\n", emptySeats);
                }
                else if (seatChoice == 'b')
                {
                    printf("Empty seats:\n");

                    for (i = 0; i < SEATS; i++)
                    {
                        if (seats[flightIndex][i].taken == 0)
                            printf("%d ", seats[flightIndex][i].number);
                    }

                    printf("\n");
                }
                else if (seatChoice == 'c')
                {
                    int order[SEATS];
                    int count = 0;

                    for (i = 0; i < SEATS; i++)
                    {
                        if (seats[flightIndex][i].taken == 1)
                        {
                            order[count] = i;
                            count++;
                        }
                    }

                    for (i = 0; i < count; i++)
                    {
                        for (j = i + 1; j < count; j++)
                        {
                            if (strcmp(seats[flightIndex][order[i]].lastName,
                                       seats[flightIndex][order[j]].lastName) > 0)
                            {
                                int temp = order[i];
                                order[i] = order[j];
                                order[j] = temp;
                            }
                        }
                    }

                    printf("Passenger list:\n");

                    for (i = 0; i < count; i++)
                    {
                        int s = order[i];
                        printf("Seat %d: %s %s\n",
                               seats[flightIndex][s].number,
                               seats[flightIndex][s].firstName,
                               seats[flightIndex][s].lastName);
                    }
                }
                else if (seatChoice == 'd')
                {
                    printf("Enter seat number (0 to cancel): ");
                    scanf("%d", &seat);

                    if (seat == 0)
                        continue;

                    if (seat < 1 || seat > SEATS)
                    {
                        printf("Invalid seat.\n");
                    }
                    else if (seats[flightIndex][seat - 1].taken == 1)
                    {
                        printf("Seat already taken.\n");
                    }
                    else
                    {
                        printf("Enter first name: ");
                        scanf("%29s", seats[flightIndex][seat - 1].firstName);

                        printf("Enter last name: ");
                        scanf("%29s", seats[flightIndex][seat - 1].lastName);

                        seats[flightIndex][seat - 1].taken = 1;
                        saveSeats(seats);
                        printf("Seat saved!\n");
                    }
                }
                else if (seatChoice == 'e')
                {
                    printf("Enter seat number (0 to cancel): ");
                    scanf("%d", &seat);

                    if (seat == 0)
                        continue;

                    if (seat < 1 || seat > SEATS)
                    {
                        printf("Invalid seat.\n");
                    }
                    else if (seats[flightIndex][seat - 1].taken == 0)
                    {
                        printf("Seat is already empty.\n");
                    }
                    else
                    {
                        seats[flightIndex][seat - 1].taken = 0;
                        saveSeats(seats);
                        printf("Seat canceled.\n");
                    }
                }
                else
                {
                    printf("Invalid choice.\n");
                }
            }

            break;
        }
    }

    printf("Thank you for using Colossus Airlines!\n");

    return 0;
}
