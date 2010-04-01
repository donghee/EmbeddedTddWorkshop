#include "CppUTest/CommandLineTestRunner.h"

extern "C"
{
#include <stdio.h>
#include "keyevent.h"
}

/*
execute unit tests
cd ../ && mingw32-make.exe
*/

TEST_GROUP(KeydownEvent)
{
	void setup()
	{
		keydown_event_count=0;

		for(int i=0; i <5; i++) {
			keydown_event_counts[i]=0;
		}
	}
	void teardown()
	{
		
	}
};

TEST(KeydownEvent, test_keydown_event_count)
{
	//key_state=off
	set_key(0, OFF);
	//no event
	LONGS_EQUAL(0, keydown_event_count);

	//key_state=on
	set_key_state(ON);

	//assert keydown event count = 1
	LONGS_EQUAL(1, keydown_event_count);

	set_key_state(OFF);set_key_state(ON);
	//assert keydown event count = 2
	LONGS_EQUAL(2, keydown_event_count);
}

TEST(KeydownEvent, test_keydown_event)
{
	//key_state=off
	set_key_state(OFF);
	//key_state=on
	set_key_state(ON);
	//assert keydown event = pressed 
	LONGS_EQUAL(PRESSED, keydown_event);
	//key_state=off
	set_key_state(OFF);
	//assert keydown event = !pressed 
	LONGS_EQUAL(RELEASED, keydown_event);
}
