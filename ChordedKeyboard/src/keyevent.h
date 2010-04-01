#define ON 1
#define OFF 0

#define PRESSED 1
#define RELEASED 2

extern int keydown_event_count;
extern int keydown_event_counts[];
extern void * keydown_event_cb;
extern int keydown_event;

void set_key_state(int state);
void set_key(int channel);
