#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue> 
using namespace std;

enum class Direction {
    UP,
    DOWN,
    IDLE
};

enum class ElevatorState {
    MOVING, 
    IDLE,
    OPEN
};

class Request {

public:
    int floor;
    Direction dir;

    Request(int f, Direction d)
    {
       floor = f;
       dir = d;
    }
};

class Elevator{

private:
    int id;
    int currentFloor;
    Direction direction;
    ElevatorState state;
    set<int> requests;

public:
    Elevator(int inputid)
    {
        id = inputid;
        currentFloor = 0;
        direction = Direction::IDLE;
        state = ElevatorState::IDLE;
    }

    int getID()
    {
        return id;
    } 

    int getCurrentFloor(){
        return currentFloor;
    }

    Direction getDirection(){
        return direction;
    }

    ElevatorState getElevatorState(){
        return state;
    }

    bool isIdle()
    {
        return state == ElevatorState::IDLE;
    }

    void addRequest(int floor)
    {
        requests.insert(floor);
        if(floor > currentFloor) direction = Direction::UP;
        else if(floor < currentFloor) direction = Direction::DOWN;
    }

    void step()
    {
        if(requests.empty())
        {
            direction = Direction::IDLE;
            state = ElevatorState::IDLE;
            return;
        }

        state = ElevatorState::MOVING;

        if(direction==Direction::UP) currentFloor++;
        else if(direction==Direction::DOWN) currentFloor--;

        if(requests.count(currentFloor))
        {
            cout << "Elevator" << id << "stopping at floor" << currentFloor << endl;
            requests.erase(currentFloor);
            state = ElevatorState::OPEN;
        }

    }

    void printStatus() {
        cout << "Elevator " << id << " at floor " << currentFloor << " going "
             << (direction == Direction::UP ? "UP" :
                 direction == Direction::DOWN ? "DOWN" : "IDLE") << endl;
    }

};

class ElevatorSystem {

private:
    vector<Elevator> elevators;

public:
    ElevatorSystem(int numElevators)
    {
        for(int i=0;i<numElevators;i++)
        {
            Elevator e(i);
            elevators.push_back(e);
        }
    }

    void externalRequest(int floor, Direction dir)
    {
        int baseIdx = -1;
        int minDist = INT_MAX;

        for(int i=0;i<elevators.size();i++)
        {
            if(elevators[i].isIdle())
            {
                int dist = abs(elevators[i].getCurrentFloor() - floor);

                if(dist < minDist)
                {
                    minDist = dist;
                    baseIdx = i;
                }
            }
        }

        if (baseIdx == -1) baseIdx = 0;
        elevators[baseIdx].addRequest(floor);
    }

    void internalRequest(int elevatorId, int floor) {
        elevators[elevatorId].addRequest(floor);
    }

    void stepSimulation() {
        for (int i = 0; i < elevators.size(); ++i) {
            elevators[i].step();
            elevators[i].printStatus();
        }
    }

};

int main() {
    ElevatorSystem es(2);

    es.externalRequest(3, Direction::UP);
    es.externalRequest(5, Direction::DOWN);

    for (int i = 0; i < 10; ++i) {
        es.stepSimulation();
    }

    es.internalRequest(0, 7);

    for (int i = 0; i < 10; ++i) {
        es.stepSimulation();
    }

    return 0;
}
