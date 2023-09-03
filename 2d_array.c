#include <stdio.h>
#include <stdlib.h>

// Define the structure for 2D array ADT
typedef struct
{
	int **arr;      // Pointer to the 2D array
	int rows;       // Number of rows
	int columns;    // Number of columns
	int length_row; // The actual number of items in the row
	int length_col; // The actual number of items in the col
} Array2D;

/******************************function declaration*********************************/
Array2D *createArray2D(int rows, int columns);
void fill(Array2D *array); //
void print(Array2D *array);
int getValue(Array2D *array, int row, int col);
void setValue(Array2D *array, int row, int col, int value);
int append(int new_item, Array2D *array);
int insert(int new_item, int row, int col, Array2D *arr);
int delete(int row, int col, Array2D *arr);
Array2D *Enlarge(Array2D *array, int new_row, int new_col);
void multi_matrix(Array2D *arr1, Array2D *arr2);
int search(int key, Array2D *array);
void count(Array2D *array);
void freeArray2D(Array2D *array);
/*************************************************************************************/

// Function to create a new 2D array
Array2D *createArray2D(int rows, int columns)
{
	// Allocate memory for the 2D array structure
	Array2D *myarray = malloc(sizeof(Array2D));

	// Allocate memory for the rows and initialize by zero
	myarray->arr = calloc(rows, sizeof(int *)); // malloc(rows * sizeof(int *)) = calloc(rows, sizeof(int *))

	// Allocate memory for the columns of each row and initialize by zero
	for (int i = 0; i < rows; i++)
	{
		myarray->arr[i] = calloc(columns, sizeof(int));
	}

	myarray->rows = rows;
	myarray->columns = columns;
	myarray->length_col = 0; // لسه مافيش عناصر دخلت
	myarray->length_row = 0;

	return myarray;
}
// fill the matrix of row = length_row and col = length_col
void fill(Array2D *array)
{
	printf("enter number of row and number of col ");
	scanf("%d %d", &array->length_row, &array->length_col);
	array->length_row--, array->length_col--;

	for (int i = 0; i <= array->length_row; i++)
	{
		for (int j = 0; j <= array->length_col; j++)
		{
			printf("Enter value for position (%d, %d): ", i, j);
			scanf("%d", &array->arr[i][j]);
		}
	}
}
// enlarge the matrix
Array2D *Enlarge(Array2D *array, int new_row, int new_col)
{

	if (array->columns >= new_col || array->rows >= new_row)
	{
		return (array);
	}
	else
	{
		int old_row = array->rows, old_col = array->columns;
		array->rows = new_row;
		array->columns = new_col;
		int **old = array->arr; // pointer to point to array->arr

		// initialize rows by zero
		array->arr = calloc(new_row, sizeof(int *));
		if (array->arr == NULL)
		{
			array->arr = old;
			free(old);
			return (array);
		}

		for (int i = 0; i < array->rows; i++)
		{
			// initialize columns by zero
			array->arr[i] = calloc(new_col, sizeof(int));
		}

		for (int i = 0; i < old_row; i++)
		{
			for (int j = 0; j < old_row; j++)
				array->arr[i][j] = old[i][j];
		}
		free(old);
	}
	return (array);
}
// print the matrix
void print(Array2D *array)
{
	for (int i = 0; i < array->rows; i++)
	{
		for (int j = 0; j < array->columns; j++)
		{
			printf(" %d ", array->arr[i][j]);
		}
		printf("\n");
	}
}

// Function to get the value at a specific position in the 2D array
int getValue(Array2D *array, int row, int col)
{
	// Check if the position is within the valid range
	if (row < 0 || row >= array->length_row || col < 0 || col >= array->length_col)
	{
		return -1;
	}

	return array->arr[row][col];
}

// Function to set the value at a specific position in the 2D array
void setValue(Array2D *array, int row, int col, int value)
{
	// Check if the position is within the valid range
	if (row < 0 || row >= array->length_row || col < 0 || col >= array->length_col)
	{
		printf("Invalid position!\n");
		return;
	}

	array->arr[row][col] = value;
}

// Function to append an element to the end of the 2D array
int append(int new_item, Array2D *array)
{
	if (array->length_row >= array->rows && array->length_col >= array->columns)
		return -1;
	// لو أخر عنصر في الاراي فاضي هنضيف العنصر وبعد كدا نطلع
	if (array->arr[array->length_row][array->length_col] == 0)
	{
		array->arr[array->length_row][array->length_col] = new_item;
		return 0;
	}

	int flag = array->length_col + 1 == array->columns ? 1 : 0;

	if (flag)
	{
		// هنضيف صف جديد
		array->length_row++;
		// new row to a dd the element
		array->arr[array->length_row][0] = new_item;
		return (1);
	}
	// هنضيف عمود جديد
	array->length_col++;
	// new col to add the element
	array->arr[0][array->length_col] = new_item;
	return (2);
}
// insert item in spcific index without override the item in this index
int insert(int new_item, int row, int col, Array2D *arr)
{
	int i, j;
	if (col > arr->length_col && row > arr->length_row)
		return (-1);

	int res = append(0, arr); // هترجع 1 لو ضيفنا الصفر في صف جديد أو 2 لو ضيفنا الصفر في عمود جديد
	if (res == 1)
	{
		i = arr->length_row, j = 0; // هنمشي من اول العمود إلي في الصف الجديد

		while (i != row)
		{
			if (j == 0) // لو وصلنا لأول عمود في الصف روح علي الصف إلي قبله
			{
				arr->arr[i][j] = arr->arr[i - 1][arr->length_col]; // روح علي الصف إلي قبله
				i--, j = arr->length_col;
				continue;
			}
			// إفضل ماشي لغاية ماتوصل لأول عمود في الصف ده
			arr->arr[i][j] = arr->arr[i][j - 1];
			j--;
		}
		// تماما وصلنا للصف إلي فيه العنصر هنبدأ نمشي علي كل عمود عشان نوصله
		while (j != col)
		{
			arr->arr[i][j] = arr->arr[i][j - 1], j--;
		}
		arr->arr[i][j] = new_item; // insert كدا وصلنا للمكان إلي عاوزين نعمل فيه

		return (0);
	}
	else if (res == 2) // في حالة لو ضفنا العنصر في عمود جديد
	{
		i = 0, j = arr->length_col; // هنمشي من أول صف في العمود الجديد

		while (j != col) // هنفضل نلوب لغاية مانوصل للعمود إلي عاوزين نحط العنصر فيه
		{
			if (i == 0) // لو وصلنا لأول صف في العمود روح علي العمود إلي قبله
			{
				arr->arr[i][j] = arr->arr[arr->length_row][j - 1]; // روح علي العمود إلي قبله
				j--, i = arr->length_row;
				continue;
			}
			// إفضل ماشي لغاية ماتوصل لأول صف في العمود ده
			arr->arr[i][j] = arr->arr[i - 1][j];
			i--;
		}
		// تماما وصلنا للعمود إلي فيه العنصر هنبدأ نمشي علي كل صف عشان نوصله
		while (i != row)
		{
			arr->arr[i][j] = arr->arr[i - 1][j], i--;
		}
		arr->arr[i][j] = new_item; // كدا وصلنا للمكان الحمد الله
		return 0;
	}
}
// delete item from spacific index
// بس هنمشي بالعكس  insert نفس ال
int delete(int row, int col, Array2D *arr)
{
	int i, j;
	if (col > arr->length_col || row > arr->length_row)
		return (-1);
	i = row, j = col; // إلي عاوزين نحذفه  index هنقف عند ال

	while (i != arr->length_row) // طالما مش وصلنا لأاخر صف أفضل أعمل لووب
	{
		if (j == arr->length_col) // في كل صف لما توصل لأخر عمود إنزل علي الصف إلي بعده
		{
			arr->arr[i][j] = arr->arr[i + 1][0];
			i++;
			j = 0;
			continue;
		}
		arr->arr[i][j] = arr->arr[i][j + 1];
		j++;
	}
	// تمام كده وصلنا لأخر صف موجود هنمشي بقي علي الأعمده بتاعته
	j = 0;
	while (j != arr->length_col)
	{
		arr->arr[i][j] = arr->arr[i][j + 1];
		j++;
	}
	arr->arr[i][j] = 0; // صفر index حط في اخر
}
// matrix multiplication
void multi_matrix(Array2D *arr1, Array2D *arr2)
{

	Array2D *res = createArray2D(arr1->length_row + 1, arr2->length_col + 1);

	printf("Multiplication of given two matrices is:\n");

	for (int i = 0; i <= arr1->length_row; i++)
	{
		for (int j = 0; j <= arr2->length_col; j++)
		{
			res->arr[i][j] = 0;

			for (int k = 0; k <= arr2->length_row; k++)
			{
				res->arr[i][j] += arr1->arr[i][k] * arr2->arr[k][j];
			}

			printf("%d\t", res->arr[i][j]);
		}

		printf("\n");
	}
	freeArray2D(res);
}
// search in matrix
int search(int key, Array2D *array)
{
	for (int i = 0; i <= array->length_row; i++)
	{
		for (int j = 0; j <= array->length_row; j++)
		{
			if (key == array->arr[i][j])
				return key;
		}
	}
	return (0);
}
// count number of element and The actual row and actual col
void count(Array2D *array)
{
	int count = 0;
	for (int i = 0; i <= array->length_row; i++)
		for (int j = 0; j <= array->length_col; j++)
			count++;

	printf("count = %d\n", count);
	printf("len_row = %d\n", array->length_row + 1);
	printf("len_col = %d\n", array->length_col + 1);
}

// Function to free the memory allocated for the 2D array
void freeArray2D(Array2D *array)
{
	// Free the memory for the columns of each row
	for (int i = 0; i < array->rows; i++)
	{
		free(array->arr[i]);
	}

	// Free the memory for the rows
	free(array->arr);

	// Free the memory for the array structure
	free(array);
}

int main()
{
	// Create a 2D array with 3 rows and 4 columns
	Array2D *array1 = createArray2D(4, 4);
	fill(array1);
	print(array1);
	printf("\n***************************\n");
	insert(99, 1, 0, array1);
	// append(99,array1);
	print(array1);
	count(array1);
	/*
	Array2D *array2 = createArray2D(4, 4);
	fill(array2);
	print(array2);
	printf("\n");
	multi_matrix(array1, array2);
	*/
	freeArray2D(array1);
	// freeArray2D(array2);

	return 0;
}
