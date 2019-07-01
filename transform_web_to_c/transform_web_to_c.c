#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <io.h> //c_file
#include <direct.h>

//testing
#include "stringweb.h" 

#ifdef _LINUX_
void _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext);
static void _split_whole_name(const char *whole_name, char *fname, char *ext);
#endif

char *str_replace (char *source, char *find,  char *rep);

// str_replace :input char *source , find specific string , replace by *rep
char *str_replace (char *source, char *find,  char *rep){  
   //   
   int find_L=strlen(find);  
   //   
   int rep_L=strlen(rep);  
   // 
   int length=strlen(source)+1;  
   //   
   int gap=0;  
     
   //   
   char *result = (char*)malloc(sizeof(char) * length);  
   strcpy(result, source);      
     
   // 
   char *former=source;  
   //   
   char *location= strstr(former, find);  
     
   //   
   while(location!=NULL){  
       //   
       gap+=(location - former);  
       //   
       result[gap]='\0';  
         
       //  
       length+=(rep_L-find_L);  
       //  
       result = (char*)realloc(result, length * sizeof(char));  
       //   
       strcat(result, rep);  
       // 
       gap+=rep_L;  
         
       //   
       former=location+find_L;  
       // 
       strcat(result, former);  
         
       // 
       location= strstr(former, find);  
   }      
  
   return result;  
  
} 

#ifdef _LINUX_
//splitpath with dir, file's name and extension name
void _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext)
{
	char *p_whole_name;
 
	drive[0] = '\0';
	if (NULL == path)
	{
		dir[0] = '\0';
		fname[0] = '\0';
		ext[0] = '\0';
		return;
	}
 
	if ('/' == path[strlen(path)])
	{
		strcpy(dir, path);
		fname[0] = '\0';
		ext[0] = '\0';
		return;
	}
 
	p_whole_name = rindex(path, '/');
	if (NULL != p_whole_name)
	{
		p_whole_name++;
		_split_whole_name(p_whole_name, fname, ext);
 
		snprintf(dir, p_whole_name - path, "%s", path);
	}
	else
	{
		_split_whole_name(path, fname, ext);
		dir[0] = '\0';
	}
}


static void _split_whole_name(const char *whole_name, char *fname, char *ext)
{
	char *p_ext;
 
	p_ext = rindex(whole_name, '.');
	if (NULL != p_ext)
	{
		strcpy(ext, p_ext);
		snprintf(fname, p_ext - whole_name + 1, "%s", whole_name);
	}
	else
	{
		ext[0] = '\0';
		strcpy(fname, whole_name);
	}
}
#endif

typedef struct _fname_arrayname_element_ {
	char filename[128];
	char arrayname[128];
	unsigned long size_t;//char size[16];
	//char ptrname[128];
}fname_arrayname_element;

unsigned int file_count=0;
fname_arrayname_element *mapping_table;
char input_file_pwd[128]={0};


#ifdef  _test_struct_init_
typedef struct table{
	char *filename;
	char *arrayname;
	unsigned long size;
	char *ptrname;		
}stringweb_h_table;

stringweb_h_table stb[]={
		{"blank.html", "blank_html", 0, (char *)&(blank_html[0])},
		{"bootstrap-slider.min.css", "bootstrap_slider_min_css", 7648, (char *)&(bootstrap_slider_min_css[0])},		
		{"bootstrap-slider.min.js", "bootstrap_slider_min_js", 37734, (char *)&(bootstrap_slider_min_js[0])},
		{"bootstrap.min.css", "bootstrap_min_css", 121200, (char *)&(bootstrap_min_css[0])},
		{"bootstrap.min.js", "bootstrap_min_js", 37045, (char *)&(bootstrap_min_js[0])},	
		{NULL, NULL, 0, NULL},
};

void test_struct_init(){
	int i;
	
	printf("\r\nbootstrap_slider_min_css_addr:%08x", bootstrap_slider_min_css);
	printf("\r\nbootstrap_slider_min_css_ptr_addr:%08x", bootstrap_slider_min_css_ptr);
	//printf("\r\nstruct_init_addr:%08x", stringweb_h_table[7]);
	
	while( stb[i].filename!= NULL){
		printf("\r\n stb fn:%s, an:%s, size:%ld, addr:%08x", &(stb[i].filename[0]), stb[i].arrayname, stb[i].size,stb[i].ptrname);
		i++;
	} 
	
}
#endif

int getallfiles(char *folder_path){

	char sdir[256], filter[256], path[256];
	struct _finddata_t c_file;
	long hFile;
	
	int i;
	unsigned int index=0;
    char drive[16];
    char dir[128];
    char fname[128];
    char ext[16];
    
    char temp[8]={0};
    //fname_arrayname_element *mapping_table;

    char *head;

	
	//strcpy( sdir, "C:\\SOME_FOLDER" );
	//strcpy( sdir, "E:\\code\\DevC\\auto_transfer\\css" );
	strcpy( sdir, folder_path );
	
	strcpy( filter, "*.*" );
	
	if(_chdir( sdir ) !=0 ){
		printf("\r\n Enter Folder failed.");
		return -1;
	}
	hFile = _findfirst(filter, &c_file);
	if( hFile!=-1 )
	{
	    do{
			// it would search . and .. at first
			if(i <2 ){
				memset(temp,0,sizeof(temp));
				strncpy(temp, c_file.name, strlen(c_file.name));
			}

			if(strcmp(c_file.name, temp) != 0 ){	
				//printf( "%s\n", c_file.name );
				file_count = file_count+1;				
			}

			i=i+1;
	    }
		while( _findnext( hFile, &c_file )==0 );	
	}
	printf("\r\n file_count :%2d\n",file_count);
	

	mapping_table = (fname_arrayname_element *)malloc( file_count * sizeof(fname_arrayname_element));
	if( mapping_table == NULL ) {
		printf("Error: unable to allocate required memory\n");
		return -1;
	}	
 
 	memset(mapping_table, 0, file_count * sizeof(fname_arrayname_element));  //init struct '\0'
 
 	i=0;
	hFile = _findfirst(filter, &c_file);
	if( hFile!=-1 )
	{
	    do{
			if(i <2 ){
				memset(temp,0,sizeof(temp));
				strncpy(temp, c_file.name, strlen(c_file.name));
			}	    
			if(strcmp(c_file.name, temp) != 0 ){		
				//printf( "%s\n", c_file.name );
				//strncpy(mapping_table[index].filename, "Test", strlen("Test"));
				//printf("\r\n%d: %s, %s",i,mapping_table[index].filename, mapping_table[index].arrayname);
				strncpy(mapping_table[index].filename, c_file.name, strlen(c_file.name)); 

				head=str_replace(c_file.name,".","_");
				head=str_replace(head,"-","_");
				strncpy(mapping_table[index].arrayname, head , strlen(head));
				//printf("\r\n%d: %s, %s",index,mapping_table[index].filename, mapping_table[index].arrayname);
				index = index +1;							
			}
			i=i+1;
	
	    }
		while( _findnext( hFile, &c_file )==0 );	
	}
	printf("\r\nInput files directory: %s\n", getcwd(NULL, NULL));
	
	memset(input_file_pwd, 0, sizeof(input_file_pwd));
	getcwd(input_file_pwd, sizeof(input_file_pwd));

	//_chdir( ".." ); //back to up folder
	//printf("\r\ncurrent working directory: %s\n", getcwd(NULL, NULL));
	for(i=0;i<index;i++){
		printf("\r\n%d: %s, %s",i,mapping_table[i].filename, mapping_table[i].arrayname);
	}

	//free(mapping_table); 
	return 0;	
}


//example E:\code\auto_transfer$ auto_transfer E:\\code\\DevC\\auto_transfer\\css\\switch.css
int main (int argc, char *argv[]){
	
	char ch=0,ch2=0;
	unsigned long i=0,ch_length;
	
	unsigned long index=0,count=0;
	unsigned long size_total=0;
	unsigned char ten=0, one=0, sum=0;
	
	char filename[128]={0}, *head, *ptr;
	char arrayname[128]={0};
	
	const char cmp = '.';

	//char *string_long="750168";	
	//printf("\r\nstring_long:%lld", atol(string_long) );
	//printf("\r\n");
    //char drive[16];
    //char dir[128];
    //char fname[128];
    //char ext[16];

	
	char fname[128];
	char input_file_full_path[256]={0};
	char pwd_path[128]={0}, output_folder[128]={0};
	
	FILE *fp_in, *fp_out, *fp_stringweb_h;



	memset(filename,0,sizeof(filename));
	memset(arrayname,0,sizeof(arrayname));
	getcwd(pwd_path, sizeof(pwd_path));
	printf("\r\nPWD_path=%s\n", pwd_path);	

	
	if(argc >2){
		printf("\r\n%s, %s",argv[0],argv[1]);
		return -2;
	}

//get all files	
	if(getallfiles(argv[1]) !=0){
		printf("\r\n Enter Folder failed.");
		return -1;		
	}  
	
	
	_chdir( &(pwd_path[0]) );	
	//printf("\r\nCurrent working directory: %s\n", getcwd(NULL, NULL));
	
//make output folder	
	if((access( "./out", 0 )) ==0){
		printf( "\r\n%s exists ", "./out");
	}
	else{
		printf( "\r\ncan not find %s , create it", "./out");
		//if (mkdir("./out",S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0){ 
		if (mkdir("./out")){
	        printf("\r\ncan not create out folder, Error:%d\n", __LINE__);
			//return -1;
		}		
	}
	//if( (access( ACCESS.C, 2 )) == 0 ){
	//	printf( "File ACCESS.C has write permission " );
	//}	
	
//enter ./out
//.c		
    if(chdir("./out") ==0)
    	printf("\r\nOut directory: %s\n", getcwd(NULL, NULL));
    else
    	printf("\r\ncan not enter /out");	
	
	printf("\r\n>>>");
	for(i=0; i<file_count ; i++){
		ch_length =0;
		
		memset(input_file_full_path,0,sizeof(input_file_full_path));
		strcpy(input_file_full_path, input_file_pwd);
		strcat(input_file_full_path, "\\");
		strcat(input_file_full_path, mapping_table[i].filename);
		printf("\r\n%d: %s",i,input_file_full_path);	
		
		fp_in=fopen(input_file_full_path,"rb");
		if( NULL == fp_in ){
	        printf( "\r\n%s open failure", input_file_full_path );
	        return -1;
	    }
		
		memset(fname,0,sizeof(fname));
		strncpy(fname,mapping_table[i].arrayname,strlen(mapping_table[i].arrayname));
		strcat(fname,".c");		
		fp_out=fopen(fname,"w+");
		
		if( NULL == fp_out ){
	        printf( "\r\n%s open failure", fname );
	        return -1;
	    }

		fprintf(fp_out,"char %s[]={", mapping_table[i].arrayname);	
		while( (ch=fgetc(fp_in)) != EOF){	
			fprintf(fp_out,"0x%02x, ",ch);
			ch_length=ch_length+1;				
		}
		

		mapping_table[i].size_t = ch_length;
		fprintf(fp_out,"};\n");

	
		
   //fseek(fp_in, 0, SEEK_END);
   //size_total = ftell(fp_in);
   //printf("\r\nsize_total:%lld",size_total);

   		
		fclose(fp_in);
		fclose(fp_out);
			
					
	}
//.h	
	fp_stringweb_h=fopen("stringweb.h","w+");
	//extern char *array_name;
	for(i=0; i<file_count ; i++){
		fprintf(fp_stringweb_h,"extern char %s[];\n", mapping_table[i].arrayname);
	}
	
	//for(i=0; i<file_count ; i++){
	//	fprintf(fp_stringweb_h,"extern char *%s;\n", mapping_table[i].ptrname);
	//}		
	
	//typedef 
	fprintf(fp_stringweb_h,"typedef struct _stringweb_table_{\n" );
	fprintf(fp_stringweb_h,"\tchar *filename;\n" );
	fprintf(fp_stringweb_h,"\tchar *arrayname;\n" );
	fprintf(fp_stringweb_h,"\tunsigned long size;\n" );
	fprintf(fp_stringweb_h,"\tchar *ptrname;\n" );
	fprintf(fp_stringweb_h,"}stb;\n" );
	
	
	//total file string count;
	fprintf(fp_stringweb_h,"unsigned int stringweb_table_count=%d;\n", file_count*4);
	//const char *stringweb table;
	//fprintf(fp_stringweb_h,"const char *stringweb_table[] = {\n");
	fprintf(fp_stringweb_h,"stb stringweb_table[] = {\n");
	for(i=0; i<file_count ; i++){
		fprintf(fp_stringweb_h,"\t{\"%s\", \"%s\", %ld, (char *)&(%s[0]) },\n", mapping_table[i].filename, mapping_table[i].arrayname, mapping_table[i].size_t, mapping_table[i].arrayname);
	}
	fprintf(fp_stringweb_h,"\t{NULL, NULL, 0, NULL},\n");
	fprintf(fp_stringweb_h,"};\n");
	

	fclose(fp_stringweb_h);		


#ifdef _test_struct_init_	
	//test_struct_init();
#endif	
		
return 0;

	
}	

