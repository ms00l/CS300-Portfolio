# CS-300 Portfolio Reflection

**What was the problem you were solving in the projects for this course?**
* The problem was creating a software solution for ABCU's Computer Science department.
* The primary usage of this software is to allow computer science advisors to access course information and verify student prerequisites on demand.

**How did you approach the problem? Consider why data structures are important to understand.**
* I approached the problem by first designing pseudocode and evaluating the runtime and memory costs of three different data structures: vectors, hash tables, and binary search trees. 
* Understanding data structures is critical because it directly impacts software performance; for instance, search speed is a critical factor for this advising tool. 
* I ultimately selected the Hash Table for the final program because it provides highly efficient lookup times compared to the vector and binary search tree data structures.

**How did you overcome any roadblocks you encountered while going through the activities or project?**
* One roadblock was that hash tables do not inherently sort data, which was required to print the course catalog in alphanumeric order. 
* I overcame this in my C++ code by extracting the course number keys into a separate vector, sorting that vector using the `<algorithm>` library, and then looping through it to print the list. 
* Another challenge was parsing the raw CSV file, which I solved by creating a custom whitespace trim method and checking for formatting errors or blank values before inserting the data.

**How has your work on this project expanded your approach to designing software and developing programs?**
* This project expanded my approach by demonstrating the value of writing and refining pseudocode before touching the actual C++ implementation. 
* It taught me to actively compare the advantages and disadvantages of various data structures, such as weighing a vector's memory efficiency against a hash table's fast lookup speed, to find the best fit for the client's specific needs.

**How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?**
* I have evolved my coding practices by organizing the program into modular functions, separating the logic for loading courses, printing the full list, and searching for individual courses. 
* I also focused on maintainability by including robust user input validation in the main menu loop and adding clear inline comments throughout the C++ file to explain the data parsing steps.