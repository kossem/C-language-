int strdiff(char *a, char *b) 
{ 
        int i,l,d,k;
	if ( strcmp (a,b)==0)
		d=-1;
	else
	{
		if ( (strlen(a)) < (strlen (b)) )
			l=strlen(a);
		else
			l=strlen(b);
		i=0;
		while ( (a[i]==b[i]) && (i < l) )
			i++;
		d=i*8;
		k=0;
		while ((a[i]&(1<<k))==(b[i]&(1<<k)) && ( k<8))
			k++;
		d+=k;
	}
	
	
	
	return d;
}
