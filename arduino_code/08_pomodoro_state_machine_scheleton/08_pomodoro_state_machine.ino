// ---------------
// -- Libraries --
// ---------------

// ---------------
// -- Variables --
// ---------------
// State Machine Variables
const int stateIdle = 0;
const int stateWork = 1;
const int stateBefore_break = 2;
const int stateAlarm = 3;
const int stateSnooze = 4;
const int stateShort_break = 5;
const int stateLong_break = 6;
int currentState = stateIdle;

// Timer variables
unsigned long timerDuration;
unsigned long timePoint;

int preAlarmLevel = 0;
int alarmlevel = 0;

// ------------------
// -- Setup & Loop --
// ------------------

void setup() {
  // Add setup code here
}

void loop() {
  updateStateMachine();
}

// ----------------
// -- Conditions --
// ----------------

boolean buttonPress() {
  return false; // TODO: Return whether condition is true
}

boolean timerExpired() {
  return false; // TODO: Return whether condition is true
}

boolean maxLevel() {
        if (preAlarmLevel > 4) {
                return true;
        }
        else {
                return false;
        }
}

boolean alarmActive() {
  return false; // TODO: Return whether condition is true
}

boolean checkBreak() {
  return false; // TODO: Return whether condition is true
}

boolean timerExpired() {
        if (millis() - timePoint > timerDuration) {
                return true;
        }
        else
                return false;
        }
}

// -------------
// -- Actions --
// -------------

void startTimer(int msec) {
        timerDuration = msec;
        timePoint = millis();
}

void showPreAlarm() {
        preAlarmLevel = preAlarmLevel + 1;
        // Activate actuator according to current preAlarmLevel
}

void activateAlarm() {
        preAlarmLevel = 0;
        alarmLevel = alarmLevel + 1;
        // Activate actuator according to current alarm level
}

void updateAlarm() {
        // Keep actuator activated to current alarm level
}

// -------------
// -- Utility --
// -------------

// --------------------
// -- State Machines --
// --------------------

void updateStateMachine() {
  switch (currentState) {
    case stateIdle:
      if (buttonPress()) {
        startTimer(1200000);
        currentState = stateWork;
        break;
      }
      break;

    case stateWork:
      if (timerExpired()) {
        showPreAlarm();
        startTimer(60000);
        currentState = stateBefore_break;
        break;
      }
      if (buttonPress()) {
        currentState = stateIdle;
        break;
      }
      break;

    case stateBefore_break:
      if (maxLevel()) {
        activateAlarm();
        currentState = stateAlarm;
        break;
      }
      if (timerExpired()) {
        showPreAlarm();
        startTimer(60000);
      }
      if (buttonPress()) {
        currentState = stateIdle;
        break;
      }
      break;

    case stateAlarm:
      if (alarmActive()) {
        updateAlarm();
      }
      if (buttonPress()) {
        startTimer();
        currentState = stateSnooze;
        break;
      }
      if (checkBreak()) {
        startTimer(300000);
        alarmLevel = 0;
        currentState = stateShort_break;
        break;
      }
      if (checkBreak()) {
        startTimer(900000);
        alarmLevel = 0;
        currentState = stateLong_break;
        break;
      }
      break;

    case stateSnooze:
      if (timerExpired()) {
        activateAlarm();
        currentState = stateAlarm;
        break;
      }
      break;

    case stateShort_break:
      if (timerExpired()) {
        currentState = stateIdle;
        break;
      }
      break;

    case stateLong_break:
      if (timerExpired()) {
        currentState = stateIdle;
        break;
      }
      break;
  }
}
