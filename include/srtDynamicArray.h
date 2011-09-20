/*
 * A dynamic array similar in functionality to the vector container in C++
 * Growth Rate of 1.5
 * On removal of element not in front/back, last element is moved into its place rather than shifting
 */
#ifndef H_SRT_DYNAMIC_ARRAY
#define H_SRT_DYNAMIC_ARRAY

#include "srtAssert.h"
#include "stdlib.h"

#define SRT_DEFAULT_DYNAMIC_ARRAY_START_SIZE 4

typedef struct {
	void **buffer;
	unsigned int count;
	unsigned int size;
} srtDynamicArray;

srtDynamicArray * srtDynamicArray_Create(unsigned int size) {
	srtDynamicArray *array = malloc(sizeof(srtDynamicArray));
	SRT_ASSERT_MSG(array, "Dynamic Array Allocation Failed!");
	if (size > 0) {
		array->buffer = malloc(size * sizeof(void *));
		SRT_ASSERT_MSG(array->buffer, "Dynamic Array Allocation Failed!");
		array->size = size;
	} else {
		array->buffer = NULL;
		array->size = 0;
	}
	array->count = 0;
	return array;
}

void srtDynamicArray_Delete(srtDynamicArray *array) {
	if (array) {
		free(array->buffer);
		free(array);
	}
}

void * srtDynamicArray_Get(srtDynamicArray *array, unsigned int index) {
	SRT_ASSERT_MSG(array && array->buffer, "NULL array passed in to srtDynamicArray_Get()");
	SRT_ASSERT_MSG(index < array->count, "Index out of range!");
	void *tmp = array->buffer[index];
	return tmp;
}

void srtDynamicArray_Set(srtDynamicArray *array, unsigned int index, void * data) {
	SRT_ASSERT_MSG(array && array->buffer, "NULL array passed in to srtDynamicArray_Set()");
	SRT_ASSERT_MSG(index < array->count, "Index out of range!");
	array->buffer[index] = data;
}

unsigned int srtDynamicArray_PushBack(srtDynamicArray *array, void *data) {
	SRT_ASSERT_MSG(array, "NULL array passed in to srtDynamicArray_PushBack()");
	if (array->count == array->size) {
		void *tmp;
		if (array->buffer) {
			tmp = realloc(array->buffer, array->size * 1.5 * sizeof(void *));
			SRT_ASSERT_MSG(tmp, "Reallocation failed during Dynamic Array Push Back!");
			array->buffer = tmp;
			array->size  *= 1.5;
		} else {
			tmp = malloc(SRT_DEFAULT_DYNAMIC_ARRAY_START_SIZE * sizeof(void *));
			SRT_ASSERT_MSG(tmp, "Reallocation failed during Dynamic Array Push Back!");
		}
	}
	array->buffer[array->count] = data;
	array->count++;
	return array->count;
}

void * srtDynamicArray_PopBack(srtDynamicArray *array) {
	SRT_ASSERT_MSG(array && array->buffer, "NULL array passed in to srtDynamicArray_PopBack()");
	void * rm = NULL;
	if (array->count > 0) {
		rm = array->buffer[array->count - 1];
		array->count--;
	}
	return rm;
}

void * srtDynamicArray_RemoveAt(srtDynamicArray *array, unsigned int index) {
	SRT_ASSERT_MSG(array && array->buffer, "NULL array passed in to srtDynamicArray_RemoveAt()");
	SRT_ASSERT_MSG(index < array->count, "Index out of range!");
	void *tmp = array->buffer[index];
	for (; index < array->count - 1; ++index) {
		array->buffer[index] = array->buffer[index + 1];
	}
	array->buffer[array->count] = NULL;
	array->count--;
	return tmp;
}

int srtDynamicArray_Remove(srtDynamicArray *array, void *data) {
	SRT_ASSERT_MSG(array, "NULL array passed in to srtDynamicArray_Remove()");
	if (array->buffer) {
		unsigned int i;
		int found = 0;
		for (i = 0; i < array->count; ++i) {
			if (data == array->buffer[i]) {
				found = 1;
				break;
			}
		}
		if (found) {
			srtDynamicArray_RemoveAt(array, i);
			/*
			if (i == 0) {
				for (i = 1; i < array->count; ++i) {
					array->buffer[i - 1] = array->buffer[i];
				}
			}
			else if (i == array->count - 1)
				srtDynamicArray_PopBack(array);
			else {
				void *data = array->buffer[i];
				for (; i < array->count - 1; ++i) {
					array->buffer[i] = array->buffer[i + 1];
				}
				array->buffer[array->count] = NULL;
				array->count--;
			}
			*/
			return 1;
		}
	}
	return 0;
}

void srtDynamicArray_Resize(srtDynamicArray *array, unsigned int size) {
	SRT_ASSERT_MSG(array, "NULL array passed in to srtDynamicArray_Resize()");
	array->buffer = realloc(array->buffer, size);
	if (array->buffer) {
		array->size = size;
		if (array->size < array->count)
			array->count = array->size;
	} else {
		array->size = 0;
		array->count = 0;
	}
}

unsigned int srtDynamicArray_Count(srtDynamicArray *array) {
	if (array)
		return array->count;
	else
		return 0;
}

#endif