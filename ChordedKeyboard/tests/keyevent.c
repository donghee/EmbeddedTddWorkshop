#include "keyevent.h"

int keydown_event_count=0;
int keydown_event_counts[]={0,0,0,0,0};
int keydown_event=0;
int _key_state=0;
int _key_states[]={0,0,0,0,0};
int _channel=0;

void keydown_event_callback() {
	keydown_event_counts[_channel]++;
	keydown_event_count = keydown_event_counts[_channel];
	keydown_event=PRESSED;
}

void keydown_event_release_callback() {
	keydown_event=RELEASED;
}

//keydown_event_cb=(void *(void))keydown_event_callback;
void (*keydown_event_cb)(void) = keydown_event_callback;

void set_key(int channel, int state) {
	_channel=channel;
	set_key_state(state);
}

void set_key_state(int state) {
	_key_state=_key_states[_channel];

	if (_key_state==0 && state==1) {
		keydown_event_cb();
	}

	if (_key_state==1 && state==0) {
		keydown_event_release_callback();
	}

	_key_states[_channel]=state;
}

