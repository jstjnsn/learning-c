struct Counter;

struct Counter *newCounter(void);

void increment(struct Counter *);

int value(struct Counter *);