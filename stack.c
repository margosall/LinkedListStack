#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF 200

typedef struct stackNode
{
	int data;
	struct stackNode *previousNode;
	struct stackNode *nextNode;
} stackNode;

int Push(stackNode **stack, int input);
int Pop(stackNode **stack);
void FreeStack(stackNode **stack);
void Peek(stackNode *stack);
void Duplicate(stackNode **stack);
void Swap(stackNode *stack);
void Display(stackNode **stack);
void Rotate(stackNode *stack);
void RotateN(stackNode *stack, int n);
void Print(stackNode *stack);

int main(void)
{
	char userChoice = '3';
	char userInput[BUFF];
	int userInteger = 0;
	int charIndex = 0;
	int userInputSize;
	stackNode *stack = NULL;

	while(userChoice)
	{
		//system("clear");
		printf("Choose operation\n\t0 Push\n\t1 Pop\n\t2 Peek\n\t3 Duplicate\n\t4 Swap\n\t5 Display\n\t6 Rotate\n\t7 Rotate N\n\t8 Print\n\t9 Exit\n>");
		if(scanf("%c%*c",&userChoice) == 1)
		{
			if(userChoice == '0')
			{
				printf("Enter number\n>");
				scanf("%s%c",userInput,&userChoice);
				if(userChoice == '\n')
				{
					userInputSize = strlen(userInput);
					printf("%s\n",userInput);
					userInteger = 0;
					charIndex = 0;
					do{
						userInteger *= 10;
						userInteger += userInput[charIndex] - '0';
						charIndex++;
					}while(charIndex < userInputSize);
					printf("userInteger %d\n",userInteger);
					Push(&stack, userInteger);
				}
			}
			else if(userChoice == '1')
			{
				Pop(&stack);
			}
			else if(userChoice == '2')
			{
				Peek(stack);
			}
			else if(userChoice == '3')
			{
				Duplicate(&stack);
			}
			else if(userChoice == '4')
			{
				Swap(stack);
			}
			else if(userChoice == '5')
			{
				Display(&stack);
			}
			else if(userChoice == '6')
			{
				Rotate(stack);
			}
			else if(userChoice == '7')
			{
				printf("Enter n-th node index\n>");
				scanf("%s%c",userInput,&userChoice);
				if(userChoice == '\n')
				{
					userInputSize = strlen(userInput);
					userInteger = 0;
					charIndex = 0;
					do{
						userInteger *= 10;
						userInteger += userInput[charIndex] - '0';
						charIndex++;
					}while(charIndex < userInputSize);
					printf("userInteger %d\n",userInteger);
				}
				RotateN(stack,userInteger);
			}
			else if(userChoice == '8')
			{
				Print(stack);
			}
			else if(userChoice == '9')
			{
				userChoice = 0;
			}
		}
	}

	FreeStack(&stack);
	return 0;
}
int Push(stackNode **stack, int input)
{
	stackNode *previousTemp;
	previousTemp = *stack;
	if((*stack) != NULL)
	{
		(*stack)->nextNode = (stackNode*)calloc(1,sizeof(stackNode));
		if((*stack)->nextNode == NULL)
		{
			printf("Overflow!\n");
			return 0;
		}
		(*stack) = (*stack)->nextNode;
		(*stack)->previousNode = previousTemp;
	}
	else
	{
		(*stack) = (stackNode*)calloc(1,sizeof(stackNode));
		if((*stack) == NULL)
		{
			return 0;
		}
		(*stack)->previousNode = NULL;
	}
	(*stack)->data = input;
	return 1;
}
int Pop(stackNode **stack)
{
	if(*stack == NULL)
	{
		printf("UnderFlow\n");
		return 0;
	}
	stackNode *previousTemp;
	previousTemp = (*stack)->previousNode;
	if((*stack) != NULL)
	{
		free((*stack));
		(*stack) = previousTemp;
		return 1;
	}
	return 0;
}
void Peek(stackNode *stack)
{
	if(stack != NULL)
	{
		printf("%p ",stack);
		//printf("%p ",stack->data);
		printf("%d\n",stack->data);
	}
	else
	{
		printf("Empty stack!\n");
	}
}
void Duplicate(stackNode **stack)
{
	if(*stack != NULL)
	{
		Push(stack,(*stack)->data);
	}
	else
	{
		printf("Empty stack!\n");
	}
}
void Swap(stackNode *stack)
{
	if(stack == NULL)
	{

		printf("Empty stack!\n");
	}
	else if(stack->previousNode == NULL)
	{
		printf("Only one stack element!\n");
	}
	else
	{
		int dataTemp;
		dataTemp = stack->data;
		stack->data = (stack->previousNode)->data;
		(stack->previousNode)->data = dataTemp;
	}
}
void Display(stackNode **stack)
{
	stackNode *previousTemp;
	if(*stack == NULL)
	{
		printf("Empty stack!\n");
	}
	while((*stack) != NULL)
	{
		previousTemp = (*stack)->previousNode;
		Peek(*stack);
		free((*stack));
		(*stack) = previousTemp;
	}
}
void Print(stackNode *inputStack)
{
	stackNode *stack = inputStack;
	if(stack == NULL)
	{
		printf("Empty stack!\n");
	}
	while(stack != NULL)
	{
		Peek(stack);
		stack = stack->previousNode;
	}
}
void Rotate(stackNode *stack)
{
	printf("Rotate\n");
	int dataTemp;
	stackNode *lastNode = stack;
	stackNode *firstNode = stack;
	if(firstNode!=NULL && (firstNode->previousNode != NULL))
	{
		/*Find first node*/
		while(firstNode->previousNode != NULL)
		{
			firstNode=firstNode->previousNode;
		}
		dataTemp = firstNode->data;
		firstNode->data = lastNode->data;
		lastNode->data = dataTemp;
		while((firstNode->nextNode != lastNode->previousNode) && (firstNode->nextNode != lastNode))
		{
			firstNode = firstNode->nextNode;
			lastNode = lastNode->previousNode;

			dataTemp = firstNode->data;
			firstNode->data = lastNode->data;
			lastNode->data = dataTemp;

		}
	}
}
void RotateN(stackNode *stack, int n)
{
	int dataTemp;
	int nodeCount = 1, nodeIndex;
	stackNode *lastNode;
	stackNode *firstNode = stack;
	if((firstNode!=NULL) && (n > 1))
	{
		/*Find first node*/
		while(firstNode->previousNode != NULL)
		{
			firstNode=firstNode->previousNode;
			nodeCount++;
		}
		if(n >= nodeCount)
		{
			Rotate(stack);
		}
		else
		{
			//Set node on n position as lastNode
			lastNode = firstNode;
			for(nodeIndex = 1;nodeIndex < n;nodeIndex++)
			{
				lastNode = lastNode->nextNode;
			}
			printf("Lastnode data %d\n",lastNode->data);
			printf("firstNode data %d\n",firstNode->data);
			dataTemp = firstNode->data;
			firstNode->data = lastNode->data;
			lastNode->data = dataTemp;

			//Rotate
			while((firstNode->nextNode != lastNode->previousNode) && (firstNode->nextNode != lastNode))
			{
				firstNode = firstNode->nextNode;
				lastNode = lastNode->previousNode;

				dataTemp = firstNode->data;
				firstNode->data = lastNode->data;
				lastNode->data = dataTemp;
			}
		}
	}
}
void FreeStack(stackNode **stack)
{
	stackNode *previousTemp;
	while((*stack) != NULL)
	{
		previousTemp = (*stack)->previousNode;
		free((*stack));
		(*stack) = previousTemp;
	}
}
