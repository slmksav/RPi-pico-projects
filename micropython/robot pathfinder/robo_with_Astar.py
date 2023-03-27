from AutonomousRobotics import PicoRobot
from time import sleep_ms

robo = PicoRobot()
startStop = False

# 0 = free space, 1 = obstacle
environment = [
    [0, 0, 0, 0, 0],
    [0, 1, 1, 1, 0],
    [0, 1, 0, 0, 0],
    [0, 0, 0, 1, 0],
    [0, 0, 0, 0, 0]
]

# the start and goal positions
start_pos = (0, 0)
goal_pos = (4, 4)

# calculate the heuristic cost
def heuristic_cost(pos):
    return abs(pos[0] - goal_pos[0]) + abs(pos[1] - goal_pos[1])

def cost_to_reach(parent_pos, pos):
    return 1  # all moves cost the same, no calculations made

# function to get ALL the neighbors of a particular node
def get_neighbors(pos):
    neighbors = []
    if pos[0] > 0 and environment[pos[0]-1][pos[1]] == 0:
        neighbors.append((pos[0]-1, pos[1]))
    if pos[0] < len(environment)-1 and environment[pos[0]+1][pos[1]] == 0:
        neighbors.append((pos[0]+1, pos[1]))
    if pos[1] > 0 and environment[pos[0]][pos[1]-1] == 0:
        neighbors.append((pos[0], pos[1]-1))
    if pos[1] < len(environment[0])-1 and environment[pos[0]][pos[1]+1] == 0:
        neighbors.append((pos[0], pos[1]+1))
    return neighbors

# Define a function to perform the A* algorithm
def A_star(start_pos, goal_pos):
    open_set = {start_pos}
    closed_set = set()
    g_score = {start_pos: 0}
    f_score = {start_pos: heuristic_cost(start_pos)}

    while open_set:
        current_pos = min(open_set, key=lambda pos: f_score[pos])
        if current_pos == goal_pos:
            return True  # goal reached

        open_set.remove(current_pos)
        closed_set.add(current_pos)

        for neighbor_pos in get_neighbors(current_pos):
            if neighbor_pos in closed_set:
                continue  # ignores all nodes evaluated in closed set so we wont go back

            tentative_g_score = g_score[current_pos] + cost_to_reach(current_pos, neighbor_pos)

            if neighbor_pos not in open_set:
                open_set.add(neighbor_pos)
            elif tentative_g_score >= g_score[neighbor_pos]:
                continue  # the current path is not better in terms of cost than the previous one

            # the best path found, calculate the F(n) score	
            g_score[neighbor_pos] = tentative_g_score
            f_score[neighbor_pos] = g_score[neighbor_pos] + heuristic_cost(neighbor_pos)


def get_path(start_pos, goal_pos):
    if A_star(start_pos, goal_pos):
        current_pos = goal_pos
        path = [current_pos]
        while current_pos != start_pos:
            current_pos = min(get_neighbors(current_pos), key=lambda pos: g_score[pos])
            path.append(current_pos)
            path.reverse()
            return path
    else:
        return None

robo.button.irq(trigger=machine.Pin.IRQ_RISING, handler=ButtonIRQHandler)

robo.setLED(0,robo.PURPLE)
robo.setLED(1,robo.PURPLE)
robo.setLED(2,robo.PURPLE)
robo.setLED(3,robo.PURPLE)
robo.show()

while True:
    if startStop == True:
        rearDistance = robo.getDistance("r")
        # only one of the ultrasonic sensors work, so rear is actually the front, but didn't rename it
        if rearDistance > 15:
            # all clear so speedd
            robo.setLED(0, robo.GREEN)
            robo.setLED(1, robo.GREEN)
            robo.setLED(2, robo.GREEN)
            robo.setLED(3, robo.GREEN)
            robo.motorOn("l", "f", 85)
            robo.motorOn("r", "f", 85)
        elif rearDistance > 5:
            # calculate path and reverse gears
            robo.setLED(0, robo.BLUE)
            robo.setLED(1, robo.BLUE)
            robo.setLED(2, robo.BLUE)
            robo.setLED(3, robo.BLUE)
            robo.motorOff("l")
            robo.motorOff("r")
            path = get_path(start_pos, goal_pos)
            if path is not None and len(path) > 1:
                next_pos = path[1]
                if next_pos[0] < start_pos[0]:
                    # turn left
                    robo.motorOn("l", "r", 100)
                    robo.motorOn("r", "f", 85)
                elif next_pos[0] > start_pos[0]:
                    # turn right
                    robo.motorOn("l", "f", 85)
                    robo.motorOn("r", "r", 100)
                elif next_pos[1] < start_pos[1]:
                    # turn left
                    robo.motorOn("l", "r", 100)
                    robo.motorOn("r", "f", 85)
                elif next_pos[1] > start_pos[1]:
                    # turn right
                    robo.motorOn("l", "f", 85)
                    robo.motorOn("r", "r", 100)
                start_pos = next_pos
            else:
                # spin on the spot
                robo.setLED(0, robo.YELLOW)
                robo.setLED(1, robo.YELLOW)
                robo.setLED(2, robo.YELLOW)
                robo.setLED(3, robo.YELLOW)
                robo.motorOn("l", "f", 100)
                robo.motorOn("r", "r", 100)
        else: # spin on the spot otherwise
                robo.setLED(0,robo.RED)
                robo.setLED(1,robo.RED)
                robo.setLED(2,robo.RED)
                robo.setLED(3,robo.RED)
                robo.motorOn("l","r",100)
                robo.motorOn("r","f",100)
        robo.show()
    else:  # motors  off
            robo.motorOff("l")
            robo.motorOff("r")
            robo.setLED(0,robo.PURPLE)
            robo.setLED(1,robo.PURPLE)
            robo.setLED(2,robo.PURPLE)
            robo.setLED(3,robo.PURPLE)
            robo.show()
    sleep_ms(50)