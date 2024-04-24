//- ------------------------------------------------------------------
//-    Copyright (c) James W. Grenning -- All Rights Reserved         
//-    For use by owners of Test-Driven Development for Embedded C,   
//-    and attendees of Renaissance Software Consulting, Co. training 
//-    classes.                                                       
//-                                                                   
//-    Available at http://pragprog.com/titles/jgade/                 
//-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3               
//-                                                                   
//-    Authorized users may use this source code in your own          
//-    projects, however the source code may not be used to           
//-    create training material, courses, books, articles, and        
//-    the like. We make no guarantees that this source code is       
//-    fit for any purpose.                                           
//-                                                                   
//-    www.renaissancesoftware.net james@renaissancesoftware.net      
//- ------------------------------------------------------------------

extern "C" {
    #include "LedDriver.h"
}

#include "CppUTest/TestHarness.h"

static uint16_t virtualLeds;

TEST_GROUP(LedDriver) {
    void setup() {
        LedDriver_Create(&virtualLeds);
    }

    void teardown() {
        // empty
    }
};

TEST(LedDriver, LedsOffAfterCreate) {
    uint16_t virtualLeds = 0xffff;
    LedDriver_Create(&virtualLeds);
    CHECK_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne) {
    LedDriver_TurnOn(1);
    CHECK_EQUAL(1, virtualLeds);
}

TEST(LedDriver, TurnOffLedOne) {
    LedDriver_TurnOn(1);
    LedDriver_TurnOff(1);
    CHECK_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds) {
    LedDriver_TurnOn(9);
    LedDriver_TurnOn(8);
    CHECK_EQUAL(0x180, virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed) {
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(8);
    CHECK_EQUAL(0xff7f, virtualLeds);
}

TEST(LedDriver, AllOn) {
    LedDriver_TurnAllOn();
    CHECK_EQUAL(0xffff, virtualLeds);
}

TEST(LedDriver, LedMemoryIsNotReadable) {
    virtualLeds = 0xffff;
    LedDriver_TurnOn(8);
    CHECK_EQUAL(0x80, virtualLeds);
}

TEST(LedDriver, UpperAndLowerBounds) {
    LedDriver_TurnOn(1);
    LedDriver_TurnOn(16);
    CHECK_EQUAL(0x8001, virtualLeds);
}

TEST(LedDriver, OutOfBoundsChangesNothing) {
    LedDriver_TurnOn(-1);
    CHECK_EQUAL(0, virtualLeds);
    LedDriver_TurnOn(0);
    CHECK_EQUAL(0, virtualLeds);
    LedDriver_TurnOn(17);
    CHECK_EQUAL(0, virtualLeds);
    LedDriver_TurnOn(3141);
    CHECK_EQUAL(0, virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm) {
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(-1);
    CHECK_EQUAL(0xffff, virtualLeds);
    LedDriver_TurnOff(0);
    CHECK_EQUAL(0xffff, virtualLeds);
    LedDriver_TurnOff(17);
    CHECK_EQUAL(0xffff, virtualLeds);
    LedDriver_TurnOff(3141);
    CHECK_EQUAL(0xffff, virtualLeds);
}

TEST(LedDriver, IsOn) {
    CHECK_FALSE(LedDriver_IsOn(11));
    LedDriver_TurnOn(11);
    CHECK(LedDriver_IsOn(11));
}

TEST(LedDriver, OutOfBoundsLedsAreAlwaysOff) {
    CHECK(LedDriver_IsOff(0));
    CHECK(LedDriver_IsOff(17));
    CHECK_FALSE(LedDriver_IsOn(0));
    CHECK_FALSE(LedDriver_IsOn(17));
}

TEST(LedDriver, IsOff) {
    CHECK(LedDriver_IsOff(12));
    LedDriver_TurnOn(12);
    CHECK_FALSE(LedDriver_IsOff(12));
}

TEST(LedDriver, TurnOffMultipleLeds) {
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(9);
    LedDriver_TurnOff(8);
    CHECK_EQUAL((~0x180)&0xffff, virtualLeds);
}

TEST(LedDriver, AllOff) {
    LedDriver_TurnAllOn();
    LedDriver_TurnAllOff();
    CHECK_EQUAL(0, virtualLeds);
}
