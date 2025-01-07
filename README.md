# Sparring Counter (In Progress)
This is a program for keeping track of points in sparring matches. 
Please head to the `sparring_counter` branch to see the latest updates. 

## General Information
- There is a red player and a blue player.
- Judges can press the red or blue button on their phone by going to `IP:5000/counter/edit`, where IP is the IP generated when the Python program is run.
- The points will then be updated in `IP:5000/counter/view`. 

## Technologies Used
- Python
- Flask
- HTML
- JavaScript

## Setup
Clone the sparring_counter branch onto your development environment. 

## Usage
Run `sparring_counter_flask.py` and note the IP address in the terminal. <br>
Go to `localhost:5000/setup` <br>
![image](https://github.com/user-attachments/assets/c9f60412-a94d-4b2a-9fb3-7139bac2a7d8) <br>
Input the red and blue player names and click submit. You will be redirected to the `/view` page. <br>
![image](https://github.com/user-attachments/assets/0449b1f1-13f4-45a3-8501-194476832cc0) <br>
Gather the judges and have them go to the `IP:5000/counter/edit` page. <br>
![image](https://github.com/user-attachments/assets/c37e69a8-064e-4b70-b9e6-14d8fd8fd6f2) <br>
You are all set to begin! <br>
The reset button can be used to reset the scores. Return to the setup page if a new match with different players begins. 

## Project Status
_in_progress_

## Room for Improvement
To Do: 
- Implement the timer function

# Snake Game in C (In Progress)
This is the classic Snake Game programmed in C. Please head to the `snake_game_c` branch to see the latest updates. 

## General Information
- This is a fun game that I chose to recreate in C in hopes of showing off my skills
- It is currently a work in progress, but I hope to finish it soon

## Technologies Used
- Windows Subsystem for Linux
- VS Code

## Setup
Set up your WSL environment and download snake_game.c to a folder of your choice.

## Usage
In the terminal, type `gcc -Wall -std=c99 -g snake_game.c -o snake_game -lncurses` to compile the program. 
To run the program, type `./snake_game`

## Project Status
_in_progress_

## Room for Improvement
To Do: 
- Implement the randomly generated apple
- Test
