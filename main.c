// Default Admin Login Credentials
// Username: admin
// Password: 1234
// User data only stored in the text file. First you have to create any user to login as a user. User records will be stored automatically in text file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a user account
struct User
{
	char username[50];
	char password[50];
	char phone[15];
	float balance;
	char fullname[100];	// Add full name
	int accountNumber;	// Add account number
};

// Function prototypes

// Admin Functions
void adminLogin(); // Log in as an admin
void createAccount(); // Create a user account as an admin
void searchAccount(); // Search for an account from admin panel
void editAccountAdmin(); // Edit any user's account from admin panel
void showAllAccounts(); // Display the list of all user accounts in admin panel
void deleteAccount(); // Delete any user's account from admin panel
void deposit(char *username); // Deposit money (admin or user)
void withdraw(char *username); // Withdraw money (admin or user)
void transferMoneyAdmin(); // Transfer money as an admin from one user account to another

// Note: Admins don't have individual money accounts. They can only manage other user's accounts.

void checkBalanceAdmin(); // Check a user account's balance as an admin

// User Functions
void userLogin(); // Log in to the user panel
void userMenu(char *username); // Display the menu in the user panel
void editAccount(); // Edit user's own account from user panel
void transferMoney(char *senderUsername); // Transfer money as a user from own account to another user's account
void checkBalance(char *username); // Check user's own account balance
void createUserAccount(); // Create a user account from the homepage

// File Operations
void readUserDataFromFile(); // Read records from the text file database
void writeUserDataToFile(); // Write records to the text file database

// Utility
void redirect(); // Redirect to the main menu after completing a task



// Array to store user accounts
struct User userAccounts[100];
int totalAccounts = 0;
char title[] = "E-Banking: Online Banking System\n--------------------------------\n";

int main()
{
	// Loads user data from file
	readUserDataFromFile();
	int choice;

	printf("%s\n", title);
	printf("Welcome to E-Banking.\n\n");

	printf("1. Login as admin.\n");
	printf("2. Login as user.\n");
	printf("3. Create user account.\n");
	printf("4. Exit.\n");

	printf("Enter your choice: ");
	scanf("%d", &choice);
	printf("\n");

	switch (choice)
	{
		case 1:
			adminLogin();
			break;
		case 2:
			userLogin();
			break;
		case 3:
			createUserAccount();
			break;
		case 4:
			printf("Exiting Program...\nThank you for using E-Banking.\n");
			return 0;
		default:
			printf("Invalid choice. Please try again.\n");
	}

	return 0;
}




void adminLogin()
{
	char username[50];
	char password[50];

	printf("%s\n", title);
	printf("Enter Admin Username: ");
	scanf("%s", username);
	printf("Enter Password: ");
	scanf("%s", password);

	// Admin authentication logic
	if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0)
	{
		printf("Login Successful!\n");

		// Displays admin menu
		int adminChoice;
		while (1)
		{
			printf("\nAdmin Menu:\n");
			printf("1. Create an account\n");
			printf("2. Search account by username\n");
			printf("3. Edit account\n");
			printf("4. Show all accounts\n");
			printf("5. Delete an account\n");
			printf("6. Deposit\n");
			printf("7. Withdraw\n");
			printf("8. Transfer money\n");
			printf("9. Check balance\n");
			printf("10. Logout\n");
			printf("Enter your choice: ");
			scanf("%d", &adminChoice);
			printf("\n");

			switch (adminChoice)
			{
				case 1:
				    printf("%s\n", title);
					createAccount();
					break;
				case 2:
				    printf("%s\n", title);
					searchAccount();
					break;
				case 3:
				    printf("%s\n", title);
					editAccountAdmin();
					break;
				case 4:
				    printf("%s\n", title);
					showAllAccounts();
					break;
				case 5:
				    printf("%s\n", title);
					deleteAccount();
					break;
				case 6:
				    printf("%s\n", title);
					{
						char depositUsername[50];
						printf("Enter the username to deposit: ");
						scanf("%s", depositUsername);
						deposit(depositUsername);
						break;
					}

				case 7:
				    printf("%s\n", title);
					{
						char withdrawUsername[50];
						printf("Enter the username to withdraw: ");
						scanf("%s", withdrawUsername);
						withdraw(withdrawUsername);
						break;
					}

				case 8:
				    printf("%s\n", title);
					transferMoneyAdmin("");
					break;
				case 9:
				    printf("%s\n", title);
					checkBalanceAdmin("");
					break;
				case 10:
				    printf("%s\n", title);
					printf("Successfully logged out.\n\n");

					return redirect();
				default:
					printf("Invalid choice. Please try again.\n");
			}
		}
	}
	else
	{
		printf("Login Failed. Invalid credentials.\n");
		printf("\n");
        return redirect();
	}
}





void createAccount()
{
	if (totalAccounts < 100)
	{

		// Clears the input buffer
		int c;
		while ((c = getchar()) != '\n' && c != EOF);

		printf("Enter Full Name: ");
		fgets(userAccounts[totalAccounts].fullname, sizeof(userAccounts[totalAccounts].fullname), stdin);
		userAccounts[totalAccounts].fullname[strcspn(userAccounts[totalAccounts].fullname, "\n")] = 0;	// Removes trailing newline

		printf("Enter Username: ");
		scanf("%s", userAccounts[totalAccounts].username);
		printf("Enter Password: ");
		scanf("%s", userAccounts[totalAccounts].password);

        printf("Enter Phone Number: ");
        scanf("%s", userAccounts[totalAccounts].phone);

		printf("Enter Initial Balance: ");
		scanf("%f", &userAccounts[totalAccounts].balance);

		// Generates unique account number
		userAccounts[totalAccounts].accountNumber = totalAccounts + 1001;	// Assuming starting account number is 1001
		totalAccounts++;
		writeUserDataToFile();	// Updates file after successful creation
		printf("Account created successfully!\n");
	}
	else
	{
		printf("Maximum account limit reached. Cannot create more accounts.\n");
	}
}





void searchAccount()
{
	// Account search logic
	char searchUsername[50];
	printf("Enter the username to search: ");
	scanf("%s", searchUsername);

	int i;
	for (i = 0; i < totalAccounts; i++)
	{
		if (strcmp(searchUsername, userAccounts[i].username) == 0)
		{
			printf("Account Found:\n");
			printf("Full Name: %s\n", userAccounts[i].fullname);
			printf("Username: %s\n", userAccounts[i].username);
			printf("Account Number: %d\n", userAccounts[i].accountNumber);
			printf("Balance: $%.2f\n", userAccounts[i].balance);
			return;
		}
	}

	printf("Account not found.\n");
}




void editAccountAdmin()
{
	// Account editing logic
	char editUsername[50];
	printf("Enter the username to edit: ");
	scanf("%s", editUsername);

	int i;
	for (i = 0; i < totalAccounts; i++)
	{
		if (strcmp(editUsername, userAccounts[i].username) == 0)
		{
			printf("Enter new password: ");
			scanf("%s", userAccounts[i].password);
			printf("Account edited successfully.\n");
			writeUserDataToFile();
			return;
		}
	}

	printf("Account not found.\n");
}




void showAllAccounts()
{
	// Displays all user accounts
	if (totalAccounts == 0)
	{
		printf("No accounts found.\n");
		return;
	}

	printf("All User Accounts:\n");
	printf("------------------\n");
	for (int i = 0; i < totalAccounts; i++)
	{
		printf("\nAccount %d:\n", i + 1);
		printf("----------\n");
		printf("Full Name: %s\n", userAccounts[i].fullname);
		printf("Username: %s\n", userAccounts[i].username);
		printf("Account Number: %d\n", userAccounts[i].accountNumber);
		printf("Phone Number: %s\n", userAccounts[i].phone);
		printf("Balance: $%.2f\n", userAccounts[i].balance);
	}
}





void deleteAccount()
{
	// Account deletion logic
	char deleteUsername[50];
	printf("Enter the username to delete: ");
	scanf("%s", deleteUsername);

	int i;
	for (i = 0; i < totalAccounts; i++)
	{
		if (strcmp(deleteUsername, userAccounts[i].username) == 0)
		{
			// Moves the last account to the position of the deleted account
			userAccounts[i] = userAccounts[totalAccounts - 1];
			totalAccounts--;
			printf("Account deleted successfully.\n");
			writeUserDataToFile();	// Updates file after successful deletion
			return;
		}
	}

	printf("Account not found.\n");
}





void deposit(char *username)
{
	// Deposit logic
	int i;
	for (i = 0; i < totalAccounts; i++)
	{
		if (strcmp(username, userAccounts[i].username) == 0)
		{
			float amount;
			printf("Enter the amount to deposit: ");
			scanf("%f", &amount);
			userAccounts[i].balance += amount;
			printf("Deposit successful. New balance: $%.2f\n", userAccounts[i].balance);

			// Writes updated user data to file
			writeUserDataToFile();

			return;
		}
	}

	printf("Account not found.\n");
}




void withdraw(char *username)
{
	// Withdrawal logic
	int i;
	for (i = 0; i < totalAccounts; i++)
	{
		if (strcmp(username, userAccounts[i].username) == 0)
		{
			float amount;
			printf("Enter the amount to withdraw: ");
			scanf("%f", &amount);
			if (amount <= userAccounts[i].balance)
			{
				userAccounts[i].balance -= amount;
				printf("Withdrawal successful. New balance: $%.2f\n", userAccounts[i].balance);
				writeUserDataToFile();	// Updates file after successful withdrawal
			}
			else
			{
				printf("Insufficient balance.\n");
			}

			return;
		}
	}

	printf("Account not found.\n");
}




void transferMoneyAdmin()
{
	// Money transfer logic
	char senderUsername[50];
	char receiverUsername[50];
	float amount;
	printf("Enter sender's username: ");
	scanf("%s", senderUsername);
	printf("Enter receiver's username: ");
	scanf("%s", receiverUsername);
	printf("Enter the amount to transfer: ");
	scanf("%f", &amount);

	int senderIndex = -1;
	int receiverIndex = -1;

	for (int i = 0; i < totalAccounts; i++)
	{
		if (strcmp(senderUsername, userAccounts[i].username) == 0)
		{
			senderIndex = i;
		}

		if (strcmp(receiverUsername, userAccounts[i].username) == 0)
		{
			receiverIndex = i;
		}
	}

	if (senderIndex != -1 && receiverIndex != -1)
	{
		if (amount <= userAccounts[senderIndex].balance)
		{
			userAccounts[senderIndex].balance -= amount;
			userAccounts[receiverIndex].balance += amount;
			printf("Transfer successful. New balance for %s: $%.2f\n", senderUsername, userAccounts[senderIndex].balance);
			printf("New balance for %s: $%.2f\n", receiverUsername, userAccounts[receiverIndex].balance);

			// Writes updated user data to file
			writeUserDataToFile();
		}
		else
		{
			printf("Sender has insufficient balance.\n");
		}
	}
	else
	{
		printf("One or both users not found.\n");
	}
}




void checkBalanceAdmin()
{
	// Balance check logic
	char checkUsername[50];
	printf("Enter the username to check balance: ");
	scanf("%s", checkUsername);

	int i;
	for (i = 0; i < totalAccounts; i++)
	{
		if (strcmp(checkUsername, userAccounts[i].username) == 0)
		{
			printf("Balance for %s: $%.2f\n", checkUsername, userAccounts[i].balance);
			return;
		}
	}

	printf("Account not found.\n");
}




void userLogin()
{
	// User login logic
	char username[50];
	char password[50];

	printf("%s\n", title);
	printf("Enter Username: ");
	scanf("%s", username);
	printf("Enter Password: ");
	scanf("%s", password);

	int i;
	for (i = 0; i < totalAccounts; i++)
	{
		if (strcmp(username, userAccounts[i].username) == 0 && strcmp(password, userAccounts[i].password) == 0)
		{
			printf("Login Successful!\n");

			// Displays user menu
			userMenu(username);

			return;
		}
	}

	printf("Login Failed. Invalid credentials.\n");
	printf("\n");
	return redirect();
}




void userMenu(char *username)
{
	int userChoice;

	while (1)
	{
		printf("\nUser Menu:\n");
		printf("1. Edit account details\n");
		printf("2. Deposit\n");
		printf("3. Withdraw\n");
		printf("4. Transfer money\n");
		printf("5. Check balance\n");
		printf("6. Logout\n");
		printf("Enter your choice: ");
		scanf("%d", &userChoice);
		printf("\n");

		switch (userChoice)
		{
			case 1:
			    printf("%s\n", title);
				editAccount(username);
				break;
			case 2:
			    printf("%s\n", title);
				deposit(username);
				break;
			case 3:
			    printf("%s\n", title);
				withdraw(username);
				break;
			case 4:
			    printf("%s\n", title);
				transferMoney(username);
				break;
			case 5:
			    printf("%s\n", title);
				checkBalance(username);
				break;
			case 6:
			    printf("%s\n", title);
				printf("Successfully logged out.\n\n");
				return redirect();
			default:
				printf("Invalid choice. Please try again.\n");
		}
	}
}




void editAccount(char *loggedInUsername)
{
	char editUsername[50];
	printf("Enter your username again to verify that you are not a robot: ");
	scanf("%s", editUsername);

	int i;
	for (i = 0; i < totalAccounts; i++)
	{
		if (strcmp(editUsername, userAccounts[i].username) == 0)
		{
			// Checks if the logged-in user is an admin or if they're trying to edit their own account
			if (strcmp(loggedInUsername, "admin") == 0 || strcmp(loggedInUsername, userAccounts[i].username) == 0)
			{
				printf("Enter new password: ");
				scanf("%s", userAccounts[i].password);
				printf("Account edited successfully.\n");
				writeUserDataToFile();
				return;
			}
			else
			{
				printf("It's not your account. You cannot edit others account\n");
				return;
			}
		}
	}

	printf("Account not found.\n");
}




void transferMoney(char *senderUsername)
{
	// Money transfer logic for user account
	char receiverUsername[50];
	float amount;
	printf("Enter receiver's username: ");
	scanf("%s", receiverUsername);
	printf("Enter the amount to transfer: ");
	scanf("%f", &amount);

	int senderIndex = -1;
	int receiverIndex = -1;

	for (int i = 0; i < totalAccounts; i++)
	{
		if (strcmp(senderUsername, userAccounts[i].username) == 0)
		{
			senderIndex = i;
		}

		if (strcmp(receiverUsername, userAccounts[i].username) == 0)
		{
			receiverIndex = i;
		}
	}

	if (senderIndex != -1 && receiverIndex != -1)
	{
		if (amount <= userAccounts[senderIndex].balance)
		{
			userAccounts[senderIndex].balance -= amount;
			userAccounts[receiverIndex].balance += amount;
			printf("Transfer successful. New balance for %s: $%.2f\n", senderUsername, userAccounts[senderIndex].balance);
			printf("New balance for %s: $%.2f\n", receiverUsername, userAccounts[receiverIndex].balance);
			writeUserDataToFile();	// Update file after successful transfer
		}
		else
		{
			printf("Sender has insufficient balance.\n");
		}
	}
	else
	{
		printf("One or both users not found.\n");
	}
}




void checkBalance(char *username)
{
	// Balance check logic for user account
	int i;
	for (i = 0; i < totalAccounts; i++)
	{
		if (strcmp(username, userAccounts[i].username) == 0)
		{
			printf("Balance for %s: $%.2f\n", username, userAccounts[i].balance);
			return;
		}
	}

	printf("Account not found.\n");
}




void createUserAccount()
{
	if (totalAccounts < 100)
	{
		printf("%s\n", title);

		// Clears the input buffer
		int c;
		while ((c = getchar()) != '\n' && c != EOF);

		printf("Enter Full Name: ");
		fgets(userAccounts[totalAccounts].fullname, sizeof(userAccounts[totalAccounts].fullname), stdin);
		userAccounts[totalAccounts].fullname[strcspn(userAccounts[totalAccounts].fullname, "\n")] = 0;	// Removes trailing newline

		printf("Enter Username: ");
		scanf("%s", userAccounts[totalAccounts].username);
		printf("Enter Password: ");
		scanf("%s", userAccounts[totalAccounts].password);

		printf("Enter Phone Number: ");
        scanf("%s", userAccounts[totalAccounts].phone);

		printf("Enter Initial Balance: ");
		scanf("%f", &userAccounts[totalAccounts].balance);

		// Generates unique account number
		userAccounts[totalAccounts].accountNumber = totalAccounts + 1001;	// Assuming starting account number is 1001
		totalAccounts++;
		writeUserDataToFile();	// Updates file after successful creation
		printf("Account created successfully!\n");
		printf("\n");
	}
	else
	{
		printf("Maximum account limit reached. Cannot create more accounts.\n");
	}
	return redirect();
	printf("\n");
}




void readUserDataFromFile()
{
	FILE *file = fopen("userDatabase.txt", "r");
	if (file == NULL)
	{
		// printf("Error opening the database file.\n");
		return;
	}

    totalAccounts = 0;

	while (fscanf(file, "%[^,],%[^,],%[^,],%f,%[^,],%d\n", userAccounts[totalAccounts].username,
			userAccounts[totalAccounts].password, userAccounts[totalAccounts].phone, &userAccounts[totalAccounts].balance,
			userAccounts[totalAccounts].fullname, &userAccounts[totalAccounts].accountNumber) != EOF)
	{
		totalAccounts++;
	}

	fclose(file);
}




void writeUserDataToFile()
{
	FILE *file = fopen("userDatabase.txt", "w");
	if (file == NULL)
	{
		printf("Error opening the database file.\n");
		return;
	}

	for (int i = 0; i < totalAccounts; i++)
	{
		fprintf(file, "%s,%s,%s,%.2f,%s,%d\n", userAccounts[i].username, userAccounts[i].password, userAccounts[i].phone, userAccounts[i].balance,
			userAccounts[i].fullname, userAccounts[i].accountNumber);
	}

	fclose(file);
}




void redirect()
{
	// Loads user data from file
	readUserDataFromFile();
	int choice;

	printf("%s\n", title);
	printf("Welcome to E-Banking.\n\n");

	printf("1. Login as admin.\n");
	printf("2. Login as user.\n");
	printf("3. Create user account.\n");
	printf("4. Exit\n");

	printf("Enter your choice: ");
	scanf("%d", &choice);
	printf("\n");

	switch (choice)
	{
		case 1:
			adminLogin();
			break;
		case 2:
			userLogin();
			break;
		case 3:
			createUserAccount();
			break;
		case 4:
			printf("Exiting Program...\nThank you for using E-Banking.\n");
			return;
		default:
			printf("Invalid choice. Please try again.\n");
	}
}
