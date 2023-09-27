/** *********************************************************************
 * @file
 *
 * @brief  Prototypes
 ***********************************************************************/

#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;


/************************************************************************
 *             Constant Variables, structures, defines and Enums
 ***********************************************************************/

#ifndef  __NETPBM__H__

 /*!
  * @brief netpbm.h definition
  */

#define __ NETPBM__H__

 /*!
  * @brief pixel definition
  */

typedef unsigned char pixel;


/*!
 * @brief image the image read in from the file
 */

struct image
{
    // don't add to this structure

    /*!
    * @brief magicNumber number that tells us what type of image we have
    */

    string magicNumber;

    /*!
    * @brief comment any number of comments that start with #
    */

    string comment;
    
    /*!
    * @brief rows the number of rows of the image
    */
    
    int rows;

    /*!
    * @brief cols the number of columns of the image
    */

    int cols;

    /*!
    * @brief redGray the array of red/gray values
    */

    pixel **redGray; //handles red channel OR grayscale

    /*!
    * @brief green the array of green values
    */
    
    pixel **green;

    /*!
    * @brief blue the array of blue values
    */

    pixel **blue;
};

// place your function prototypes here

/************************************************************************
 *                         Function Prototypes
 ***********************************************************************/

bool openInput(ifstream& in, string file);

bool openOutput(ofstream& out, string file);

void allocateArray(pixel**& ptr, int rows, int cols);

void freeUpArray(pixel**& ptr, int rows);

void readAscii(ifstream& in, image& im, int& maxValue);

void writeAscii(ofstream& out, image& im, int& maxValue);

void readBinary(ifstream& in, image& im, int& maxValue);

void writeBinary(ofstream& out, image& im, int& maxValue);

void flipX(image& im);

void flipY(image& im);

void rotateCW(image& im);

void rotateCCW(image& im);

void grayscale(image& im);

void writeGrayscaleAscii(ofstream& out, image& im, int& maxValue);

void writeGrayscaleBinary(ofstream& out, image& im, int& maxValue);

void sepia(image& im);

#endif