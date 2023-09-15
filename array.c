#include <stdio.h>
#include <stdlib.h>

// Define the array ADT structure
typedef struct
{
	int *arr;   // Pointer to the array
	int size;   // Maximum size of the array
	int length; // Current number of elements in the array
} Array;

// Function declarations
Array *createArray(int size);				// Create a new array
int fill(Array *array);				 	// Fill the array with user input
void display(Array *array);				// Print the elements of the array
int getElement(Array *array, int index);		// Get the element at a specific index
void setElement(Array *array, int index, int value);	// Set the element at a specific index
int getSize(Array *array);				// Get the maximum size of the array
int get_length(Array *array);				// Get the current number of elements in the array
int insert(Array *array, int index, int new_item);	// Insert an element at a specific index
int delete(int index, Array *array);			// Delete an element at a specific index
int append(int new_item, Array *array);			// Append an element to the end of the array
Array *Enlarge(Array *array, int new_size);		// Increase the size of the array
Array *merge(Array *arr1, Array *arr2);			// Merge two arrays into one array
int search(Array *array, int key);			// Search for an element in the array

// Function to create a new array
Array *createArray(int size)
{
	Array *newArray = malloc(sizeof(Array));
	newArray->size = size;
	newArray->length = 0;
	newArray->arr = malloc(size * sizeof(int));
	return (newArray);
}

// Function to fill the array with user input
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

	return (0);
}

// Function to display the elements of the array
void display(Array *array)
{
	int length = get_length(array);

	for (int i = 0; i < length; i++)
	{
		printf("%d ", array->arr[i]);
	}

	printf("\n");
}

// Function to get the maximum size of the array
int getSize(Array *array)
{
	return array->size;
}

// Function to get the current number of elements in the array
int get_length(Array *array)
{
	return array->length;
}

// Function to get the element at a specific index
int getElement(Array *array, int index)
{
	if (index < 0 || index >= array->size)
		exit(1);

	return array->arr[index];
}

// Function to set the element at a specific index
void setElement(Array *array, int index, int value)
{
	if (index < 0 || index >= array->size)
	{
		printf("Error: Index out of bounds\n");
		exit(1);
	}

	array->arr[index] = value;
}

// Function to insert an element at a specific index
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

// Function to delete an element at a specific index
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

// Function to append an element to the end of the array
int append(int new_item, Array *array)
{
	if (array->length >= array->size)
		return (-1);

	array->arr[array->length] = new_item;

	return (0);
}

// Function to increase the size of the array
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

// Function to merge two arrays into one array
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

// Function to search for an element in the array
int search(Array *array, int key)
{
	for (int i = 0; i < array->length; i++)
	{
		if (array->arr[i] == key)
			return i;
	}
	return (-1);
}

int main()
{
	int size;
	printf("Enter the size of the array: ");
	scanf("%d", &size);

	Array *array = createArray(size);

	int choice, length;
	int index, element, new_size;
	int search_key;
	int result;

	do
	{
		printf("\nArray Operations:\n");
		printf("1. Fill the array\n");
		printf("2. Display the array\n");
		printf("3. Get the element at a specific index\n");
		printf("4. Set the element at a specific index\n");
		printf("5. Get the size of the array\n");
		printf("6. Get the current number of elements in the array\n");
		printf("7. Insert an element at a specific index\n");
		printf("8. Delete an element at a specific index\n");
		printf("9. Append an element to the end of the array\n");
		printf("10. Enlarge the array\n");
		printf("11. Merge two arrays\n");
		printf("12. Search for an element in the array\n");
		printf("0. Exit\n\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			fill(array);
			break;
		case 2:
			display(array);
			break;
		case 3:
			printf("Enter the index: ");
			scanf("%d", &index);
			element = getElement(array, index);
			printf("Element at index %d: %d\n", index, element);
			break;
		case 4:
			printf("Enter the index: ");
			scanf("%d", &index);
			printf("Enter the value: ");
			scanf("%d", &element);
			setElement(array, index, element);
			printf("Element set\n");
			break;
		case 5:
			size = getSize(array);
			printf("Size of the array: %d\n", size);
			break;
		case 6:
			length = get_length(array);
			printf("Current number of elements in the array: %d\n", length);
			break;
		case 7:
			printf("Enter the index: ");
			scanf("%d", &index);
			printf("Enter the element: ");
			scanf("%d", &element);
			result = insert(array, index, element);
			if (result == -1)
				printf("Error: Index out of bounds\n");
			else
				printf("Element inserted\n");
			break;
		case 8:
			printf("Enter the index: ");
			scanf("%d", &index);
			result = delete(index, array);
			if (result == -1)
				printf("Error: Index out of bounds\n");
			else
				printf("Element deleted\n");
			break;
		case 9:
			printf("Enter the element: ");
			scanf("%d", &element);
			result = append(element, array);
			if (result == -1)
				printf("Error: Array is full\n");
			else
				printf("Element appended\n");
			break;
		case 10:
			printf("Enter the new size: ");
			scanf("%d", &new_size);
			array = Enlarge(array, new_size);
			printf("Array enlarged\n");
			break;
		case 11:
			printf("Enter the size of the first array: ");
			scanf("%d", &size);
			Array *arr1 = createArray(size);
			fill(arr1);

			printf("Enter the size of the second array: ");
			scanf("%d", &size);
			Array *arr2 = createArray(size);
			fill(arr2);

			Array *mergedArray = merge(arr1, arr2);
			printf("Merged array: ");
			display(mergedArray);
			break;
		case 12:
			printf("Enter the element to search: ");
			scanf("%d", &search_key);
			result = search(array, search_key);
			if (result == -1)
				printf("Element not found in the array\n");
			else
				printf("Element found at index %d\n", result);
			break;
		case 0:
			printf("Exiting program\n");
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	} while (choice != 0);

	// Free the memory allocated for the array
	free(array->arr);
	free(array);

	return (0);
}