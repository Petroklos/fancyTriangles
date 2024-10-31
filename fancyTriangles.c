#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// function prototypes
void clearInputBuffer();
int isValidTriangle(char *triangleType);
int isValidAlignment(char *alignment);
void getTriangleInfo(char *triangleType, char *alignment, int *height, int *width);
void isosceles(bool *nodes, int height, int width);
void leftAligned(bool *nodes, int height, int width);
void rightAligned(bool *nodes, int height, int width);
void fancyPrintIso(bool *nodes, int height, int width);
void fancyPrintIso(bool *nodes, int height, int width);
void fancyPrintLeft(bool *nodes, int height, int width);
void fancyPrintRight(bool *nodes, int height, int width);

// main()
int main() {
    char triangleType = ' ';
    char alignment = ' ';
    int height = 0;
    int width = 0;

    // Get triangle information from the user
    getTriangleInfo(&triangleType, &alignment, &height, &width);
    
    // Allocate memory for the triangle representation
    bool *nodes = malloc(height * width * sizeof(bool));
    if (nodes == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Generate and print the triangle based on user input
    if (triangleType == 'i' || triangleType == 'I') {
        isosceles(nodes, height, width);
        fancyPrintIso(nodes, height, width);
    } else if (alignment == 'L' || alignment == 'l') {
        leftAligned(nodes, height, width);
        fancyPrintLeft(nodes, height, width);
    } else {
        rightAligned(nodes, height, width);
        fancyPrintRight(nodes, height, width);
    }
    
	// Free the allocated memory
    free(nodes);
    return 0;
}

// Function to get triangle type, alignment, height, and width from the user
void getTriangleInfo(char *triangleType, char *alignment, int *height, int *width) {
    printf("This program prints a triangle. Is it an Isosceles or a Right Angle? ");
    do {
        scanf(" %c", triangleType); // Space before %c to skip whitespace
        clearInputBuffer();
    } while (!isValidTriangle(triangleType));
    printf("\n");

    if (*triangleType == 'r' || *triangleType == 'R') {
        printf("Is the triangle left aligned or right aligned? Please enter Left or Right: ");
        do {
            scanf(" %c", alignment); // Space before %c to skip whitespace
            clearInputBuffer();
        } while (!isValidAlignment(alignment));
        printf("\n");
    }

    printf("What is the height of this triangle? Please enter a number larger than zero: ");
    while (scanf("%d", height) != 1 || *height <= 0) {
        printf("Invalid input. Please enter a valid number: ");
        clearInputBuffer();
    }
    printf("\n");

    clearInputBuffer();

    // Set width based on triangle type
    if (*triangleType == 'r' || *triangleType == 'R') {
        *width = *height; // Right-aligned triangle has width equal to height
    } else {
        *width = *height * 2 + 1; // Isosceles triangle width calculation
    }
}

// Function to clear the input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Clear until newline or EOF
}

// Function to validate triangle type input
int isValidTriangle(char *triangleType) {
    if (*triangleType == 'i' || *triangleType == 'I' || *triangleType == 'r' || *triangleType == 'R') {
        return 1;
    } else {
        printf("Invalid input. Please enter Isosceles or Right Angle: ");
        return 0;
    }
}

// Function to validate alignment input
int isValidAlignment(char *alignment) {
    if (*alignment == 'l' || *alignment == 'L' || *alignment == 'r' || *alignment == 'R') {
        return 1;
    } else {
        printf("Invalid input. Please enter Left or Right: ");
        return 0;
    }
}

// Function to generate an isosceles triangle
void isosceles(bool *nodes, int height, int width) {
    for (int i = 0; i < height; i++) {
        int blanks = (width / 2) - i;
        for (int j = 0; j < blanks; j++) {
            nodes[i * width + j] = false;
        }
        for (int j = 0; j < (2 * i + 1); j++) {
            nodes[i * width + blanks + j] = true;
        }
        for (int j = blanks + (2 * i + 1); j < width; j++) {
            nodes[i * width + j] = false;
        }
    }
}

// Function to generate a left-aligned triangle
void leftAligned(bool *nodes, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= i; j++) {
            nodes[i * width + j] = true; // Fill hashes for the current row
        }
        for (int j = i + 1; j < width; j++) {
            nodes[i * width + j] = false; // Fill trailing spaces
        }
    }
}

// Function to generate a right-aligned triangle
void rightAligned(bool *nodes, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < height - i - 1; j++) {
            nodes[i * width + j] = false; // Fill leading spaces
        }
        for (int j = height - i - 1; j < height; j++) {
            nodes[i * width + j] = true; // Fill hashes
        }
        for (int j = height; j < width; j++) {
            nodes[i * width + j] = false; // Fill trailing spaces
        }
    }
}

// Function to print an isosceles triangle with fancy characters
void fancyPrintIso(bool *nodes, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
			if (!nodes[i * width + j]) {
			    printf(" ");
				continue;
			}
			
            if ((j == 0 || !nodes[i * width + j - 1]) && (j == width - 1 || !nodes[i * width + j + 1])) {
                printf("Λ"); // Top of the triangle
            } else if ((j == 0 || !nodes[i * width + j - 1]) && nodes[i * width + j + 1]) {
                printf("/"); // Left edge
            } else if (nodes[i * width + j - 1] && (j == width - 1 || !nodes[i * width + j + 1])) {
                printf("\\"); // Right edge
            } else if (i == height - 1) {
                printf("_"); // Base of the triangle
            } else {
                printf(" "); // Empty space
            }
        }
        printf("\n"); // New line after each row
    }
}

// Function to print a left-aligned triangle with fancy characters
void fancyPrintLeft(bool *nodes, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
			if (!nodes[i * width + j]) {
			    printf(" ");
				continue;
			}
			
            if (i != 0 && j == 0) {
                printf("|"); // Left border
            } else if (i == height - 1 && j == width - 1) {
                printf("\\"); // Bottom right corner
            } else if ((j == 0 || !nodes[i * width + j - 1]) && nodes[i * width + j + 1]) {
                printf("/"); // Left edge
            } else if (i == 0 && j == 0) {
                printf("."); // Top left corner
            } else if (nodes[i * width + j - 1] && (j == width - 1 || !nodes[i * width + j + 1])) {
                printf("\\"); // Right edge
            } else if (i == height - 1) {
                printf("_"); // Base of the triangle
            } else {
                printf(" "); // Empty space
            }
        }
        printf("\n"); // New line after each row
	}
}

// Function to print a right-aligned triangle with fancy characters
void fancyPrintRight(bool *nodes, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
			if (!nodes[i * width + j]) {
			    printf(" ");
				continue;
			}
			
            if (i != 0 && j == width - 1) {
                printf("|"); // Right border
            } else if (nodes[i * width + j] == '#' && i == height - 1 && j == 0) {
                printf("/"); // Bottom left corner
            } else if ((j == 0 || !nodes[i * width + j - 1]) && nodes[i * width + j + 1]) {
                printf("/"); // Left edge
            } else if (nodes[i * width + j - 1] && (j == width - 1 || !nodes[i * width + j + 1])) {
                printf("\\"); // Right edge
            } else if ((j == 0 || !nodes[i * width + j - 1])) {
                printf("."); // Top right corner
            } else if (i == height - 1) {
                printf("_"); // Base of the triangle
            } else {
                printf(" "); // Empty space
            }
        }
        printf("\n"); // New line after each row
    }
}