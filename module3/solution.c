
#include <stdio.h>
#include <string.h>

#define SEATS 128
#define FLIGHTS 4

struct Seat {
    int number;
    int assigned;
    char first[30];
    char last[30];
};

int main(void)
{
    struct Seat seats[FLIGHTS][SEATS];
    int flights[FLIGHTS] = {101, 102, 201, 202};
    char choice, option, action;
    int i, j, flight, seat, empty;

    for (i = 0; i < FLIGHTS; i++)
    {
        for (j = 0; j < SEATS; j++)
        {
            seats[i][j].number = j + 1;
            seats[i][j].assigned = 0;
        }
    }

    while (1)
    {
        printf("\nColossus Airlines\n");
        printf("a. Outbound Flight\n");
        printf("b. Inbound Flight\n");
        printf("c. Quit\n");
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
            printf("\na. Flight Number\n");
            printf("b. Back to Main\n");
            printf("Enter choice: ");
            scanf(" %c", &option);

            if (option == 'b')
                break;

            if (option != 'a')
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

            int index = -1;

            for (i = 0; i < FLIGHTS; i++)
            {
                if (flights[i] == flight)
                    index = i;
            }

            if (index == -1 ||
                (choice == 'a' && index >= 2) ||
                (choice == 'b' && index < 2))
            {
                printf("Invalid flight number.\n");
                continue;
            }

            while (1)
            {
                printf("\nFlight %d Menu\n", flight);
                printf("a. Show number of empty seats\n");
                printf("b. Show list of empty seats\n");
                printf("c. Show alphabetical list of seats\n");
                printf("d. Assign a customer to a seat\n");
                printf("e. Delete a seat assignment\n");
                printf("f. Return to Main menu\n");
                printf("Enter choice: ");
                scanf(" %c", &action);

                if (action == 'f')
                    break;

                if (action == 'a')
                {
                    empty = 0;

                    for (i = 0; i < SEATS; i++)
                    {
                        if (seats[index][i].assigned == 0)
                            empty++;
                    }

                    printf("Empty seats: %d\n", empty);
                }
                else if (action == 'b')
                {
                    printf("Empty seats:\n");

                    for (i = 0; i < SEATS; i++)
                    {
                        if (seats[index][i].assigned == 0)
                            printf("%d ", seats[index][i].number);
                    }

                    printf("\n");
                }
                else if (action == 'c')
                {
                    int order[SEATS];
                    int count = 0;

                    for (i = 0; i < SEATS; i++)
                    {
                        if (seats[index][i].assigned == 1)
                        {
                            order[count] = i;
                            count++;
                        }
                    }

                    for (i = 0; i < count; i++)
                    {
                        for (j = i + 1; j < count; j++)
                        {
                            if (strcmp(seats[index][order[i]].last,
                                       seats[index][order[j]].last) > 0)
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
                               seats[index][s].number,
                               seats[index][s].first,
                               seats[index][s].last);
                    }
                }
                else if (action == 'd')
                {
                    printf("Enter seat number (0 to cancel): ");
                    scanf("%d", &seat);

                    if (seat == 0)
                        continue;

                    if (seat < 1 || seat > SEATS)
                    {
                        printf("Invalid seat.\n");
                    }
                    else if (seats[index][seat - 1].assigned == 1)
                    {
                        printf("Seat already taken.\n");
                    }
                    else
                    {
                        printf("Enter first name: ");
                        scanf("%29s", seats[index][seat - 1].first);

                        printf("Enter last name: ");
                        scanf("%29s", seats[index][seat - 1].last);

                        seats[index][seat - 1].assigned = 1;
                        printf("Seat reserved!\n");
                    }
                }
                else if (action == 'e')
                {
                    printf("Enter seat number (0 to cancel): ");
                    scanf("%d", &seat);

                    if (seat == 0)
                        continue;

                    if (seat < 1 || seat > SEATS)
                    {
                        printf("Invalid seat.\n");
                    }
                    else if (seats[index][seat - 1].assigned == 0)
                    {
                        printf("Seat is already empty.\n");
                    }
                    else
                    {
                        seats[index][seat - 1].assigned = 0;
                        printf("Reservation deleted.\n");
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
