#include <stdio.h>
#include <stdlib.h>

// Define the array ADT structure
typedef struct
{
	int *arr;
	int size;
	int length;
} Array;

// function declartion
Array *createArray(int size);   // create new array
int fill(Array *array);         // fill array
void display(Array *array);     // print the array
int getElement(Array *array, int index); // get element from array
void setElement(Array *array, int index, int value); // set elemnt in array (override)
int getSize(Array *array);      // get the size of array
int get_length(Array *array);   // get number of item in array
int insert(Array *array, int index, int new_item);// insert item in specific index
int delete(int index, Array *array); // delete index from array
int append(int new_item, Array *array); // append aitem in the end of array
Array *Enlarge(Array *array, int new_size); // update the size of array
Array *merge(Array *arr1, Array *arr2); // merge two array in one array
int search(Array *array, int key);// search in array

// Function to create a new array
Array *createArray(int size)
{
	Array *newArray = malloc(sizeof(Array));
	newArray->size = size;
	newArray->length = 0;
	newArray->arr = malloc(size * sizeof(int));
	return (newArray);
}
int fill(Array *array)
{
	int no_of_item;
	printf("enter the number of items\n ");
	scanf("%d", &no_of_item);

	if (no_of_item > array->size)
	{
		return (-1);
	}
	else
	{
		for (int i = 0; i < no_of_item; i++)
		{
			printf("enter int the index %d : ", i + 1);
			scanf("%d", &array->arr[i]);
			array->length++;
		}
	}
}
void display(Array *array)
{
	int length = get_length(array);

	for (int i = 0; i < length; i++)
		printf("%d ", array->arr[i]);

	printf("\n");
}

int getSize(Array *array)
{
	return array->size;
}

int get_length(Array *array)
{
	return (array->length);
}

int getElement(Array *array, int index)
{
	if (index < 0 || index >= array->size)
		exit(1);

	return (array->arr[index]);
}

void setElement(Array *array, int index, int value)
{
	if (index < 0 || index >= array->size)
	{
		printf("Error: Index out of bounds\n");
		exit(1);
	}
	array->arr[index] = value;
}

int insert(Array *array, int index, int new_item)
{
	if (index >= 0 && index < array->size)
	{
		for (int i = array->length; i > index; i--)
		{
			array->arr[i] = array->arr[i - 1];
		}

		array->arr[index] = new_item;
		array->length++;
	}
	else
		return (-1);

	return (0);
}

int delete(int index, Array *array)
{ 
	if (index >= 0 && index < array->size)
	{
		for (int i = index; i < array->length - 1; i++)
		{
			array->arr[i] = array->arr[i + 1];
		}
		array->length--;
	}
	else
		return (-1);
	return (0);
}

int append(int new_item, Array *array)
{
	if (array->length >= array->size)
		return (-1);

	array->arr[array->length] = new_item;
}

Array *Enlarge(Array *array, int new_size)
{

	if (new_size <= array->size)
	{
		return (array);
	}
	else
	{
		array->size = new_size;

		int *old = array->arr;
		array->arr = malloc(sizeof(int) * new_size);
		if (array->arr == NULL)
		{
			array->arr = old;
			free(old);
			return (array);
		}

		for (int i = 0; i < array->length; i++)
		{
			array->arr[i] = old[i];
		}

		free(old);
	}
	return (array);
}
int search(Array *array, int key)
{
	for (int i = 0; i < array->length; i++)
	{
		if (key == array->arr[i])
		{
			return (i);
		}
	}
	return (-1);
}
Array *merge(Array *arr1, Array *arr2)
{
	int new_size = arr1->size + arr2->size;
	int *old = arr1->arr;

	arr1->arr = malloc(sizeof(int) * new_size);
	if (arr1 == NULL)
		return (NULL);

	arr1->size = new_size;
	int i;

	for (i = 0; i < arr1->length; i++)
	{
		arr1->arr[i] = old[i];
	}
	free(old);

	int j = i;
	for (int i = 0; i < arr2->length; i++)
	{
		arr1->arr[j++] = arr2->arr[i];
		arr1->length++;
	}

	return (arr1);
}

void destroyArray(Array *array)
{
	free(array->arr);
	free(array);
}

// Example usage
int main()
{
	int size;
	printf("enter the size of array : ");
	scanf("%d",&size);
	Array *myArray = createArray(size);

	int n = fill(myArray);
	if (n == -1)
		return (1);

	int size = getSize(myArray);
	printf("Array size: %d\n", size);
	display(myArray);

	int index, num;
	printf("enter the index to insert the number ");
	scanf("%d", &index);

	printf("enter the number to be inserted in this index %d : ",index);
	scanf("%d",&num);
	n = insert(myArray, index, num);
	if (n == -1)
		printf("faild insert element ");
	else
		display(myArray);

	printf("enter the new size to enlarge array");
	scanf("%d", &size);
	Enlarge(myArray, size);

	printf("new size = %d\n", getSize(myArray));

	Array *arr2 = createArray(5);
	n = fill(arr2);
	if (n == -1)
		return (1);
	myArray = merge(myArray, arr2);
	display(myArray);
	printf("size = %d && length = %d \n", getSize(myArray), get_length(myArray));

	destroyArray(myArray);
	destroyArray(arr2);

	return 0;
}
