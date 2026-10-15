---
title: Home
---

## Computer Science ePortfolio

Welcome to my ePortfolio for CS 499, the Computer Science capstone at Southern New Hampshire University. This portfolio shows my work across three areas of computer science: software design and engineering, algorithms and data structures, and databases.

## Professional Self-Assessment

When I started the Computer Science program at Southern New Hampshire University, I was looking for a career that I would find fulfilling and would fit my personality. When researching a career that would fit my criteria, software engineering stood out to me as checking off those boxes. I completed my bachelor’s degree while working full time. During my time as a student, I got promoted at work to a senior-level management role. I balanced school, work, and family, and that taught me how to manage my time and how to stay focused on long-term goals. My goal after graduating is to start my tech career as a software engineer and to eventually transition into AI and machine learning engineering.

Completing this program and building my ePortfolio has made me more analytical and a better problem solver overall. Going back to projects that I had already completed has shown me how much I have grown. In each artifact, I found problems that I did not notice the first time like finding bugs, inefficient code, and security flaws. Being able to find and fix those problems in my own work and others’ code is one of the biggest skills I gained from this program.

### Collaborating in a Team Environment

As a manager, I frequently meet with my direct reports and my store’s leadership team to discuss action plans on what needs to be accomplished. I am engaged in planning the store’s operations like merchandising, training schedules, hiring and staffing decisions, and sales goals. One time, a large merchandising reset came down from the regional team, and our team had to create an action plan of who would complete each part of it and by when, all while also maintaining essential daily operations with limited staff. The key is to follow up with my team at regular intervals and to also be available with each associate if my assistance is needed. This is the same idea as planning a sprint on a software team, where each project is broken down into tasks that have owners and must be completed by a certain deadline. In my ePortfolio, I also created a code review video and added code headers and comments to every enhanced file. This is to improve communication with other developers so that they can easily understand and review my work.

### Communicating with Stakeholders

While explaining things to someone, I have learned that it is important to know my audience. Some people learn best by listening to instructions, while others need a demonstration to fully grasp the concept. When something needs a demonstration, I will either model it, write it out, or draw a diagram. Otherwise, I can explain it in a classroom style with questions, answers, and examples. I used that same approach in my ePortfolio. My code review was made for peers and managers to be able to look over and understand. My narratives and the ePortfolio website were written so that employers can see my work and my reasons behind it.

### Data Structures and Algorithms

Throughout the program, I learned that choosing the right data structure and algorithm for the problem matters just as much as designing and writing the code. In my algorithms enhancement, I built a hash table and compared it to a binary search tree by using a benchmark. When the courses were added in sorted order, the tree ended up becoming a long line and searching through the courses took 116,021 microseconds. The hash table in that same test ran in 4,852 microseconds. That result matches the Big-O time complexity of each data structure and showed me why design choices should also be backed by data.

### Software Engineering and Databases

In my CS 465 class, I built a full stack web application called Travlr using the MEAN stack framework. In it, MongoDB stored the data, Express ran the server, Angular powered the admin site, and Node.js ran everything together. The app had a customer-facing website and had an admin site where listings could be added, updated, or deleted. The most difficult part of this class was that it was the first time I used JavaScript, and there was a learning curve to make sure that each part of the stack correctly worked with the other parts. The skills that I built throughout this program helped me redesign my CS 330 3D scene with an object-oriented base class so that new objects could be added without changing the rendering code. I also added an index to my MongoDB database which cut the number of documents searched from 10,000 down to 17 for a filter.

### Security

I believe that security is a continuous process that starts when an application is first designed and continues through launch and all updates after that. In my secure coding and software security courses, I learned to use static analysis tools to find vulnerabilities within the code, and to run dependency checks periodically on any third-party software. I also learned how to utilize JSON Web Tokens when building the Travlr app so that only logged-in admins could change listings. Because of learning secure coding practices, I was able to identify and remove security flaws within my artifacts for my ePortfolio. Within the dashboard’s code, there were hardcoded database credentials visible in a public repository, so anyone who saw the code could log in to the database and would be able to manipulate the data. Therefore, I created a read-only database account and turned on access control within MongoDB. I also moved the login credentials into an .env file and made sure that file was part of a .gitignore file so that the credentials could never be public. While reviewing my final code, I also found that the dashboard was still connecting with an admin account and fixed it before uploading. My course planner also now validates all user input and checks every line of the data file before using it.

### How My Artifacts Fit Together

The three artifacts in my ePortfolio come from different courses and use different languages and tools. My 3D desk scene shows software design in C++ and OpenGL. My course planner shows data structures and algorithms in C++. My Grazioso Salvare dashboard shows databases and security with Python and MongoDB. These artifacts show that I can design software that is easy to maintain, make it efficient, and keep it secure. Each artifact includes the original code, the enhanced code, and a narrative explaining what I changed and what I learned.

- [Download Professional-Self Assessment (Word)](https://github.com/FreddyCase13/FreddyCase13.github.io/raw/main/CS499_Freddy_Case_Professional_Self_Assessment.docx)

## Contents
- [Code Review](./code-review)
- [Software Design and Engineering: CS 330 3D Desk Scene](software-design)
- [Algorithms and Data Structures: CS 300 Course Planner](algorithms)
- [Databases: CS 340 Grazioso Salvare Dashboard](databases)
