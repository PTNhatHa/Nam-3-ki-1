
int table[][MAX];
token search_token (unsigned int *i, attri tt){
	// tra ve tri tu vung cua tu to bdau tu vi tri i, thuoc tinh tra ve cho tt
	token tk; unsigned char c;
	state s=0, cs;
	//c?t ký t? tr?ng b?
	do {
		c=readchar(x,*i);
		cs=table[s][c];
		if (cs==ERROR_STATE)
		{
			printf(“loi tai vi tri %i”,*i); tk=“”;break;
		}
		if (star_end_state(cs)) 
		{
			strcpy(tt,attribute(cs)); 
			break;
		}
		if (nostar_end_state(cs)) 
		{
			catchar_in_token(c,tk);
			*i++;
			strcpy(tt,attribute(cs));
			break;
		}
		if (*i>=(strlen(x)-1)) 
		{
			printf(“het xau vao, ko roi vao TT ket thuc”);
			tk=“”; break;
		}
		catchar_in_token(c,tk);
		*i++;
		s=cs;
	}while(1);
	return tk;
}

void create_table(int table[][MAX]){
// tao bang chuyen trang thai table
}

void lexical_analysis(){
	token tk; attri a;
	create_table(table);
	do {
		tk=search_token(&i,a);
		save_token_and_attribute(tk,a);
	}while ((*tk!='\0')&&(i<strlen(x)));
}


