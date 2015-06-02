%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define YYDEBUG 1	
extern int lineNumber;

// Узел дерева	
struct treeNode
{
	int nodeType;          // Тип узла дерева / семантического значения
	union
	{
		struct treeNode *node;
		struct variableInfo* var;
		struct constantInfo *constant;
		struct functionInfo* func;    			
		struct paramsListNode* params;
	} value;
	struct treeNode *left;
	struct treeNode *right;
};


//--------------------------------------------------
struct functionInfo
{
    char *name;
    char type;
    struct paramsListNode *params;
    struct treeNode *operations;
	struct variableListNode* varDeclaratons;
};

struct funcTableNode
{
    struct functionInfo *func;
    struct funcTableNode *next;
};
//----------------------------------------------------

struct parameterInfo
{
    char* name;
    char type;
    struct variableInfo* var;
	struct treeNode* node;
};

struct paramsListNode
{
    struct parameterInfo* param;
    struct paramsListNode* next;
};
//---------------------------------------------------

struct arrayInfo
{
    int sizeOfElement;
    int length;
    void *ptr;
};

struct constantInfo
{
    char type;
    union
    {
        int intValue;
        char charValue;
        struct arrayInfo* arrValue;
    } value;
};

//-------------------------------------------------
struct variableInfo
{
    int isParam;
    char* name;
    char type;
    union
    {
        int intValue;
        char charValue;
        struct arrayInfo* arrayValue;
    } value;
};

struct variableListNode
{
    struct variableInfo *var;
    struct variableListNode *next;
};
//--------------------------------------------------


//struct treeNode* treeRoot = NULL;       // Корень дерева
struct funcTableNode* FuncTable = NULL; // Список функций
struct variableListNode* curVarList = NULL; // Список объявленных переменных текущей функции
struct paramsListNode* curParamList = NULL;

int errors = 0;

// Добавление узла в дерево
struct treeNode* GetTreeNode(char nType, struct treeNode* Left, struct treeNode* Right);

// Добавить функцию в список
struct functionInfo* AddFunction(char fType, char *fName, struct paramsListNode* Params);

// Проверить наличие функции в списке
struct functionInfo* CheckFunction(char *fName);

// Добавить параметр в список
struct paramsListNode* AddToParamsList(struct treeNode* node, struct variableInfo *pVar);

// Вернуть структуру переменной
struct variableInfo* GetVar(char vType, char *vName, int isParam);

// Добавить переменную в текущий список
struct variableListNode* AddToVariableList(struct variableInfo *Var);

// Проверить, объявлена ли переменная
struct variableInfo* CheckVariable(char *vName);

struct paramsListNode* AddToArgsList(struct treeNode* node, struct paramsListNode *Next);

void ShowFunctionsSemantic();

void ShowMainSemantic();


void printParameters(struct paramsListNode *params);
void printVariableDeclarations(struct variableListNode* varDeclaratons);
void printOperators(struct treeNode *operations, int depth);
void printType(int type);

%}



%union 
{
    struct treeNode* node;
	struct 
	{
		char* ptr;
		int lineNumber;
	} str;
	
	int num;
}
%defines

%token VOID INT CHAR IF ELSE WHILE DO PRINT FOR SCAN RETURN STRING MAIN
%token number identifier semicolon comma quest
%token left_bracket right_bracket left_sqBracket right_sqBracket begin end comment
%token equal compare less_equal more_equal more less not_equal not or and
%token plus minus mul division plus_equal minus_equal div_equal mul_equal inc dec

%start axiom
%left plus minus plus_equal minus_equal
%left mul division div_equal mul_equal
%left left_bracket right_bracket
%left inc dec
%left uminus
%left or and not
%error-verbose

%%
axiom: 	
		functions main_func
		| main_func
		;
		
main_func:
		type MAIN left_bracket declaration_args right_bracket begin declarations operators end
		{
			if(/*errors == 0*/  1)
			{
				// Печатаем информацию о функциях
				ShowFunctionsSemantic();
				
				// Печатаем информацию о MAIN
				printf("\n\n/MAIN/: ");
				
				printf("\n/Parameters/: ");
				printParameters(curParamList);
				
				printf("\n/Variable declarations/: ");
				printVariableDeclarations(curVarList);
				
				printf("\n/Operators/: ");
				printOperators($<node>8, 0);
			}
			
		}
		;
	
functions: 	
		function 
		| functions function

		;
		
///*/****************************************/////////////////////////////////		

functionDeclaration: 	
			type identifier left_bracket declaration_args right_bracket
			{
				// Добавляем функцию в список и возвращаем её структуру
				struct functionInfo* func = AddFunction($<num>1, $<str>2.ptr, curParamList);
				curParamList = NULL;
				if(func == NULL)
				{
					printf("\nline %d: Function %s redeclared\n", $<str>2.lineNumber, $<str>2.ptr);
					errors++;
				}
				
				$<node>$ = GetTreeNode(-1, NULL, NULL);
				$<node>$->value.func = func;
			}
			;
		
function: 
		functionDeclaration begin declarations operators end
		{
			if ($<node>1->value.func != NULL)
			{
				$<node>$ = $<node>1;
				
				struct functionInfo* func = $<node>1->value.func;			
				func->operations = $<node>4;  		// Операции внутри функции
				func->varDeclaratons = curVarList;	// Список объявленных переменных
			}			
			curVarList = NULL;  // Начало нового списка переменных для следующей функции
		}
		;
		
declaration_arg:
		type identifier
		{
			struct variableInfo* var = GetVar($<num>1, $<str>2.ptr, 1);			
			struct variableListNode* varList = AddToVariableList(var);
			
			if(varList == NULL)
			{
				printf("\nline %d: variable %s redeclared\n", $<str>2.lineNumber, $<str>2.ptr);
				errors++;
			}
			else AddToParamsList(NULL, var);

		}
		| type identifier left_sqBracket right_sqBracket
		{
			struct variableInfo* var; 
			if($<num>1 == 0) 
				var = GetVar(3, $<str>2.ptr, 1);
			else if($<num>1 == 1) 
				var = GetVar(5, $<str>2.ptr, 1);
			
			
			struct variableListNode* varList = AddToVariableList(var);			
			if(varList == NULL)
			{
				printf("\nline %d: variable %s redeclared\n", $<str>2.lineNumber, $<str>2.ptr);
				errors++;
			}
			else AddToParamsList(NULL, var);
		}


declaration_args: 
		//Пусто
		| declaration_arg	
		| declaration_arg comma declaration_args
		;
		
declaration: 	
			type identifier semicolon
			{
				struct variableInfo* var = GetVar($<num>1, $<str>2.ptr, 0);
				struct variableListNode* varList = AddToVariableList(var);
				if(varList == NULL)	
				{				
					printf("\nline %d: variable %s redeclared\n", $<str>2.lineNumber, $<str>2.ptr);
					errors++;
				}
			}
			| type identifier left_sqBracket number right_sqBracket semicolon
			{					
				struct variableInfo* var = GetVar(3, $<str>2.ptr, 0); // Тип переменной - массив
				struct variableListNode* varList = AddToVariableList(var);
				if(varList == NULL)	
				{				
					printf("\nline %d: variable %s redeclared\n", $<str>2.lineNumber, $<str>2.ptr);
					errors++;
				}
				else
				{
					struct arrayInfo* array = (struct arrayInfo*)malloc(sizeof(struct arrayInfo));
					array->length = $<num>4;
					if($<num>1 == 0)				
						array->sizeOfElement = 1;	// CHAR				
					else if($<num>1 == 1)				
						array->sizeOfElement = 2;	// INT	
						
					var->value.arrayValue = array;
				}
			}
			| type identifier left_sqBracket right_sqBracket equal STRING semicolon
			{
				struct variableInfo* var = GetVar(4, $<str>2.ptr, 0); // Тип переменной - массив
				struct variableListNode* varList = AddToVariableList(var);
				if(varList == NULL)		
				{
					printf("\nline %d: variable %s redeclared\n", $<str>2.lineNumber, $<str>2.ptr);
					errors++;
				}
				else
				{
					struct arrayInfo* array = (struct arrayInfo*)malloc(sizeof(struct arrayInfo));
					array->sizeOfElement = 1;
					array->length = strlen($<str>6.ptr) + 1;
					array->ptr = $<str>6.ptr;
						
					var->value.arrayValue = array;
				}
			}
			; 
			
declarations:
			/*Пусто*/
			| declaration declarations
			| error declarations
			{
				errors++;
			}
			;
		
///*/****************************************/////////////////////////////////	


args:
	/*пусто*/
	{
		$<node>$ = GetTreeNode(4, NULL, NULL);
		$<node>$->value.params = NULL;
	}	
	| arg
	{			
		$<node>$ = GetTreeNode(4, NULL, NULL);
        $<node>$->value.params = AddToArgsList($<node>1, NULL);
	}
	| args comma arg
	{
		$<node>$ = GetTreeNode(4, NULL, NULL);
        $<node>$->value.params = AddToArgsList($<node>3, $<node>1->value.params);
	}
	;
		
arg: 
	identifier
	{
		struct variableInfo* var = CheckVariable($<str>1.ptr);
		if(var == NULL)
		{
			printf("\nline %d: variable %s undeclared\n", $<str>1.lineNumber, $<str>1.ptr);
			$<node>$ = NULL;
			errors++;
		}
		else
		{
			$<node>$ = GetTreeNode(0, NULL, NULL);
			$<node>$->value.var = var;
		}
				
	}
	| number
	{
		struct constantInfo* constant = (struct constantInfo*)malloc(sizeof(struct constantInfo));
		constant->type = 0; // Тип константы - number
        constant->value.intValue = $<num>1;
		
		$<node>$ = GetTreeNode(1, NULL, NULL);
		$<node>$->value.constant = constant;
	}	
	| STRING
	{	
		struct arrayInfo* array = (struct arrayInfo*)malloc(sizeof(struct arrayInfo));
		array->sizeOfElement = 1;
        array->length = strlen($<str>1.ptr) + 1;
        array->ptr = $<str>1.ptr;
		
		struct constantInfo* constant = (struct constantInfo*)malloc(sizeof(struct constantInfo));
		constant->type = 1; // Тип константы - строка
        constant->value.arrValue = array;
        
		$<node>$ = GetTreeNode(1, NULL, NULL);
		$<node>$->value.constant = constant;		
	}
	;
	
	
operators:  /*пустота*/
			{
				$<node>$ = NULL;
			}

			| operator operators
			{				
				$<node>$ = GetTreeNode(3, $<node>2, $<node>1);
			}
			| error operators
			{
				errors++;
			}
			;

Code_block: begin operators end
			{
				$<node>$ = $<node>2;
			}
		    | operator
			{
				$<node>$ = GetTreeNode(3, NULL, $<node>1);
			}
			;
	
	
IF_Condition: IF left_bracket statement right_bracket Code_block ELSE Code_block 
			{
				$<node>$ = GetTreeNode(10, $<node>5, $<node>7);	
				$<node>$->value.node = $<node>3; // Условие
			}
			| IF left_bracket statement right_bracket Code_block
			{
				$<node>$ = GetTreeNode(10, $<node>5, NULL);	
				$<node>$->value.node = $<node>3; // Условие
			}
			;
			
WHILE_cycle: WHILE left_bracket statement right_bracket Code_block
			{
				$<node>$ = GetTreeNode(11, $<node>3, $<node>5);	
			}
		    ;
		   
FOR_cycle: 
			FOR left_bracket statement semicolon statement semicolon statement right_bracket Code_block
			{
				struct treeNode* rightNode = GetTreeNode(-1, $<node>5, $<node>7);
				$<node>$ = GetTreeNode(9, $<node>3, rightNode);
				$<node>$->value.node = $<node>9; // Блок кода
			}
			;
		 
PRINT_func: 
			| PRINT left_bracket arg right_bracket
			{				
				$<node>$ = GetTreeNode(12, NULL, $<node>3); // Тип 12 - PRINT
				// Правая ветвь - аргумент print'а
			}
			;
			
SCAN_func:
			SCAN left_bracket identifier right_bracket
			{
				struct variableInfo* var = CheckVariable($<str>3.ptr);
				if(var == NULL)
				{
					printf("\nline %d: variable %s undeclared\n", $<str>3.lineNumber, $<str>3.ptr);
					$<node>$ = NULL;
					errors++;
				}
				else
				{
					$<node>$ = GetTreeNode(13, NULL, NULL); 
					$<node>$->value.var = var;
				}				
			}
			;		  

operator: 
	statement semicolon 
	{
		$<node>$ = $<node>1;
	}
//	| error
	| IF_Condition
	{
		$<node>$ = $<node>1;
	}
	| WHILE_cycle        
	{
		$<node>$ = $<node>1;
	}
	| FOR_cycle          	
	{
		$<node>$ = $<node>1;
	}
	| PRINT_func semicolon   
	{
		$<node>$ = $<node>1;
	}
	| SCAN_func semicolon    
	{
		$<node>$ = $<node>1;
	}
	| RETURN primary semicolon
	{
		$<node>$ = GetTreeNode(15, NULL, $<node>2);
	}
	;
	
array_access:
		identifier left_sqBracket logical_expr right_sqBracket
		{
			struct variableInfo* var = CheckVariable($<str>1.ptr);
			if(var == NULL)
			{
				printf("\nline %d: variable %s undeclared\n", $<str>1.lineNumber, $<str>1.ptr);
				$<node>$ = NULL;
				errors++;
			}
			else
			{
				$<node>$ = GetTreeNode(44, NULL, $<node>3);
				$<node>$->value.var = var;
			}		
		}
		;

statement: 
		logical_expr	
		{
			$<node>$ = $<node>1;
		}
		| identifier equal logical_expr          // Присваивание значения переменной
		{
			struct variableInfo* var = CheckVariable($<str>1.ptr);
			if(var == NULL)
			{
				printf("\nline %d: variable %s undeclared\n", $<str>1.lineNumber, $<str>1.ptr);
				$<node>$ = NULL;
				errors++;
			}
			else
			{
				$<node>$ = GetTreeNode(7, NULL, $<node>3);
				$<node>$->value.var = var;
			}
		}
		| array_access equal logical_expr       // Присваивание значения элементу массива
		{
			$<node>$ = GetTreeNode(8, $<node>1, $<node>3);
		}
//		| identifier plus_equal logical_expr
//		| identifier minus_equal logical_expr
//		| identifier div_equal unary_expr
//		| identifier mul_equal unary_expr
		;
		
		
logical_expr: 
			logical_or_expr	
			{
				$<node>$ = $<node>1;
			}
			| logical_expr not_equal logical_or_expr	
			{
				$<node>$ = GetTreeNode(40, $<node>1, $<node>3);
			}
			| logical_expr less logical_or_expr
			{
				$<node>$ = GetTreeNode(35, $<node>1, $<node>3);
			}
			| logical_expr more logical_or_expr
			{
				$<node>$ = GetTreeNode(36, $<node>1, $<node>3);
			}
			| logical_expr compare logical_or_expr
			{
				$<node>$ = GetTreeNode(39, $<node>1, $<node>3);
			}
			| logical_expr less_equal  logical_or_expr
			{
				$<node>$ = GetTreeNode(37, $<node>1, $<node>3);
			}
			| logical_expr more_equal logical_or_expr 
			{
				$<node>$ = GetTreeNode(38, $<node>1, $<node>3);
			}
			;
			
logical_or_expr: 
			logical_and_expr	
			{
				$<node>$ = $<node>1;
			}
			| logical_or_expr or logical_and_expr
			{
				$<node>$ = GetTreeNode(42, $<node>1, $<node>3);
			}
			;
			
logical_and_expr: 
			plus_expr	
			{
				$<node>$ = $<node>1;
			}
			| logical_and_expr and plus_expr
			{
				$<node>$ = GetTreeNode(43, $<node>1, $<node>3);
			}
			;
			
			
plus_expr: 
			mul_expr	
			{
				$<node>$ = $<node>1;
			}
			| plus_expr plus mul_expr
			{
				$<node>$ = GetTreeNode(30, $<node>1, $<node>3);
			}
			| plus_expr minus mul_expr
			{
				$<node>$ = GetTreeNode(31, $<node>1, $<node>3);
			}
			| plus_expr plus error
			{
				errors++;
			}
			| plus_expr minus error
			{
				errors++;
			}
			;
			
			
mul_expr: 
		unary_expr
		{
			$<node>$ = $<node>1;
		}
		| mul_expr mul unary_expr  
		{
			$<node>$ = GetTreeNode(32, $<node>1, $<node>3);
		}
		| mul_expr division unary_expr
		{
			$<node>$ = GetTreeNode(33, $<node>1, $<node>3);
		}
		| mul_expr division error
		{
			errors++;
		}
		| mul_expr mul error
		{
			errors++;
		}
		;
		
		
unary_expr:
//		post_unary_expr	
		primary
		{
			$<node>$ = $<node>1;
		}
		| minus unary_expr %prec uminus
		{
			$<node>$ = GetTreeNode(45, NULL, $<node>2);
		}
		| unary_expr inc
		{
			$<node>$ = GetTreeNode(46, NULL, $<node>1);
		}
		| unary_expr dec
		{
			$<node>$ = GetTreeNode(47, NULL, $<node>1);
		}
		| not unary_expr
		{
			$<node>$ = GetTreeNode(41, NULL, $<node>2);
		}
		;
		
/*		
post_unary_expr: 
			primary	
			| primary inc
			| primary dec
			;
*/

primary: 
		number 	
		{
			struct constantInfo* constant = (struct constantInfo*)malloc(sizeof(struct constantInfo));
			constant->type = 0; // Тип константы - number
			constant->value.intValue = $<num>1;
			
			$<node>$ = GetTreeNode(1, NULL, NULL);
			$<node>$->value.constant = constant;
		}
		| identifier
		{
			struct variableInfo* var = CheckVariable($<str>1.ptr);
			if(var == NULL)
			{
				printf("\nline %d: variable %s undeclared\n", $<str>1.lineNumber, $<str>1.ptr);
				$<node>$ = NULL;
				errors++;
			}
			else
			{
				$<node>$ = GetTreeNode(0, NULL, NULL);
				$<node>$->value.var = var;
			}
		}
		| left_bracket statement right_bracket
		{
			$<node>$ = $<node>2;
		}
		| identifier left_bracket args right_bracket // Вызов функции
		{
			struct functionInfo* func = CheckFunction($<str>1.ptr);
			if(func == NULL)	
			{			
				printf("\nline %d: Function %s undeclared!\n", $<str>1.lineNumber, $<str>1.ptr);
				errors++;
			}
			else
			{
				$<node>$ = GetTreeNode(14, NULL, $<node>3);
				$<node>$->value.func = func;
			}
		}
		| array_access	
		{
			$<node>$ = $<node>1;
		}
		;
		

	
type:  	INT    { $<num>$ = $<num>1;}
		| CHAR { $<num>$ = $<num>1;}
		| VOID { $<num>$ = $<num>1;}
	;
%%

struct treeNode* GetTreeNode(char nType, struct treeNode* Left, struct treeNode* Right)
{
	struct treeNode* node = (struct treeNode*)malloc(sizeof(struct treeNode));
    node->nodeType = nType;
    node->left = Left;
    node->right = Right;
    return node;
}

struct functionInfo* AddFunction(char fType, char *fName, struct paramsListNode* Params)
{
	// Проверка повторного объявления
	struct funcTableNode* workNode = FuncTable;
    while(workNode)
    {
        if(strcmp(fName, workNode->func->name) == 0)
			return NULL;		
        workNode = workNode->next;
    }

	struct functionInfo* funcInfo = (struct functionInfo*)malloc(sizeof(struct functionInfo));	
    funcInfo->name = (char*)malloc(strlen(fName)+1);
	strcpy(funcInfo->name, fName);	
    funcInfo->type = fType;    
    funcInfo->params = Params;
	
	
	// Добавление в список функций
    struct funcTableNode* funcNode = (struct funcTableNode*)malloc(sizeof(struct funcTableNode));
    funcNode->func = funcInfo;
    funcNode->next = NULL;

    workNode = FuncTable;
    if(workNode)
    {
        while(workNode->next)
            workNode = workNode->next;
			
        workNode->next = funcNode;
    }
    else
    {
        FuncTable = funcNode;
    }

    return funcInfo;
}

struct functionInfo* CheckFunction(char *fName)
{
	struct funcTableNode* workNode = FuncTable;
	while(workNode)
	{
		if(strcmp(workNode->func->name, fName) == 0)
			return workNode->func;
			
		workNode = workNode->next;
	}
	return NULL;
}

struct paramsListNode* AddToParamsList(struct treeNode* node, struct variableInfo *pVar)
{
    struct parameterInfo *parameter = (struct parameterInfo*)malloc(sizeof(struct parameterInfo));
    parameter->var = pVar;
	parameter->node = node;
	
    struct  paramsListNode* listNode = (struct paramsListNode*)malloc(sizeof(struct paramsListNode));
    listNode->next = NULL;
    listNode->param = parameter;	
	
	struct  paramsListNode* workNode = curParamList;
    if(workNode)
    {
        while(workNode->next)
            workNode = workNode->next;
			
        workNode->next = listNode;
    }
    else
    {
        curParamList = listNode;
    }
	return listNode;
}

// Вернуть структуру переменной
struct variableInfo* GetVar(char vType, char *vName, int isParam)
{
    struct variableInfo* var = (struct variableInfo*)malloc(sizeof(struct variableInfo));
    var->type = vType;
	var->isParam = isParam;
	
	var->value.intValue = 0;
	var->value.charValue = 0;

    var->name = (char*)malloc(strlen(vName)+1);
    strcpy(var->name, vName);
    return var;
}

struct variableInfo* CheckVariable(char *vName)
{
	struct variableListNode* workNode = curVarList;
	while(workNode)
	{
		if(strcmp(workNode->var->name, vName) == 0)
			return workNode->var;
			
		workNode = workNode->next;
	}
	return NULL;
}

struct variableListNode* AddToVariableList(struct variableInfo *Var)
{	
	// Проверка на повтор объявления
	struct variableListNode* workNode = curVarList;
	while(workNode)
	{
		if(strcmp(workNode->var->name, Var->name) == 0)
			return NULL;			
		workNode = workNode->next;
	}

	// Добавление в список
    struct  variableListNode* listNode = (struct variableListNode*)malloc(sizeof(struct variableListNode));
    listNode->next = NULL;
    listNode->var = Var;
			
	workNode = curVarList;
    if(workNode)
    {
        while(workNode->next)
            workNode = workNode->next;
			
        workNode->next = listNode;
    }
    else
    {
        curVarList = listNode;
    }
	return listNode;
}

void printType(int type)
{
	if(type == 0) printf("int"); 
	else if (type == 1) printf("char"); 
	else if (type == 2) printf("void");
}

void printParameters(struct paramsListNode *params)
{
	struct  paramsListNode* workNode = params;
	while(workNode)
	{
		struct parameterInfo* parameter = workNode->param;
		
		printType(parameter->var->type);
		if(workNode->next == NULL)	printf(" %s", parameter->var->name);
		else printf(" %s, ", parameter->var->name);	
		
		workNode = workNode->next;
	}
}

void printVariableDeclarations(struct variableListNode* varDeclaratons)
{
	struct  variableListNode* workNode = varDeclaratons;
	while(workNode)
	{
		struct variableInfo* var = workNode->var;
		if(var->isParam == 0)
		{
			printType(var->type);
			if(workNode->next == NULL)	printf(" %s", var->name);
			else printf(" %s, ", var->name);
		}	
		workNode = workNode->next;
	}
}

void printSpaces(int num)
{
	int i;
	printf("\n");
	for(i = 0; i < num; i++)
		printf("   ");
}

void printLogicTree(struct treeNode *root)
{
	if(!root) return;
	if((root->nodeType < 0) || (root->nodeType > 1 && root->nodeType < 14) || (root->nodeType > 14 && root->nodeType < 30)
		|| (root->nodeType > 47)) return;	
	  
	printLogicTree(root->left);
	
	switch(root->nodeType)
	{
		case 30:
			printf("+");
			break;
		case 31:
			printf("-");
			break;
		case 32:
			printf("*");
			break;
		case 33:
			printf("/");
			break;
		case 34:
			printf("=");
			break;
		case 35:
			printf("<");
			break;
		case 36:
			printf(">");
			break;
		case 37:
			printf("<=");
			break;
		case 38:
			printf(">=");
			break;
		case 39:
			printf("==");
			break;
		case 40:
			printf("!=");
			break;
		case 41:
			printf("!");
			break;
		case 42:
			printf("||");
			break;
		case 43:
			printf("&&");
			break;
			
		case 44:  // массив
			printf(root->value.var->name);
			printf("["); 
			printLogicTree(root->right); 
			printf("]");
			return;
		
		case 45:
			printf("-");
			printLogicTree(root->right); 
			return;
			
		case 46:			
			printLogicTree(root->right); 
			printf("++");
			return;
			
		case 47:
			printLogicTree(root->right); 
			printf("--");
			return;
			
		case 14:  // Вызов функции
			printf("%s(..)", root->value.func->name);
			return;
			
		case 0: // Переменная
			printf(root->value.var->name);
			break;
			
		case 1: // Константа
			printf("%d", root->value.constant->value.intValue);
			break;
	}
		
	printLogicTree(root->right);
}


void printOperators(struct treeNode *operations, int depth)
{
	struct treeNode* rightNode;
	struct treeNode* workNode = operations;
	
	while(workNode)
	{
		printSpaces(depth);
		
		rightNode = workNode->right;
		if(rightNode) //printf(" %d", workNode->right->nodeType);
		{
			switch(rightNode->nodeType)
			{
				case 7:
					printf("assignment: %s = ", rightNode->value.var->name);
					printLogicTree(rightNode->right);
					break;
				
				case 8:
					printf("assignment: %s[", rightNode->left->value.var->name);
					printLogicTree(rightNode->left->right);
					printf("] = ");
					printLogicTree(rightNode->right);
					break;
					
				case 9:  // for
					printf("FOR: ");
					printLogicTree(rightNode->left); printf("; ");
					printLogicTree(rightNode->right->left); printf("; ");
					printLogicTree(rightNode->right->right);
					
					printOperators(rightNode->value.node, depth+1);						
					break;
					
				case 10: // if
					printf("IF: ");
					printLogicTree(rightNode->value.node);
					printOperators(rightNode->left, depth+1);	
					
					if(rightNode->right)
					{
						printSpaces(depth);
						printf("ELSE:");
						printOperators(rightNode->right, depth+1);
					}
					break;
					
				case 11: // while
					printf("WHILE: ");
					printLogicTree(rightNode->left);
					printOperators(rightNode->right, depth+1);
					break;
					
				case 12: // print
					printf("PRINT: ");
					if(rightNode->right->nodeType == 0)
						printf(rightNode->right->value.var->name);
					else if(rightNode->right->nodeType == 1)
					{
						if(rightNode->right->value.constant->type == 0)
							printf("%d", rightNode->right->value.constant->value.intValue);
						else if(rightNode->right->value.constant->type == 1)
							printf(rightNode->right->value.constant->value.arrValue->ptr);
					}					
					break;
				
				case 13: // scan	
					printf("SCAN: ");
					printf(rightNode->value.var->name);					
					break;
					
				case 14: // function call
					printf("%s(..)", rightNode->value.func->name);					
					break;
					
				case 15: // return
					printf("RETURN ");
					printLogicTree(rightNode->right);
					break;
					
				default:
					printLogicTree(rightNode);
			}
		}
	
		
		
		//----------------------------------------------------
		workNode = workNode->left;
	}
}

void ShowFunctionsSemantic()
{
	struct funcTableNode* workNode = FuncTable;
	while(workNode)
	{
		struct functionInfo* func = workNode->func;
		//--------------------------------------
		printf("\n\n/FUNCTION/: ");
		printType(func->type);
		printf(" %s", func->name);
		
		printf("\n/Parameters/: ");
		printParameters(func->params);
		
		printf("\n/Variable declarations/: ");
		printVariableDeclarations(func->varDeclaratons);
		
		printf("\n/Operators/: ");
		printOperators(func->operations, 0);
		
		//--------------------------------------	
		workNode = workNode->next;
		printf("\n---------------------------------------");
	}
}


struct paramsListNode* AddToArgsList(struct treeNode* node, struct paramsListNode *Next)
{
    struct parameterInfo *parameter = (struct parameterInfo*)malloc(sizeof(struct parameterInfo));
    parameter->var = NULL;
	parameter->node = node;
	
    struct  paramsListNode* listNode = (struct paramsListNode*)malloc(sizeof(struct paramsListNode));
    listNode->next = Next;
    listNode->param = parameter;
    return listNode;
}
