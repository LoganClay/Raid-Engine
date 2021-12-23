#pragma once
#include <iostream>
#include "KeyboardOut.h"

class GameEngine;

class Control{
public:
	virtual bool trigger(KeyboardIn mouse, KeyboardOut keys) = 0;

	virtual void event(GameEngine* g) = 0;
};
class Node {
public:
	Control *control;
	Node* next;


	Node(Control* c) {
		this -> control = c;
		this -> next = NULL;
	}
	void setNext(Node *n) { this -> next = n; }
};
class Controls {
public:	
	
	int controlsSize;

	Node* first;
	Node* last;

	Controls() {
		controlsSize = 0;
		first = NULL;
		last = NULL;
	}

	Node* addControl(Control* c) {
		if (controlsSize == 0) {
			first = new Node(c);
			last = first;
			controlsSize++;
			return first;
		}
		else {
			Node* new_node = new Node(c);
			last->setNext(new_node);
			last = new_node;
			controlsSize++;
			return last;
		}
	}
	void removeControl(Node* node) {
		if (controlsSize == 0) return;
		Node* temp = first;
		Node* temp2 = last;
		Node* temp3;
		for (int i = 0; i < controlsSize; i++) {
			if (temp == node && i == 0) {
				temp2 = temp->next;
				delete temp;
				first = temp2;
				break;
			}
			else if (temp == node && i == controlsSize) {
				delete temp;
				last = temp2;
				break;
			}
			else if (temp == node) {
				temp3 = temp->next;
				temp2->setNext(temp3);
				delete temp;
				break;
			}
			temp2 = temp;
			temp = temp->next;
		}
		controlsSize--;
	}
	void truncateControls(Node* node) {
		Node* temp = first;
		Node* temp2 = last;
		int sizeTemp = controlsSize;
		bool trunc = false;
		for (int i = 0; i < sizeTemp; i++) {
			if (trunc) {
				temp2 = temp->next;
				delete temp;
				temp = temp2;
				controlsSize--;
			}
			else {
				temp2 = temp;
				temp = temp->next;
			}
			if (trunc == false && temp == node) {
				trunc = true;
				temp2->setNext(NULL);
				last = temp2;
			}
		}
	}
	void clearControls() {
		Node* temp = first;
		Node* temp2 = last;
		for (int i = 0; i < controlsSize; i++) {
			temp2 = temp->next;
			delete temp;
			temp = temp2;
		}
		first = NULL;
		last = NULL;
		controlsSize = 0;
	}
	Node* getIndex(int i) {
		if (i > controlsSize || i < 0)return first;
		Node* node = first;
		for (int x = 0; x < i; x++) {
			node = node->next;
		}
		return node;
	}
};
