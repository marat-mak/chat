#pragma once

#include <stdlib.h>
#include <vector>
#include "user.h"
#include "message.h"
#include <stdio.h>
#include <cstdlib>

#if defined(__linux__)
#include "mygetch.h"
#else
#include <conio.h>
#endif



void reg();

bool signUp();

void userMenu();

void readMessage();

void writeMessage();

void showUsers();

void loadUsers();

void loadMessages();
