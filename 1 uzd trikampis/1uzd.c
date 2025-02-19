#include<stdio.h>

typedef struct {
    int x;
    int y;
} Point;

int distanceSquared(Point a, Point b) {
    return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
}

int isRightTriangle(Point a, Point b, Point c) {
    int ab = distanceSquared(a, b);
    int bc = distanceSquared(b, c);
    int ca = distanceSquared(c, a);

    return (ab + bc == ca || ab + ca == bc || bc + ca == ab);
}

int main() {
    Point a, b, c;
    printf("Enter coordinates for point A (x y): ");
    scanf("%d %d", &a.x, &a.y);
    printf("Enter coordinates for point B (x y): ");
    scanf("%d %d", &b.x, &b.y);
    printf("Enter coordinates for point C (x y): ");
    scanf("%d %d", &c.x, &c.y);

    if (isRightTriangle(a, b, c)) {
        printf("The points form a right triangle.\n");
    } else {
        printf("The points do not form a right triangle.\n");
    }

    return 0;
}