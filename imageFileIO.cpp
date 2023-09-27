/** *********************************************************************
 * @file
 *
 * @brief   functions that deal with file input and output
 ***********************************************************************/

#include "netPBM.h"

 /** *********************************************************************
  * @author David Hill
  *
  * @par Description:
  * This function opens an input file, checks if it's open,
  * and if not, will return an error message.
  *
  * @param[in] in - the input stream.
  * @param[in] file - the file name to open.
  *
  * @returns a boolean value. True if the file opened correctly and false
  * if it did not.
  *
  * @par Example:
    @verbatim
    ifstream in;
    string s = argv[3];
    openInput(in, s);

    output: true
    @endverbatim

  ***********************************************************************/

bool openInput(ifstream& in, string file)
{
    // open the file for both in and binary
    in.open(file, ios::in | ios::binary);

    // if it didn't open correctly, output error message
    if (!in.is_open())
    {
        cout << "Unable to open input file: " + file << endl;
        return false;
    }
    return true;
}



/** *********************************************************************
 * @author David Hill
 *
 * @par Description:
 * This function opens an output file, checks if it's open,
 * and if not, will return an error message.
 *
 * @param[in] out - the output stream.
 * @param[in] file - the file name to open.
 *
 * @returns a boolean value. True if the file opened correctly and false
 * if it did not.
 *
 * @par Example:
   @verbatim
   ofstream out;
   string s = argv[3];
   openInput(out, s);

   output: true
   @endverbatim

 ***********************************************************************/

bool openOutput(ofstream& out, string file)
{
    // open the file for both out and binary
    out.open(file, ios::out | ios::binary);

    // if it didn't open correctly, output error message
    if (!out.is_open())
    {
        cout << "Unable to open output file: " + file << endl;
        return false;
    }
    return true;
}



/** *********************************************************************
 * @author David Hill
 *
 * @par Description:
 * This function reads in the image data in ascii, allocates the arrays,
 * and stores the data in the arrays of im.
 *
 * @param[in] in - the input stream.
 * @param[in] im - the image to fill.
 * @param[in] maxValue - the max value of the pixels
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   ifstream in;
   image im;
   int maxValue = 255;

   readAscii(in, im, maxValue);

   im now contains all the data that "in" read in.
   @endverbatim

 ***********************************************************************/

void readAscii(ifstream& in, image& im, int& maxValue)
{
    int i = 0;
    int j = 0;
    int num;
    string com;
    getline(in, com); // read rest of line after magic number

    // while first character of next line is # (35 in ascii) 
    // add this line to in.comment
    while (in.peek() == 35)
    {
        getline(in, com);
        im.comment += com + '\n';
    }

    // read in columns and rows
    in >> im.cols;
    in >> im.rows;

    // allocate arrays with these sizes
    allocateArray(im.redGray, im.rows, im.cols);
    allocateArray(im.green, im.rows, im.cols);
    allocateArray(im.blue, im.rows, im.cols);

    // read in maxValue
    in >> maxValue;

    // fill arrays with data in file
    while (i < im.rows)
    {
        while (j < im.cols)
        {
            in >> num;
            im.redGray[i][j] = num;
            in >> num;
            im.green[i][j] = num;
            in >> num;
            im.blue[i][j] = num;
            j++;
        }
        i++;
        j = 0;
    }
}



/** *********************************************************************
 * @author David Hill
 *
 * @par Description:
 * This function writes out the image data in ascii.
 *
 * @param[in] out - the out stream.
 * @param[in] im - the image to write out.
 * @param[in] maxValue - the max value of the pixels
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   ofstream out;
   image im;
   int maxValue = 255;

   writeAscii(out, im, maxValue);

   out now contains all of the image data stored in "im".
   @endverbatim

 ***********************************************************************/

void writeAscii(ofstream& out, image& im, int& maxValue)
{
    int i = 0;
    int j = 0;

    // output magic number, any comments, columns and rows, and maxValue
    out << im.magicNumber << endl;
    out << im.comment;
    out << im.cols << " " << im.rows << endl;
    out << maxValue << endl;

    // output values from each array
    while (i < im.rows)
    {
        while (j < im.cols)
        {
            out << (int)im.redGray[i][j] << endl;
            out << (int)im.green[i][j] << endl;
            out << (int)im.blue[i][j] << endl;
            j++;
        }
        i++;
        j = 0;
    }
}



/** *********************************************************************
 * @author David Hill
 *
 * @par Description:
 * This function reads in the image data in binary, allocates the arrays,
 * and stores the data in the arrays of im.
 *
 * @param[in] in - the input stream.
 * @param[in] im - the image to fill.
 * @param[in] maxValue - the max value of the pixels
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   ifstream in;
   image im;
   int maxValue = 255;

   readBinary(in, im, maxValue);

   im now contains all the data that "in" read in.
   @endverbatim

 ***********************************************************************/

void readBinary(ifstream& in, image& im, int& maxValue)
{
    int i = 0;
    int j = 0;
    pixel space;
    string com;
    getline(in, com); // read rest of line after magic number

    // while first character of next line is # (35 in ascii)
    // add this line to in.comment
    while (in.peek() == 35)
    {
        getline(in, com);
        im.comment += com + '\n';
    }

    // read in columns and rows
    in >> im.cols;
    in >> im.rows;

    // allocate arrays with these sizes
    allocateArray(im.redGray, im.rows, im.cols);
    allocateArray(im.green, im.rows, im.cols);
    allocateArray(im.blue, im.rows, im.cols);

    // read in maxValue
    in >> maxValue;

    // read in single space after maxValue
    in.read((char*)&space, sizeof(pixel));

    // fill arrays with data in file
    while (i < im.rows)
    {
        while (j < im.cols)
        {
            in.read((char*)&im.redGray[i][j], sizeof(pixel));
            in.read((char*)&im.green[i][j], sizeof(pixel));
            in.read((char*)&im.blue[i][j], sizeof(pixel));
            j++;
        }
        i++;
        j = 0;
    }
}



/** *********************************************************************
 * @author David Hill
 *
 * @par Description:
 * This function writes out the image data in binary.
 *
 * @param[in] out - the out stream.
 * @param[in] im - the image to write out.
 * @param[in] maxValue - the max value of the pixels
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   ofstream out;
   image im;
   int maxValue = 255;

   writeBinary(out, im, maxValue);

   out now contains all of the image data stored in "im".
   @endverbatim

 ***********************************************************************/

void writeBinary(ofstream& out, image& im, int& maxValue)
{
    int i = 0;
    int j = 0;
    pixel space = '\n'; // use this to print after maxValue

    // output magic number, any comments, columns and rows, and maxValue
    // with a space afterwards
    out << im.magicNumber << endl;
    out << im.comment;
    out << im.cols << " " << im.rows << endl;
    out << maxValue;
    out.write((char*)&space, sizeof(pixel));

    // output values from each array
    while (i < im.rows)
    {
        while (j < im.cols)
        {
            out.write((char*)&im.redGray[i][j], sizeof(pixel));
            out.write((char*)&im.green[i][j], sizeof(pixel));
            out.write((char*)&im.blue[i][j], sizeof(pixel));
            j++;
        }
        i++;
        j = 0;
    }
}



/** *********************************************************************
 * @author David Hill
 *
 * @par Description:
 * This function writes out the image data in ascii for grayscale images.
 *
 * @param[in] out - the out stream.
 * @param[in] im - the image to write out.
 * @param[in] maxValue - the max value of the pixels
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   ofstream out;
   image im;
   int maxValue = 255;

   writeGrayscaleAscii(out, im, maxValue);

   out now contains the grayscale image from "im".
   @endverbatim

 ***********************************************************************/

void writeGrayscaleAscii(ofstream& out, image& im, int& maxValue)
{
    int i = 0;
    int j = 0;

    // output magic number, any comments, columns and rows, and maxValue
    out << im.magicNumber << endl;
    out << im.comment;
    out << im.cols << " " << im.rows << endl;
    out << maxValue << endl;

    // output values from just the redGray array
    while (i < im.rows)
    {
        while (j < im.cols)
        {
            out << (int)im.redGray[i][j] << endl;
            j++;
        }
        i++;
        j = 0;
    }
}



/** *********************************************************************
 * @author David Hill
 *
 * @par Description:
 * This function writes out the image data in binary for grayscale images.
 *
 * @param[in] out - the out stream.
 * @param[in] im - the image to write out.
 * @param[in] maxValue - the max value of the pixels
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   ofstream out;
   image im;
   int maxValue = 255;

   writeGrayscaleBinary(out, im, maxValue);

   out now contains the grayscale image from "im".
   @endverbatim

 ***********************************************************************/

void writeGrayscaleBinary(ofstream& out, image& im, int& maxValue)
{
    int i = 0;
    int j = 0;
    pixel space = '\n'; // use this to print after maxValue

    // output magic number, any comments, columns and rows, and maxValue
    // with a space afterwards
    out << im.magicNumber << endl;
    out << im.comment;
    out << im.cols << " " << im.rows << endl;
    out << maxValue;
    out.write((char*)&space, sizeof(pixel));

    // output values from just the redGray array
    while (i < im.rows)
    {
        while (j < im.cols)
        {
            out.write((char*)&im.redGray[i][j], sizeof(pixel));
            j++;
        }
        i++;
        j = 0;
    }
}