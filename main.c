#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
            char *name;
            struct node *left;
            struct node *left_middle;
            struct node *right_middle;
            struct node *right;
            struct node *parent;
    };
struct node *root;  
struct node *copy;     
struct node *cut;  
struct node* newnode(struct node *parent_of_this,char *string);   
void display(struct node *this_node);
void display_inner(struct node *this_nodes_child); 
struct node* insert(char *string, struct node *node_parent);
struct node* goto_parent(struct node *child);
void print_path(struct node *current_node,int counter);
struct node* copynode(struct node *parent_to_copy);

struct node* insert(char *string, struct node *node_parent) {
    struct node *temp=newnode(node_parent,string);
    if (node_parent -> right==NULL ) {
        node_parent -> right =temp;
    }else if (node_parent -> right_middle ==NULL) {
        node_parent -> right_middle = temp;   
    }else if (node_parent -> left_middle==NULL ) {
        node_parent -> left_middle = temp;        
    }else if (node_parent -> left ==NULL) {
        node_parent -> left = temp;          
    }else{
        printf("\nYou can not create more files in this folder");
    }

    return(node_parent);
}

struct node* delete_node(char *string, struct node *current_dir) {
    int num;
    if(current_dir->right!=NULL){
        num=strcmp(current_dir->right->name, string);
        if(num==0){
            current_dir->right=NULL;         
        }
    }
    if(current_dir->right_middle!=NULL){
        num=strcmp(current_dir->right_middle->name, string);
        if(num==0){
            current_dir->right_middle=NULL;         
        }
    }
    if(current_dir->left_middle!=NULL){
        num=strcmp(current_dir->left_middle->name, string);
        if(num==0){
            current_dir->left_middle=NULL;         
        }
    }
    if(current_dir->left!=NULL){
        num=strcmp(current_dir->left->name, string);
        if(num==0){
            current_dir->left=NULL;         
        }
    }

    return(current_dir);
}

struct node* cut_directory(char *string, struct node *current_dir_cut){
    int num;
    int not_found=0;

    if(current_dir_cut->right!=NULL){
        num=strcmp(current_dir_cut->right->name, string);
        if(num==0){
            current_dir_cut->right->parent=cut; 
            cut->right = current_dir_cut->right;   
            current_dir_cut->right=NULL; 
            not_found=1;       
        }
    }
    if(current_dir_cut->right_middle!=NULL){
        num=strcmp(current_dir_cut->right_middle->name, string);
        if(num==0){
            current_dir_cut->right_middle->parent=cut;  
            cut->right = current_dir_cut->right_middle;   
            current_dir_cut->right_middle=NULL;
            not_found=1;    
        }
    }
    if(current_dir_cut->left_middle!=NULL){
        num=strcmp(current_dir_cut->left_middle->name, string);
        if(num==0){
            current_dir_cut->left_middle->parent=cut; 
            cut->right = current_dir_cut->left_middle;
            current_dir_cut->left_middle=NULL;
            not_found=1;        
        }
    }
    if(current_dir_cut->left!=NULL){
        num=strcmp(current_dir_cut->left->name, string);
        if(num==0){
            current_dir_cut->left->parent=cut;  
            cut->right = current_dir_cut->left; 
            current_dir_cut->left=NULL;
            not_found=1;      
        }
    }
    if(not_found==0){
         printf("\nNo such directory");              
    }
    return(current_dir_cut);
     
}

struct node* recreate_path(struct node *parent_copy, struct node *child_copy){
       
    parent_copy=copynode(child_copy);
    if(child_copy->right!=NULL){
            //parent_copy->right=insert(child_copy->name,parent_copy->right);                    
            parent_copy->right=recreate_path(parent_copy->right,child_copy->right);             
    }
    if(child_copy->right_middle!=NULL){
            //parent_copy->right_middle=insert(child_copy->name,parent_copy->right_middle);                              
            parent_copy->right_middle=recreate_path(parent_copy->right_middle,child_copy->right_middle);    
    }
    if(child_copy->left_middle!=NULL){
           // parent_copy->left_middle=insert(child_copy->name,parent_copy->left_middle);   
            parent_copy->left_middle=recreate_path(parent_copy->left_middle,child_copy->left_middle); 
    }
    if(child_copy->left!=NULL){
            //parent_copy->left=insert(child_copy->name,parent_copy->left);                      
            parent_copy->left=recreate_path(parent_copy->left,child_copy->left); 
    } 
    return(parent_copy);
}

struct node* copynode(struct node *parent_to_copy)
{
  
  struct node* node = (struct node*)
                       malloc(sizeof(struct node));
  node->name = parent_to_copy->name;
  node->left = parent_to_copy->left;
  node->left_middle = parent_to_copy->left_middle;
  node->right_middle = parent_to_copy->right_middle;
  node->right = parent_to_copy->right;
  node->parent = parent_to_copy->parent;
  return(node);
}

struct node* copy_directory(char *string, struct node *current_dir_copy){
    int num;
    int not_found=0;

    if(current_dir_copy->right!=NULL){
        num=strcmp(current_dir_copy->right->name, string);
        if(num==0){
            copy->right=recreate_path(copy->right,current_dir_copy->right);       
            not_found=1;       
        }
    }
    if(current_dir_copy->right_middle!=NULL){
        num=strcmp(current_dir_copy->right_middle->name, string);
        if(num==0){
            copy->right=recreate_path(copy->right,current_dir_copy->right_middle);  
            not_found=1;    
        }
    }
    if(current_dir_copy->left_middle!=NULL){
        num=strcmp(current_dir_copy->left_middle->name, string);
        if(num==0){
            copy->right=recreate_path(copy->right,current_dir_copy->left_middle);  
            not_found=1;        
        }
    }
    if(current_dir_copy->left!=NULL){
        num=strcmp(current_dir_copy->left->name, string);
        if(num==0){
            copy->right=recreate_path(copy->right,current_dir_copy->left);  
            not_found=1;      
        }
    }
    if(not_found==0){
         printf("\nNo such directory");              
    }
    return(current_dir_copy);
     
}

struct node* paste_directory(struct node *current_dir_paste){
    int not_found=0;

    if(cut->right!=NULL){
          if(current_dir_paste->right==NULL){
            cut->right->parent=current_dir_paste; 
            current_dir_paste->right = cut->right;   
            cut->right=NULL; 
            not_found=1;       
        }else if(current_dir_paste->right_middle==NULL){
                cut->right->parent=current_dir_paste;  
                current_dir_paste->right_middle = cut->right;   
                cut->right=NULL;
                not_found=1;    
        }else if(current_dir_paste->left_middle==NULL){
                cut->right->parent=current_dir_paste; 
                current_dir_paste->left_middle = cut->right;
                cut->right=NULL;
                not_found=1;        
        }else if(current_dir_paste->left==NULL){
                cut->right->parent=current_dir_paste;  
                current_dir_paste->left = cut->right; 
                cut->right=NULL;
                not_found=1;      
        }
        if(not_found==0){
             printf("\nThis folder is full");              
        }
        return(current_dir_paste);              
    }
    if(copy->right!=NULL){
          if(current_dir_paste->right==NULL){
            copy->right->parent=current_dir_paste; 
            current_dir_paste->right = copy->right;   
            copy->right=NULL; 
            not_found=1;       
        }else if(current_dir_paste->right_middle==NULL){
                copy->right->parent=current_dir_paste;  
                current_dir_paste->right_middle = copy->right;   
                copy->right=NULL;
                not_found=1;    
        }else if(current_dir_paste->left_middle==NULL){
                copy->right->parent=current_dir_paste; 
                current_dir_paste->left_middle = copy->right;
                cut->right=NULL;
                not_found=1;        
        }else if(current_dir_paste->left==NULL){
                copy->right->parent=current_dir_paste;  
                current_dir_paste->left = copy->right; 
                copy->right=NULL;
                not_found=1;      
        }
        if(not_found==0){
             printf("\nThis folder is full");              
        }
        return(current_dir_paste);              
    }

    printf("\nNothing to paste");              
    return(current_dir_paste);                                                     

     
}

void display_inner(struct node *this_nodes_child) {   
     printf("\n%s",this_nodes_child->name); 
}

void display(struct node *this_node) {   
    int count_children=0;
    if(this_node->right!=NULL){ 
       display_inner(this_node->right); 
        count_children++;
    }
    if(this_node->right_middle!=NULL){ 
        display_inner(this_node->right_middle); 
        count_children++;
    }
    if(this_node->left_middle!=NULL){ 
        display_inner(this_node->left_middle); 
        count_children++;
    }
    if(this_node->left!=NULL){ 
        display_inner(this_node->left);  
        count_children++;
    }
    if(count_children==0){
         printf("\nThe folder is empty");                 
    }
}
void display_all(struct node *node_to_display_in_all, int intial) {   
    int i;

    printf("\n");
    for (i=0; i<intial; i++){
        printf("  ");
    }
    if(intial>0){
        printf("| ");           
    }
    printf("%s",node_to_display_in_all->name); 
    intial++;
    if (node_to_display_in_all -> right!=NULL ) {
        display_all(node_to_display_in_all->right,intial);
    }
    if (node_to_display_in_all -> right_middle!=NULL) {
        display_all(node_to_display_in_all->right_middle,intial);
    }
    if (node_to_display_in_all -> left_middle!=NULL ) {
        display_all(node_to_display_in_all->left_middle,intial);    
    }
    if (node_to_display_in_all -> left!=NULL) {
        display_all(node_to_display_in_all->left,intial);         
    }
}

struct node* newnode(struct node *parent_of_this,char *string)
{
  char *nameed=malloc(sizeof(char)*(strlen(string)+1));;
  strcpy(nameed, string);
  struct node* node = (struct node*)
                       malloc(sizeof(struct node));
  node->name = nameed;
  node->left = NULL;
  node->left_middle = NULL;
  node->right_middle = NULL;
  node->right = NULL;
  node->parent = parent_of_this;
  return(node);
}

struct node* goto_child(struct node *parent,char *string) {   
    int got_child=0;
    int num;
    if(parent->right!=NULL){
        num=strcmp(parent->right->name, string);
        if(num==0){ 
           got_child=1;   
           return(parent->right);   
        }
    }
    if(parent->right_middle!=NULL){
        num=strcmp(parent->right_middle->name, string);
        if(num==0){                                         
            got_child=1;
            return(parent->right_middle); 
        }
    }
    if(parent->left_middle!=NULL){
        num=strcmp(parent->left_middle->name, string);
        if(num==0){                                        
            got_child=1;
            return(parent->left_middle);  
        }
    }
    if(parent->left!=NULL){
        num=strcmp(parent->left->name, string);
        if(num==0){                                 
            got_child=1;
            return(parent->left);  
        }
    }
    if(got_child==0){
        printf("\nNo such directory");   
        return(parent); 
    }           
}

struct node* goto_parent(struct node *child) {   
    if(child->parent!=NULL){ 
       return(child->parent);  
    }else{
         printf("\nThis is the root folder");   
         return(child);            
    }
}

void print_path(struct node *current_node,int counter) {   
    if(current_node->parent!=NULL){ 
        print_path(current_node->parent,0);  
    }
    if(counter==0){
       printf("%s\\",current_node->name);  
    }else{
       printf("%s>",current_node->name); 
    }              
}
       
int main(int argc, char *argv[]){
    
    int running=1;
    char check_mk[5];
    char check_copy[5];
    char check_cut[4];
    char check_del[7];
    char check_cd[3];
    char command[64];
    char name_dir[64];
    char cut_dir[64];
    char copy_dir[64];
    char del_dir[64];
    char cd_dir[64];
    root =newnode(NULL,"root");
    cut =newnode(NULL,"cut");
    copy =newnode(NULL,"copy");
    struct node *current; 
    current=root;
    
    while(running==1){
        memset( check_mk, '\0', 5 );
        memset( name_dir, '\0', 64 );
        memset( check_copy, '\0', 5 );
        memset( copy_dir, '\0', 64 );
        memset( check_cut, '\0', 4 );
        memset( cut_dir, '\0', 64 );
        memset( check_del, '\0', 7 );
        memset( del_dir, '\0', 7 );
        memset( check_cd, '\0', 3 );
        memset( cd_dir, '\0', 7 );          
        memset( command, '\0', 64 );
        
        print_path(current,1);
        gets(command);
        
        
        memcpy ( check_mk, &command[0], sizeof(check_mk) );
        check_mk[4]='\0';
        memcpy( name_dir, &command[5], sizeof(command));
        name_dir[63]='\0';
        memcpy ( check_copy, &command[0], sizeof(check_copy) );
        check_copy[4]='\0';
        memcpy( copy_dir, &command[5], sizeof(command));
        copy_dir[63]='\0';
        memcpy ( check_cut, &command[0], sizeof(check_cut) );
        check_cut[3]='\0';
        memcpy( cut_dir, &command[4], sizeof(command));
        cut_dir[63]='\0';
        memcpy ( check_del, &command[0], sizeof(check_del) );
        check_del[6]='\0';
        memcpy( del_dir, &command[7], sizeof(command));
        del_dir[63]='\0';
        memcpy ( check_cd, &command[0], sizeof(check_cd) );
        check_cd[2]='\0';
        memcpy( cd_dir, &command[3], sizeof(command));
        cd_dir[63]='\0';

        if(strcmp(command,"dir")==0){  
                   display(current);                          
        }else if(strcmp(command,"dirall")==0){ 
                   display_all(root,0);   
        }else if(strcmp(command,"paste")==0){ 
                   current=paste_directory(current);                   
        }else if(strcmp(check_cut,"cut")==0){ 
                   current=cut_directory(cut_dir,current);
        }else if(strcmp(check_copy,"copy")==0){ 
                   current=copy_directory(copy_dir, current);                          
        }else if(strcmp(check_mk,"make")==0){ 
                   current=insert(copy_dir, current);                       
        }else if(strcmp(check_del,"delete")==0){
                   current=delete_node(del_dir,current);                                 
        }else if(strcmp(command,"cdup")==0){
                   current=goto_parent(current);                          
        }else if(strcmp(check_cd,"cd")==0){ 
                   current=goto_child(current,cd_dir);                              
        }else if(strcmp(command,"exit")==0){
                   running=0;                             
        }else{
              printf("Command \'%.*s\' is not recognized", sizeof(command), command);
        }
        printf("\n");
    
    }
    	
    return 0;
}

