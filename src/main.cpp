#include <GL/glut.h>
#include <cmath>

// ===============================
// Window
// ===============================
const int WIDTH = 1000;
const int HEIGHT = 650;

// ===============================
// Character
// ===============================
float playerX = 150.0f;
float playerY = 115.0f;

bool jumping = false;
float jumpOffset = 0.0f;

// ===============================
// Animation
// ===============================
float butterflyX = 300.0f;
float butterflyY = 420.0f;

float fireflyAngle = 0.0f;
float magicAngle = 0.0f;

bool magicActivated = false;

// ===============================
// Utility Functions
// ===============================

void drawCircle(float cx, float cy, float r)
{
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(cx, cy);

    for (int i = 0; i <= 100; i++)
    {
        float angle = 2.0f * 3.14159f * i / 100.0f;

        glVertex2f(
            cx + r * cos(angle),
            cy + r * sin(angle)
        );
    }

    glEnd();
}

void drawRectangle(float x1, float y1,
                   float x2, float y2)
{
    glBegin(GL_QUADS);

    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);

    glEnd();
}

// ===============================
// Background
// ===============================

void drawSky()
{
    glColor3f(0.08f, 0.15f, 0.30f);

    drawRectangle(
        0, 250,
        WIDTH, HEIGHT
    );
}

void drawMoon()
{
    glColor3f(1.0f, 0.95f, 0.65f);

    drawCircle(820, 530, 55);

    // Small dark circle to create crescent effect
    glColor3f(0.08f, 0.15f, 0.30f);

    drawCircle(845, 550, 45);
}

void drawStars()
{
    glPointSize(3);

    glColor3f(1.0f, 1.0f, 0.8f);

    glBegin(GL_POINTS);

    glVertex2f(100, 550);
    glVertex2f(180, 500);
    glVertex2f(250, 570);
    glVertex2f(350, 520);
    glVertex2f(450, 580);
    glVertex2f(550, 510);
    glVertex2f(650, 570);
    glVertex2f(730, 500);
    glVertex2f(900, 570);
    glVertex2f(950, 480);

    glEnd();
}

// ===============================
// Ground
// ===============================

void drawGround()
{
    glColor3f(0.08f, 0.25f, 0.12f);

    drawRectangle(
        0, 0,
        WIDTH, 250
    );

    // Path
    glColor3f(0.35f, 0.25f, 0.15f);

    glBegin(GL_POLYGON);

    glVertex2f(400, 0);
    glVertex2f(600, 0);
    glVertex2f(540, 250);
    glVertex2f(460, 250);

    glEnd();
}

// ===============================
// Trees
// ===============================

void drawTree(float x, float y, float scale)
{
    // Tree trunk
    glColor3f(0.25f, 0.12f, 0.05f);

    drawRectangle(
        x - 15 * scale,
        y,
        x + 15 * scale,
        y + 130 * scale
    );

    // Leaves
    glColor3f(0.04f, 0.30f, 0.12f);

    drawCircle(
        x,
        y + 150 * scale,
        55 * scale
    );

    drawCircle(
        x - 40 * scale,
        y + 125 * scale,
        45 * scale
    );

    drawCircle(
        x + 40 * scale,
        y + 125 * scale,
        45 * scale
    );

    drawCircle(
        x,
        y + 190 * scale,
        45 * scale
    );
}

void drawForest()
{
    drawTree(80, 180, 1.0f);
    drawTree(200, 170, 0.8f);
    drawTree(330, 180, 1.1f);

    drawTree(700, 175, 1.0f);
    drawTree(830, 170, 0.85f);
    drawTree(950, 180, 1.1f);
}

// ===============================
// Character
// ===============================

void drawCharacter()
{
    float y = playerY + jumpOffset;

    // Body
    glColor3f(0.2f, 0.4f, 0.8f);

    drawRectangle(
        playerX - 18,
        y,
        playerX + 18,
        y + 55
    );

    // Head
    glColor3f(1.0f, 0.75f, 0.55f);

    drawCircle(
        playerX,
        y + 75,
        22
    );

    // Eyes
    glColor3f(0.0f, 0.0f, 0.0f);

    drawCircle(
        playerX - 7,
        y + 78,
        3
    );

    drawCircle(
        playerX + 7,
        y + 78,
        3
    );

    // Legs
    glBegin(GL_LINES);

    glVertex2f(playerX - 8, y);
    glVertex2f(playerX - 15, y - 30);

    glVertex2f(playerX + 8, y);
    glVertex2f(playerX + 15, y - 30);

    glEnd();
}

// ===============================
// Butterfly
// ===============================

void drawButterfly()
{
    glPushMatrix();

    glTranslatef(
        butterflyX,
        butterflyY,
        0
    );

    // Animated rotation
    glRotatef(
        sin(fireflyAngle) * 15,
        0,
        0,
        1
    );

    // Wings
    glColor3f(0.8f, 0.3f, 1.0f);

    drawCircle(-18, 0, 18);
    drawCircle(18, 0, 18);

    // Body
    glColor3f(0.1f, 0.05f, 0.05f);

    drawRectangle(-4, -18, 4, 18);

    glPopMatrix();
}

// ===============================
// Fireflies
// ===============================

void drawFireflies()
{
    glPointSize(6);

    glColor3f(1.0f, 0.9f, 0.2f);

    glBegin(GL_POINTS);

    float glow = sin(fireflyAngle) * 15;

    glVertex2f(250, 300 + glow);
    glVertex2f(350, 350 - glow);
    glVertex2f(650, 330 + glow);
    glVertex2f(750, 280 - glow);
    glVertex2f(880, 350 + glow);

    glEnd();
}

// ===============================
// Magic Portal
// ===============================

void drawMagicPortal()
{
    glPushMatrix();

    glTranslatef(500, 360, 0);

    // Transformation: rotation
    glRotatef(
        magicAngle,
        0,
        0,
        1
    );

    if (magicActivated)
        glColor3f(0.8f, 0.2f, 1.0f);
    else
        glColor3f(0.3f, 0.1f, 0.5f);

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 100; i++)
    {
        float angle =
            2.0f * 3.14159f * i / 100.0f;

        float r = magicActivated
                      ? 70.0f
                      : 50.0f;

        glVertex2f(
            r * cos(angle),
            r * sin(angle)
        );
    }

    glEnd();

    // Inner portal
    if (magicActivated)
    {
        glColor3f(0.2f, 0.7f, 1.0f);

        drawCircle(
            0,
            0,
            35
        );
    }

    glPopMatrix();
}

// ===============================
// Display
// ===============================

void display()
{
    glClear(
        GL_COLOR_BUFFER_BIT
    );

    drawSky();
    drawStars();
    drawMoon();

    drawGround();
    drawForest();

    drawMagicPortal();

    drawFireflies();
    drawButterfly();

    drawCharacter();

    glutSwapBuffers();
}

// ===============================
// Keyboard
// ===============================

void keyboard(
    unsigned char key,
    int x,
    int y
)
{
    switch (key)
    {
        case 'a':
        case 'A':

            playerX -= 15;

            break;

        case 'd':
        case 'D':

            playerX += 15;

            break;

        case 'w':
        case 'W':

            if (!jumping)
            {
                jumping = true;
            }

            break;

        case ' ':

            // Activate magical portal
            if (fabs(playerX - 500) < 150)
            {
                magicActivated = true;
            }

            break;

        case 'r':
        case 'R':

            playerX = 150;

            magicActivated = false;

            break;

        case 27:

            exit(0);
    }

    // Keep character inside screen
    if (playerX < 30)
        playerX = 30;

    if (playerX > WIDTH - 30)
        playerX = WIDTH - 30;

    glutPostRedisplay();
}

// ===============================
// Animation Timer
// ===============================

void update(int value)
{
    fireflyAngle += 0.08f;

    magicAngle += 2.0f;

    // Butterfly movement
    butterflyX += 1.5f;

    butterflyY =
        420.0f +
        sin(fireflyAngle) * 40.0f;

    if (butterflyX > WIDTH + 50)
        butterflyX = -50;

    // Jump animation
    if (jumping)
    {
        jumpOffset += 8;

        if (jumpOffset >= 80)
        {
            jumping = false;
        }
    }
    else if (jumpOffset > 0)
    {
        jumpOffset -= 8;
    }

    glutPostRedisplay();

    glutTimerFunc(
        30,
        update,
        0
    );
}

// ===============================
// Initialization
// ===============================

void init()
{
    glClearColor(
        0.05f,
        0.10f,
        0.20f,
        1.0f
    );

    glMatrixMode(
        GL_PROJECTION
    );

    glLoadIdentity();

    gluOrtho2D(
        0,
        WIDTH,
        0,
        HEIGHT
    );

    glMatrixMode(
        GL_MODELVIEW
    );
}

// ===============================
// Main
// ===============================

int main(
    int argc,
    char** argv
)
{
    glutInit(
        &argc,
        argv
    );

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB
    );

    glutInitWindowSize(
        WIDTH,
        HEIGHT
    );

    glutInitWindowPosition(
        100,
        50
    );

    glutCreateWindow(
        "A Little Journey to Enchanted Forest"
    );

    init();

    glutDisplayFunc(
        display
    );

    glutKeyboardFunc(
        keyboard
    );

    glutTimerFunc(
        30,
        update,
        0
    );

    glutMainLoop();

    return 0;
}
