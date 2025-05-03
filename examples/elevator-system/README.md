# Elevator System Design

## Follow-up Questions and Answers

### Question 1: How does your system handle multiple external requests to the same floor?

#### Current Implementation
- Each elevator maintains a `set<int> requests`, which automatically eliminates duplicate requests to the same floor
- If multiple external requests are made for floor 3 (either up or down), and they're assigned to the same elevator, that floor is added only once to the elevator's request set

#### Limitation
- We are not distinguishing between UP and DOWN requests from a floor

#### Improvement Suggestions
1. Use a `map<int, set<Direction>>` to track both floor and direction
2. Prioritize stops based on current elevator direction and pending requests

### Question 2: What happens if multiple elevators are idle? How do you choose which one to send?

#### Current Behavior
```cpp
if (elevators[i].isIdle()) {
    int dist = abs(elevators[i].getCurrentFloor() - floor);
    if (dist < minDist) {
        minDist = dist;
        bestIdx = i;
    }
}
```
- We choose the closest idle elevator to the requested floor
- If multiple elevators are equally close, the first one found in the loop is selected

#### Limitations
- Not optimal if elevators are equidistant — there's no tiebreaker
- Doesn't consider future load (e.g., one elevator might be closer, but about to receive more internal requests)
- Hardcoded fallback to elevator 0 if none are idle

#### Better Approach
Add a priority mechanism:
- Favor idle elevators closer to the direction of the request
- Consider elevator load (how many pending requests)
- Assign weights based on current state, distance, and request direction

Example Scheduler Implementation:
```cpp
class Scheduler {
public:
    static int calculateScore(const Elevator& e, int requestFloor, Direction requestDir) {
        int score = 0;

        if (!e.isIdle()) {
            score += 1000; // Penalize moving elevators
        }

        int floorDiff = abs(e.getCurrentFloor() - requestFloor);
        score += floorDiff;

        // Penalize direction mismatch
        if (e.getDirection() != Direction::IDLE && e.getDirection() != requestDir) {
            score += 500;
        }

        return score;
    }

    static int selectElevator(const vector<Elevator>& elevators, int requestFloor, Direction requestDir) {
        int bestScore = INT_MAX;
        int bestIdx = 0;

        for (int i = 0; i < elevators.size(); ++i) {
            int score = calculateScore(elevators[i], requestFloor, requestDir);
            if (score < bestScore) {
                bestScore = score;
                bestIdx = i;
            }
        }

        return bestIdx;
    }
};
```

### Question 3: If an elevator is going UP, should it stop for DOWN requests along the way?

#### Short Answer
No, a well-designed elevator should not stop for DOWN requests while going UP, because:
- It breaks directional consistency
- It causes unnecessary delays for current passengers
- It creates poor user experience

#### Ideal Behavior
When an elevator is going UP, it should only stop at:
- Internal UP requests
- External UP calls on floors above it
- Once it finishes all UP requests, it can reverse direction and handle DOWN requests

This is how real elevators behave — it's called the "SCAN algorithm" (like in disk scheduling), which serves requests in one direction first, then reverses.

### Question 4: Class Responsibilities

#### 1. ElevatorSystem
- Manages the entire building's elevators and incoming requests
- Receives external requests from floors
- Forwards them to the Scheduler to choose the best elevator
- Can forward internal requests to a specific elevator
- Orchestrates the simulation steps for all elevators

#### 2. Elevator
- Controls the behavior and state of one physical elevator
- Tracks:
  - Current floor
  - Direction
  - State (moving/open/idle)
  - Separate up/down requests
- Moves one step at a time (step()), decides whether to stop, switch direction, etc.
- Exposes methods to add new requests and print its current state

#### 3. Scheduler
- Selects the most appropriate elevator for a request based on a scoring heuristic
- Uses custom scoring logic to factor:
  - Proximity
  - Direction alignment
  - Load/state
- Allows this logic to evolve independently (clean separation of concerns)

#### 4. Request (optional)
- Encapsulates an external floor request (floor + direction)
- Helps clarify the interface between ElevatorSystem and Scheduler
- Could be extended to include timestamp, priority, etc.

#### 5. Enums: Direction and ElevatorState
- Improve readability and reduce magic values
- Direction helps guide movement logic (UP, DOWN, IDLE)
- ElevatorState can be extended to simulate door open/close, maintenance mode, etc.

### Question 6: Data Structure Choices

#### Why set<int> for requests?
- Automatic sorting of floor requests (ascending order)
- No duplicate floor requests
- Efficient lookup/removal with O(log n) time

#### Alternative Data Structures

| Data Structure | When to Use |
|----------------|-------------|
| priority_queue<int> | When you need custom sort logic (e.g., by priority, direction) |
| queue<int> | When you want to preserve request order (e.g., FIFO internal requests) |
| map<int, Direction> | When you want to track both floor and direction per request |
| vector<int> + sort | If request volume is small and order only needed occasionally |
| multiset<int> | If you want to allow duplicate floor requests (not recommended for realism) |

### Question 7: Supporting 100 Elevators Across 100 Floors

#### Key Design Improvements for Scalability

1. **Efficient Scheduler**
   - Use a min-heap (priority queue) to track best elevators by score
   - Maintain an index of idle elevators by floor to reduce lookup time

2. **Sharding Requests**
   - Divide building into zones (e.g., floors 0-20 → Elevator Group A, 21-40 → Group B)
   - Each zone is managed independently to reduce scheduling complexity

3. **Lazy Evaluation**
   - Store requests in a queue and pop at runtime
   - Remove duplicate or expired requests proactively

4. **Asynchronous Step Handling**
   - Parallelize step simulation per elevator
   - Each elevator's step() can be called independently

5. **Monitoring & Logging System**
   - Add logging to monitor elevator load, wait times, performance
   - Helps optimize routing in high-volume environments

### Question 8: Handling Concurrent Requests

#### Key Concepts for Handling Concurrency

1. **Thread Safety**
   - Each elevator may run in its own thread
   - Shared Request Queue must be protected using mutex or lock_guard

2. **Producer-Consumer Model**
   - External button presses are producers of requests
   - The Scheduler is a consumer that dispatches those requests to elevators

3. **Event-Driven Elevator Loops**
   - Each elevator acts as an actor
   - Wait for requests
   - Simulate movement
   - Emit events like "floor reached" or "doors opened"

### Question 10: Handling Elevator Failure

#### Step-by-Step Design Plan

1. **Detecting Failure**
   - Add a method setOperational(bool) in Elevator
   - Maintain a flag isOperational which the scheduler can check

2. **Handling in the Scheduler**
   - Update the scheduler logic to skip elevators that are not operational

3. **Reassign Requests on Failure**
   - Collect all pending requests from failed elevator
   - Re-insert them into the global request pool or assign directly to other elevators

4. **System Alerts**
   - Define a callback/event handler to log or alert maintenance

