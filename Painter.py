import pygame

WIDTH = 256
HEIGHT = 256
FPS = 60

BLACK = (0, 0, 0, 255)
WHITE = (255, 255, 255, 255)

BRUSH_SIZE = 10
BRUSH_COUNT = 5

def PaintMidle(pos1, pos2, count):
    deltaPos = [0, 0]
    deltaPos[0] = (pos2[0] - pos1[0])/ count
    deltaPos[1] = (pos2[1] - pos1[1])/ count
    pos = [pos2[0], pos2[1]]

    for i in range(count):
        pygame.draw.rect(screen, WHITE, (pos[0] - BRUSH_SIZE/2, pos[1], BRUSH_SIZE, BRUSH_SIZE))
        pos[0]+=deltaPos[0]
        pos[1]+=deltaPos[1]


pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

running = True
painting = False
lastPos = (0, 0)

screen.fill(BLACK)

while running:

    clock.tick(FPS)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if event.type == pygame.MOUSEBUTTONDOWN:
            painting = True
            lastPos = pygame.mouse.get_pos()

        if event.type == pygame.MOUSEBUTTONUP:
            painting = False

        if event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE:
            screen.fill(BLACK)


    if painting:
        pos = pygame.mouse.get_pos()
        PaintMidle(lastPos, pos, BRUSH_COUNT)
        lastPos = pos

    pygame.display.flip()


matrix = [0]*HEIGHT
for i in range(HEIGHT):
    matrix[i] = [0]*WIDTH

for y in range(HEIGHT):
    for x in range(WIDTH):
        if screen.get_at((x, y)) == WHITE:
            matrix[y][x] = 1



for y in range(HEIGHT):
    for x in range(WIDTH):
        print(matrix[y][x], sep = '', end = '')
    print()

pygame.quit()
