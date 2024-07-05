
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
//Initializing the 2D arrays used to represent the photo pixels.
unsigned char image[SIZE][SIZE];
unsigned char image1[SIZE][SIZE],image2[SIZE][SIZE];

void loadImage();
void loadImage1();
void saveImage();
void bwImage();
void invertFilter();
void mergeFilter();
void flipImageO();
void DLImage();
void RotateImage();
void detectedImage();
void enlargeImage();
void shrinkImage();
void MirrorImage();
void ShuffleImage();
void blurImage();
void cropImage();
void skewRight();
void skewUp();

int main()
{
    while(true){
        char n;
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

        cin>>n;
        if (n == '1') {
            bwImage();
            saveImage();

        }
        else if (n == '2') {
            invertFilter();
            saveImage();
        }
        else if (n == '3') {
            loadImage1();
            mergeFilter();
            saveImage();
        }
        else if (n == '4') {
            flipImageO();
            saveImage();
        }
        else if (n == '5') {
            DLImage();
            saveImage();
        }
        else if (n == '6') {
            RotateImage();
            saveImage();
        }
        else if(n=='7'){
            detectedImage();
            saveImage();
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
            MirrorImage();
            saveImage();
        }
        else if(n=='b'){
            ShuffleImage();
            saveImage();
        }
        else if(n=='c'){
            blurImage();
            blurImage();
            blurImage();
            saveImage();

        }
        else if(n=='d'){
            cropImage();
            saveImage();
        }
        else if(n=='e'){
            skewRight();
            saveImage();
        }
        else if(n=='f'){
            skewUp();
            saveImage();
        }
        else if(n=='s'){
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
    cout << "Please enter file name of the image to process {without '.bmp'}: ";
    cin >> imageFileName;

    // Add .bmp extension and load the image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void saveImage()
{
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add .bmp extension and save the image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}
void bwImage(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if (image[i][j]>127) // if bites is >127 we will make them white
                image[i][j] =255;

            else   // if they don't we make them black

                image[i][j]=0;
        }
    }
}

void invertFilter(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            // to get inverse of image =(255-number of bites for each pixel)
            image[i][j]=255-image[i][j];
        }
    }
}
void loadImage1()
{
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Please enter file name of the image 2 to process: ";
    cin >> imageFileName;

    // Add .bmp extension and load the image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image1);
}
void mergeFilter(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {

            //we need to avarge the sum of two images
            image[i][j] = (image1[i][j]+image[i][j])/2;
        }
    }
}

void flipImageO(){
    char choose;
    cout << "Flip (h)orizontally or (v)ertically ?" << endl;

    cin >> choose;

    if (choose == 'h') { // Flip horizontally
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                // Swap pixels horizontally
                unsigned char image2 = image[i][j];
                image[i][j] = image[i][SIZE - 1 - j];
                image[i][SIZE - 1 - j] = image2;
            }
        }
    } else if (choose == 'v') { // Flip vertically
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                // Swap pixels vertically
                unsigned char image2 = image[i][j];
                image[i][j] = image[SIZE -1 - i][j];
                image[SIZE - 1 - i][j] = image2;
            }
        }
    }
}

void DLImage(){
    char n;
    cout<<"Do you want to (d)arken or (l)ighten?"<<endl;
    cin>>n;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            // to get a light image we will do this equation((255-number of bites for each pixel)/20 ehen add them on the original image

            if (n == 'l') {
                image[i][j] = (255 - image[i][j]) / 2 + image[i][j];

                //for a dark image (nunber of bites/2)

            } else
                image[i][j] = image[i][j] / 2;
        }
    }
}

void RotateImage()
{
    int degrees;
    cout << "Rotate (90), (180) or (270) degrees?" << endl;

    cin >> degrees;

    unsigned char rotatedImage[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // The variable 'degrees' represents the angle at which the image should be rotated (90, 180, or 270 degrees).
            switch (degrees)
            {
                // When rotating 90 degrees clockwise:
                case 90:
                    // Calculate the new pixel position in the rotated image.
                    // The pixel at (i, j) in the original image becomes (j, SIZE - i - 1) in the rotated image.
                    rotatedImage[i][j] = image[SIZE - j - 1][i];
                    break;

                    // When rotating 180 degrees clockwise:
                case 180:
                    // The pixel at (i, j) in the original image becomes (SIZE - i - 1, SIZE - j - 1) in the rotated image.
                    rotatedImage[i][j] = image[SIZE - i - 1][SIZE - j - 1];
                    break;
                    // When rotating 270 degrees clockwise:
                case 270:
                    // The pixel at (i, j) in the original image becomes (j, SIZE - i - 1) in the rotated image.
                    rotatedImage[i][j] = image[j][SIZE - i - 1];
                    break;

                    // If the 'degrees' value is not 90, 180, or 270, no rotation is performed.
                default:
                    break;
            }

        }
    }
    // We copy the rotated image to the original image to preserve the rotated image to show it to the user
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = rotatedImage[i][j];
        }
    }
    saveImage();

}
void detectedImage(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if (image[i][j]>127) // if bites is >127 we will make them white
                image[i][j] =255;

            else   // if they don't we make them black
                image[i][j]=0;
        }
    }
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            image2[i][j]=255;
        }
    }
    for(int i = 1 ; i < SIZE-1; i++){
        for(int j = 1 ; j < SIZE-1; j++){
            if(image[i][j] == 0) {
                if (image[i][j + 1] == 255 || image[i][j - 1] == 255 || image[i + 1][j] == 255 || image[i - 1][j] == 255
                    || image[i + 1][j + 1] == 255 || image[i - 1][j - 1] == 255) {
                    image2[i][j] = 0;
                }
                else {
                    image2[i][j] = 255;
                }
            }
        }
    }
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE; j++ ){
            image[i][j] = image2[i][j] ;
        }
    }
}
void enlargeImage() {
    int q;
    cout << "Which quarter to enlarge 1, 2, 3, or 4?" << endl;
    cin >> q;


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (q == 1) {
                // If quarter 1 is selected, enlarge the image using quarter 1 of image1 etc..
                // Divide the coordinates by 2 to access the first quarter in image1
                image[i][j] = image1[i / 2][j / 2];
            }
            else if (q == 2) {
                // Divide the row coordinate by 2 and add 128 to the column coordinate to access the second quarter in image1
                image[i][j] = image1[i / 2][(j / 2) + 128];
            }
            else if (q == 3) {
                // Add 128 to the row coordinate and divide the column coordinate by 2 to access the third quarter in image1
                image[i][j] = image1[(i / 2) + 128][j / 2];
            }
            else {
                // Add 128 to both row and column coordinates to access the fourth quarter in image1
                image[i][j] = image1[(i / 2) + 128][(j / 2) + 128];
            }
        }
    }
}

void shrinkImage()
{
    cout<<"Shrink to (1/2), (1/3) or (1/4)?"<<endl;
    string str;cin>>str;
    int fact;
    if(str=="1/2"){
        fact=2;
    }
    else if(str=="1/3"){
        fact=3;
    }
    else{
        fact=4;
    }
    int newWidth = SIZE / fact;
    int newHeight = SIZE / fact;
    unsigned char shrinkImg[newWidth][newHeight];

    for (int i = 0; i < newWidth; i++)
    {
        for (int j = 0; j < newHeight; j++)
        {
            // Calculate the average color value in the scaleFactor x scaleFactor block
            int sum = 0;
            for (int x = 0; x < fact; x++)
            {
                for (int y = 0; y < fact; y++)
                {
                    sum += image[i * fact + x][j * fact + y];
                }
            }
            shrinkImg[i][j] = sum / (fact * fact);
        }
    }

    // Copy the shrinkImg back to the original image array
    for (int i = 0; i < newWidth; i++)
    {
        for (int j = 0; j < newHeight; j++)
        {
            image[i][j] = shrinkImg[i][j];
        }
    }
//to make the background of the image colored white
    //first we make the rest of the width white
    for (int i = newWidth; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = 255;
        }
    }
    //second we make the rest of the lenght white
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = newHeight; j < SIZE; j++)
        {
            image[i][j] = 255;
        }
    }
}
void MirrorImage() {
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?";
    char mirror;
    cin >> mirror;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (mirror == 'u') {  // Loop through the upper half of the image and copy it to the down half, and vice versa
                image[SIZE-1-i][j] = image[i][j];
            } else if (mirror == 'r') { // Loop through the right half of the image and copy it to the left half, and vice versa
                image[i][j] = image[i][SIZE - j - 1];
            } else if (mirror == 'l') {// Loop through the left half of the image and copy it to the right half, and vice versa
                image[i][255 - j - 1] = image[i][j];
            } else image[i][j] = image[SIZE - i - 1][j];// Loop through the down half of the image and copy it to the upper half, and vice versa
        }
    }
}

void ShuffleImage() {
    cout << "New order of quarters ? ";
    int c[4], s = 0, n = 0;

    // Read the new order of quarters from the user
    for (int m = 0; m < 4; m++) {
        cin >> c[m];
    }

    // Loop through the image and shuffle the quarters
    for (int i = 0; i < 255/2; i++) {
        for (int j = 0; j < 255/2; j++) {
            for (int m = 0; m < 4; m++) {
                // Determine the shift values based on the selected quarter (c[m])
                if (c[m] == 1) {
                    n = 0;
                    s = 0;
                }
                else if (c[m] == 2) {
                    n = 0;
                    s = 128;
                }
                else if (c[m] == 3) {
                    n = 128;
                    s = 0;
                }
                else {
                    n = 128;
                    s = 128;
                }

                // Based on the selected quarter (m), copy the corresponding part of the image
                if (m == 0)
                    image2[i][j] = image[i + n][j + s];
                else if (m == 1)
                    image2[i][j + 128] = image[i + n][j + s];
                else if (m == 2)
                    image2[i + 128][j] = image[i + n][j + s];
                else
                    image2[i + 128][j + 128] = image[i + n][j + s];
            }
        }
    }

    // Copy the shuffled image (image2) back to the original image (image)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = image2[i][j];
        }
    }
}

void blurImage(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) { //To make image blue We need to collect all the pixels around the pixel we are at, then divide them by the number of pixels we collected.
            image2[i][j]=(image[i+1][j]+image[i-1][j]+image[i][j+1]+image[i][j-1]+image[i+1][j+1]+image[i-1][j-1]+image[i-1][j+1]+image[i+1][j-1])/8;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = image2[i][j];
        }
    }
}


void cropImage() {
    int x, y, l, w;
    cout << "Please enter x y l w: ";
    cin >> x >> y >> l >> w;

    // Validate input coordinates (ensure they are within bounds)
    if (x < 0 || y < 0 || l > SIZE || w > SIZE) {
        cout << "Invalid cropping coordinates. Make sure they are within image bounds{less than or equl 256}." << endl;
        return;
    }

    // Initialize croppedImage with white pixels (255)
    unsigned char croppedImage[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            croppedImage[i][j] = 255;
        }
    }

    // Copy the cropped region from the original image
    for (int i = y; i < l; i++) {
        for (int j = x; j < w; j++) {
            croppedImage[i][j] = image[i][j];
        }
    }

    // Update the original image with the cropped region
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = croppedImage[i][j];
        }
    }
}


void skewRight() {
    double rad;
    cout << "Please enter degree to skew right: ";
    cin >> rad;
    rad = 90 - rad;  // Calculate complementary angle (90 degrees - user input)
    rad = (rad * 22) / (180 * 7);  // Convert degrees to radians
    double l = 256 / (1 + 1 / tan(rad));  // Calculate the length of the skewed image
    double m = 256 - l;  // Calculate the Horizontal displacement for skewing
    double s = m / SIZE;  // Calculate the step size for Horizontal displacement
    double p = 256 / l;  // Calculate the pixel displacement per step

    unsigned char image2[SIZE][SIZE];
    unsigned char image3[SIZE][SIZE];

    // Initialize the image2 array with white pixels
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image2[i][j] = 255;
        }
    }

    // shrink the original image into image2
    for (int i = 0; i < SIZE; i++) {
        double ptr = 0;
        for (int j = 0; j < l; j++) {
            // Copy pixel values from the original image to the skewed position in image2
            image2[i][j] = image[i][(int)ptr + (int)p];
            ptr += p;//the ptr increases by the pixel Horizontal displacement per step to shrink the image evrey (p+ptr) put pexel in the image2
        }
    }

    // Copy the shrinked image (image2) back to the original image (image)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = image2[i][j];
        }
    }

    // Initialize the image3 with white pixels
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image3[i][j] = 255;
        }
    }

    // Shift the image horizontally by the calculated Horizontal displacement (m)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image3[i][j + (int)m] = image[i][j];
        }
        m -= s;  // Decrease the Horizontal displacement for the next row
    }

    // Copy the shifted image (image3) back to the original image (image)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = image3[i][j];
        }
    }
}

void skewUp() {
    double rad;
    cout << "Please enter degree to skew Up: ";
    cin >> rad;
    rad = 90 - rad;
    rad = (rad * 22) / (180 * 7);
    double l = 256 / (1 + 1 / tan(rad));
    double m = 256 - l;  // Calculate the vertical displacement for skewing
    double s = m / SIZE;  // Calculate the step size for vertical displacement
    double p = 256 / l;

    unsigned char image2[SIZE][SIZE];
    unsigned char image3[SIZE][SIZE];

    // Initialize the image2 array with white pixels
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image2[i][j] = 255;
        }
    }

    double ptr = 0;//we declared the ptr out of the nasted loop this time
    // shrink the original image into image2
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Copy pixel values from the original image to the skewed position in image2
            image2[i][j] = image[(int)ptr + (int)p][j];
        }
        ptr += p;
    }

    // Copy the skewed image (image2) back to the original image (image)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = image2[i][j];
        }
    }

    // Initialize the image3 array with white pixels
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image3[i][j] = 255;
        }
    }

    // Shift the image vertically by the calculated displacement (m)
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < l; i++) {
            // Copy pixel values from the original image to the shifted position in image3
            image3[i + (int)m][j] = image[i][j];
        }
        m -= s;  // Decrease the vertical displacement for the next column
    }

    // Copy the shifted image (image3) back to the original image (image)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = image3[i][j];
        }
    }
}
