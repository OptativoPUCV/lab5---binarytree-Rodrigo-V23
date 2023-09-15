#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;

struct TreeNode
{
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

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2))
{
  TreeMap* mapa = (TreeMap*)malloc(sizeof(TreeMap));
  if(mapa == NULL)
  {
    return NULL;
  }
  mapa -> current = NULL;
  mapa -> root = NULL;
  mapa -> lower_than = lower_than;

  return mapa;
  //new->lower_than = lower_than;
  return NULL;
}
void insertTreeMap(TreeMap * tree, void* key, void * value)
{
  TreeNode * newNode = createTreeNode(key, value);
  if(tree -> root == NULL)
  {
    tree -> root = newNode;
  }
  else
  {
    TreeNode * currentNode = tree -> root;
    TreeNode * parent = NULL;

    while(currentNode != NULL)
      {
        parent = currentNode;
        if(tree -> lower_than(key, currentNode -> pair -> key))
        {
          currentNode = currentNode -> left;
        }
        else
        {
          if(tree -> lower_than(currentNode -> pair -> key, key))
          {
            currentNode = currentNode -> right;
          }
          else
          {
            free(newNode);
            return;
          }
        }
      }
    newNode -> parent = parent;
    if(tree -> lower_than(key, parent -> pair -> key))
    {
      parent -> left = newNode;
    }
    else
    {
      parent -> right = newNode;
    }
  }
  tree -> current = newNode;
}
TreeNode * minimum(TreeNode * x)
{
  if(x == NULL)
  {
    return NULL;
  }
  while(x -> left != NULL) 
  {
    x = x -> left;
  }
  return x;
}
void removeNode(TreeMap * tree, TreeNode* node)
{
  
}
void eraseTreeMap(TreeMap * tree, void* key)
{
  if (tree == NULL || tree->root == NULL) return;

  if (searchTreeMap(tree, key) == NULL) return;
  TreeNode* node = tree->current;
  removeNode(tree, node);
}
Pair * searchTreeMap(TreeMap * tree, void* key)
{
  tree -> current = NULL;
  TreeNode * currentNode = tree -> root;

  while(currentNode != NULL)
    {
      int valor = tree -> lower_than(key, currentNode -> pair -> key);
      if(valor == 0)
      {
        tree -> current = currentNode;
        return currentNode -> pair;
      }
      else
      {
        if(valor < 0)
        {
          currentNode = currentNode -> left;
        }
        else
        {
          currentNode = currentNode -> right;
        }
      }
    }
  return NULL;
}
   

Pair * upperBound(TreeMap * tree, void* key)
{
  TreeNode * currentNode = tree -> root;
  TreeNode * ub_node = NULL;
  
  while(currentNode != NULL)
  {
    
    if(int valor = lower_that(key, currentNode -> pair -> key) < 0)
    {
      return currentNode -> pair;
    }
    else
    {
      if(lower_that(currentNode -> pair -> key, key))
      {
        ub_node = currentNode;
        currentNode = currentNode -> left;
      }
      else
      {
        currentNode = currentNode -> right;
      }
    }
    if(ub_node == NULL)
    {
      return NULL;
    }
    else
    {
      return ub_node -> pair;
    }
  }
}
Pair * firstTreeMap(TreeMap * tree)
{
  TreeNode * minNode = minimum(tree -> root);
  if(minNode != NULL)
  {
    tree -> current = minNode;
    return minNode -> pair;
  }
  return NULL;
}
Pair * nextTreeMap(TreeMap * tree)
{
  if(tree -> current != NULL)
  {
    TreeNode * siguiente = tree -> current -> right;
    if(siguiente != NULL)
    {
      tree -> current = minimum(siguiente);
      return tree -> current -> pair;
    }
    else
    {
      TreeNode * current = tree -> current;
      TreeNode * parent = current -> parent;
      while(parent != NULL && parent -> right == current)
      {
        current = parent;
        parent = parent -> parent;
      }
      tree -> current = parent;
      if(parent != NULL)
      {
        return parent -> pair;
      }
    }
  }
  return NULL;
}
