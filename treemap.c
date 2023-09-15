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
Pair* searchTreeMap(TreeMap* tree, void* key) {
    // Inicializar el puntero current
    tree->current = NULL;

    // Comenzar la búsqueda desde la raíz del árbol
    TreeNode* currentNode = tree->root;

    while (currentNode != NULL) {
        // Comparar la clave actual con la clave buscada utilizando la función de comparación
        int comparisonResult = tree->lower_than(key, currentNode->pair->key);

        if (comparisonResult == 0) {
            // La clave buscada es igual a la clave actual, se encontró el nodo
            tree->current = currentNode;
            return currentNode->pair;
        } else if (comparisonResult < 0) {
            // La clave buscada es menor que la clave actual, buscar en el subárbol izquierdo
            currentNode = currentNode->left;
        } else {
            // La clave buscada es mayor que la clave actual, buscar en el subárbol derecho
            currentNode = currentNode->right;
        }
    }

    // Si llegamos aquí, la clave no se encontró en el árbol
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
