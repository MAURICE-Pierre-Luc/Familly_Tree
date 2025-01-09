# projetCIR1_groupe_5

## Table of Contents
1. [Introduction](#Introduction)
2. [First-menu](#First-menu)
3. [Second-menu](#Second-menu)
4. [Third-menu](#Third-menu)

### Introduction
The purpose of this project is to enable the visualization of a person's ancestors over two generations. However, there are additional options that we detail here.


### First-menu
The first menu of our program is as follows:

```
What do you want to do
------------------------
1. Read CSV file
2. Exit
------------------------
Your choice:
```

The options allow you to:
1. Read a CSV file, which is structured as follows:
   - Line 1: Total number of people
   - Line 2: Sample person in the format "person_id, father_id, mother_id, last_name, first_name, birth_date, birth_region"
   - Line 3 to (Total number of people + 2): Person in the format "person_id, father_id, mother_id, last_name, first_name, birth_date, birth_region"
   Attention: The IDs must be unique for the program to function correctly.
2. Exit the program

If you select option 1, you will see the following message:

```
Read CSV file
------------------------
Enter CSV file name:
```

For the file to be recognized, it must:
- Be in a subfolder (at the same level as the program)
- Only type "filename.csv"

If you enter a valid file name, a confirmation message appears:

```
File "filename.csv" read successfully!
```

Otherwise, you will see the following message:

```
Error opening "filename.csv", file does not exist
```

Followed by the second menu:

### Second-menu
```
What do you want to do
------------------------
1. Show family tree info
2. Export HTML family tree files
3. Export HTML info file
4. Export all files
5. Query family tree
6. Go back to principal menu
------------------------
Your choice:
```

The options allow you to:
1. Display the information of the loaded population
2. Export the family trees of all loaded people
3. Export the information displayed in option 1
4. Perform 2 and 3 simultaneously
5. Query the loaded population
6. Return to the first menu

If you choose option 5, the third (and final) menu appears:

### Third-menu
```
What do you want to do
------------------------
1. Get first born in the database
2. Get last born in the database
3. Get number of people born in a region
4. Get the region with the highest number of births
5. Get the number of people born on a given day and month
6. Get the name of the parents with the most children
7. Get the information of a given person
8. Export all query results to HTML file
9. Go back to previous menu
------------------------
Your choice:
```

The options allow you to:
1. Display the information of the oldest person
2. Display the information of the youngest person
3. Display the number of births in a region
4. Display the region with the most births
5. Display the number of people born on a given date
6. Display the names of the parents with the most children
7. Display the information of a person
8. Export the queries MADE (only the last ones for those done multiple times)
9. Return to the second menu

If you choose option 3, the following message appears:

```
The available regions are:
------------------------
"list of regions from the loaded population"
------------------------
Please enter the region of your choice from the list above
------------------------
Your choice:
```

If you enter a valid region name, you will see a message like:

```
The amount of birth in "entered region" is "number of births"
```

Otherwise, you will see the following message:

```
Invalid region name
```

And the third menu reappears.

If you choose option 5, the following message appears:

```
Enter the day and month respecting the format: dd/mm (can be d/m)
------------------------
Your choice:
```

If the date is valid (February 29th is a valid date), you get a message like:

```
The number of people born on "entered date" is: "number of births"
```

Otherwise, you get:

```
Invalid month provided.
The number of people born on "entered date" is: -1
```

Or:

```
Invalid day provided for month "entered month number"
The number of people born on "entered date" is: -1
```

If you choose option 7, the following message appears:

```
Please enter the last name of the person: "enter last name"
Please enter the first name of the person: "enter first name"
```

If you enter a correct last name AND first name, you get:

```
    Sex: "sex"
    Name: "First name"
    Last name: "Last name"
    Born the: "Date of birth"
    From:
        Father: "Father's first name"
        Mother: "Mother's first name"
    At: "Birth region"
```

Otherwise, you get:

```
The person does not exist or, name or last name is wrong
```