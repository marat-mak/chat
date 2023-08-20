#pragma once

#include <stdlib.h>
#include <vector>
#include "user.h"
#include "message.h"
#include <stdio.h>
#include <cstdlib>

#if defined(__linux__)
#include "mygetch.h"
#define ENTER 10
#else
#include <conio.h>
#define ENTER 13
#endif


class CSocket;
void reg(CSocket* pClient);

bool signUp(CSocket* pClient);

void userMenu();

void readMessage();

void writeMessage();

void showUsers();

void loadUsers();

void loadMessages();
