/** *********************************************************************
 * @file
 *
 * @brief   functions that deal with manipulating the images
 ***********************************************************************/

#include "netPBM.h"

 /** *********************************************************************
  * @author David Hill
  *
  * @par Description:
  * This function flips an image on the X axis.
  *
  * @param[in] im - the image to be manipulated
  *
  * @returns none
  *
  * @par Example:
    @verbatim
    image im;

    flipX(im);

    "im" is now flipped on the X axis.
    @endverbatim

  ***********************************************************************/

void flipX(image& im)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int r = im.rows - 1;
    while (i < im.rows / 2)
    {
        while (j < im.cols)
        {
            // swap value on top row with the one on bottom row
            // do this for each array
            temp = im.redGray[i][j];
            im.redGray[i][j] = im.redGray[r][j];
            im.redGray[r][j] = temp;
            temp = im.blue[i][j];
            im.blue[i][j] = im.blue[r][j];
            im.blue[r][j] = temp;
            temp = im.green[i][j];
            im.green[i][j] = im.green[r][j];
            im.green[r][j] = temp;
            j++;
        }
        // move one row closer to the middle on both sides
        i++;
        r--;
        j = 0;
    }
}



/** *********************************************************************
 * @author David Hill
 *
 * @par Description:
 * This function flips an image on the Y axis.
 *
 * @param[in] im - the image to be manipulated
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   image im;

   flipY(im);

   "im" is now flipped on the Y axis.
   @endverbatim

 ***********************************************************************/

void flipY(image& im)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int c = im.cols - 1;
    while (j < im.cols / 2)
    {
        while (i < im.rows)
        {
            // swap value on left col with the one on right col
            // do this for each array
            temp = im.redGray[i][j];
            im.redGray[i][j] = im.redGray[i][c];
            im.redGray[i][c] = temp;
            temp = im.blue[i][j];
            im.blue[i][j] = im.blue[i][c];
            im.blue[i][c] = temp;
            temp = im.green[i][j];
            im.green[i][j] = im.green[i][c];
            im.green[i][c] = temp;
            i++;
        }
        // move one col closer to the middle on both sides
        j++;
        c--;
        i = 0;
    }
}



/** *********************************************************************
 * @author David Hill
 *
 * @par Description:
 * This function rotates an image clockwise.
 *
 * @param[in] im - the image to be manipulated
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   image im;

   rotateCW(im);

   "im" is now rotated 90 degrees in the clockwise direction.
   @endverbatim

 ***********************************************************************/

void rotateCW(image& im)
{
    int r = im.rows;
    int c = im.cols;
    int i = 0;
    int j = r - 1;
    int x = 0;
    int y = 0;

    // create and allocate 3 new arrays with the opposite sizes
    // (rows equals cols of im, and cols equals rows of im)
    pixel** redGrayNew;
    pixel** greenNew;
    pixel** blueNew;
    allocateArray(redGrayNew, c, r);
    allocateArray(greenNew, c, r);
    allocateArray(blueNew, c, r);

    // copy each row from the original array (starting at top left)
    // down each column of the new array (starting from top right)
    while (x < c)
    {
        while (y < r)
        {
            redGrayNew[x][y] = im.redGray[j][i];
            greenNew[x][y] = im.green[j][i];
            blueNew[x][y] = im.blue[j][i];
            y++;
            j--;
        }
        i++;
        x++;
        y = 0;
        j = r - 1;
    }
    // change rows to cols and cols to rows back to im
    im.rows = c;
    im.cols = r;

    // copy new arrays back to the arrays in im
    im.redGray = redGrayNew;
    im.blue = blueNew;
    im.green = greenNew;
}



/** *********************************************************************
 * @author David Hill
 *
 * @par Description:
 * This function rotates an image counterclockwise.
 *
 * @param[in] im - the image to be manipulated
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   image im;

   rotateCCW(im);

   "im" is now rotated 90 degrees in the counterclockwise direction.
   @endverbatim

 ***********************************************************************/

void rotateCCW(image& im)
{
    int r = im.rows;
    int c = im.cols;
    int i = 0;
    int j = c - 1;
    int x = 0;
    int y = 0;
    
    // create and allocate 3 new arrays with the opposite sizes
    // (rows equals cols of im, and cols equals rows of im)
    pixel** redGrayNew;
    pixel** greenNew;
    pixel** blueNew;
    allocateArray(redGrayNew, c, r);
    allocateArray(greenNew, c, r);
    allocateArray(blueNew, c, r);

    // copy each row from the original array (starting from top left)
    // down each column of the new array (starting from bottom left)
    while (x < c)
    {
        while (y < r)
        {
            redGrayNew[x][y] = im.redGray[i][j];
            greenNew[x][y] = im.green[i][j];
            blueNew[x][y] = im.blue[i][j];
            y++;
            i++;
        }
        j--;
        x++;
        y = 0;
        i = 0;
    }

    // change rows to cols and cols to rows back to im
    im.rows = c;
    im.cols = r;

    // copy new arrays back to the arrays in im
    im.redGray = redGrayNew;
    im.blue = blueNew;
    im.green = greenNew;
}



/** *********************************************************************
 * @author David Hill
 *
 * @par Description:
 * This function changes the image to a grayscale image.
 *
 * @param[in] im - the image to be manipulated
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   image im;

   grayscale(im);

   "im" is now a grayscale image.
   @endverbatim

 ***********************************************************************/

void grayscale(image& im)
{
    int i = 0;
    int j = 0;

    // apply grayscale equation just to each pixel in the redgray array
    while (i < im.rows)
    {
        while (j < im.cols)
        {
             im.redGray[i][j] = (int) (.3 * im.redGray[i][j] + .6 *
                im.green[i][j] + .1 * im.blue[i][j]);
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
 * This function changes the image to a sepia image.
 *
 * @param[in] im - the image to be manipulated
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   image im;

   sepia(im);

   "im" is now a sepia image.
   @endverbatim

 ***********************************************************************/

void sepia(image& im)
{
    int val = 0;
    int i = 0;
    int j = 0;

    // apply sepia equation to each pixel in each array
    // if value goes over 255, set it back to 255
    while (i < im.rows)
    {
        while (j < im.cols)
        {
            int r = im.redGray[i][j];
            int g = im.green[i][j];
            int b = im.blue[i][j];
            val = (int) (0.393 * r + 0.769 * g + 0.189 * b);
            if (val > 255)
            {
                im.redGray[i][j] = 255;
            }
            else
            {
                im.redGray[i][j] = val;
            }
            val = (int) (0.349 * r + 0.686 * g + 0.168 * b);
            if (val > 255)
            {
                im.green[i][j] = 255;
            }
            else
            {
                im.green[i][j] = val;
            }
            val = (int) (0.272 * r + 0.534 * g + 0.131 * b);
            if (val > 255)
            {
                im.blue[i][j] = 255;
            }
            else
            {
                im.blue[i][j] = val;
            }
            j++;
        }
        i++;
        j = 0;
    }
}