# Robot War Simulator 🤖🎮

This project is a Robot War Simulator, implemented in standard C++, that simulates a battlefield where robots compete in warfare following specific rules and behaviors. It leverages Object-Oriented Programming (OOP) principles such as inheritance, polymorphism, and operator overloading, while adhering to custom data structure implementations.

Features

Battlefield
- A 2D battlefield matrix (M x N) represents the war zone.
- Robots, battlefield locations, and boundaries are visually represented using characters and symbols.

Simulation Mechanics
- Turn-based Simulation: Robots take actions sequentially in each turn.
- Each turn involves three potential actions:
      Look: Reveals surroundings of a robot (depending on its capabilities).
      Move: Moves to one of 8 possible neighboring locations.
      Fire: Shoots at specific locations (based on robot type).

Robot Classes and Types
Base Class:
Robot is an abstract base class inherited by specialized abstract classes:
      - MovingRobot
      - ShootingRobot
      - SeeingRobot
      - SteppingRobot
Robots inherit capabilities via multiple inheritance, depending on their type.

Robot Types:
      - RoboCop: Can look, move, and fire three shots per turn within a firing range.
      - Terminator: Looks and moves, stepping over enemy robots to destroy them.
      - BlueThunder: Fires at adjacent locations in a clockwise pattern.
      - MadBot: Fires at adjacent locations randomly.
      - RoboTank: Fires at random battlefield locations.
      - TerminatorRoboCop: Combines the abilities of Terminator and RoboCop.
      - UltimateRobot: Combines all capabilities: moves, steps on enemies, and fires at multiple random locations.

Simulation Rules
1. Robots cannot reveal their positions to others.
2. A robot can only occupy one position at a time.
3. Robots have three lives and can re-enter the battlefield up to three times after being destroyed.
4. The simulation ends when either the simulation steps are completed or only one robot remains.

Input Format
The simulation starts based on a configuration file that specifies:

1. Battlefield dimensions (M x N).
2. Number of simulation steps (T).
3. Number of robots (R).
4. Robot details:
    - Type, name, and position (e.g., Terminator Alpha 35 20).
    - Random placement if position is unspecified.
  

Key Features
1. Action Tracking:
    - Display battlefield and robot actions after every turn.
    - Save simulation details to a text file for review.

2. Custom Data Structures:
    - No use of STL containers (e.g., vector, queue, list).
    - All required data structures are implemented manually.

3. Robot Queue:
    - Tracks destroyed robots awaiting re-entry.

4. Simulation Flow:
    - Robots act in a fixed sequence determined by a custom data structure.
