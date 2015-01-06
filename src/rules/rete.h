#include "state.h"

#define OP_NOP 0
#define OP_LT 0x01
#define OP_LTE 0x02
#define OP_GT 0x03
#define OP_GTE 0x04
#define OP_EQ 0x05
#define OP_NEQ 0x06
#define OP_EX 0x07
#define OP_NEX 0x08
#define OP_ALL 0x09
#define OP_ANY 0x0A
#define OP_OR 0x0B
#define OP_AND 0x0C
#define OP_END 0x0D
#define OP_ADD 0x0E
#define OP_SUB 0x0F
#define OP_MUL 0x10
#define OP_DIV 0x11
#define OP_TYPE 0x12

#define NODE_ALPHA 0
#define NODE_BETA_CONNECTOR 1
#define NODE_ACTION 2
#define NODE_M_OFFSET 0

typedef struct reference {
    unsigned int hash;
    unsigned int nameOffset;
    unsigned int idOffset;
} reference;

typedef struct jsonValue {
    unsigned char type;
    union { 
        long i; 
        double d; 
        unsigned char b; 
        unsigned int stringOffset;
        unsigned int idiomOffset;
        reference property;
    } value;
} jsonValue;

typedef struct idiom {
    unsigned char operator;
    jsonValue left;
    jsonValue right; 
} idiom;

typedef struct expression {
    unsigned int nameOffset;
    unsigned int aliasOffset;
    unsigned short termsLength;
    union {
        unsigned int termsOffset; 
        unsigned int *termsPointer;
    } t;
} expression;

typedef struct join {
    unsigned short count;
    unsigned int expressionsOffset;
    unsigned short expressionsLength;
} join;

typedef struct alpha {
    unsigned int hash;
    unsigned char operator;
    unsigned int betaListOffset;
    unsigned int nextListOffset;
    unsigned int nextOffset;
    jsonValue right;
} alpha;

typedef struct betaConnector {
    unsigned int nextOffset;
} betaConnector;

typedef struct action {
    unsigned int index;
    unsigned int joinsOffset;
    unsigned short joinsLength;
} action;

typedef struct node {
    unsigned int nameOffset;
    unsigned char type;
    union { 
        alpha a; 
        betaConnector b; 
        action c; 
    } value;
} node;

typedef struct ruleset {
    unsigned int nameOffset;
    node *nodePool;
    unsigned int nodeOffset;
    unsigned int *nextPool;
    unsigned int nextOffset;
    char *stringPool;
    unsigned int stringPoolLength; 
    expression *expressionPool;
    unsigned int expressionOffset;
    idiom *idiomPool;
    unsigned int idiomOffset;
    join *joinPool;
    unsigned int joinOffset;
    unsigned int actionCount;
    void *bindingsList;
    unsigned int *stateBuckets;
    unsigned int stateBucketsLength;
    stateEntry *state; 
    unsigned int maxStateLength;
    unsigned int stateLength;
    unsigned int lruStateOffset;
    unsigned int mruStateOffset;
    unsigned int orNodeOffset;
    unsigned int andNodeOffset;
    unsigned int endNodeOffset;
} ruleset;


