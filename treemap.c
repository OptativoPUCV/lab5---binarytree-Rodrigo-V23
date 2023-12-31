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
  if(node->left == NULL && node->right == NULL)
  {
    if(node->parent != NULL)
    {
      if(node->parent->left == node)
      {
        node->parent->left = NULL;
      }
      else
      {
        node->parent->right = NULL;
      }
    }
    else
    {
      tree -> root = NULL;
    }
    free(node);
    return;
  }
  if(node->left == NULL || node->right == NULL)
  {
    TreeNode* aux = node->left != NULL ? node->left : node->right;
    if(node->parent != NULL)
    {
      if (node->parent->left == node)
      {
        node->parent->left = aux;
      }
      else
      {
        node->parent->right = aux;
      }
      aux->parent = node->parent;
    }
    else
    {
      tree -> root = NULL;
      aux -> parent = NULL;
    }
    free(node);
    return;
  }
  TreeNode* lastNode = minimum(node->right);
  node->pair->key = lastNode->pair->key;
  node->pair->value = lastNode->pair->value;
  removeNode(tree, lastNode);
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
  TreeNode * currentNode = tree -> root;
  while(currentNode != NULL)
  {
    if(is_equal(tree, currentNode -> pair -> key, key))
    {
      tree -> current = currentNode;
      return currentNode -> pair;
    }
    else
    {
      if(tree -> lower_than(key, currentNode -> pair -> key))
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
    
    if(is_equal(tree, currentNode -> pair -> key, key))
    {
      return currentNode -> pair;
    }
    else
    {
      if(tree -> lower_than(currentNode -> pair -> key, key) == 1)
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