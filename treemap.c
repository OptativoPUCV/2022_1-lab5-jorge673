#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

  TreeMap* map=(TreeMap*)malloc(sizeof(TreeMap));
  map->lower_than = lower_than;
  
  return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  if (tree==NULL || tree->root==NULL) return;

  searchTreeMap(tree, key);
  TreeNode* node=tree->current;

  if(tree->lower_than(node->pair->key,key)){
    TreeNode* new=createTreeNode(key,value);
    new->parent=node;
    node->right=new;
    tree->current=new;
  }
  if(tree->lower_than(key,node->pair->key)){
    TreeNode* new=createTreeNode(key,value);
    new->parent=node;
    node->left=new;
    tree->current=new;
  }

}

TreeNode * minimum(TreeNode * x){

  TreeNode* aux=x;

  while (aux!=NULL)
  {
    if (aux->left==NULL)
    {
      return aux;
    }
    
    aux=aux->left;
  }
  

  return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  if (tree == NULL || tree->root == NULL) return;

  if(node->parent->left==node){
    if(node->left==NULL || node->right==NULL){
      if (node->left!=NULL){

        node->left->parent=node->parent;
        node->parent->left=node->left;
        
      }else if (node->right!=NULL){

        node->right->parent=node->parent;
        node->parent->left=node->right;

      }else{
        node->parent->left=node->left;
        node=NULL;
      }
      
    }else{
      puts("nodo izquierdo tiene 2 hijos");
      TreeNode* son=node->right;
      son=minimum(son);
      node->parent->left=son;
      son->parent=node->parent;
      son->right=node->right;
    }

  }else{
    if(node->left==NULL || node->right==NULL){
      if (node->left!=NULL){

        node->left->parent=node->parent;
        node->parent->right=node->left;
        
      }else if (node->right!=NULL){

        node->right->parent=node->parent;
        node->parent->right=node->right;

      }else{
        node->parent->right=node->left;
        node=NULL;
      }
      
    }else{
      puts("nodo derecho tiene 2 hijos");
      TreeNode* son=node->right;
      son=minimum(son);
      node->parent->right=son;
      son->parent=node->parent;
      son->right=node->right;
    }
  }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  TreeNode* aux=tree->root;
  while(aux!=NULL){
    tree->current=aux;
    if(tree->lower_than(key,aux->pair->key)){
      aux=aux->left;
    }else if(tree->lower_than(aux->pair->key,key)){
      aux=aux->right;
    }else{
      tree->current=aux;
      return aux->pair;
    }
  } 
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {

    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
