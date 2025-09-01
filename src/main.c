#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define EFOPEN(file) assert(("file could not be opened", file))
#define EFCLOSE(close) assert(("file could not be closed", !close))

#define ELISP_EMPAREN() fprintf(stderr, "file doesnt contain matching brackets\n"); exit(EXIT_FAILURE);

// the multiplier for the respective bracket
// this allows me to encode data, if index == ( -> -index; if index == ) -> index
// i couldve used an enum but i would much rather check because what if idx{0} = (
enum TOKENS {
  T_OBRAC = '(',
  T_CBRAC = ')',
  T_COMM = '$'
};

// children is null if its linear (llist, stack, queue)
// else its a tree. i have proven that i can use a single ll so here its double
// a branch in a tree would be {.data=&chr, .children={&subexpr1, &subexpr2}}
typedef struct node {
  struct node *prev;
  struct node *next;
  struct node **children; // a linked list of pointers (calling realloc is expensive)
  uint64_t childCount;
  uint64_t key; // for tree stuff i guess  
  void *data;
} node_t;

///////////////////////////////////////////////////////////////////////////////
// DATA STRUCTURES
///////////////////////////////////////////////////////////////////////////////
void *stackTail(node_t *head) {
  static node_t *iter = NULL;
  for (iter = head; iter->next; iter = iter->next) {} 
  return iter;
}  
void stackPush(node_t *head, node_t *new) {
  static node_t *tail = NULL;
  tail = stackTail(head);
  // printf("%ld\n", *(uint64_t*)tail->data);
  new->prev = tail;
  tail->next = new;
}
void *stackPop(node_t *head) {
  static node_t *tail = NULL, *penult = NULL;
  tail = stackTail(head);
  if (tail == head) {
    return NULL;
  }
  penult = tail->prev;
  if (penult) {
    penult->next = NULL;
  }
  tail->prev = NULL;
  return tail;
}
void queueEnqueue(node_t *head, node_t *new) {
  return stackPush(head, new);
}
void *queueDequeue(node_t **head) {
  static node_t *tail = NULL; // not the tail but thats my convention
  tail = *head;
  if (*head) {
    (*head) = (*head)->next;
    tail->next = NULL;
  }
  if (*head) {
    (*head)->prev = NULL;
  }
  return tail;
}
void llistRShift(node_t **head, node_t *new) {
  new->next = (*head);
  (*head)->prev = new;
  (*head) = new;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// FILE READING
///////////////////////////////////////////////////////////////////////////////
// this accounts for the \0 by adding 1 to the actual size
// a rope (implemented as a tree) would be better (will do in the future)
uint64_t readFileLength(const char *const filePath) {
  static FILE *file = NULL;
  uint64_t size = 0;

  file = fopen(filePath, "r");
  EFOPEN(file);
  fseek(file, 0ULL, SEEK_END);
  size = ftell(file);
  // rewind(file); // i dont know if i need this
  EFCLOSE(fclose(file));
  return size + 1; // +1 due to the EOF / \0 at the end
}
// this relies on the file buffer already being allocated
void readFileIntoBuffer(const char *const filePath, char *const fileBuffer, const uint64_t fileLen) {
  static FILE *file = NULL;
  file = fopen(filePath, "r");
  EFOPEN(file);
  fread(fileBuffer, sizeof(*fileBuffer), fileLen, file);
  EFCLOSE(fclose(file));
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PRE PROCESSING
///////////////////////////////////////////////////////////////////////////////
// i know that the next step removes the comments and stuff
// but thats hardly possible if the file is a tree
// returns the offset to allocate a new child into the tree
uint64_t getExprs(char *const fileBuffer, const uint64_t fileLen,
		     const int64_t fileOffset) {
  static int64_t openBracket = 0;
  // if there is a new subexpression return its index so it can be allocated
  for (uint64_t fileIter = fileOffset+1; fileIter < fileLen; ++fileIter) {
    if (openBracket < 0) {
      ELISP_EMPAREN();
    }
    switch (fileBuffer[fileIter]) {
    case T_OBRAC:
      openBracket++;
      return fileIter;
    case T_CBRAC:
      openBracket--;
      return fileIter;
    }
  }
  if (openBracket != 0) {
    ELISP_EMPAREN();
  }    
  return fileLen;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// DEBUGGING
///////////////////////////////////////////////////////////////////////////////
void printNode(node_t *const node) {
  printf("%p ->\t%p{%ld : %p} ->\t%p\n",
         node->prev, node, *(uint64_t*)node->data, node->children, node->next);
}
void printStack(node_t *const node) {
  static node_t *iter = NULL;
  for (iter = node; iter; iter = iter->next) {
    printNode(iter);
  }
}
// trees dont have a next, trees have a prev and children as a linked list
void printTree(node_t *const node, uint64_t indent) {
  static node_t *iter = NULL;
  if (!node) {
    return;
  }    

  for (uint64_t idt = 0; idt < indent; printf(" "), ++idt) {}

  printf("%p <- %p ->>", node->prev, node);
  for (uint64_t idx = 0; idx < node->childCount; ++idx) {
    printf("%p", node->children[idx]);
  }
  for (uint64_t idx = 0; idx < node->childCount; ++idx) {
    printTree(node->children[idx], indent+1);
  }
  
}  
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
  // reads the file contents
  const char *file = "./test.brac";
  const uint64_t fileLen = readFileLength(file);
  char buffer[fileLen];
  memset(buffer, 0, fileLen);
  readFileIntoBuffer(file, buffer, fileLen);
  int64_t fileIter = -1;

  // stores the indexes of all the brackets
  node_t *openBrack = NULL;
  node_t *closeBrack = NULL;
  do {
    uint64_t returnVal = getExprs(buffer, fileLen, fileIter);
    node_t *new = calloc(1, sizeof(*new));
    *new = (node_t){.data = calloc(1, sizeof(uint64_t))};
    *(uint64_t*)new->data = returnVal;

    if (buffer[returnVal] == T_OBRAC) {
      if (!openBrack) { openBrack = new;
      } else {          stackPush(openBrack, new); }
    } else if (buffer[returnVal] == T_CBRAC) {
      if (!closeBrack) { closeBrack = new;
      } else {           stackPush(closeBrack, new); }
    }
    fileIter = returnVal;
  } while (fileIter < fileLen);

  // now openBrack.len === closeBrack.len and now i can store it in a tree
  // after this is where the actual things will happen, the comment removal and
  // the like
  uint64_t oBrackIdx = 0;
  uint64_t cBrackIdx = 0;
  node_t *openPop = NULL;
  node_t *closePop = NULL;

  node_t *tree = calloc(1, sizeof(*tree));
  node_t *root = tree;
  node_t *iter = NULL;
  for (uint64_t fileIdx = 0; fileIdx < fileLen; ++fileIdx) {
    openPop = queueDequeue(&openBrack);
    closePop = queueDequeue(&closeBrack);
    oBrackIdx = openPop  ? *(uint64_t*)openPop->data  : (uint64_t)-1;
    cBrackIdx = closePop ? *(uint64_t*)closePop->data : (uint64_t)-1;
    if (oBrackIdx < cBrackIdx) {
      if (closeBrack)  { llistRShift(&closeBrack, closePop);
      } else {           closeBrack = closePop; }

      //*
      node_t *subtree = calloc(1, sizeof(*subtree));
      subtree->data = calloc((oBrackIdx - fileIdx) + 1, sizeof(char));
      strncpy(subtree->data, &buffer[fileIdx], oBrackIdx - fileIdx);
      printf("%s\n", subtree->data);
      // */

      // printf("%.*s#{", (oBrackIdx - fileIdx), &buffer[fileIdx]);
      fileIdx = oBrackIdx;
    } else if (oBrackIdx > cBrackIdx) {
      if (openBrack)  { llistRShift(&openBrack, openPop);
      } else {           openBrack = openPop; }

      //*
      node_t *subtree = calloc(1, sizeof(*subtree));
      subtree->data = calloc((oBrackIdx - fileIdx) + 1, sizeof(char));
      strncpy(subtree->data, &buffer[fileIdx], oBrackIdx - fileIdx);
      printf("%s\n", subtree->data);
      // */

      printf("%.*s}#", (cBrackIdx - fileIdx), &buffer[fileIdx]);
      fileIdx = cBrackIdx;
    }
  }
  // printTree(root, 0);
  /*
  printf("%s\n", buffer);
  printStack(openBrack);
  printStack(closeBrack);
  // */
  return 0;
}
