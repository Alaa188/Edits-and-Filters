
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;
unsigned char image[SIZE][SIZE][RGB], image1[SIZE][SIZE][RGB],image2[SIZE][SIZE][RGB],image3[SIZE][SIZE];

void loadImage();
void loadImage2();
void saveImage();
void saveImage2();
void bwImage();
void invertFilter();
void mergeFilter();
void flipImage();
void RotatedImage();
void DLImage();
void detectedImage();
void enlargeImage();
void shrinkImage();
void mirrorImage();
void shuffledImage();
void blurImage();
void croppedImage();
int main()
{
    while(true){
        cout<<"hello,user"<<endl;
        loadImage();
        cout << "Please select a filter to apply or 0 to exit:" << endl;
        cout << "1- Black & White Filter" << endl;
        cout << "2- Invert Filter" << endl;
        cout << "3- Merge Filter" << endl;
        cout << "4- Flip Image" << endl;
        cout << "5- Darken and Lighten Image" << endl;
        cout << "6- Rotate Image" << endl;
        cout << "7- Detect Image Edges" << endl;
        cout << "8- Enlarge Image" << endl;  //not yet
        cout << "9- Shrink Image"<<endl;
        cout << "a- Mirror 1/2 Image" << endl; //not yet
        cout << "b- Shuffle Image" << endl;
        cout << "c- Blur Image" << endl;
        cout << "d- Crop Image"<<endl;
        cout << "e- Skew Image Right" << endl;
        cout << "f- Skew Image Up" << endl;
        cout << "s- Save the image to a file" << endl;
        cout << "0- Exit" << endl;
        char n;
        cin>>n;

        if(n=='1') {
            bwImage();
            saveImage2();
        }
        else if(n=='2'){
            invertFilter();
            saveImage();
        }
        else if(n=='3'){
            loadImage2();
            mergeFilter();
            saveImage();
        }
        else if(n=='4'){
            flipImage();
            saveImage();
        }
        else if(n=='5'){
            RotatedImage();
            saveImage();
        }
        else if(n=='6'){
            DLImage();
            saveImage();
        }
        else if(n=='7'){
            detectedImage();
            saveImage2();
        }
        else if(n=='8'){
            enlargeImage();
            saveImage();
        }
        else if(n=='9'){
            shrinkImage();
            saveImage();
        }
        else if(n=='a'){
            mirrorImage();
            saveImage();
        }
        else if(n=='b'){
            shuffledImage();
            saveImage();
        }
        else if(n=='c'){
            blurImage();
            saveImage();
        }
        else if(n=='d'){
            croppedImage();
            saveImage();
        }
        else{
            break;
        }
    }
    return 0;
}
void loadImage()
{
    char imageFileName[100];
    // Get gray scale image file name
    cout << "Enter the source image file name {without '.bmp'}: ";
    cin >> imageFileName;
    // Add .bmp extension and load the image
    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image1);
}
void loadImage2()
{
    char imageFileName[100];
    // Get gray scale image file name
    cout << "Enter the source image2 file name: ";
    cin >> imageFileName;
    // Add .bmp extension and load the image
    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image2);
}
void saveImage()
{
    char imageFileName[100];
    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    // Add .bmp extension and save the image
    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}
void saveImage2()
{
    char imageFileName[100];
    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    // Add .bmp extension and save the image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image3);
}
// Function to convert the image to black and white
void bwImage()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int l = 0; l < RGB; l++)
            {
                // Check if the pixel value is greater than a threshold (60 in this case)
                // If it is, set the pixel value to 255 (white), otherwise set it to 0 (black)
                if (image1[i][j][l] > 60)
                    image3[i][j] = 255;
                else
                    image3[i][j] = 0;
            }
        }
    }
}

// Function to apply the invert filter to the image
void invertFilter()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int l = 0; l < RGB; l++)
            {
                // Invert the pixel value by subtracting it from 255
                image[i][j][l] = 255 - image1[i][j][l];
            }
        }
    }
}

// Function to merge two images by taking the average of pixel values
void mergeFilter()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int l = 0; l < RGB; l++)
            {
                // Compute the average of pixel values from the two input images
                image[i][j][l] = (image1[i][j][l] + image2[i][j][l]) / 2;
            }
        }
    }
}

// Function to flip the image vertically or horizontally
void flipImage()
{
    string x;
    cout << "Enter 'vertical' or 'horizontal': ";
    cin >> x;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int l = 0; l < RGB; l++)
            {
                if (x == "vertical")
                {
                    // Flip the image vertically
                    image[i][j][l] = image1[i][SIZE - j - 1][l];
                }
                else
                {
                    // Flip the image horizontally
                    image[i][j][l] = image1[SIZE - i - 1][j][l];
                }
            }
        }
    }
}

// Function to rotate the image by 90, 180, 270, or 360 degrees
void RotatedImage()
{
    int x;
    cout << "Enter the degree (90, 180, 270, or 360): ";
    cin >> x;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int l = 0; l < RGB; l++)
            {
                if (x == 270)
                {
                    // Rotate the image 270 degrees
                    image[i][j][l] = image1[j][SIZE - i - 1][l];
                }
                else if (x == 90)
                {
                    // Rotate the image 90 degrees
                    image[i][j][l] = image1[SIZE - j - 1][i][l];
                }
                else if (x == 180)
                {
                    // Rotate the image 180 degrees
                    image[i][j][l] = image1[SIZE - i - 1][SIZE - j - 1][l];
                }
                else
                {
                    // No rotation
                    image[i][j][l] = image1[i][j][l];
                }
            }
        }
    }
}

// Function to darken or lighten the image
void DLImage()
{
    int x;
    cout << "Enter 1 for darkening or 2 for lightening: ";
    cin >> x;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int l = 0; l < RGB; l++)
            {
                if (x == 1)
                    // Darken the pixel by dividing it by 2
                    image[i][j][l] = image1[i][j][l] / 2;
                else
                    // Lighten the pixel by blending it with its complement
                    image[i][j][l] = (255 - image1[i][j][l]) / 2 + image1[i][j][l];
            }
        }
    }
}

// Function to detect edges in the image
void detectedImage()
{
    // Convert the image to a binary image using a threshold (60 in this case)
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int l = 0; l < RGB; l++)
            {
                if (image1[i][j][l] > 60)
                    image1[i][j][l] = 255; // Set pixel to white
                else
                    image1[i][j][l] = 0; // Set pixel to black
            }
        }
    }

    // Initialize a new image (image3) as a blank white image
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image3[i][j] = 255;
        }
    }

    // Apply an edge detection algorithm to identify and highlight edges in the image
    for (int i = 1; i < SIZE - 1; i++)
    {
        for (int j = 1; j < SIZE - 1; j++)
        {
            for (int l = 1; l < RGB; l++)
            {
                if (image1[i][j][l] == 0)
                {
                    // Check if a neighboring pixel is white, indicating an edge
                    if (image1[i][j + 1][l] == 255 || image1[i][j - 1][l] == 255 ||
                        image1[i + 1][j][l] == 255 || image1[i - 1][j][l] == 255 ||
                        image1[i + 1][j + 1][l] == 255 || image1[i - 1][j - 1][l] == 255)
                    {
                        // Set the pixel in the output image to black to highlight the edge
                        image3[i][j] = 0;
                    }
                    else
                    {
                        // Set the pixel in the output image to white
                        image3[i][j] = 255;
                    }
                }
            }
        }
    }
}

// Function to enlarge the image in quarters (1, 2, 3, or 4)
void enlargeImage()
{
    int q;
    cout << "Please enter the quarter you need to enlarge (1, 2, 3, or 4): ";
    cin >> q;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int l = 0; l < RGB; l++)
            {
                if (q == 1)
                {
                    // Enlarge the image by taking pixels from the top-left quarter
                    image[i][j][l] = image1[i / 2][j / 2][l];
                }
                else if (q == 2)
                {
                    // Enlarge the image by taking pixels from the top-right quarter
                    image[i][j][l] = image1[i / 2][(j / 2) + 128][l];
                }
                else if (q == 3)
                {
                    // Enlarge the image by taking pixels from the bottom-left quarter
                    image[i][j][l] = image1[(i / 2) + 128][(j / 2)][l];
                }
                else
                {
                    // Enlarge the image by taking pixels from the bottom-right quarter
                    image[i][j][l] = image1[(i / 2) + 128][(j / 2) + 128][l];
                }
            }
        }
    }
}

// Function to shrink the image to 1/2, 1/3, or 1/4
void shrinkImage()
{
    int n;
    cout << "Please enter 2 to shrink the photo to 1/2, 3 to shrink the photo to 1/3, or 4 to shrink the photo to 1/4: ";
    cin >> n;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int l = 0; l < RGB; l++)
            {
                // Initialize the output image as a blank white image
                image[i][j][l] = 255;
            }
        }
    }

    // Shrink the image by copying pixels from the original image to the output image
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int l = 0; l < RGB; l++)
            {
                image[i / n][j / n][l] = image1[i][j][l];
            }
        }
    }
}

// Function to mirror the image horizontally or vertically
void mirrorImage()
{
    string s;
    cout << "Please enter 'left' or 'right' to mirror horizontally, or 'upper' or 'lower' to mirror vertically: ";
    cin >> s;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int l = 0; l < RGB; l++)
            {
                if (s == "right")
                {
                    // Mirror the image horizontally (left to right)
                    image1[i][j][l] = image1[i][SIZE - 1 - j][l];
                }
                else if (s == "lower")
                {
                    // Mirror the image vertically (top to bottom)
                    image1[i][j][l] = image1[SIZE - i - 1][j][l];
                }
                else if (s == "upper")
                {
                    // Mirror the image vertically (bottom to top)
                    image1[SIZE - i - 1][j][l] = image1[i][j][l];
                }
                else if (s == "left")
                {
                    // Mirror the image horizontally (right to left)
                    image1[i][SIZE - j - 1][l] = image1[i][j][l];
                }
            }
        }
    }

    // Copy the mirrored image to the output image
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int l = 0; l < RGB; l++)
            {
                image[i][j][l] = image1[i][j][l];
            }
        }
    }
}

// Function to shuffle image quadrants based on user input
void shuffledImage()
{
    int c[4], s = 0, n = 0;

    // Read user input to determine quadrant shuffling
    for (int m = 0; m < 4; m++)
    {
        cin >> c[m];
    }

    for (int i = 0; i < 255 / 2; i++)
    {
        for (int j = 0; j < 255 / 2; j++)
        {
            for (int l = 0; l < RGB; l++)
            {
                for (int m = 0; m < 4; m++)
                {
                    // Determine which quadrant to copy from (1, 2, 3, or 4)
                    if (c[m] == 1)
                    {
                        n = 0;
                        s = 0;
                    }
                    else if (c[m] == 2)
                    {
                        n = 0;
                        s = 128;
                    }
                    else if (c[m] == 3)
                    {
                        n = 128;
                        s = 0;
                    }
                    else
                    {
                        n = 128;
                        s = 128;
                    }

                    // Copy pixels from the corresponding quadrant of the input image to the output image
                    if (m == 0)
                        image[i][j][l] = image1[i + n][j + s][l];
                    else if (m == 1)
                        image[i][j + 128][l] = image1[i + n][j + s][l];
                    else if (m == 2)
                        image[i + 128][j][l] = image1[i + n][j + s][l];
                    else
                        image[i + 128][j + 128][l] = image1[i + n][j + s][l];
                }
            }
        }
    }
}

// Function to apply a blur filter to the image
void blurImage()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int l = 0; l < RGB; l++)
            {
                // Apply a simple 3x3 blur filter to the image using neighboring pixels
                image[i][j][l] = (image1[i + 1][j][l] + image1[i - 1][j][l] + image1[i][j + 1][l] + image1[i][j - 1][l] + image1[i + 1][j + 1][l] + image1[i - 1][j - 1][l] + image1[i - 1][j + 1][l] + image1[i + 1][j - 1][l]) / 8;
            }
        }
    }
}

// Function to crop a section of the image
void croppedImage()
{
    int x, l, y, w;
    cout << "Please enter x, y position: ";
    cin >> x >> y;
    cout << "Please enter length and width: ";
    cin >> l >> w;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int l = 0; l < RGB; l++)
            {
                // Initialize the output image as a blank white image
                image[i][j][l] = 255;
            }
        }
    }

    // Copy the specified section of the input image to the output image
    for (int i = x; i < SIZE - x; i++)
    {
        for (int j = y; j < SIZE - y; j++)
        {
            for (int l = 0; l < RGB; l++)
            {
                image[i][j][l] = image1[i][j][l];
            }
        }
    }
}
