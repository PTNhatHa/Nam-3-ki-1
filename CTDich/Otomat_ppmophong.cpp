
const int ERROR_STATE=100;
typedef int state;// kieu cac trang thai
typedef unsigned char *attri;// kieu cua thuoc tinh
typedef unsigned char *token; //kieu cua tu to
unsigned char *x;//xau vao x
unsigned int i=0;// vi tri cua ky tu doc trong xau x

unsigned char readchar(unsigned char *x, unsigned int i){
//tra ve ky tu tiep theo
if(i<strlen(x)) return (*(x+i));
else return ('\0'); }

attri attribute(state s) {
	// tra ve thuoc tinh tuong ung voi trang thai ket thuc
	char *ch;
	switch(s){
		case 2: strcpy(ch,"so sanh lon hon bang");break;
		case 3: strcpy(ch,"dich phai"); break;
		case 4: strcpy(ch,"so sanh lon hon"); break;
		case 6: strcpy(ch,"so sanh nho hon bang");break;
		case 7: strcpy(ch,"dich trai"); break;
		case 8: strcpy(ch,"so sanh nho hon"); break;
		case 10: strcpy(ch,"so sanh khong bang"); break;
		case 11: strcpy(ch,"phu dinh"); break;
		case 13: strcpy(ch,"so sanh bang"); break;
		case 14: strcpy(ch,"gan"); break;
		case 17: strcpy(ch,"cong bang"); break;
		case 18: strcpy(ch,"tang 1"); break;
		case 19: strcpy(ch,"cong"); break;
		case 21: strcpy(ch,"tru bang"); break;
		case 22: strcpy(ch,"giam 1"); break;
		case 23: strcpy(ch,"tru"); break;
		case 25: strcpy(ch,"nhan bang"); break;
		case 26: strcpy(ch,"nhan"); break;
		case 28: strcpy(ch,"chia bang"); break;
		case 29: strcpy(ch,"chia"); break;
		case 30: strcpy(ch,"chia lay du"); break;
		default: strcpy(ch,"token ko duoc doan nhan(tt ko dung \0");
	}
	return ch;
}

int nostar_end_state(state s){
//kiem tra trang thai s co phai la trang thai ket thuc khong sao ?
	switch(s){
		case 2:
		case 3:
		case 6:
		case 7:
		case 10:
		case 13:
		case 17:
		case 18:
		case 21:
		case 22:
		case 25:
		case 28:
		case 30: return 1;
		default: return 0;
	}
}

int star_end_state(state s){
	//kiem tra trang thai s co phai la trang thai ket thuc sao ?
	switch(s){
		case 4:
		case 8:
		case 11:
		case 14:
		case 19:
		case 23:
		case 26:
		case 29: return 1;
		default: return 0;
	}
}

state start_state_otherbrand(state s){
	state start;
	switch(s){
		case 0: start=15; break;
		case 15: start=ERROR_STATE;
	}
	return start;
}
	
int start_state(state s){
	if ((s==0) || (s==15)) return 1; else return 0;
}

void catchar_in_token (unsigned char c, token tk){
	// ghep them ky tu c vao cho tu to tk
	unsigned char *tam;
	*tam=c; //*(tk+strlen(tk))=c;
	*(tam+1)='\0'; //*(tk+strlen(tk)+1)='\0';
	strcat(tk,tam); //
}

token search_token (unsigned int *i, attri tt){
// tra ve tri tu vung cua tu to bdau tu vi tri i, thuoc tinh tra ve cho tt
	token tk;
	state s=0;
	int stop=0;
	unsigned char c;
	do {
		c=readchar(x,*i);
		*i=*i+1;
	} while ((c==' ')&&(*i<strlen(x)));
	
	while (*i<strlen(x)&&(!stop))
	{
		switch(s){
			case 0: if (c=='>') s=1;
				else if (c=='<') s=5;
				else if (c=='!') s=9;
				else if (c=='=') s=12;
				else s=start_state_otherbrand(s);
				break;
			case 1: if (c=='=') s=2;
				else if (c=='>') s=3;
				else s=4;
				break;
			case 5: if (c=='=') s=6;
				else if (c=='<') s=7;
				else s=8;
				break;
			case 9: if (c=='=') s=10;
				else s=11;
				break;
			case 12: if (c=='=') s=13;
				else s=14;
				break;
			case 15: if (c=='+') s=16;
				else if (c=='-') s=20;
				else if (c=='*') s=24;
				else if (c=='/') s=27;
				else if (c=='%') s=30;
				else s=start_state_otherbrand(s);
				break;
			case 16: if (c=='=') s=17;
				else if (c=='+') s=18;
				else s=19;
				break;
			case 20: if (c=='=') s=21;
				else if (c=='-') s=22;
				else s=23;
				break;
			case 24: if (c=='=') s=25;
				else s=26;
				break;
			case 27: if (c=='=') s=28;
				else s=29;
				break;
			default: stop=1;
		}
		if (s==ERROR_STATE
		{
			stop=1;
			printf("loi tai ky tu thu %i",*i);
			*tk='\0'; 
		}
		else if (start_state(s));
		else if (nostar_end_state(s)) 
		{
			catchar_in_token(c,tk);
			*i=*i+1; stop=1;
			strcpy(tt,attribute(s));
		}
		else if (star_end_state(s))
		{
		strcpy(tt,attribute(s)); stop=1;
		}
		else 
		{
			catchar_in_token(c,tk); 
			*i=*i+1; 
			c=readchar(x,*i);
		}
	}
	return tk;
}

void save_token_and_attribute(token tk,attri a){
//luu tru tk,a vao danh sach
}

void lexical_analysis(){
	token tk; attri a;
	do {
		tk=search_token(&i,a);
		save_token_and_attribute(tk,a);
	}while ((*tk!='\0')&&(i<strlen(x)));
}

main(){
	//nhap xau vao x
	i=0;
	lexical_analysis();
	//in danh sach tu to va thuoc tinh
}
