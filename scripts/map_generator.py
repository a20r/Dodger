
import pygame
import sys

OBSTACLE_COLOR = (255, 0, 0)
BACKGROUND_COLOR = (200, 200, 200)
GOAL_COLOR = (255, 0, 255)
START_COLOR = (0, 0, 255)
ROBOT_COLOR = (0, 0, 255)


def draw_circle(screen, point, is_goal):
    if is_goal:
        pygame.draw.circle(screen, GOAL_COLOR, point, 30, 3)
    else:
        pygame.draw.circle(screen, START_COLOR, point, 30, 3)


def draw_polygon(screen, point_list, color, currently_working):
    if len(point_list) == 1:
        pygame.draw.circle(screen, color, point_list[0], 3)
    elif len(point_list) == 2:
        pygame.draw.line(screen, color, point_list[0], point_list[1], 3)
    elif len(point_list) == 0:
        return
    else:
        if currently_working:
            pygame.draw.lines(screen, color, False, point_list, 3)
        else:
            pygame.draw.polygon(screen, color, point_list)


def start(width, height, filename):
    pygame.display.init()
    screen = pygame.display.set_mode((width, height))
    screen.fill(BACKGROUND_COLOR)
    done = False

    obstacle_list = list()
    current_obstacle = list()
    robot = list()

    start_point = [0, 0]
    end_point = [width, height]

    editing_obstacles = True

    while not done:

        screen.fill(BACKGROUND_COLOR)
        for obstacle in obstacle_list:
            draw_polygon(screen, obstacle, OBSTACLE_COLOR, False)
        draw_circle(screen, start_point, False)
        draw_circle(screen, end_point, True)
        draw_polygon(screen, current_obstacle, OBSTACLE_COLOR,
                     editing_obstacles)
        draw_polygon(screen, robot, ROBOT_COLOR, not editing_obstacles)

        event_list = pygame.event.get()
        for event in event_list:
            if event.type == pygame.MOUSEBUTTONUP:

                pos = pygame.mouse.get_pos()

                if pygame.key.get_pressed()[pygame.K_s]:
                    start_point = pos
                elif pygame.key.get_pressed()[pygame.K_g]:
                    end_point = pos
                elif not editing_obstacles:
                    robot.append(pos)
                elif editing_obstacles:
                    current_obstacle.append(pos)

            elif event.type == pygame.KEYUP:

                if event.key == pygame.K_e:
                    obstacle_list.append(current_obstacle)

                    current_obstacle = list()

                elif event.key == pygame.K_w:
                    pygame.display.set_caption("Writing to " + filename)
                    to_cpp(
                        width, height,
                        obstacle_list,
                        robot,
                        start_point,
                        end_point,
                        filename
                    )
                elif event.key == pygame.K_o:
                    editing_obstacles = True
                elif event.key == pygame.K_r:
                    editing_obstacles = False

            elif event.type == pygame.QUIT:
                to_cpp(
                    width, height,
                    obstacle_list,
                    robot,
                    start_point,
                    end_point,
                    filename)
                exit()

        pygame.display.flip()


def to_cpp(width, height, obstacle_list, robot, start_pos, goal_pos, filename):
    with open(filename, "w") as f:
        f.write("#include <vector>\n")
        f.write("using namespace std;\n")
        f.write("class ObstaclesInstance {};\n")


if __name__ == "__main__":
    if len(sys.argv) == 4:
        start(int(sys.argv[1]), int(sys.argv[2]), sys.argv[3])
    else:
        raise Exception("Not enough command line arguments given")
