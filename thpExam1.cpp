/** *********************************************************************
 * @file
 *
 * @brief demonstrates image manipulation on ascii and binary files.
 ***********************************************************************/

 /** ********************************************************************
 *
 * @mainpage Take Home Programming Exam 1 - Image Manipulation
 *
 * @section course_section Course Information
 *
 * @authors David Hill
 *
 * @date March 7, 2022
 *
 * @par Instructor:
 *         Prof. Schrader
 *
 * @par Course:
 *         CSC 215 - Section 2 - 1:00 pm
 *
 * @par Location:
 *         Classroom Building - Room 329
 *
 * @section program_section Program Information
 *
 * @details This program will read in an input image, either in binary
 * or ascii, and output it, again, in either binary or ascii, depending
 * on command line arguments. If the number of arguments is 4, it will
 * not perform any manipulation on the image; it will just output it
 * as it was. If the number of arguments is 5, one of the arguments will
 * specify what manipulation to put on the image. It will then output
 * the manipulated image.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
   @verbatim
   c:\> thpExam1.exe --outputtype basename image.ppm
   c:\> thpExam1.exe [option] --outputtype basename image.ppm
   d:\> c:\bin\thpExam1.exe --outputtype basename image.ppm
   d:\> c:\bin\thpExam1.exe [option] --outputtype basename image.ppm

        --outputtype - type of data to output, either binary or ascii
        basename - name of output file
        image.ppm - name of input file
        [option] - type of manipulation on image
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * @bug when outputting from an ascii file to a binary file with grayscale,
 *      in gimp the image is correct, but in notepad it will take a long time
 *      to open the file, and it looks very different from what the input
 *      binary file looks like.
 *
 * @par Modifications and Development Timeline:
   @verbatim
   Date          Modification
   ------------  --------------------------------------------------------
   Feb  9, 2022  Finished error messages for invalid and incorrect number
                 of command line arguments.
   Feb 14, 2022  Finished my functions for the IO and got them working
                 correctly.
   Feb 24, 2022  Finished 2 functions to allocate and free up arrays.
   Feb 28, 2022  Allocated each of the 3 arrays.
   Mar  4, 2022  Got each array filled correctly from the input file.
   Mar  5, 2022  Got the start of my output working for the new file.
   Mar  5, 2022  Created 2 functions readAscii and writeAscii
                 and got them working.
   Mar  6, 2022  Got my flipX function working.
   Mar  6, 2022  Finished my flipY function.
   Mar  6, 2022  Got my grayscale function working.
   Mar  6, 2022  Got my sepia function working.
   Mar  6, 2022  Finished my rotateClockwise function.
   Mar  6, 2022  Finished my rotateCounterClockwise function.
   Mar  7, 2022  Got my readBinary and writeBinary function working.
                 I can now read and write to and from both ascii
                 and binary.
   Mar  7, 2022  Finished commenting my functions.
   Mar  7, 2022  Finished doxygen.
   @endverbatim

   Gitlab commit log, <a href = "https://gitlab.cse.sdsmt.edu/
   101061288/csc215s22programs/-/commits/master" target="_blank">
   Click Here.</a>
 *
 ***********************************************************************/


#include "netPBM.h"


 /** *********************************************************************
  * @author David Hill
  *
  * @par Description:
  * This is the starting point to the program. It will check command line
  * arguments to see if the input was put in correctly. If there is an
  * incorrect number of command line arguments, or they were not put in
  * correctly, an error message will print and the program will exit. 
  * Otherwise, it will read in what output type, files, and manipulation,
  * if one exists, and start reading in the file. It will dynamically
  * allocate 3 2d arrays for the RGB values of the image, perform a
  * manipulation if there exists one, and then write out the data to the
  * output file in the format of the output type.
  *
  *
  * @param[in] argc - the number of arguments from the command prompt.
  * @param[in] argv - a 2d array of characters containing the arguments.
  *
  * @returns 0 if the program executed correctly
  *
  * @verbatim
    see usage statement above.
    @endverbatim
  *
  ***********************************************************************/

int main(int argc, char** argv)
{
    string outputType;
    string optionCode; // only exists if there are 5 arguments
    string outputName; // name of output file
    image im;
    int maxValue = 0; // will always be 255 for this assignment
    ifstream in;
    ofstream out;

    // output error message for invalid # of arguments
    if (argc != 4 && argc != 5)
    {
        cout << "Usage: thpExam1.exe --outputtype basename image.ppm"
            << endl
            << "or:    thpExam1.exe [option] "
            << "--outputtype basename image.ppm"
            << endl;
        exit(0);
    }
    if (argc == 4)
    {
        // extension will be ppm since grayscale cannot be used here
        outputName = (string)argv[2] + ".ppm";
        outputType = argv[1];

        // output error message for invalid outputType
        if (outputType != "--ascii" && outputType != "--binary")
        {
            cout << "Usage: thpExam1.exe "
                << "--outputtype basename image.ppm"
                << endl;
            exit(0);
        }

        // check if files open correctly
        if (!openInput(in, argv[3]))
        {
            in.close();
            exit(0);
        }
        if (!openOutput(out, outputName))
        {
            out.close();
            exit(0);
        }
    }
    if (argc == 5)
    {
        optionCode = argv[1];
        outputType = argv[2];

        // output error message for incorrect optionCode
        if (optionCode != "--flipX" && optionCode != "--flipY" &&
            optionCode != "--rotateCW" && optionCode != "--rotateCCW"
            && optionCode != "--grayscale" && optionCode != "--sepia")
        {
            cout << "Usage: thpExam1.exe [option] "
                << "--outputtype basename "
                << "image.ppm" << endl;
            exit(0);
        }

        // output error message for incorrect outputType
        if (outputType != "--ascii" && outputType != "--binary")
        {
            cout << "Usage: thpExam1.exe [option] "
                << "--outputtype basename "
                << "image.ppm" << endl;
            exit(0);
        }

        // change extension name to pgm for grayscale; 
        // otherwise, use ppm
        if (optionCode == "--grayscale")
        {
            outputName = (string)argv[3] + ".pgm";
        }
        else
        {
            outputName = (string)argv[3] + ".ppm";
        }

        // check if files open correctly
        if (!openInput(in, argv[4]))
        {
            in.close();
            exit(0);
        }
        if (!openOutput(out, outputName))
        {
            out.close();
            exit(0);
        }
    }

    // read in magic number
    in >> im.magicNumber;
    
    // for input, we can only have ppm files, not grayscale ones
    // if magic number doesn't match the two we can have,
    // output error message and close files
    if (im.magicNumber != "P3" && im.magicNumber != "P6")
    {
        cout << "Invalid magic number" << endl;
        in.close();
        out.close();
        exit(0);
    }
    
    // read in either ascii or binary data based on what the magic number is
    // change magic number accordingly based on what the outputType is,
    // perform an operation based on what optionCode is,
    // and write out either ascii or binary data based on what outputType is
    if (im.magicNumber == "P3")
    {
        if (outputType == "--ascii")
        {
            
            if (optionCode == "--grayscale")
            {
                im.magicNumber = "P2";
                readAscii(in, im, maxValue);
                grayscale(im);
                writeGrayscaleAscii(out, im, maxValue);
            }
            else if (optionCode == "--sepia")
            {
                im.magicNumber = "P3";
                readAscii(in, im, maxValue);
                sepia(im);
                writeAscii(out, im, maxValue);
            }
            else if (optionCode == "--flipX")
            {
                im.magicNumber = "P3";
                readAscii(in, im, maxValue);
                flipX(im);
                writeAscii(out, im, maxValue);
            }
            else if (optionCode == "--flipY")
            {
                im.magicNumber = "P3";
                readAscii(in, im, maxValue);
                flipY(im);
                writeAscii(out, im, maxValue);
            }
            else if (optionCode == "--rotateCW")
            {
                im.magicNumber = "P3";
                readAscii(in, im, maxValue);
                rotateCW(im);
                writeAscii(out, im, maxValue);
            }
            else if (optionCode == "--rotateCCW")
            {
                im.magicNumber = "P3";
                readAscii(in, im, maxValue);
                rotateCCW(im);
                writeAscii(out, im, maxValue);
            }
            else 
            {
                readAscii(in, im, maxValue);
                writeAscii(out, im, maxValue);
            }
        }
        else if (outputType == "--binary")
        {
            if (optionCode == "--grayscale")
            {
                im.magicNumber = "P5";
                readAscii(in, im, maxValue);
                grayscale(im);
                writeGrayscaleBinary(out, im, maxValue);
            }
            else if (optionCode == "--sepia")
            {
                im.magicNumber = "P6";
                readAscii(in, im, maxValue);
                sepia(im);
                writeBinary(out, im, maxValue);
            }
            else if (optionCode == "--flipX")
            {
                im.magicNumber = "P6";
                readAscii(in, im, maxValue);
                flipX(im);
                writeBinary(out, im, maxValue);
            }
            else if (optionCode == "--flipY")
            {
                im.magicNumber = "P6";
                readAscii(in, im, maxValue);
                flipY(im);
                writeBinary(out, im, maxValue);
            }
            else if (optionCode == "--rotateCW")
            {
                im.magicNumber = "P6";
                readAscii(in, im, maxValue);
                rotateCW(im);
                writeBinary(out, im, maxValue);
            }
            else if (optionCode == "--rotateCCW")
            {
                im.magicNumber = "P6";
                readAscii(in, im, maxValue);
                rotateCCW(im);
                writeBinary(out, im, maxValue);
            }
            else
            {
                im.magicNumber = "P6";
                readAscii(in, im, maxValue);
                writeBinary(out, im, maxValue);
            }
        }
    }
    else if (im.magicNumber == "P6")
    {
        if (outputType == "--ascii")
        {
            if (optionCode == "--grayscale")
            {
                im.magicNumber = "P2";
                readBinary(in, im, maxValue);
                grayscale(im);
                writeGrayscaleAscii(out, im, maxValue);
            }
            else if (optionCode == "--sepia")
            {
                im.magicNumber = "P3";
                readBinary(in, im, maxValue);
                sepia(im);
                writeAscii(out, im, maxValue);
            }
            else if (optionCode == "--flipX")
            {
                im.magicNumber = "P3";
                readBinary(in, im, maxValue);
                flipX(im);
                writeAscii(out, im, maxValue);
            }
            else if (optionCode == "--flipY")
            {
                im.magicNumber = "P3";
                readBinary(in, im, maxValue);
                flipY(im);
                writeAscii(out, im, maxValue);
            }
            else if (optionCode == "--rotateCW")
            {
                im.magicNumber = "P3";
                readBinary(in, im, maxValue);
                rotateCW(im);
                writeAscii(out, im, maxValue);
            }
            else if (optionCode == "--rotateCCW")
            {
                im.magicNumber = "P3";
                readBinary(in, im, maxValue);
                rotateCCW(im);
                writeAscii(out, im, maxValue);
            }
            else
            {
                im.magicNumber = "P3";
                readBinary(in, im, maxValue);
                writeAscii(out, im, maxValue);
            }
        }
        else if (outputType == "--binary")
        {
            if (optionCode == "--grayscale")
            {
                im.magicNumber = "P5";
                readBinary(in, im, maxValue);
                grayscale(im);
                writeGrayscaleBinary(out, im, maxValue);
            }
            else if (optionCode == "--sepia")
            {
                im.magicNumber = "P6";
                readBinary(in, im, maxValue);
                sepia(im);
                writeBinary(out, im, maxValue);
            }
            else if (optionCode == "--flipX")
            {
                im.magicNumber = "P6";
                readBinary(in, im, maxValue);
                flipX(im);
                writeBinary(out, im, maxValue);
            }
            else if (optionCode == "--flipY")
            {
                im.magicNumber = "P6";
                readBinary(in, im, maxValue);
                flipY(im);
                writeBinary(out, im, maxValue);
            }
            else if (optionCode == "--rotateCW")
            {
                im.magicNumber = "P6";
                readBinary(in, im, maxValue);
                rotateCW(im);
                writeBinary(out, im, maxValue);
            }
            else if (optionCode == "--rotateCCW")
            {
                im.magicNumber = "P6";
                readBinary(in, im, maxValue);
                rotateCCW(im);
                writeBinary(out, im, maxValue);
            }
            else
            {
                readBinary(in, im, maxValue);
                writeBinary(out, im, maxValue);
            }
        }
    }
    
    // free up arrays and close files
    freeUpArray(im.redGray, im.rows);
    freeUpArray(im.green, im.rows);
    freeUpArray(im.blue, im.rows);
    in.close();
    out.close();
}