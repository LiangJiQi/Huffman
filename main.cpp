#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//代码还很糙，但已经全部实现了。包含字符的源文件已经被我替换了，方便检测是否建立正确。
//把源文件替换回来了，要用我这个文件（charPrint.txt）啊，原本换行符号和-符号没有加入编码。但是也可以有。

typedef struct Node{															//huffman树结点
	char Char;																	//结点包含的字符
	int weight;																	//字符的权重
	Node *lchile,*rchile;														//结点的左右孩子
	Node *parent;																//结点的双亲
}BitNode,*HuffmanTree;

void printHuffmanTree(HuffmanTree &T,char str[15],char charCode[][15],int &i );	//用来输出huffman树
void InitHuffmanTree(HuffmanTree &T);											//初始化huffman树
void getCharNumber(int charNumber[][55]);										//得到charPrint.txt文件里各个字符对应的权重
HuffmanTree CreateHuffmanTree(HuffmanTree &T,int charNumber[][55]);				//根据charNumber数组建立huffman树
void printCharCode(char charCode[][15]);										//将charPrint.txt文件经过huffman树编码得到的编码输出到charInput.txt
void verifyCode(HuffmanTree &T,FILE *charCodeFile);								//用huffman树将charInput.txt文件反编码输出至verifyCodeToChar.txt文件
bool verifyCodeTrue();															//验证verifyCodeToChar.txt文件和charPrint.txt文件是否一样
	
int main(){
	int charNumber[2][55];														//储存每个字符和每个字符的权重（charNumber[0][0]储存字符，charNumber[1][0]储存权重）
	char str[15] = "";															//用来输出每个字符编码的
	char charCode[55][15];														//储存每个字符的编码（charCode[0][0]储存字符，charCode[0][1]--charCode[0][14]储存编码）
	int i = 0;																	//用来计数
	HuffmanTree huffmanTree;													//未初始化的huffman树

	for(int k = 0;k < 55;k++)													//初始化每个字符的编码
		for(int l = 0 ; l < 15;l++)
			charCode[k][l] = '\0';

	getCharNumber(charNumber);													//得到每个字符的权重
	InitHuffmanTree(huffmanTree);												//初始化huffman树
	huffmanTree = CreateHuffmanTree(huffmanTree,charNumber);					//创建huffman树

	printf("\nEach char's weight is：\n");
	for(int i = 0;i<55;i++){
		if(charNumber[1][i] == 0)
			break;
		printf("%c    %-6d",charNumber[0][i],charNumber[1][i]);
		if((i+1)%5 == 0)
			printf("\n");
		}

	printf("\nEach char's Code is：\n");
	printHuffmanTree(huffmanTree,str,charCode,i);								//遍历输出并根据huffman树创建各个字符的编码
	printCharCode(charCode);													//输出源文件经过huffman树编码后的编码至新文件
	
	FILE *charVerifyFile = fopen("verifyCodeToChar.txt","wt");					//调试用代码，清空verifyCodeChar.txt文件内容
	fclose(charVerifyFile);

	FILE *charCodeFile = fopen("charInput.txt","rt");							
	while(!feof(charCodeFile)){
		verifyCode(huffmanTree,charCodeFile);									//将编码的文件反编码为新文件
	}
	fclose(charCodeFile);

	
	
	/*for(int j  = 0;j < i;j++){												
		for(char *p = charCode[j];*p != '\0';p++)
			printf("%c",*p);
	printf("\n");
	}*/

	if(verifyCodeTrue())														//比较验证源文件和反编码的文件是否相同
		printf("\nThe char to code is right\n\n");
	else printf("\nThe char to code is wrong\n\n ");

			return 0;
	}

void InitHuffmanTree(HuffmanTree &huffmanTree){									//初始化huffman树
	huffmanTree->Char == '1';
	huffmanTree->weight == 0;
	huffmanTree->lchile == NULL;
	huffmanTree->rchile == NULL;
}

void getCharNumber(int charNumber[][55]){

	FILE *charPrint;															//源文件指针
	char Char;																	//读取文件的每个字符

	for(int i = 0;i<55;i++)														//初始化每个权重为0
		charNumber[1][i] = 0;

	if((charPrint = fopen("charPrint.txt","r+")) == NULL)						//打开文件
		printf("Open file error");
	else{
		;
		while((Char = (char)fgetc(charPrint)) != EOF){							//循环每次读取源文件一个字符，字符相同则累加权重
		switch(Char){
					case ' ':charNumber[1][0]++;charNumber[0][0]=(int)(' ');break;
					case 'A':charNumber[1][1]++;charNumber[0][1]=(int)('A');break;
					case 'a':charNumber[1][2]++;charNumber[0][2]=(int)('a');break;
					case 'B':charNumber[1][3]++;charNumber[0][3]=(int)('B');break;
					case 'b':charNumber[1][4]++;charNumber[0][4]=(int)('b');break;
					case 'C':charNumber[1][5]++;charNumber[0][5]=(int)('C');break;
					case 'c':charNumber[1][6]++;charNumber[0][6]=(int)('c');break;
					case 'D':charNumber[1][7]++;charNumber[0][7]=(int)('D');break;
					case 'd':charNumber[1][8]++;charNumber[0][8]=(int)('d');break;
					case 'E':charNumber[1][9]++;charNumber[0][9]=(int)('E');break;
					case 'e':charNumber[1][10]++;charNumber[0][10]=(int)('e');break;
					case 'F':charNumber[1][11]++;charNumber[0][11]=(int)('F');break;
					case 'f':charNumber[1][12]++;charNumber[0][12]=(int)('f');break;
					case 'G':charNumber[1][13]++;charNumber[0][13]=(int)('G');break;
					case 'g':charNumber[1][14]++;charNumber[0][14]=(int)('g');break;
					case 'H':charNumber[1][15]++;charNumber[0][15]=(int)('H');break;
					case 'h':charNumber[1][16]++;charNumber[0][16]=(int)('h');break;
					case 'I':charNumber[1][17]++;charNumber[0][17]=(int)('I');break;
					case 'i':charNumber[1][18]++;charNumber[0][18]=(int)('i');break;
					case 'J':charNumber[1][19]++;charNumber[0][19]=(int)('J');break;
					case 'j':charNumber[1][20]++;charNumber[0][20]=(int)('j');break;
					case 'K':charNumber[1][21]++;charNumber[0][21]=(int)('K');break;
					case 'k':charNumber[1][22]++;charNumber[0][22]=(int)('k');break;
					case 'L':charNumber[1][23]++;charNumber[0][23]=(int)('L');break;
					case 'l':charNumber[1][24]++;charNumber[0][24]=(int)('l');break;
					case 'M':charNumber[1][25]++;charNumber[0][25]=(int)('M');break;
					case 'm':charNumber[1][26]++;charNumber[0][26]=(int)('m');break;
					case 'N':charNumber[1][27]++;charNumber[0][27]=(int)('N');break;
					case 'n':charNumber[1][28]++;charNumber[0][28]=(int)('n');break;
					case 'O':charNumber[1][29]++;charNumber[0][29]=(int)('O');break;
					case 'o':charNumber[1][30]++;charNumber[0][30]=(int)('o');break;
					case 'P':charNumber[1][31]++;charNumber[0][31]=(int)('P');break;
					case 'p':charNumber[1][32]++;charNumber[0][32]=(int)('p');break;
					case 'Q':charNumber[1][33]++;charNumber[0][33]=(int)('Q');break;
					case 'q':charNumber[1][34]++;charNumber[0][34]=(int)('q');break;
					case 'R':charNumber[1][35]++;charNumber[0][35]=(int)('R');break;
					case 'r':charNumber[1][36]++;charNumber[0][36]=(int)('r');break;
					case 'S':charNumber[1][37]++;charNumber[0][37]=(int)('S');break;
					case 's':charNumber[1][38]++;charNumber[0][38]=(int)('s');break;
					case 'T':charNumber[1][39]++;charNumber[0][39]=(int)('T');break;
					case 't':charNumber[1][40]++;charNumber[0][40]=(int)('t');break;
					case 'U':charNumber[1][41]++;charNumber[0][41]=(int)('U');break;
					case 'u':charNumber[1][42]++;charNumber[0][42]=(int)('u');break;
					case 'V':charNumber[1][43]++;charNumber[0][43]=(int)('V');break;
					case 'v':charNumber[1][44]++;charNumber[0][44]=(int)('v');break;
					case 'W':charNumber[1][45]++;charNumber[0][45]=(int)('W');break;
					case 'w':charNumber[1][46]++;charNumber[0][46]=(int)('w');break;
					case 'X':charNumber[1][47]++;charNumber[0][47]=(int)('X');break;
					case 'x':charNumber[1][48]++;charNumber[0][48]=(int)('x');break;
					case 'Y':charNumber[1][49]++;charNumber[0][49]=(int)('Y');break;
					case 'y':charNumber[1][50]++;charNumber[0][50]=(int)('y');break;
					case 'Z':charNumber[1][51]++;charNumber[0][51]=(int)('Z');break;
					case 'z':charNumber[1][52]++;charNumber[0][52]=(int)('z');break;
					case ',':charNumber[1][53]++;charNumber[0][53]=(int)(',');break;
					case '.':charNumber[1][54]++;charNumber[0][54]=(int)('.');break;
			}
		}

	}

	for(int i = 0;i < 55;i++)													//将字符按权重由小到大排序
		for(int j =i+1;j < 55;j++){
			if(charNumber[1][i]>charNumber[1][j] && charNumber[1][j] != 0){
				for(int k =0;k < 2;k++){
					int tmp = charNumber[k][j];
					charNumber[k][j] = charNumber[k][i];
					charNumber[k][i] = tmp;
				}
			}
			else {
				if(charNumber[1][i] == 0)
					for(int k =0;k < 2;k++){
						int tmp = charNumber[k][j];
						charNumber[k][j] = charNumber[k][i];
						charNumber[k][i] = tmp;
				}
			}
		}

		fclose(charPrint);
		return ;
}

HuffmanTree CreateHuffmanTree(HuffmanTree &huffmanTree,int charNumber[][55]){	//huffmanTree将会是连接时的右孩子，charNumber已经储存好每个字符和权重

	int i = 0,l = 0;															//i用来计数，作下标，表示第几个数组结点，l用来记录有多少个字符
	HuffmanTree huffmanTreeNode;												//每次连接两个结点时的左孩子
	HuffmanTree huffmanTreeNodeNULL;											//每次连接两个结点时的双亲
	HuffmanTree huffmanTreeNodeArg[55];											//结点数组，用来遍历寻找最小两个结点和储存已连接的结点

	for(int j =0; j < 55;j++){													//建立森林，每棵树都是单独的结点，用字符和权重初始化，数组储存
		if(charNumber[1][j] == 0)
			break;
		huffmanTreeNodeArg[j] = (HuffmanTree) malloc(sizeof(Node));
		huffmanTreeNodeArg[j]->Char = charNumber[0][j];
		huffmanTreeNodeArg[j]->weight = charNumber[1][j];
		huffmanTreeNodeArg[j]->lchile = NULL;
		huffmanTreeNodeArg[j]->rchile = NULL;
		huffmanTreeNodeArg[j]->parent = NULL;
		l++;
	}

	if(charNumber[1][i] > 0)													//将第一个结点和第二个结点化为左孩子和右孩子
		huffmanTreeNode = huffmanTreeNodeArg[i];
	else return NULL;
		i++;
	if(charNumber[1][i] > 0)
		huffmanTree = huffmanTreeNodeArg[i];
	else return NULL;

	while(true){
			
		huffmanTreeNodeNULL = (HuffmanTree) malloc(sizeof(Node));				//将两个结点连接
		huffmanTreeNodeNULL->Char = '1';										//两个结点的双亲结点符号定义为‘1’
		huffmanTreeNodeNULL->weight = huffmanTree->weight + huffmanTreeNode->weight;
		huffmanTreeNodeNULL->lchile = huffmanTreeNode;
		huffmanTreeNodeNULL->rchile = huffmanTree;
		huffmanTreeNodeNULL->parent = NULL;
		huffmanTree->parent = huffmanTreeNodeNULL;								
		huffmanTreeNode->parent = huffmanTreeNodeNULL;

		huffmanTreeNodeArg[i] = huffmanTreeNodeNULL;							//得到新的权值结点，重新放入结点数组

		huffmanTreeNode = huffmanTreeNodeArg[i];								//把将要连接的左孩子暂时初始化为新权值的结点
		for(int j = 0; j < l;j++){												//寻找是否还有更小权值的结点
				if(huffmanTreeNodeArg[j]->weight < huffmanTreeNode->weight && huffmanTreeNodeArg[j]->weight != 0 && huffmanTreeNodeArg[j]->parent == NULL)//要求双亲指针为空避免已经连接的结点再连接
					huffmanTreeNode = huffmanTreeNodeArg[j];
		}

		for(int j = 0; j < l;j++)												//将右孩子暂时初始化为最大权值的
				if(huffmanTreeNodeArg[j]->weight > huffmanTree->weight)
					huffmanTree = huffmanTreeNodeArg[j];
		
		for(int j = 0; j < l;j++){												//寻找第二小权值的结点
				if(huffmanTreeNodeArg[j]->weight < huffmanTree->weight && huffmanTreeNodeArg[j]->weight != 0 && huffmanTreeNodeArg[j]->parent == NULL && huffmanTreeNodeArg[j] != huffmanTreeNode){//要求不与左孩子相等即为第二小权值
					huffmanTree = huffmanTreeNodeArg[j];
					i = j;														//记录将要将新权值结点插入的位置
				}
		}

		int k = 0;																//检测退出循环的条件是否满足，即只有一个结点的双亲指针为空
		for(int j = 0;j < l;j++)
			if(huffmanTreeNodeArg[j]->parent != NULL)
				k++;

		if(k == (l-1))
			break;
	}

	return huffmanTreeNodeNULL;

}

void printHuffmanTree(HuffmanTree &huffmanTree,char str[15],char charCode[55][15],int &i){//str储存当前一个字符的编码，charCode储存每个字符的编码，i用来记录第几个字符
	
	if(huffmanTree->lchile != NULL){											//先往左孩子递归走到叶子结点
		strcat(str,"0");														//每次往左孩子走时将编码加0
		printHuffmanTree(huffmanTree->lchile,str,charCode,i);					//进入左孩子递归
	}
	if(huffmanTree->rchile != NULL){											//同上，进入右孩子
		strcat(str,"1");
		printHuffmanTree(huffmanTree->rchile,str,charCode,i);
	}

	if(huffmanTree->lchile == NULL && huffmanTree->rchile == NULL && str != NULL){//走到叶子结点
		printf(str);															//输出字符的编码
		char *p = str;															
		charCode[i][0] = huffmanTree->Char;
		int j = 1;
		for(;*p != '\0';j++)													//用数组记录每个字符的编码
			charCode[i][j] = *(p++);
		if(j <= 8)														//第二次修改的地方
			printf("	");
		i++;
	}
	if(strlen(str) >= 1)														//每次往回走的时候减掉最后一个字符编码
		str[strlen(str)-1] = '\0';
	if(huffmanTree->Char != '1')												//输出字符权重和字符
		printf("	%-15d    %-c\n",huffmanTree->weight,huffmanTree->Char);//第二次修改的地方
		
}

void printCharCode(char charCode[][15]){										//charCode储存每个字符的编码
	FILE *charPrint,*charInput;													//源文件和源文件编码后输出文件

	if((charPrint = fopen("charInput.txt","r+")) == NULL)
		printf("Open Input File Error");
	if((charInput = fopen("charPrint.txt","r+")) == NULL)
		printf("Open Print File Error");

	while(!feof(charInput)){
		char Char = fgetc(charInput);											//得到源文件一个字符
		for(int i = 0 ;i < 55;i++){
			if(Char == charCode[i][0]){											//按照储存的字符编码数组输出到文件
				for(char* p = charCode[i]+1;*p != '\0';p++)
					fputc(*p,charPrint);
				break;
			}
			if(Char == '\n'){											//第二次修改的地方
				fputc('\n',charPrint);
				break;
			}
			if(Char == '-'){
				fputc('-',charPrint);
				break;
			}
		}
	}
	fclose(charPrint);
	fclose(charInput);
}

void verifyCode(HuffmanTree &huffmanTree,FILE *charCodeFile){					//huffman是建立好的树，charCodeFile是源文件经过编码后的文件
	if(feof(charCodeFile))
		return ;
	HuffmanTree huffmanTreeNode = huffmanTree;
	char CodeChar;																//编码后的文件的每一个字符

	if(huffmanTreeNode->lchile == NULL && huffmanTreeNode->rchile == NULL && huffmanTreeNode->Char != '1'){//如果为叶子结点
		FILE *charCodeInput = fopen("verifyCodeToChar.txt","at+");				//以在文件尾部追加方式打开新文件
		fputc(huffmanTreeNode->Char,charCodeInput);								//将叶子结点的符号写入
		fclose(charCodeInput);
		return;
	}
	while(!feof(charCodeFile)){										//第二次修改的地方
		CodeChar = getc(charCodeFile);											//得到编码后文件的一个字符
		if(CodeChar == '\n'){
			FILE *charCodeInput = fopen("verifyCodeToChar.txt","at+");				
			fputc('\n',charCodeInput);								
			fclose(charCodeInput);
		}
		if(CodeChar == '-'){
			FILE *charCodeInput = fopen("verifyCodeToChar.txt","at+");				
			fputc('-',charCodeInput);								
			fclose(charCodeInput);
		}
		break;
	}
	if(CodeChar == '0')															//如果字符为0，则往左走，下同理，递归方法
		verifyCode(huffmanTreeNode->lchile,charCodeFile);
	if(CodeChar == '1')
		verifyCode(huffmanTreeNode->rchile,charCodeFile);

}

bool verifyCodeTrue(){															//检测源文件和反编码后得到的文件包含字符是否相同
	FILE *charInput = fopen("charPrint.txt","rt");
	FILE *charVerify = fopen("verifyCodeToChar.txt","rt");

	while(!feof(charInput)){
		if(fgetc(charInput) != fgetc(charVerify))								//有一个字符不相同则返回false
			return false;
	}
	return true;
}