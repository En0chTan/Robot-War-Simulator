//***********|**********|**********|
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "Vector.h" // Custom data structure implementations
#include "List.h"   // Custom data structure implementations
#include "Queue.h"  // Custom data structure implementations

using namespace std;

// Forward declaration of Battlefield class
class Battlefield;

// Base Robot class
// This class serves as the base class for all types of robots in the game.
// It contains common attributes and methods that all robots share.
class Robot
{
protected:
    int robotPositionX = -1; // X coordinate of the robot on the battlefield
    int robotPositionY = -1; // Y coordinate of the robot on the battlefield
    string id_ = "";         // Unique identifier for the robot (e.g., BT01)
    string robotType_ = "";  // Type of the robot (e.g., RoboCop)
    string robotName_ = "";  // Name of the robot (e.g., BT01_Beta)
    int numOfLives_ = 3;     // Number of lives the robot has
    int numOfKills_ = 0;     // Number of kills the robot has made

public:
    // Constructor to initialize robot attributes
    Robot(string id = "", int x = -1, int y = -1) : id_(id), robotPositionX(x), robotPositionY(y) {}

    // Virtual destructor
    virtual ~Robot() {}

    // Getter and setter methods for robot's X coordinate
    int x() const { return robotPositionX; }
    void setX(int x) { robotPositionX = x; }

    // Getter and setter methods for robot's Y coordinate
    int y() const { return robotPositionY; }
    void setY(int y) { robotPositionY = y; }

    // Getter and setter methods for robot's ID
    string id() const { return id_; }
    void setId(string id) { id_ = id; }

    // Getter and setter methods for robot's type
    string robotType() const { return robotType_; }
    void setRobotType(string robotType) { robotType_ = robotType; }

    // Getter and setter methods for robot's name
    string robotName() const { return robotName_; }
    void setRobotName(string robotName) { robotName_ = robotName; }

    // Getter and setter methods for robot's number of lives
    int numOfLives() const { return numOfLives_; }
    void setNumOfLives(int numOfLives) { numOfLives_ = numOfLives; }

    // Getter method for robot's number of kills
    int getNumOfKills() const { return numOfKills_; }

    // Method to convert robot's attributes to a string
    string toString() const
    {
        return "Robot " + id_ + " has " + to_string(numOfKills_) + " kills.";
    }

    // Overloaded output operator to print robot's attributes
    friend ostream &operator<<(ostream &out, const Robot &r)
    {
        out << r.id_ << " at (" << r.robotPositionX << ", " << r.robotPositionY << ")";
        return out;
    }

    // Pure virtual functions to be implemented by derived classes
    virtual void setLocation(int x, int y) = 0;
    virtual void actions(Battlefield *battlefield, ofstream &outputFile) = 0;
    void checkForUpgrade(Battlefield *battlefield, ofstream &outputFile);
};

// Abstract classes for different robot actions
class SeeingRobot : virtual public Robot
{
public:
    virtual ~SeeingRobot() {}
    virtual void actionLook(Battlefield *battlefield, ofstream &outputFile) = 0;
};

class MovingRobot : virtual public Robot
{
public:
    virtual ~MovingRobot() {}
    virtual void actionMove(Battlefield *battlefield, ofstream &outputFile) = 0;
};

class ShootingRobot : virtual public Robot
{
public:
    virtual ~ShootingRobot() {}
    virtual void actionFire(Battlefield *battlefield, ofstream &outputFile) = 0;
};

class SteppingRobot : virtual public Robot
{
public:
    virtual ~SteppingRobot() {}
    virtual void actionStep(Battlefield *battlefield, ofstream &outputFile) = 0;
};

class TeleportingRobot : virtual public Robot
{
public:
    virtual ~TeleportingRobot() {}
    virtual void actionTP(Battlefield *battlefield, ofstream &outputFile) = 0;
};

class BombingRobot : virtual public Robot
{
public:
    virtual ~BombingRobot() {}
    virtual void actionBomb(Battlefield *battlefield, ofstream &outputFile) = 0;
};

class LaserRobot : virtual public Robot
{
public:
    virtual ~LaserRobot() {}
    virtual void actionLaser(Battlefield *battlefield, ofstream &outputFile) = 0;
};

// RoboCop class inherits from multiple action classes
// This class represents a RoboCop robot which can see, move, and shoot.
class RoboCop : public SeeingRobot, public MovingRobot, public ShootingRobot
{
private:
    static int robotAutoIncrementInt_; // Static counter to generate unique IDs for RoboCop instances
public:
    // Constructor to initialize RoboCop attributes
    RoboCop(string id = "", int x = -1, int y = -1)
    {
        id_ = id;
        robotPositionX = x;
        robotPositionY = y;
        robotAutoIncrementInt_++;
        robotType_ = "RoboCop";
    }
    static int robotAutoIncrementInt() { return robotAutoIncrementInt_; }
    virtual ~RoboCop() {}

    // Set the location of the RoboCop
    virtual void setLocation(int x, int y)
    {
        robotPositionX = x;
        robotPositionY = y;
    }

    // Look around the battlefield
    virtual void actionLook(Battlefield *battlefield, ofstream &outputFile);

    // Move to a new location on the battlefield
    virtual void actionMove(Battlefield *battlefield, ofstream &outputFile);

    // Fire at targets on the battlefield
    virtual void actionFire(Battlefield *battlefield, ofstream &outputFile);

    // Perform all actions (look, move, fire) on the battlefield
    virtual void actions(Battlefield *battlefield, ofstream &outputFile);
};
int RoboCop::robotAutoIncrementInt_ = 0;

// Terminator class inherits from SeeingRobot and SteppingRobot
// This class represents a Terminator robot which can see and step on other robots to terminate them.
class Terminator : public SeeingRobot, public SteppingRobot
{
private:
    static int robotAutoIncrementInt_; // Static counter to generate unique IDs for Terminator instances
public:
    // Constructor to initialize Terminator attributes
    Terminator(string id = "", int x = -1, int y = -1)
    {
        id_ = id;
        robotPositionX = x;
        robotPositionY = y;
        robotAutoIncrementInt_++;
        robotType_ = "Terminator";
    }
    static int robotAutoIncrementInt() { return robotAutoIncrementInt_; }
    virtual ~Terminator() {}

    // Set the location of the Terminator
    virtual void setLocation(int x, int y)
    {
        robotPositionX = x;
        robotPositionY = y;
    }

    // Look around the battlefield
    virtual void actionLook(Battlefield *battlefield, ofstream &outputFile);

    // Step to a new location on the battlefield
    virtual void actionStep(Battlefield *battlefield, ofstream &outputFile);

    // Perform all actions (look, step) on the battlefield
    virtual void actions(Battlefield *battlefield, ofstream &outputFile);
};
int Terminator::robotAutoIncrementInt_ = 0;

// TerminatorRoboCop class inherits from multiple action classes
// This class represents a hybrid robot that can see, shoot, and step on other robots.
class TerminatorRoboCop : public SeeingRobot, public ShootingRobot, public SteppingRobot
{
private:
    static int robotAutoIncrementInt_; // Static counter to generate unique IDs for TerminatorRoboCop instances
public:
    // Constructor to initialize TerminatorRoboCop attributes
    TerminatorRoboCop(string id = "", int x = -1, int y = -1)
    {
        id_ = id;
        robotPositionX = x;
        robotPositionY = y;
        robotType_ = "TerminatorRoboCop";
        robotAutoIncrementInt_++;
    }
    static int robotAutoIncrementInt() { return robotAutoIncrementInt_; }
    virtual ~TerminatorRoboCop() {}

    // Set the location of the TerminatorRoboCop
    virtual void setLocation(int x, int y)
    {
        robotPositionX = x;
        robotPositionY = y;
    }

    // Look around the battlefield
    virtual void actionLook(Battlefield *battlefield, ofstream &outputFile);

    // Fire at targets on the battlefield
    virtual void actionFire(Battlefield *battlefield, ofstream &outputFile);

    // Step to a new location on the battlefield
    virtual void actionStep(Battlefield *battlefield, ofstream &outputFile);

    // Perform all actions (look, fire, step) on the battlefield
    virtual void actions(Battlefield *battlefield, ofstream &outputFile);
};
int TerminatorRoboCop::robotAutoIncrementInt_ = 0;

// BlueThunder class inherits from ShootingRobot
// This class represents a BlueThunder robot which can only shoot.
class BlueThunder : public ShootingRobot
{
private:
    static int robotAutoIncrementInt_; // Static counter to generate unique IDs for BlueThunder instances
    int fireDirection_ = 0;            // Direction in which the robot fires
public:
    // Constructor to initialize BlueThunder attributes
    BlueThunder(string id = "", int x = -1, int y = -1)
    {
        id_ = id;
        robotPositionX = x;
        robotPositionY = y;
        robotAutoIncrementInt_++;
        robotType_ = "BlueThunder";
    }
    static int robotAutoIncrementInt() { return robotAutoIncrementInt_; }
    virtual ~BlueThunder() {}

    // Set the location of the BlueThunder
    virtual void setLocation(int x, int y)
    {
        robotPositionX = x;
        robotPositionY = y;
    }

    // Fire at targets on the battlefield
    virtual void actionFire(Battlefield *battlefield, ofstream &outputFile);

    // Perform all actions (fire) on the battlefield
    virtual void actions(Battlefield *battlefield, ofstream &outputFile);
};
int BlueThunder::robotAutoIncrementInt_ = 0;

// Madbot class inherits from ShootingRobot
// This class represents a Madbot robot which can only shoot.
class Madbot : public ShootingRobot
{
private:
    static int robotAutoIncrementInt_; // Static counter to generate unique IDs for Madbot instances
public:
    // Constructor to initialize Madbot attributes
    Madbot(string id = "", int x = -1, int y = -1)
    {
        id_ = id;
        robotPositionX = x;
        robotPositionY = y;
        robotAutoIncrementInt_++;
        robotType_ = "Madbot";
    }
    static int robotAutoIncrementInt() { return robotAutoIncrementInt_; }
    virtual ~Madbot() {}

    // Set the location of the Madbot
    virtual void setLocation(int x, int y)
    {
        robotPositionX = x;
        robotPositionY = y;
    }

    // Fire at targets on the battlefield
    virtual void actionFire(Battlefield *battlefield, ofstream &outputFile);

    // Perform all actions (fire) on the battlefield
    virtual void actions(Battlefield *battlefield, ofstream &outputFile);
};
int Madbot::robotAutoIncrementInt_ = 0;

// RoboTank class inherits from ShootingRobot
// This class represents a RoboTank robot which can only shoot.
class RoboTank : public ShootingRobot
{
private:
    static int robotAutoIncrementInt_; // Static counter to generate unique IDs for RoboTank instances
public:
    // Constructor to initialize RoboTank attributes
    RoboTank(string id = "", int x = -1, int y = -1)
    {
        id_ = id;
        robotPositionX = x;
        robotPositionY = y;
        robotAutoIncrementInt_++;
        robotType_ = "RoboTank";
    }
    static int robotAutoIncrementInt() { return robotAutoIncrementInt_; }
    virtual ~RoboTank() {}

    // Set the location of the RoboTank
    virtual void setLocation(int x, int y)
    {
        robotPositionX = x;
        robotPositionY = y;
    }

    // Fire at targets on the battlefield
    virtual void actionFire(Battlefield *battlefield, ofstream &outputFile);

    // Perform all actions (fire) on the battlefield
    virtual void actions(Battlefield *battlefield, ofstream &outputFile);
};
int RoboTank::robotAutoIncrementInt_ = 0;

// UltimateRobot class inherits from multiple action classes
// This class represents an UltimateRobot which can see, move, shoot, and step on other robots.
class UltimateRobot : public SeeingRobot, public ShootingRobot, public SteppingRobot, public MovingRobot
{
private:
    static int robotAutoIncrementInt_; // Static counter to generate unique IDs for UltimateRobot instances
public:
    // Constructor to initialize UltimateRobot attributes
    UltimateRobot(string id = "", int x = -1, int y = -1)
    {
        id_ = id;
        robotPositionX = x;
        robotPositionY = y;
        robotAutoIncrementInt_++;
        robotType_ = "UltimateRobot";
    }
    static int robotAutoIncrementInt() { return robotAutoIncrementInt_; }
    virtual ~UltimateRobot() {}

    // Set the location of the UltimateRobot
    virtual void setLocation(int x, int y)
    {
        robotPositionX = x;
        robotPositionY = y;
    }

    // Look around the battlefield
    virtual void actionLook(Battlefield *battlefield, ofstream &outputFile);

    // Move to a new location on the battlefield
    virtual void actionMove(Battlefield *battlefield, ofstream &outputFile);

    // Fire at targets on the battlefield
    virtual void actionFire(Battlefield *battlefield, ofstream &outputFile);

    // Step to a new location on the battlefield
    virtual void actionStep(Battlefield *battlefield, ofstream &outputFile);

    // Perform all actions (look, move, fire, step) on the battlefield
    virtual void actions(Battlefield *battlefield, ofstream &outputFile);
};
int UltimateRobot::robotAutoIncrementInt_ = 0;

// TeleportRobot class inherits from TeleportingRobot
// This class represents a TeleportRobot which can teleport.
class TeleportRobot : public TeleportingRobot
{
private:
    static int robotAutoIncrementInt_; // Static counter to generate unique IDs for TeleportRobot instances
public:
    // Constructor to initialize TeleportRobot attributes
    TeleportRobot(string id = "", int x = -1, int y = -1)
    {
        id_ = id;
        robotPositionX = x;
        robotPositionY = y;
        robotAutoIncrementInt_++;
        robotType_ = "TeleportRobot";
    }
    static int robotAutoIncrementInt() { return robotAutoIncrementInt_; }
    virtual ~TeleportRobot() {}

    // Set the location of the TeleportRobot
    virtual void setLocation(int x, int y)
    {
        robotPositionX = x;
        robotPositionY = y;
    }

    // Teleport to a new location on the battlefield
    virtual void actionTP(Battlefield *battlefield, ofstream &outputFile);

    // Perform all actions (teleport) on the battlefield
    virtual void actions(Battlefield *battlefield, ofstream &outputFile);
};
int TeleportRobot::robotAutoIncrementInt_ = 0;

// BomberBot class inherits from BombingRobot
// This class represents a BomberBot which can throw grenades.
class BomberBot : public BombingRobot
{
private:
    static int robotAutoIncrementInt_; // Static counter to generate unique IDs for BomberBot instances
public:
    // Constructor to initialize BomberBot attributes
    BomberBot(string id = "", int x = -1, int y = -1)
    {
        id_ = id;
        robotPositionX = x;
        robotPositionY = y;
        robotAutoIncrementInt_++;
        robotType_ = "BomberBot";
    }
    static int robotAutoIncrementInt() { return robotAutoIncrementInt_; }
    virtual ~BomberBot() {}

    // Set the location of the BomberBot
    virtual void setLocation(int x, int y)
    {
        robotPositionX = x;
        robotPositionY = y;
    }

    // Throw a grenade on the battlefield
    virtual void actionBomb(Battlefield *battlefield, ofstream &outputFile);

    // Perform all actions (throw grenade) on the battlefield
    virtual void actions(Battlefield *battlefield, ofstream &outputFile);
};
int BomberBot::robotAutoIncrementInt_ = 0;

// LaserBot class inherits from LaserRobot
// This class represents a LaserBot which can fire a laser.
class LaserBot : public LaserRobot
{
private:
    static int robotAutoIncrementInt_; // Static counter to generate unique IDs for LaserBot instances
public:
    // Constructor to initialize LaserBot attributes
    LaserBot(string id = "", int x = -1, int y = -1)
    {
        id_ = id;
        robotPositionX = x;
        robotPositionY = y;
        robotAutoIncrementInt_++;
        robotType_ = "LaserBot";
    }
    static int robotAutoIncrementInt() { return robotAutoIncrementInt_; }
    virtual ~LaserBot() {}

    // Set the location of the LaserBot
    virtual void setLocation(int x, int y)
    {
        robotPositionX = x;
        robotPositionY = y;
    }

    // Fire a laser on the battlefield
    virtual void actionLaser(Battlefield *battlefield, ofstream &outputFile);

    // Perform all actions (fire laser) on the battlefield
    virtual void actions(Battlefield *battlefield, ofstream &outputFile);
};
int LaserBot::robotAutoIncrementInt_ = 0;

// Battlefield class definition
// This class represents the battlefield where robots perform their actions.
class Battlefield
{
private:
    int BTF_NUM_OF_COLS_ = -1;     // Number of columns on the battlefield
    int BTF_NUM_OF_ROWS_ = -1;     // Number of rows on the battlefield
    int turns_ = -1;               // Number of turns in the game
    int numOfRobots_ = -1;         // Number of robots on the battlefield
    Vector<Robot *> robots_;       // Custom Vector class to store robots
    Vector<Vector<string>> btf_;   // Custom 2D Vector class to represent the battlefield grid
    Queue<Robot *> revivalQueue_;  // Custom Queue class to store robots to be revived
    static Battlefield *instance_; // Singleton instance of the Battlefield class

    Battlefield(const Battlefield &) = delete;
    Battlefield &operator=(const Battlefield &) = delete;

public:
    // Counters for each type of robot
    int roboCopCount_ = 0;
    int terminatorCount_ = 0;
    int terminatorRoboCopCount_ = 0;
    int blueThunderCount_ = 0;
    int madbotCount_ = 0;
    int roboTankCount_ = 0;
    int ultimateRobotCount_ = 0;
    int teleportRobotCount_ = 0;
    int BomberBotCount_ = 0;
    int LaserBotCount_ = 0;

    // Getter for robots vector
    Vector<Robot *> getRobots() { return robots_; }

    // Constructor
    Battlefield() {}

    // Singleton instance getter
    static Battlefield *getInstance()
    {
        if (!instance_)
        {
            instance_ = new Battlefield();
        }
        return instance_;
    }

    // Destructor to clean up dynamically allocated robots
    ~Battlefield()
    {
        for (auto robot : robots_)
        {
            delete robot;
        }
    }

    // Getter methods for battlefield dimensions and game attributes
    int BTF_NUM_OF_COLS() { return BTF_NUM_OF_COLS_; }
    int BTF_NUM_OF_ROWS() { return BTF_NUM_OF_ROWS_; }
    int turns() { return turns_; }
    int numOfRobots() { return numOfRobots_; }
    Vector<Robot *> robots() { return robots_; }
    Vector<Vector<string>> btf() { return btf_; }

    // Read input file to initialize battlefield and robots
    void readFile(string filename)
    {
        string strIn;
        string robotType = "";
        string robotName = "";
        string robotId = "";
        string strX = "";
        string strY = "";
        int x = -1;
        int y = -1;

        ifstream inFile;
        inFile.open(filename);
        if (!inFile)
        {
            cout << "Cannot open the file: " << filename << endl;
            exit(1);
        }

        inFile >> strIn >> strIn >> strIn;
        inFile >> BTF_NUM_OF_COLS_;
        inFile >> BTF_NUM_OF_ROWS_;
        cout << "----------------------------------------------------------------------" << endl;
        cout << "|                  Game Start! Data Initializaton ...                |" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        cout << "\nM by N: " << BTF_NUM_OF_COLS_ << " " << BTF_NUM_OF_ROWS_ << "\n";
        inFile >> strIn >> turns_;
        cout << "Steps: " << turns_ << endl;
        inFile >> strIn >> numOfRobots_;
        cout << "Robots: " << numOfRobots_ << "\n"
             << endl;

        for (int i = 0; i < numOfRobots_; ++i)
        {
            inFile >> robotType >> robotName >> strX >> strY;
            cout << robotType << " " << robotName << " " << strX << " " << strY << "\n";
            size_t underscorePos = robotName.find('_');
            if (underscorePos != string::npos)
            {
                robotId = robotName.substr(0, underscorePos);
            }
            if (strX == "random")
            {
                x = rand() % BTF_NUM_OF_COLS_;
                cout << robotId << " randomX: " << x << endl;
            }
            else
            {
                x = stoi(strX);
            }
            if (strY == "random")
            {
                y = rand() % BTF_NUM_OF_ROWS_;
                cout << robotId << " randomY: " << y << endl;
            }
            else
            {
                y = stoi(strY);
            }

            if (robotType == "RoboCop")
            {
                roboCopCount_++;
                robotId = (roboCopCount_ < 10) ? "RC0" + to_string(roboCopCount_) : "RC" + to_string(roboCopCount_);
                robots_.push_back(new RoboCop(robotId, x, y));
            }
            else if (robotType == "Terminator")
            {
                terminatorCount_++;
                robotId = (terminatorCount_ < 10) ? "T0" + to_string(terminatorCount_) : "T" + to_string(terminatorCount_);
                robots_.push_back(new Terminator(robotId, x, y));
            }
            else if (robotType == "TerminatorRoboCop")
            {
                terminatorRoboCopCount_++;
                robotId = (terminatorRoboCopCount_ < 10) ? "TR0" + to_string(terminatorRoboCopCount_) : "TR" + to_string(terminatorRoboCopCount_);
                robots_.push_back(new TerminatorRoboCop(robotId, x, y));
            }
            else if (robotType == "BlueThunder")
            {
                blueThunderCount_++;
                robotId = (blueThunderCount_ < 10) ? "BT0" + to_string(blueThunderCount_) : "BT" + to_string(blueThunderCount_);
                robots_.push_back(new BlueThunder(robotId, x, y));
            }
            else if (robotType == "Madbot")
            {
                madbotCount_++;
                robotId = (madbotCount_ < 10) ? "MB0" + to_string(madbotCount_) : "MB" + to_string(madbotCount_);
                robots_.push_back(new Madbot(robotId, x, y));
            }
            else if (robotType == "RoboTank")
            {
                roboTankCount_++;
                robotId = (roboTankCount_ < 10) ? "RT0" + to_string(roboTankCount_) : "RT" + to_string(roboTankCount_);
                robots_.push_back(new RoboTank(robotId, x, y));
            }
            else if (robotType == "UltimateRobot")
            {
                ultimateRobotCount_++;
                robotId = (ultimateRobotCount_ < 10) ? "UR0" + to_string(ultimateRobotCount_) : "UR" + to_string(ultimateRobotCount_);
                robots_.push_back(new UltimateRobot(robotId, x, y));
            }
            else if (robotType == "TeleportRobot")
            {
                teleportRobotCount_++;
                robotId = (teleportRobotCount_ < 10) ? "TP0" + to_string(teleportRobotCount_) : "TP" + to_string(teleportRobotCount_);
                robots_.push_back(new TeleportRobot(robotId, x, y));
            }
            else if (robotType == "BomberBot")
            {
                BomberBotCount_++;
                robotId = (BomberBotCount_ < 10) ? "BB0" + to_string(BomberBotCount_) : "BB" + to_string(BomberBotCount_);
                robots_.push_back(new BomberBot(robotId, x, y));
            }
            else if (robotType == "LaserBot")
            {
                LaserBotCount_++;
                robotId = (LaserBotCount_ < 10) ? "LB0" + to_string(LaserBotCount_) : "LB" + to_string(LaserBotCount_);
                robots_.push_back(new LaserBot(robotId, x, y));
            }
        }

        inFile.close();
        btf_.resize(BTF_NUM_OF_ROWS_);
        for (int i = 0; i < btf_.size(); ++i)
        {
            btf_[i].resize(BTF_NUM_OF_COLS_);
        }
        for (int i = 0; i < btf_.size(); ++i)
        {
            for (int j = 0; j < btf_[i].size(); ++j)
            {
                btf_[i][j] = "";
            }
        }
        placeRobots();
    }

    // Place robots on the battlefield
    void placeRobots()
    {
        for (int i = 0; i < btf_.size(); ++i)
        {
            for (int j = 0; j < btf_[i].size(); ++j)
            {
                btf_[i][j] = "";
            }
        }
        for (int i = 0; i < robots_.size(); ++i)
        {
            if (robots_[i]->y() < btf_.size() && robots_[i]->x() < btf_[0].size())
            {
                btf_[robots_[i]->y()][robots_[i]->x()] = robots_[i]->id();
            }
            else
            {
                cout << "Error message: Invalid location for the robot " << robots_[i]->id() << endl;
                exit(1);
            }
        }
    }

    // Remove robot by ID from the battlefield
    void eraseRobotById(string id)
    {
        for (int i = 0; i < robots_.size(); ++i)
        {
            if (robots_[i]->id() == id)
            {
                cout << "Killed robot " << *robots_[i] << endl;
                robots_.erase(robots_.begin() + i);
                break;
            }
        }
        placeRobots();
    }

    // Add a robot back to the battlefield
    void pushBackRobot(Robot *robot)
    {
        cout << "Push back robot " << *robot << "\n"
             << endl;
        robots_.push_back(robot);
        placeRobots();
    }

    // Display the battlefield grid
    void displayBTF(ostream &out) const
    {
        out << "     ";
        for (int j = 0; j < btf_[0].size(); ++j)
        {
            out << "  " << right << setfill('0') << setw(2) << j << " ";
        }
        out << endl;

        for (int i = 0; i < btf_.size(); ++i)
        {
            out << "    ";
            for (int j = 0; j < btf_[0].size(); ++j)
                out << "+----";
            out << "+" << endl;

            out << "  " << right << setfill('0') << setw(2) << i;
            for (int j = 0; j < btf_[0].size(); ++j)
            {
                if (btf_[i][j] == "")
                {
                    out << "|" << "    ";
                }
                else
                {
                    out << "|" << left << setfill(' ') << setw(4) << btf_[i][j];
                }
            }
            out << "|" << endl;
        }
        out << "    ";
        for (int j = 0; j < btf_[0].size(); ++j)
            out << "+----";
        out << "+" << endl;

        out << "\n";
    }

    // Run robot actions for each turn
    void runRobotActions(ofstream &outputFile)
    {
        int turn = 1;
        int revive_CD = 3; // Cooldown for reviving robots
        while (turn <= turns_)
        {
            // Check if there's only one robot left standing
            if (robots_.size() == 1)
            {
                cout << "----------------------------------------------------------------------" << endl;
                cout << "|               Only one robot left standing. Game over!             |" << endl;
                cout << "----------------------------------------------------------------------\n"
                     << endl;
                displayBTF(cout); // Print final grid when the game ends
                displayBTF(outputFile);
                return;
            }

            for (int i = 0; i < robots_.size(); ++i)
            {
                // Execute actions for each robot
                cout << "------------------------------- Step " << turn << " -------------------------------" << endl;
                outputFile << "------------------------------- Step " << turn << " -------------------------------" << endl;

                cout << *robots_[i] << endl;
                outputFile << *robots_[i] << endl;

                cout << "Num of lives: " << robots_[i]->numOfLives() << endl;
                outputFile << "Num of lives: " << robots_[i]->numOfLives() << endl;

                cout << "------------------------ " << *robots_[i] << " Action" << " ------------------------ \n"
                     << endl;
                outputFile << "------------------------ " << *robots_[i] << " Action" << " ------------------------ \n"
                           << endl;

                robots_[i]->actions(this, outputFile);
                cout << "\n";
                outputFile << "\n";

                displayBTF(cout);
                displayBTF(outputFile);

                cout << "\n"
                     << endl;
                outputFile << "\n"
                           << endl;

                // Increment the turn counter after each robot's turn
                turn++;
                if (!revivalQueue_.empty())
                {
                    revive_CD--;
                    if (revive_CD == 0)
                    {
                        // Revive robots after each round
                        reviveRobots();

                        // Reset cooldown
                        revive_CD = revivalQueue_.empty() ? 3 : 2;
                    }
                }

                // Check if the turn reaches the maximum number of turns
                if (turn == turns_ + 1)
                {
                    cout << "----------------------------------------------------------------------" << endl;
                    cout << "|                  Maximum turns reached. Game over!                 |" << endl;
                    cout << "----------------------------------------------------------------------\n\n"
                         << endl;

                    displayBTF(cout); // Print final grid when the game ends
                    displayBTF(outputFile);

                    cout << "\n"
                         << "------------------------- Finale Battle Report -----------------------\n"
                         << endl;
                    outputFile << "\n"
                               << "------------------------- Finale Battle Report -----------------------\n"
                               << endl;
                    return;
                }
            }
        }
    }

    // Print the area around a specific location
    void printLookArea(int x, int y, ostream &out) const
    {
        out << "Look area centered at (" << x << ", " << y << "):\n\n";

        // Print the column indices
        out << "     ";
        for (int j = x - 1; j <= x + 1; ++j)
        {
            if (j >= 0 && j < BTF_NUM_OF_COLS_)
            {
                out << right << setfill('0') << setw(2) << j << "   ";
            }
            else
            {
                out << "     ";
            }
        }
        out << endl;

        // Print the top border
        out << "   ";
        for (int j = x - 1; j <= x + 1; ++j)
        {
            out << "+----";
        }
        out << "+" << endl;

        for (int i = y - 1; i <= y + 1; ++i)
        {
            // Print the row index
            if (i >= 0 && i < BTF_NUM_OF_ROWS_)
            {
                out << right << setfill('0') << setw(2) << i << " ";
            }
            else
            {
                out << "   ";
            }

            for (int j = x - 1; j <= x + 1; ++j)
            {
                if (i >= 0 && i < BTF_NUM_OF_ROWS_ && j >= 0 && j < BTF_NUM_OF_COLS_)
                {
                    if (btf_[i][j] == "")
                    {
                        out << "|    ";
                    }
                    else
                    {
                        out << "|" << setw(4) << left << setfill(' ') << btf_[i][j];
                    }
                }
                else
                {
                    out << "|####";
                }
            }
            out << "|\n";

            // Print the row border
            out << "   ";
            for (int j = x - 1; j <= x + 1; ++j)
            {
                out << "+----";
            }
            out << "+" << endl;
        }

        // Spacing
        out << " " << endl;
    }

    // Check if a position is occupied by a robot
    bool isOccupied(int x, int y) const
    {
        for (auto robot : robots_)
        {
            if (robot->x() == x && robot->y() == y)
            {
                return true;
            }
        }
        return false;
    }

    // Move a robot to a new position
    void moveRobot(Robot *robot, int newX, int newY)
    {
        if (!isOccupied(newX, newY) && newX >= 0 && newX < BTF_NUM_OF_COLS() && newY >= 0 && newY < BTF_NUM_OF_ROWS())
        {
            robot->setX(newX);
            robot->setY(newY);
            placeRobots();
        }
    }

    // Attack a position on the battlefield
    bool attackPosition(int x, int y, const string &attackerId)
    {
        for (auto robot : robots_)
        {
            if (robot->x() == x && robot->y() == y)
            {
                cout << attackerId << " kills " << robot->id() << " at (" << x << ", " << y << ")" << endl;
                queueForRevival(robot);
                eraseRobotById(robot->id());
                return true;
            }
        }
        return false;
    }

    // Queue a robot for revival
    void queueForRevival(Robot *robot)
    {
        if (robot->numOfLives() > 1)
        {
            robot->setNumOfLives(robot->numOfLives() - 1);
            revivalQueue_.enqueue(robot);
        }
    }

    // Revive robots from the queue
    void reviveRobots()
    {
        if (!revivalQueue_.empty())
        {
            Robot *robot = revivalQueue_.front();
            revivalQueue_.dequeue();
            cout << robot->id() << " Lives left :" << robot->numOfLives() << endl;
            int x = robot->x();
            int y = robot->y();
            if (isOccupied(x, y))
            {
                do
                {
                    x = rand() % BTF_NUM_OF_COLS_;
                    y = rand() % BTF_NUM_OF_ROWS_;
                } while (isOccupied(x, y));
            }
            robot->setX(x);
            robot->setY(y);
            pushBackRobot(robot);
        }
    }
};

Battlefield *Battlefield::instance_ = nullptr;

// RoboCop action methods
void RoboCop::actionLook(Battlefield *battlefield, ofstream &outputFile)
{
    cout << "RoboCop " << id_ << " looking around:\n";
    outputFile << "RoboCop " << id_ << " looking around:\n";
    battlefield->printLookArea(robotPositionX, robotPositionY, cout);
    battlefield->printLookArea(robotPositionX, robotPositionY, outputFile);
}

void RoboCop::actionMove(Battlefield *battlefield, ofstream &outputFile)
{
    while (true)
    {
        // Generate a random direction
        int direction = rand() % 8;

        // Define possible directions (pairs of x, y offsets)
        static const pair<int, int> directions[] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

        // Calculate new position based on the random direction
        int newX = robotPositionX + directions[direction].first;
        int newY = robotPositionY + directions[direction].second;

        // Check if the new position is within the grid boundaries and unoccupied
        if (newX >= 0 && newX < battlefield->BTF_NUM_OF_COLS() &&
            newY >= 0 && newY < battlefield->BTF_NUM_OF_ROWS() &&
            !battlefield->isOccupied(newX, newY) &&
            (newX != robotPositionX || newY != robotPositionY))
        {

            // Move the robot to the new position
            battlefield->moveRobot(this, newX, newY);

            // Output the new position
            cout << "RoboCop " << id_ << " moved to (" << newX << ", " << newY << ")\n";
            outputFile << "RoboCop " << id_ << " moved to (" << newX << ", " << newY << ")\n";
            break; // Exit the loop after successful move
        }
    }
}

void RoboCop::actionFire(Battlefield *battlefield, ofstream &outputFile)
{
    int shots = 3;              // Number of shots RoboCop can fire
    const int maxDistance = 10; // Maximum distance RoboCop can fire
    int tempX, tempY;

    for (int i = 0; i < shots; ++i)
    {
        int distance = 0;
        int distanceX = 0;
        int distanceY = 0;

        do
        {
            distanceX = rand() % 21 - 10;
            distanceY = rand() % 21 - 10;
            distance = abs(distanceX) + abs(distanceY);
            tempX = distanceX + robotPositionX;
            tempY = distanceY + robotPositionY;
        } while (
            distance < 1 || distance > maxDistance ||
            tempX < 0 || tempX >= battlefield->BTF_NUM_OF_COLS() ||
            tempY < 0 || tempY >= battlefield->BTF_NUM_OF_ROWS());

        cout << id_ << " fires at (" << tempX << ", " << tempY << ")" << endl;
        outputFile << id_ << " fires at (" << tempX << ", " << tempY << ")" << endl;
        if (battlefield->attackPosition(tempX, tempY, id_) == true)
        {
            numOfKills_++;
            cout << "Number of kills: " << numOfKills_ << '\n';
            outputFile << "Number of kills: " << numOfKills_ << '\n';
        }
        else
        {
            cout << "Number of kills: " << numOfKills_ << '\n';
            outputFile << "Number of kills: " << numOfKills_ << '\n';
        }
    }
}

void RoboCop::actions(Battlefield *battlefield, ofstream &outputFile)
{
    actionLook(battlefield, outputFile);
    actionMove(battlefield, outputFile);
    actionFire(battlefield, outputFile);
    checkForUpgrade(battlefield, outputFile);
}

// Terminator action methods
void Terminator::actionLook(Battlefield *battlefield, ofstream &outputFile)
{
    cout << "Terminator " << id_ << " looking around:\n";
    outputFile << "Terminator " << id_ << " looking around:\n";
    battlefield->printLookArea(robotPositionX, robotPositionY, cout);
    battlefield->printLookArea(robotPositionX, robotPositionY, outputFile);
}

void Terminator::actionStep(Battlefield *battlefield, ofstream &outputFile)
{
    static const pair<int, int> directions[] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
    bool attacked = false;

    // First loop to detect and attack if any adjacent cell contains a robot
    for (auto dir : directions)
    {
        int newX = robotPositionX + dir.first;
        int newY = robotPositionY + dir.second;
        if (newX >= 0 && newX < battlefield->BTF_NUM_OF_COLS() && newY >= 0 && newY < battlefield->BTF_NUM_OF_ROWS())
        {
            if (battlefield->isOccupied(newX, newY))
            {
                cout << "Terminator " << id_ << " stepped robot at (" << newX << ", " << newY << ")\n";
                outputFile << "Terminator " << id_ << " stepped robot at (" << newX << ", " << newY << ")\n";
                battlefield->attackPosition(newX, newY, id_);
                numOfKills_++;
                cout << "Number of kills: " << numOfKills_ << '\n';
                outputFile << "Number of kills: " << numOfKills_ << '\n';
                attacked = true;
                break;
            }
        }
    }

    // If no attack was made, move to a random adjacent position
    if (!attacked)
    {
        int randomIndex = rand() % 8;
        for (int i = 0; i < 8; ++i)
        {
            int index = (randomIndex + i) % 8;
            int newX = robotPositionX + directions[index].first;
            int newY = robotPositionY + directions[index].second;
            if (newX >= 0 && newX < battlefield->BTF_NUM_OF_COLS() && newY >= 0 && newY < battlefield->BTF_NUM_OF_ROWS())
            {
                battlefield->moveRobot(this, newX, newY);
                cout << "Terminator " << id_ << " stepped to (" << newX << ", " << newY << ")\n";
                outputFile << "Terminator " << id_ << " stepped to (" << newX << ", " << newY << ")\n";
                cout << "Number of kills: " << numOfKills_ << '\n';
                outputFile << "Number of kills: " << numOfKills_ << '\n';
                break;
            }
        }
    }
}

void Terminator::actions(Battlefield *battlefield, ofstream &outputFile)
{
    actionLook(battlefield, outputFile);
    actionStep(battlefield, outputFile);
    checkForUpgrade(battlefield, outputFile);
}

// TerminatorRoboCop action methods
void TerminatorRoboCop::actionLook(Battlefield *battlefield, ofstream &outputFile)
{
    cout << "TerminatorRoboCop " << id_ << " looking around:\n";
    outputFile << "TerminatorRoboCop " << id_ << " looking around:\n";
    battlefield->printLookArea(robotPositionX, robotPositionY, cout);
    battlefield->printLookArea(robotPositionX, robotPositionY, outputFile);
}

void TerminatorRoboCop::actionFire(Battlefield *battlefield, ofstream &outputFile)
{
    int shots = 3;              // Number of shots TerminatorRoboCop can fire
    const int maxDistance = 10; // Maximum distance TerminatorRoboCop can fire
    int tempX, tempY;

    for (int i = 0; i < shots; ++i)
    {
        int distance = 0;
        int distanceX = 0;
        int distanceY = 0;

        do
        {
            distanceX = rand() % 21 - 10;
            distanceY = rand() % 21 - 10;
            distance = abs(distanceX) + abs(distanceY);
            tempX = distanceX + robotPositionX;
            tempY = distanceY + robotPositionY;
        } while (
            distance < 1 || distance > maxDistance ||
            tempX < 0 || tempX >= battlefield->BTF_NUM_OF_COLS() ||
            tempY < 0 || tempY >= battlefield->BTF_NUM_OF_ROWS());

        cout << id_ << " fires at (" << tempX << ", " << tempY << ")" << endl;
        outputFile << id_ << " fires at (" << tempX << ", " << tempY << ")" << endl;
        if (battlefield->attackPosition(tempX, tempY, id_) == true)
        {
            numOfKills_++;
            cout << "Number of kills: " << numOfKills_ << '\n';
            outputFile << "Number of kills: " << numOfKills_ << '\n';
        }
        else
        {
            cout << "Number of kills: " << numOfKills_ << '\n';
            outputFile << "Number of kills: " << numOfKills_ << '\n';
        }
    }
}

void TerminatorRoboCop::actionStep(Battlefield *battlefield, ofstream &outputFile)
{
    static const pair<int, int> directions[] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
    bool attacked = false;

    // First loop to detect and attack if any adjacent cell contains a robot
    for (auto dir : directions)
    {
        int newX = robotPositionX + dir.first;
        int newY = robotPositionY + dir.second;
        if (newX >= 0 && newX < battlefield->BTF_NUM_OF_COLS() && newY >= 0 && newY < battlefield->BTF_NUM_OF_ROWS())
        {
            if (battlefield->isOccupied(newX, newY))
            {
                cout << "TerminatorRoboCop " << id_ << " stepped robot at (" << newX << ", " << newY << ")\n";
                outputFile << "TerminatorRoboCop " << id_ << " stepped robot at (" << newX << ", " << newY << ")\n";
                battlefield->attackPosition(newX, newY, id_);
                numOfKills_++;
                cout << "Number of kills: " << numOfKills_ << '\n';
                outputFile << "Number of kills: " << numOfKills_ << '\n';
                attacked = true;
                break;
            }
        }
    }

    // If no attack was made, move to a random adjacent position
    if (!attacked)
    {
        int randomIndex = rand() % 8;
        for (int i = 0; i < 8; ++i)
        {
            int index = (randomIndex + i) % 8;
            int newX = robotPositionX + directions[index].first;
            int newY = robotPositionY + directions[index].second;
            if (newX >= 0 && newX < battlefield->BTF_NUM_OF_COLS() && newY >= 0 && newY < battlefield->BTF_NUM_OF_ROWS())
            {
                battlefield->moveRobot(this, newX, newY);
                cout << "TerminatorRoboCop " << id_ << " stepped to (" << newX << ", " << newY << ")\n";
                outputFile << "TerminatorRoboCop " << id_ << " stepped to (" << newX << ", " << newY << ")\n";
                cout << "Number of kills: " << numOfKills_ << '\n';
                outputFile << "Number of kills: " << numOfKills_ << '\n';
                break;
            }
        }
    }
}

void TerminatorRoboCop::actions(Battlefield *battlefield, ofstream &outputFile)
{
    actionLook(battlefield, outputFile);
    actionFire(battlefield, outputFile);
    actionStep(battlefield, outputFile);
    checkForUpgrade(battlefield, outputFile);
}

// BlueThunder action methods
void BlueThunder::actionFire(Battlefield *battlefield, ofstream &outputFile)
{
    int x = robotPositionX;
    int y = robotPositionY;
    static const pair<int, int> directions[] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
    int targetX = x + directions[fireDirection_].first;
    int targetY = y + directions[fireDirection_].second;
    cout << id_ << " fires at (" << targetX << ", " << targetY << ")" << endl;
    outputFile << id_ << " fires at (" << targetX << ", " << targetY << ")" << endl;
    if (battlefield->attackPosition(targetX, targetY, id_) == true)
    {
        numOfKills_++;
        cout << "Number of kills: " << numOfKills_ << '\n';
        outputFile << "Number of kills: " << numOfKills_ << '\n';
    }
    else
    {
        cout << "Number of kills: " << numOfKills_ << '\n';
        outputFile << "Number of kills: " << numOfKills_ << '\n';
    }
    fireDirection_ = (fireDirection_ + 1) % 8;
}

void BlueThunder::actions(Battlefield *battlefield, ofstream &outputFile)
{
    actionFire(battlefield, outputFile);
}

// Madbot action methods
void Madbot::actionFire(Battlefield *battlefield, ofstream &outputFile)
{
    int x = robotPositionX;
    int y = robotPositionY;
    int dir = rand() % 8;
    static const pair<int, int> directions[] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
    int targetX = x + directions[dir].first;
    int targetY = y + directions[dir].second;
    cout << id_ << " randomly fires at (" << targetX << ", " << targetY << ")" << endl;
    outputFile << id_ << " randomly fires at (" << targetX << ", " << targetY << ")" << endl;
    if (battlefield->attackPosition(targetX, targetY, id_) == true)
    {
        numOfKills_++;
        cout << "Number of kills: " << numOfKills_ << '\n';
        outputFile << "Number of kills: " << numOfKills_ << '\n';
    }
    else
    {
        cout << "Number of kills: " << numOfKills_ << '\n';
        outputFile << "Number of kills: " << numOfKills_ << '\n';
    }
}

void Madbot::actions(Battlefield *battlefield, ofstream &outputFile)
{
    actionFire(battlefield, outputFile);
    checkForUpgrade(battlefield, outputFile);
}

// RoboTank action methods
void RoboTank::actionFire(Battlefield *battlefield, ofstream &outputFile)
{
    int targetX = rand() % battlefield->BTF_NUM_OF_COLS();
    int targetY = rand() % battlefield->BTF_NUM_OF_ROWS();

    // Add logic to not shoot itself
    cout << id_ << " fires across the battlefield at (" << targetX << ", " << targetY << ")" << endl;
    outputFile << id_ << " fires across the battlefield at (" << targetX << ", " << targetY << ")" << endl;
    if (battlefield->attackPosition(targetX, targetY, id_) == true)
    {
        numOfKills_++;
        cout << "Number of kills: " << numOfKills_ << '\n';
        outputFile << "Number of kills: " << numOfKills_ << '\n';
    }
    else
    {
        cout << "Number of kills: " << numOfKills_ << '\n';
        outputFile << "Number of kills: " << numOfKills_ << '\n';
    }
}

void RoboTank::actions(Battlefield *battlefield, ofstream &outputFile)
{
    actionFire(battlefield, outputFile);
    checkForUpgrade(battlefield, outputFile);
}

// UltimateRobot action methods
void UltimateRobot::actionLook(Battlefield *battlefield, ofstream &outputFile)
{
    cout << "UltimateRobot " << id_ << " looking around:\n";
    outputFile << "UltimateRobot " << id_ << " looking around:\n";
    battlefield->printLookArea(robotPositionX, robotPositionY, cout);
    battlefield->printLookArea(robotPositionX, robotPositionY, outputFile);
}

void UltimateRobot::actionMove(Battlefield *battlefield, ofstream &outputFile)
{
    static const pair<int, int> directions[] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
    bool attacked = false;

    // First loop to detect and attack if any adjacent cell contains a robot
    for (auto dir : directions)
    {
        int newX = robotPositionX + dir.first;
        int newY = robotPositionY + dir.second;
        if (newX >= 0 && newX < battlefield->BTF_NUM_OF_COLS() && newY >= 0 && newY < battlefield->BTF_NUM_OF_ROWS())
        {
            if (battlefield->isOccupied(newX, newY))
            {
                battlefield->attackPosition(newX, newY, id_);
                cout << "UltimateRobot " << id_ << " stepped robot at (" << newX << ", " << newY << ")\n";
                outputFile << "UltimateRobot " << id_ << " stepped robot at (" << newX << ", " << newY << ")\n";
                numOfKills_++;
                attacked = true;
                cout << "Number of kills: " << numOfKills_ << '\n';
                outputFile << "Number of kills: " << numOfKills_ << '\n';
                break;
            }
        }
    }

    // If no attack was made, move to a random adjacent position
    if (!attacked)
    {
        int randomIndex = rand() % 8;
        for (int i = 0; i < 8; ++i)
        {
            int index = (randomIndex + i) % 8;
            int newX = robotPositionX + directions[index].first;
            int newY = robotPositionY + directions[index].second;
            if (newX >= 0 && newX < battlefield->BTF_NUM_OF_COLS() && newY >= 0 && newY < battlefield->BTF_NUM_OF_ROWS())
            {
                battlefield->moveRobot(this, newX, newY);
                cout << "UltimateRobot " << id_ << " stepped to (" << newX << ", " << newY << ")\n";
                outputFile << "UltimateRobot " << id_ << " stepped to (" << newX << ", " << newY << ")\n";
                cout << "Number of kills: " << numOfKills_ << '\n';
                outputFile << "Number of kills: " << numOfKills_ << '\n';
                break;
            }
        }
    }
}

void UltimateRobot::actionFire(Battlefield *battlefield, ofstream &outputFile)
{
    int shots = 3; // Number of shots UltimateRobot can fire
    int tempX, tempY;

    for (int i = 0; i < shots; ++i)
    {
        int distanceX = 0;
        int distanceY = 0;

        do
        {
            distanceX = rand() % 21 - 10;
            distanceY = rand() % 21 - 10;
            tempX = distanceX + robotPositionX;
            tempY = distanceY + robotPositionY;
        } while (
            abs(distanceX) + abs(distanceY) < 1 ||
            tempX < 0 || tempX >= battlefield->BTF_NUM_OF_COLS() ||
            tempY < 0 || tempY >= battlefield->BTF_NUM_OF_ROWS());

        cout << id_ << " fires at (" << tempX << ", " << tempY << ")" << endl;
        outputFile << id_ << " fires at (" << tempX << ", " << tempY << ")" << endl;
        if (battlefield->attackPosition(tempX, tempY, id_) == true)
        {
            numOfKills_++;
            cout << "Number of kills: " << numOfKills_ << '\n';
            outputFile << "Number of kills: " << numOfKills_ << '\n';
        }
        else
        {
            cout << "Number of kills: " << numOfKills_ << '\n';
            outputFile << "Number of kills: " << numOfKills_ << '\n';
        }
    }
}

void UltimateRobot::actionStep(Battlefield *battlefield, ofstream &outputFile)
{
    static const pair<int, int> directions[] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
    bool attacked = false;

    // First loop to detect and attack if any adjacent cell contains a robot
    for (auto dir : directions)
    {
        int newX = robotPositionX + dir.first;
        int newY = robotPositionY + dir.second;
        if (newX >= 0 && newX < battlefield->BTF_NUM_OF_COLS() && newY >= 0 && newY < battlefield->BTF_NUM_OF_ROWS())
        {
            if (battlefield->isOccupied(newX, newY))
            {
                cout << "UltimateRobot " << id_ << " stepped robot at (" << newX << ", " << newY << ")\n";
                outputFile << "UltimateRobot " << id_ << " stepped robot at (" << newX << ", " << newY << ")\n";
                battlefield->attackPosition(newX, newY, id_);
                numOfKills_++;
                cout << "Number of kills: " << numOfKills_ << '\n';
                outputFile << "Number of kills: " << numOfKills_ << '\n';
                attacked = true;
                break;
            }
        }
    }

    // If no attack was made, move to a random adjacent position
    if (!attacked)
    {
        int randomIndex = rand() % 8;
        for (int i = 0; i < 8; ++i)
        {
            int index = (randomIndex + i) % 8;
            int newX = robotPositionX + directions[index].first;
            int newY = robotPositionY + directions[index].second;
            if (newX >= 0 && newX < battlefield->BTF_NUM_OF_COLS() && newY >= 0 && newY < battlefield->BTF_NUM_OF_ROWS())
            {
                battlefield->moveRobot(this, newX, newY);
                cout << "UltimateRobot " << id_ << " stepped to (" << newX << ", " << newY << ")\n";
                outputFile << "UltimateRobot " << id_ << " stepped to (" << newX << ", " << newY << ")\n";
                cout << "Number of kills: " << numOfKills_ << '\n';
                outputFile << "Number of kills: " << numOfKills_ << '\n';
                break;
            }
        }
    }
}

// Perform all actions (look, move, fire, step) on the battlefield
void UltimateRobot::actions(Battlefield *battlefield, ofstream &outputFile)
{
    actionLook(battlefield, outputFile); // UltimateRobot looks around
    actionMove(battlefield, outputFile); // UltimateRobot moves to a new position
    actionFire(battlefield, outputFile); // UltimateRobot fires at targets
    actionStep(battlefield, outputFile); // UltimateRobot steps to adjacent cells
}

// TeleportRobot action methods
void TeleportRobot::actionTP(Battlefield *battlefield, ofstream &outputFile)
{
    int distanceX = 0;
    int distanceY = 0;
    int tempX, tempY;

    // Generate a random position to teleport to
    do
    {
        distanceX = rand() % 21 - 10;
        distanceY = rand() % 21 - 10;
        tempX = distanceX + robotPositionX;
        tempY = distanceY + robotPositionY;
    } while (
        abs(distanceX) + abs(distanceY) < 1 ||
        tempX < 0 || tempX >= battlefield->BTF_NUM_OF_COLS() ||
        tempY < 0 || tempY >= battlefield->BTF_NUM_OF_ROWS());

    int targetX = rand() % battlefield->BTF_NUM_OF_COLS();
    int targetY = rand() % battlefield->BTF_NUM_OF_ROWS();

    cout << id_ << " teleported across the battlefield at (" << targetX << ", " << targetY << ")" << endl;
    outputFile << id_ << " teleported across the battlefield at (" << targetX << ", " << targetY << ")" << endl;
    if (battlefield->attackPosition(tempX, tempY, id_) == true)
    {
        numOfKills_++;
        cout << "Number of kills: " << numOfKills_ << '\n';
        outputFile << "Number of kills: " << numOfKills_ << '\n';
    }
    else
    {
        cout << "Number of kills: " << numOfKills_ << '\n';
        outputFile << "Number of kills: " << numOfKills_ << '\n';
    }
    battlefield->moveRobot(this, targetX, targetY);
}

void TeleportRobot::actions(Battlefield *battlefield, ofstream &outputFile)
{
    actionTP(battlefield, outputFile);        // TeleportRobot teleports to a new location
    checkForUpgrade(battlefield, outputFile); // Check if TeleportRobot can be upgraded
}

// BomberBot action methods
void BomberBot::actionBomb(Battlefield *battlefield, ofstream &outputFile)
{
    int shots = 1;             // Number of bombs BomberBot can throw
    const int maxDistance = 6; // Maximum distance BomberBot can throw
    int tempX, tempY;

    // Loop to handle the number of bombs thrown
    for (int i = 0; i < shots; ++i)
    {
        int distanceX = 0;
        int distanceY = 0;

        // Generate a random position to bomb
        do
        {
            distanceX = rand() % 21 - 10;
            distanceY = rand() % 21 - 10;
            tempX = distanceX + robotPositionX;
            tempY = distanceY + robotPositionY;
        } while (
            abs(distanceX) + abs(distanceY) < 1 || abs(distanceX) + abs(distanceY) > maxDistance ||
            tempX < 0 || tempX >= battlefield->BTF_NUM_OF_COLS() ||
            tempY < 0 || tempY >= battlefield->BTF_NUM_OF_ROWS());

        cout << id_ << " fires at (" << tempX << ", " << tempY << ")" << endl;
        outputFile << id_ << " fires at (" << tempX << ", " << tempY << ")" << endl;
        if (battlefield->attackPosition(tempX, tempY, id_))
        {
            numOfKills_++;
        }

        // Attack surrounding positions
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (dx == 0 && dy == 0)
                    continue;

                int surroundingX = tempX + dx;
                int surroundingY = tempY + dy;

                if (surroundingX >= 0 && surroundingX < battlefield->BTF_NUM_OF_COLS() &&
                    surroundingY >= 0 && surroundingY < battlefield->BTF_NUM_OF_ROWS())
                {
                    cout << id_ << " also attacks surrounding position (" << surroundingX << ", " << surroundingY << ")" << endl;
                    outputFile << id_ << " also attacks surrounding position (" << surroundingX << ", " << surroundingY << ")" << endl;
                    if (battlefield->attackPosition(surroundingX, surroundingY, id_))
                    {
                        numOfKills_++;
                    }
                }
            }
        }

        cout << "Number of kills: " << numOfKills_ << '\n';
        outputFile << "Number of kills: " << numOfKills_ << '\n';
    }
}

void BomberBot::actions(Battlefield *battlefield, ofstream &outputFile)
{
    actionBomb(battlefield, outputFile); // BomberBot throws bombs on the battlefield
}

// LaserBot action methods
void LaserBot::actionLaser(Battlefield *battlefield, ofstream &outputFile)
{
    int tempX, tempY;

    // Fire a laser across the row from the current position
    for (int i = robotPositionX - 1; i >= 0; i--)
    {
        tempX = i;
        tempY = robotPositionY;
        if (battlefield->attackPosition(tempX, tempY, id_))
        {
            numOfKills_++;
        }
    }

    cout << id_ << " fires from (" << robotPositionX << ", " << tempY << ") to (" << tempX << ", " << tempY << ")" << endl;
    outputFile << id_ << " fires from (" << robotPositionX << ", " << tempY << ") to (" << tempX << ", " << tempY << ")" << endl;
    cout << "Number of kills: " << numOfKills_ << '\n';
    outputFile << "Number of kills: " << numOfKills_ << '\n';
}

void LaserBot::actions(Battlefield *battlefield, ofstream &outputFile)
{
    actionLaser(battlefield, outputFile); // LaserBot fires its laser
}

// Implementing checkForUpgrade method for the Robot class
void Robot::checkForUpgrade(Battlefield *battlefield, ofstream &outputFile)
{
    if (numOfKills_ == 3)
    {
        string newType, newId;

        // Determine the new type and ID for the upgraded robot
        if (robotType_ == "RoboCop")
        {
            newType = "TerminatorRoboCop";
            int count = ++battlefield->terminatorRoboCopCount_;
            newId = (count < 10) ? "TR0" + to_string(count) : "TR" + to_string(count);
        }
        else if (robotType_ == "Terminator")
        {
            newType = "TerminatorRoboCop";
            int count = ++battlefield->terminatorRoboCopCount_;
            newId = (count < 10) ? "TR0" + to_string(count) : "TR" + to_string(count);
        }
        else if (robotType_ == "BlueThunder")
        {
            newType = "Madbot";
            int count = ++battlefield->madbotCount_;
            newId = (count < 10) ? "MB0" + to_string(count) : "MB" + to_string(count);
        }
        else if (robotType_ == "Madbot")
        {
            newType = "RoboTank";
            int count = ++battlefield->roboTankCount_;
            newId = (count < 10) ? "RT0" + to_string(count) : "RT" + to_string(count);
        }
        else if (robotType_ == "RoboTank")
        {
            newType = "UltimateRobot";
            int count = ++battlefield->ultimateRobotCount_;
            newId = (count < 10) ? "UR0" + to_string(count) : "UR" + to_string(count);
        }
        else if (robotType_ == "TerminatorRoboCop")
        {
            newType = "UltimateRobot";
            int count = ++battlefield->ultimateRobotCount_;
            newId = (count < 10) ? "UR0" + to_string(count) : "UR" + to_string(count);
        }
        else
        {
            return;
        }

        // Remove the old robot and add the upgraded robot
        battlefield->eraseRobotById(id_);

        Robot *upgradedRobot = nullptr;
        if (newType == "TerminatorRoboCop")
        {
            upgradedRobot = new TerminatorRoboCop(newId, robotPositionX, robotPositionY);
        }
        else if (newType == "Madbot")
        {
            upgradedRobot = new Madbot(newId, robotPositionX, robotPositionY);
        }
        else if (newType == "RoboTank")
        {
            upgradedRobot = new RoboTank(newId, robotPositionX, robotPositionY);
        }
        else if (newType == "UltimateRobot")
        {
            upgradedRobot = new UltimateRobot(newId, robotPositionX, robotPositionY);
        }

        battlefield->pushBackRobot(upgradedRobot);

        cout << robotType_ << " upgraded to " << newType << " with ID " << newId << endl;
        outputFile << robotType_ << " upgraded to " << newType << " with ID " << newId << endl;
        numOfKills_ = 0; // reset kill counter
    }
}

// Main function to start the simulation
int main()
{
    Battlefield *battlefield = Battlefield::getInstance();

    string filename = "input.txt";
    cout << "Read " << filename << ":\n";
    battlefield->readFile(filename); // Initialize battlefield from input file
    cout << endl;

    ofstream outputFile("output.txt");
    if (!outputFile)
    {
        cerr << "Error opening output.txt file for writing!" << endl;
        return 1; // Exit with error code
    }

    outputFile << "------------------------ Display starting grid ------------------------\n"
               << endl;
    battlefield->displayBTF(cout); // Display the initial state of the battlefield
    battlefield->displayBTF(outputFile);

    outputFile << "\n";
    battlefield->runRobotActions(outputFile); // Run the simulation
    for (auto robot : battlefield->getRobots())
    {
        outputFile << "Robot " << robot->id() << " has " << robot->getNumOfKills() << " kills." << endl;
    }

    // Close the file stream
    outputFile.close();

    return 0;
}
