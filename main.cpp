#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//���뻹�ܲڣ����Ѿ�ȫ��ʵ���ˡ������ַ���Դ�ļ��Ѿ������滻�ˣ��������Ƿ�����ȷ��
//��Դ�ļ��滻�����ˣ�Ҫ��������ļ���charPrint.txt������ԭ�����з��ź�-����û�м�����롣����Ҳ�����С�

typedef struct Node{															//huffman�����
	char Char;																	//���������ַ�
	int weight;																	//�ַ���Ȩ��
	Node *lchile,*rchile;														//�������Һ���
	Node *parent;																//����˫��
}BitNode,*HuffmanTree;

void printHuffmanTree(HuffmanTree &T,char str[15],char charCode[][15],int &i );	//�������huffman��
void InitHuffmanTree(HuffmanTree &T);											//��ʼ��huffman��
void getCharNumber(int charNumber[][55]);										//�õ�charPrint.txt�ļ�������ַ���Ӧ��Ȩ��
HuffmanTree CreateHuffmanTree(HuffmanTree &T,int charNumber[][55]);				//����charNumber���齨��huffman��
void printCharCode(char charCode[][15]);										//��charPrint.txt�ļ�����huffman������õ��ı��������charInput.txt
void verifyCode(HuffmanTree &T,FILE *charCodeFile);								//��huffman����charInput.txt�ļ������������verifyCodeToChar.txt�ļ�
bool verifyCodeTrue();															//��֤verifyCodeToChar.txt�ļ���charPrint.txt�ļ��Ƿ�һ��
	
int main(){
	int charNumber[2][55];														//����ÿ���ַ���ÿ���ַ���Ȩ�أ�charNumber[0][0]�����ַ���charNumber[1][0]����Ȩ�أ�
	char str[15] = "";															//�������ÿ���ַ������
	char charCode[55][15];														//����ÿ���ַ��ı��루charCode[0][0]�����ַ���charCode[0][1]--charCode[0][14]������룩
	int i = 0;																	//��������
	HuffmanTree huffmanTree;													//δ��ʼ����huffman��

	for(int k = 0;k < 55;k++)													//��ʼ��ÿ���ַ��ı���
		for(int l = 0 ; l < 15;l++)
			charCode[k][l] = '\0';

	getCharNumber(charNumber);													//�õ�ÿ���ַ���Ȩ��
	InitHuffmanTree(huffmanTree);												//��ʼ��huffman��
	huffmanTree = CreateHuffmanTree(huffmanTree,charNumber);					//����huffman��

	printf("\nEach char's weight is��\n");
	for(int i = 0;i<55;i++){
		if(charNumber[1][i] == 0)
			break;
		printf("%c    %-6d",charNumber[0][i],charNumber[1][i]);
		if((i+1)%5 == 0)
			printf("\n");
		}

	printf("\nEach char's Code is��\n");
	printHuffmanTree(huffmanTree,str,charCode,i);								//�������������huffman�����������ַ��ı���
	printCharCode(charCode);													//���Դ�ļ�����huffman�������ı��������ļ�
	
	FILE *charVerifyFile = fopen("verifyCodeToChar.txt","wt");					//�����ô��룬���verifyCodeChar.txt�ļ�����
	fclose(charVerifyFile);

	FILE *charCodeFile = fopen("charInput.txt","rt");							
	while(!feof(charCodeFile)){
		verifyCode(huffmanTree,charCodeFile);									//��������ļ�������Ϊ���ļ�
	}
	fclose(charCodeFile);

	
	
	/*for(int j  = 0;j < i;j++){												
		for(char *p = charCode[j];*p != '\0';p++)
			printf("%c",*p);
	printf("\n");
	}*/

	if(verifyCodeTrue())														//�Ƚ���֤Դ�ļ��ͷ�������ļ��Ƿ���ͬ
		printf("\nThe char to code is right\n\n");
	else printf("\nThe char to code is wrong\n\n ");

			return 0;
	}

void InitHuffmanTree(HuffmanTree &huffmanTree){									//��ʼ��huffman��
	huffmanTree->Char == '1';
	huffmanTree->weight == 0;
	huffmanTree->lchile == NULL;
	huffmanTree->rchile == NULL;
}

void getCharNumber(int charNumber[][55]){

	FILE *charPrint;															//Դ�ļ�ָ��
	char Char;																	//��ȡ�ļ���ÿ���ַ�

	for(int i = 0;i<55;i++)														//��ʼ��ÿ��Ȩ��Ϊ0
		charNumber[1][i] = 0;

	if((charPrint = fopen("charPrint.txt","r+")) == NULL)						//���ļ�
		printf("Open file error");
	else{
		;
		while((Char = (char)fgetc(charPrint)) != EOF){							//ѭ��ÿ�ζ�ȡԴ�ļ�һ���ַ����ַ���ͬ���ۼ�Ȩ��
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

	for(int i = 0;i < 55;i++)													//���ַ���Ȩ����С��������
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

HuffmanTree CreateHuffmanTree(HuffmanTree &huffmanTree,int charNumber[][55]){	//huffmanTree����������ʱ���Һ��ӣ�charNumber�Ѿ������ÿ���ַ���Ȩ��

	int i = 0,l = 0;															//i�������������±꣬��ʾ�ڼ��������㣬l������¼�ж��ٸ��ַ�
	HuffmanTree huffmanTreeNode;												//ÿ�������������ʱ������
	HuffmanTree huffmanTreeNodeNULL;											//ÿ�������������ʱ��˫��
	HuffmanTree huffmanTreeNodeArg[55];											//������飬��������Ѱ����С�������ʹ��������ӵĽ��

	for(int j =0; j < 55;j++){													//����ɭ�֣�ÿ�������ǵ����Ľ�㣬���ַ���Ȩ�س�ʼ�������鴢��
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

	if(charNumber[1][i] > 0)													//����һ�����͵ڶ�����㻯Ϊ���Ӻ��Һ���
		huffmanTreeNode = huffmanTreeNodeArg[i];
	else return NULL;
		i++;
	if(charNumber[1][i] > 0)
		huffmanTree = huffmanTreeNodeArg[i];
	else return NULL;

	while(true){
			
		huffmanTreeNodeNULL = (HuffmanTree) malloc(sizeof(Node));				//�������������
		huffmanTreeNodeNULL->Char = '1';										//��������˫�׽����Ŷ���Ϊ��1��
		huffmanTreeNodeNULL->weight = huffmanTree->weight + huffmanTreeNode->weight;
		huffmanTreeNodeNULL->lchile = huffmanTreeNode;
		huffmanTreeNodeNULL->rchile = huffmanTree;
		huffmanTreeNodeNULL->parent = NULL;
		huffmanTree->parent = huffmanTreeNodeNULL;								
		huffmanTreeNode->parent = huffmanTreeNodeNULL;

		huffmanTreeNodeArg[i] = huffmanTreeNodeNULL;							//�õ��µ�Ȩֵ��㣬���·���������

		huffmanTreeNode = huffmanTreeNodeArg[i];								//�ѽ�Ҫ���ӵ�������ʱ��ʼ��Ϊ��Ȩֵ�Ľ��
		for(int j = 0; j < l;j++){												//Ѱ���Ƿ��и�СȨֵ�Ľ��
				if(huffmanTreeNodeArg[j]->weight < huffmanTreeNode->weight && huffmanTreeNodeArg[j]->weight != 0 && huffmanTreeNodeArg[j]->parent == NULL)//Ҫ��˫��ָ��Ϊ�ձ����Ѿ����ӵĽ��������
					huffmanTreeNode = huffmanTreeNodeArg[j];
		}

		for(int j = 0; j < l;j++)												//���Һ�����ʱ��ʼ��Ϊ���Ȩֵ��
				if(huffmanTreeNodeArg[j]->weight > huffmanTree->weight)
					huffmanTree = huffmanTreeNodeArg[j];
		
		for(int j = 0; j < l;j++){												//Ѱ�ҵڶ�СȨֵ�Ľ��
				if(huffmanTreeNodeArg[j]->weight < huffmanTree->weight && huffmanTreeNodeArg[j]->weight != 0 && huffmanTreeNodeArg[j]->parent == NULL && huffmanTreeNodeArg[j] != huffmanTreeNode){//Ҫ����������ȼ�Ϊ�ڶ�СȨֵ
					huffmanTree = huffmanTreeNodeArg[j];
					i = j;														//��¼��Ҫ����Ȩֵ�������λ��
				}
		}

		int k = 0;																//����˳�ѭ���������Ƿ����㣬��ֻ��һ������˫��ָ��Ϊ��
		for(int j = 0;j < l;j++)
			if(huffmanTreeNodeArg[j]->parent != NULL)
				k++;

		if(k == (l-1))
			break;
	}

	return huffmanTreeNodeNULL;

}

void printHuffmanTree(HuffmanTree &huffmanTree,char str[15],char charCode[55][15],int &i){//str���浱ǰһ���ַ��ı��룬charCode����ÿ���ַ��ı��룬i������¼�ڼ����ַ�
	
	if(huffmanTree->lchile != NULL){											//�������ӵݹ��ߵ�Ҷ�ӽ��
		strcat(str,"0");														//ÿ����������ʱ�������0
		printHuffmanTree(huffmanTree->lchile,str,charCode,i);					//�������ӵݹ�
	}
	if(huffmanTree->rchile != NULL){											//ͬ�ϣ������Һ���
		strcat(str,"1");
		printHuffmanTree(huffmanTree->rchile,str,charCode,i);
	}

	if(huffmanTree->lchile == NULL && huffmanTree->rchile == NULL && str != NULL){//�ߵ�Ҷ�ӽ��
		printf(str);															//����ַ��ı���
		char *p = str;															
		charCode[i][0] = huffmanTree->Char;
		int j = 1;
		for(;*p != '\0';j++)													//�������¼ÿ���ַ��ı���
			charCode[i][j] = *(p++);
		if(j <= 8)														//�ڶ����޸ĵĵط�
			printf("	");
		i++;
	}
	if(strlen(str) >= 1)														//ÿ�������ߵ�ʱ��������һ���ַ�����
		str[strlen(str)-1] = '\0';
	if(huffmanTree->Char != '1')												//����ַ�Ȩ�غ��ַ�
		printf("	%-15d    %-c\n",huffmanTree->weight,huffmanTree->Char);//�ڶ����޸ĵĵط�
		
}

void printCharCode(char charCode[][15]){										//charCode����ÿ���ַ��ı���
	FILE *charPrint,*charInput;													//Դ�ļ���Դ�ļ����������ļ�

	if((charPrint = fopen("charInput.txt","r+")) == NULL)
		printf("Open Input File Error");
	if((charInput = fopen("charPrint.txt","r+")) == NULL)
		printf("Open Print File Error");

	while(!feof(charInput)){
		char Char = fgetc(charInput);											//�õ�Դ�ļ�һ���ַ�
		for(int i = 0 ;i < 55;i++){
			if(Char == charCode[i][0]){											//���մ�����ַ���������������ļ�
				for(char* p = charCode[i]+1;*p != '\0';p++)
					fputc(*p,charPrint);
				break;
			}
			if(Char == '\n'){											//�ڶ����޸ĵĵط�
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

void verifyCode(HuffmanTree &huffmanTree,FILE *charCodeFile){					//huffman�ǽ����õ�����charCodeFile��Դ�ļ������������ļ�
	if(feof(charCodeFile))
		return ;
	HuffmanTree huffmanTreeNode = huffmanTree;
	char CodeChar;																//�������ļ���ÿһ���ַ�

	if(huffmanTreeNode->lchile == NULL && huffmanTreeNode->rchile == NULL && huffmanTreeNode->Char != '1'){//���ΪҶ�ӽ��
		FILE *charCodeInput = fopen("verifyCodeToChar.txt","at+");				//�����ļ�β��׷�ӷ�ʽ�����ļ�
		fputc(huffmanTreeNode->Char,charCodeInput);								//��Ҷ�ӽ��ķ���д��
		fclose(charCodeInput);
		return;
	}
	while(!feof(charCodeFile)){										//�ڶ����޸ĵĵط�
		CodeChar = getc(charCodeFile);											//�õ�������ļ���һ���ַ�
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
	if(CodeChar == '0')															//����ַ�Ϊ0���������ߣ���ͬ���ݹ鷽��
		verifyCode(huffmanTreeNode->lchile,charCodeFile);
	if(CodeChar == '1')
		verifyCode(huffmanTreeNode->rchile,charCodeFile);

}

bool verifyCodeTrue(){															//���Դ�ļ��ͷ������õ����ļ������ַ��Ƿ���ͬ
	FILE *charInput = fopen("charPrint.txt","rt");
	FILE *charVerify = fopen("verifyCodeToChar.txt","rt");

	while(!feof(charInput)){
		if(fgetc(charInput) != fgetc(charVerify))								//��һ���ַ�����ͬ�򷵻�false
			return false;
	}
	return true;
}