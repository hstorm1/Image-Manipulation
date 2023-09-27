/** *********************************************************************
 * @file
 *
 * @brief   functions that deal with allocating and freeing up arrays
 ***********************************************************************/

#include "netPBM.h"

 /** *********************************************************************
  * @author David Hill
  *
  * @par Description:
  * This function allocates a 2d array of pixels.
  *
  * @param[in] ptr - the array to be allocated
  * @param[in] rows - the number of rows in the array
  * @param[in] cols - the number of columns in the array
  *
  * @returns none
  *
  * @par Example:
    @verbatim
    pixel** arr;
    int rows = 20;
    int cols = 10;

    allocateArray(arr, rows, cols);

    "arr" is now allocated for that number of rows and cols.
    @endverbatim

  ***********************************************************************/

void allocateArray(pixel**& ptr, int rows, int cols)
{
    int i;

    // create new ptr
    ptr = new (nothrow) pixel * [rows];

    // if it is null exit with error message
    if (ptr == nullptr)
    {
        cout << "Unable to allocate memory" << endl;
        exit(1);
    }
    // fill each 1d array
    // if any of them are null, exit with error message and clean up
    for (i = 0; i < rows; i++)
    {
        ptr[i] = new pixel[cols];
        if (ptr[i] == nullptr)
        {
            freeUpArray(ptr, i);
            cout << "Unable to allocate memory" << endl;
            exit(1);
        }
    }
}



/** *********************************************************************
 * @author David Hill
 *
 * @par Description:
 * This function frees up a 2d array of pixels.
 *
 * @param[in] ptr - the array to be freed up
 * @param[in] rows - the number of rows in the array
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   pixel** arr;
   int rows = 20;

   freeUpArray(arr, rows);

   "arr" is now freed up.
   @endverbatim

 ***********************************************************************/

void freeUpArray(pixel**& ptr, int rows)
{
    int i;

    // if the array is null, just return
    if (ptr == nullptr)
    {
        return;
    }

    // delete each 1d array
    for (i = 0; i < rows; i++)
    {
        delete[] ptr[i];
    }
    delete[] ptr;
}